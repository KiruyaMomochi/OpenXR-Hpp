//## Copyright (c) 2017-2020 The Khronos Group Inc.
//## Copyright (c) 2019-2020 Collabora, Ltd.
//##
//## Licensed under the Apache License, Version 2.0 (the "License");
//## you may not use this file except in compliance with the License.
//## You may obtain a copy of the License at
//##
//##     http://www.apache.org/licenses/LICENSE-2.0
//##
//## Unless required by applicable law or agreed to in writing, software
//## distributed under the License is distributed on an "AS IS" BASIS,
//## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//## See the License for the specific language governing permissions and
//## limitations under the License.
//##
//## ---- Exceptions to the Apache 2.0 License: ----
//##
//## As an exception, if you use this Software to generate code and portions of
//## this Software are embedded into the generated code as a result, you may
//## redistribute such product without providing attribution as would otherwise
//## be required by Sections 4(a), 4(b) and 4(d) of the License.
//##
//## In addition, if you combine or link code generated by this Software with
//## software that is licensed under the GPLv2 or the LGPL v2.0 or 2.1
//## ("`Combined Software`") and if a court of competent jurisdiction determines
//## that the patent provision (Section 3), the indemnity provision (Section 9)
//## or other Section of the License conflicts with the conditions of the
//## applicable GPL or LGPL license, you may retroactively and prospectively
//## choose to deem waived or otherwise exclude such Section(s) of the License,
//## but only in their entirety and only with respect to the Combined Software.


//# include('file_header.hpp')
/*!
 * @file
 * @brief Inline implementations - include @ref openxr_method_impls.hpp instead!
 *
 * Contains inline implementations of simple method wrappers.
 */

#ifdef OPENXR_HPP_DOXYGEN
//# include('define_namespace.hpp')
#include "openxr_handles.hpp"
#endif

#ifndef OPENXR_HANDLES_HPP_
#error "This is not meant to be included on its own."
#endif

namespace OPENXR_HPP_NAMESPACE {

//# for cur_cmd in sorted_cmds
//## /*{ cur_cmd }*/

/*{ protect_begin(cur_cmd) }*/
/*{ discouraged_begin(cur_cmd) }*/

//#     set method = basic_cmds[cur_cmd.name]
//#     set enhanced = enhanced_cmds[cur_cmd.name]

//## Should we hide the result-returning function in enhanced mode?
//#     set hide_simple = enhanced.masks_simple

//# if hide_simple
#ifdef OPENXR_HPP_DISABLE_ENHANCED_MODE
//# endif

//#     include('method_impl_simple.hpp')

//# if hide_simple
#endif  // OPENXR_HPP_DISABLE_ENHANCED_MODE
//# endif

/*{ discouraged_end(cur_cmd) }*/
/*{ protect_end(cur_cmd) }*/
//# endfor


}  // namespace OPENXR_HPP_NAMESPACE

//# include('file_footer.hpp')
