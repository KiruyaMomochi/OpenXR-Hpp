//## Copyright (c) 2017-2019 The Khronos Group Inc.
//## Copyright (c) 2019 Collabora, Ltd.
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

//# from 'method_decl_macros.hpp' import method_prototypes with context
//# from 'macros.hpp' import make_spec_ref

//# set type = shortname
//# set raw_type = handle.name
//# set input_param_type = type + " const&"
//# set invalid = "XR_NULL_HANDLE"
//# set comparison_operators = ('<', '>', '<=', '>=', '==', '!=')
//# set doc_group = "handles"

//# extends "valuewrapperclass.hpp"

/*% block comment_brief %*/Handle class - wrapping /*{raw_type}*/ without indicating ownership./*% endblock comment_brief %*/

//# block member_types
using Type = /*{ type }*/;
using RawHandleType = /*{raw_type}*/;
//# endblock member_types

//# block constructor_default
//! Default (empty/null) constructor
OPENXR_HPP_CONSTEXPR /*{ type }*/ () noexcept : val_(XR_NULL_HANDLE) {}
//# endblock constructor_default

//# block constructor_explicit
//#     filter block_doxygen_comment
//! @brief Conversion constructor from the raw /*{raw_type}*/ type
//!
//! Explicit on 32-bit platforms by default unless `OPENXR_HPP_TYPESAFE_CONVERSION` is defined.
//#     endfilter
OPENXR_HPP_TYPESAFE_EXPLICIT /*{ type }*/ (RawHandleType handle) noexcept : val_(handle) {}
//# endblock constructor_explicit

//# block extra_constructors_conversion_assign
//! Constructor from nullptr - creates empty/null handle.
OPENXR_HPP_CONSTEXPR /*{ type }*/ (std::nullptr_t /* unused */) noexcept : val_(XR_NULL_HANDLE) {}

#if defined(OPENXR_HPP_TYPESAFE_CONVERSION)
//#     filter block_doxygen_comment
//! @brief Assignment operator from the raw /*{raw_type}*/
//!
//! Does *not* destroy any contained non-null handle first! For that, see @ref UniqueHandle.
//!
//! Only provided if `OPENXR_HPP_TYPESAFE_CONVERSION` is defined (64-bit platforms by default).
//#     endfilter
Type &operator=(RawHandleType handle) noexcept {
    val_ = handle;
    return *this;
}
#endif

//#     filter block_doxygen_comment
//! @brief Assignment operator from nullptr - assigns to empty/null handle.
//!
//! Does *not* destroy any contained non-null handle first! For that, see @ref UniqueHandle.
//#     endfilter
Type &operator=(std::nullptr_t /* unused */) noexcept {
    val_ = XR_NULL_HANDLE;
    return *this;
}

//#     filter block_doxygen_comment
//! @brief Conversion operator to the raw /*{raw_type}*/ type
//!
//! Explicit on 32-bit platforms by default unless `OPENXR_HPP_TYPESAFE_CONVERSION` is defined.
//#     endfilter
OPENXR_HPP_CONSTEXPR OPENXR_HPP_TYPESAFE_EXPLICIT operator RawHandleType() const noexcept { return val_; }
//# endblock extra_constructors_conversion_assign

//# block method_put
//#     filter block_doxygen_comment
//! @brief "Put" function for assigning as null (by default) then getting the address of the raw pointer to pass to creation functions.
//!
//! e.g.
//! ```
//! /*{type}*/ yourHandle;
//! auto result = d.xrCreate/*{- type -}*/(..., yourHandle.put()));
//! ```
//!
//! @see xr::put(/*{type}*/&, bool)
//#     endfilter
RawHandleType *put(bool clear = true) noexcept {
    if (clear) val_ = XR_NULL_HANDLE;
    return &val_;
}
//# endblock

//# block extra_methods
/*!
 * @name OpenXR API calls as member functions
 * @{
 */
//## Generate "member function" prototypes
//# for cur_cmd in sorted_cmds if cur_cmd.params[0].type == raw_type
/*{ method_prototypes(cur_cmd, handle) }*/

//# endfor

//! @}
//# endblock extra_methods

//# block extra_free_functions
//#     filter block_doxygen_comment
//! @brief Equality comparison between /*{type}*/ and nullptr: true if the handle is null.
//! @relates /*{type}*/
//#     endfilter
OPENXR_HPP_CONSTEXPR OPENXR_HPP_INLINE bool operator==(/*{type}*/ const &lhs, std::nullptr_t /* unused */) noexcept {
    return lhs.get() == XR_NULL_HANDLE;
}
//#     filter block_doxygen_comment
//! @brief Equality comparison between nullptr and /*{type}*/: true if the handle is null.
//! @relates /*{type}*/
//#     endfilter
OPENXR_HPP_CONSTEXPR OPENXR_HPP_INLINE bool operator==(std::nullptr_t /* unused */, /*{type}*/ const &rhs) noexcept {
    return rhs.get() == XR_NULL_HANDLE;
}
//#     filter block_doxygen_comment
//! @brief Inequality comparison between /*{type}*/ and nullptr: true if the handle is not null.
//! @relates /*{type}*/
//#     endfilter
OPENXR_HPP_CONSTEXPR OPENXR_HPP_INLINE bool operator!=(/*{type}*/ const &lhs, std::nullptr_t /* unused */) noexcept {
    return lhs.get() != XR_NULL_HANDLE;
}
//#     filter block_doxygen_comment
//! @brief Inequality comparison between nullptr and /*{type}*/: true if the handle is not null.
//! @relates /*{type}*/
//#     endfilter
OPENXR_HPP_CONSTEXPR OPENXR_HPP_INLINE bool operator!=(std::nullptr_t /* unused */, /*{type}*/ const &rhs) noexcept {
    return rhs.get() != XR_NULL_HANDLE;
}
//# endblock extra_free_functions

//# block free_put
//#     filter block_doxygen_comment
//! @brief Free "put" function for clearing (by default) and getting the address of the raw /*{raw_type}*/ handle in a /*{type}*/ (by
//! reference).
//!
//! e.g.
//! ```
//! /*{type}*/ yourHandle;
//! auto result = d.xrCreate/*{- type -}*/(..., put(yourHandle));
//! ```
//!
//! @ingroup utility_accessors
//! @relates /*{type}*/
//#     endfilter
static OPENXR_HPP_INLINE /*{ raw_type }*/ *put(/*{type}*/ &h, bool clear = true) noexcept { return h.put(clear); }

//#     filter block_doxygen_comment
//! @brief Free "put" function for clearing (by default) and getting the address of the raw /*{raw_type}*/ handle in a /*{type}*/ (by
//! pointer).
//!
//! e.g.
//! ```
//! void yourFunction(/*{type}*/* yourHandle) {
//!     auto result = d.xrCreate/*{- type -}*/(..., put(yourHandle));
//!     ....
//! }
//! ```
//!
//! @relates /*{type}*/
//! @ingroup utility_accessors
//#     endfilter
static OPENXR_HPP_INLINE /*{raw_type}*/ *put(/*{type}*/ *h, bool clear = true) noexcept {
    OPENXR_HPP_ASSERT(h != nullptr);
    return h->put(clear);
}
//# endblock free_put
