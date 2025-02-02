#!/usr/bin/python3 -i
#
# Copyright (c) 2019 The Khronos Group Inc.
# Copyright (c) 2019 Collabora, Ltd.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""Provides functionality to use Jinja2 when generating C/C++ code, while eliminating the need to import Jinja2 from any other file."""

import os
import re
from pathlib import Path

_ADDED_TO_PATH = False

OPENXR = os.getenv("OPENXR_REPO")
if not OPENXR:
    OPENXR = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', 'OpenXR-SDK-Source'))


def _add_to_path():
    global _ADDED_TO_PATH
    if not _ADDED_TO_PATH:
        import sys
        # Find Jinja2 in source tree, as last resort.
        sys.path.append(
            str(
                Path(OPENXR).resolve() / "external" / "python"))
        _ADDED_TO_PATH = True


_WHITESPACE = re.compile(r"[\s\n]+")


class Initializers:
    """Like jinja's joiner, except our first one is : instead of empty."""

    def __init__(self):
        self.comma = False

    def __call__(self) -> str:
        if not self.comma:
            self.comma = True
            return ":"
        return ","


def _undecorate(name):
    """Undecorate a name by removing the leading Xr and making it lowercase."""
    lower = name.lower()
    assert(lower.startswith('xr'))
    return lower[2:]


def _quote_string(s):
    return '"{}"'.format(s)


def _base_name(name):
    return name[2:]


def _collapse_whitespace(s):
    return _WHITESPACE.sub(" ", s)


def _protect_begin(entity, parent=None):
    if not entity: return None
    lines = []
    if hasattr(entity, 'ext_name') and not entity.ext_name.startswith("XR_VERSION"):
        if not parent or not hasattr(parent, 'ext_name') or parent.ext_name != entity.ext_name:
            lines.append("#ifdef {}".format(entity.ext_name))
    if entity.protect_value:
        if not parent or parent.protect_string != entity.protect_string:
            # No need to double-protect if condition the same
            lines.append("#if {}".format(entity.protect_string))
    return "\n".join(lines)


def _protect_end(entity, parent=None):
    if not entity: return None
    lines = []
    if entity.protect_value:
        if not parent or parent.protect_string != entity.protect_string:
            # No need to double-protect if condition the same
            lines.append("#endif // {}".format(entity.protect_string))
    if hasattr(entity, 'ext_name') and not entity.ext_name.startswith("XR_VERSION"):
        if not parent or not hasattr(parent, 'ext_name') or parent.ext_name != entity.ext_name:
            lines.append("#endif  // {}".format(entity.ext_name))
    return "\n".join(lines)


def make_jinja_environment(file_with_templates_as_sibs=None, search_path=None, trim_blocks=True):
    """Create a Jinja2 environment customized to generate C/C++ headers/code for Khronos APIs.

    Delimiters have been changed from Jinja2 defaults to permit better interoperability with
    editors and other tooling expecting C/C++ code, by combining them with comments:

    - Blocks are bracketed like /*% block_contents %*/ instead of {% block_contents %}
    - Variable outputs are bracketed like /*{ var }*/ instead of {{ var }}
    - Line statements start with //# instead of just #
    - Line comments start with //## instead of just ##

    Other details:

    - autoescape is turned off because this isn't HTML.
    - trailing newline kept
    - blocks are trimmed (by default) for easier markup.
    - the loader is a file system loader, building a search path from file_with_templates_as_sibs
      (if your template is a sibling of your source file, just pass file_with_templates_as_sibs=__file__),
      and search_path (an iterable if you want more control)

    Provided filters:

    - quote_string - wrap something in double-quotes
    - undecorate - same as the generator utility function: remove leading two-character API prefix and make lowercase.
    - base_name - just removes leading two-character API prefix
    - collapse_whitespace - minimizes internal whitespace with a regex

    Provided functions used as globals:

    - protect_begin(entity) and protect_end(entity) - use in a pair, and pass an entity
      (function/command, struct, etc), and if it is noted with protect="something" in the XML,
      the appropriate #if and #endif will be printed (for protect_begin and protect_end respectively.)

    You may further add globals and filters to the returned environment.
    """

    _add_to_path()
    from jinja2 import Environment, FileSystemLoader

    search_paths = []
    if file_with_templates_as_sibs:
        search_paths.append(
            str(Path(file_with_templates_as_sibs).resolve().parent))
    if search_path:
        search_paths.extend(search_path)
    env = Environment(keep_trailing_newline=True,
                      trim_blocks=trim_blocks,
                      block_start_string="/*%",
                      block_end_string="%*/",
                      variable_start_string="/*{",
                      variable_end_string="}*/",
                      line_statement_prefix="//#",
                      line_comment_prefix="//##",
                      autoescape=False,
                      loader=FileSystemLoader(search_paths))
    env.filters['quote_string'] = _quote_string
    env.filters['undecorate'] = _undecorate
    env.filters['base_name'] = _base_name
    env.filters['collapse_whitespace'] = _collapse_whitespace
    env.globals['protect_begin'] = _protect_begin
    env.globals['protect_end'] = _protect_end
    env.globals['initializers'] = Initializers

    return env


class JinjaTemplate:
    def __init__(self, env, fn):
        """Load and parse a Jinja2 template given a Jinja2 environment and the template file name.

        Create the environment using make_jinja_environment().

        Syntax errors are caught, have their details printed, then are re-raised (to stop execution).
        """
        _add_to_path()
        from jinja2 import TemplateSyntaxError
        try:
            self.template = env.get_template(fn)
        except TemplateSyntaxError as e:
            print("Jinja2 template syntax error during parse: {}:{} error: {}".
                  format(e.filename, e.lineno, e.message))
            raise e

    def render(self, *args, **kwargs):
        """Render the Jinja2 template with the provided context.

        All arguments are passed through; this just wraps the Jinja2 template render method
        to handle syntax error exceptions so that Jinja2 does not need to be imported anywhere
        but this file.
        """
        _add_to_path()
        from jinja2 import TemplateSyntaxError

        try:
            return self.template.render(*args, **kwargs)
        except TemplateSyntaxError as e:
            error_str = "Jinja2 template syntax error during render: {}:{} error: {}".format(
                e.filename, e.lineno, e.message)
            print(error_str)
            raise RuntimeError(error_str)
