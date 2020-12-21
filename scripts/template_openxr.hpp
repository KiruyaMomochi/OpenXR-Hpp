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

//# include 'file_header.hpp'

//# from 'macros.hpp' import forwardCommandArgs, make_spec_url


/*!
 * @defgroup config Configuration Options
 * @brief Preprocessor macros that may be set to control the behavior of OpenXR-Hpp
 */

/**
 * @def OPENXR_HPP_NAMESPACE
 * @brief Define to the namespace you wish to place OpenXR-Hpp in: defaults to `xr`.
 *
 * @ingroup config
 */

//# include('nongenerated_base.hpp') without context

#include "openxr_atoms.hpp"

namespace OPENXR_HPP_NAMESPACE {
using BilateralPaths = std::array<Path, SIDE_COUNT>;
}  // namespace OPENXR_HPP_NAMESPACE

#include "openxr_time.hpp"
#include "openxr_version.hpp"
#include "openxr_static_dispatch.hpp"
#include "openxr_dynamic_dispatch.hpp"

//## These includes are currently unused
//## //# include('template_openxr_nongenerated_chains.hpp') without context
//## //# include('template_openxr_nongenerated_enhanced.hpp') without context

#include "openxr_handles.hpp"
#include "openxr_structs.hpp"

/*
 * Inline implementations of all trampoline methods and free functions follow.
 * Prototypes may be found above, either in the associated handle class, or immediately following the section of handle classes.
 */
#include "openxr_method_impls.hpp"


//# include 'file_footer.hpp'
