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

//# from 'template_macros.hpp' import wrapperSizeStaticAssert

namespace OPENXR_HPP_NAMESPACE {

namespace impl {

    class XR_MAY_ALIAS InputStructBase {
    protected:
        InputStructBase(StructureType type_,
                        const void* next_ = nullptr)
            : type(type_), next(next_) {}

    public:
        StructureType type;
        const void* next;
    };
    /*{ wrapperSizeStaticAssert('::XrBaseInStructure', 'InputStructBase') }*/

    class XR_MAY_ALIAS OutputStructBase {
    protected:
        OutputStructBase(StructureType type_, void* next_ = nullptr)
            : type(type_), next(next_) {}

    public:
        StructureType type;
        void* next;
    };
    /*{ wrapperSizeStaticAssert('::XrBaseOutStructure', 'OutputStructBase') }*/
}  // namespace impl

struct XR_MAY_ALIAS EventDataBuffer : public impl::InputStructBase {
private:
    using Parent = impl::InputStructBase;

protected:
    EventDataBuffer(StructureType type_, const void* next_ = nullptr)
        : Parent(type_, next_), varying{} {}

public:
    EventDataBuffer() : Parent(StructureType::EventDataBuffer), varying{} {
        (void)varying;
    }
    XrEventDataBuffer* put() noexcept {
            *this = {};
            return reinterpret_cast<XrEventDataBuffer*>(this);
    }
    XrEventDataBuffer* get() noexcept {
            return reinterpret_cast<XrEventDataBuffer*>(this);
    }
    XrEventDataBuffer const* get() const noexcept {
            return reinterpret_cast<XrEventDataBuffer const*>(this);
    }

private:
    uint8_t varying[4000];
};
/*{ wrapperSizeStaticAssert('::XrEventDataBuffer', 'EventDataBuffer') }*/

OPENXR_HPP_INLINE XrEventDataBuffer* put(EventDataBuffer& v) noexcept {
    return v.put();
}

//# macro _makeReturnOnlyConstructor(s)
        //! Empty constructor for a type that is marked as "returnonly"
        explicit /*{s.cpp_name }*/ (

            /*{s.next_param_decl_with_default if s.typed_struct}*/)
//#     if s.typed_struct
            : Parent(/*{s.struct_type_enum}*/, /*{s.next_param_name}*/)
//#     endif
            {}
//# endmacro

//# macro _makeFullInitializingConstructor(struct, s)

//#     if s.is_abstract
    protected:
        //! Protected constructor: this type is abstract.
//#     else
        //! Constructor initializing all members.
//#     endif
        /*{ s.cpp_name }*/ (
//#     set visible_members = struct.members | reject('cpp_hidden_member') | list
//#     set first_defaultable_index0 = index0_of_first_visible_defaultable_member(visible_members)
//#     set arg_comma = joiner(", ")
                  /*%- if s.is_abstract %*/ /*{ arg_comma() }*/ StructureType type_ /*% endif -%*/
//#     for member in visible_members
                  /*{- arg_comma() }*/ /*{ project_cppdecl(struct, member, defaulted=(loop.index0 >= first_defaultable_index0), suffix="_", input=True) -}*/
//#     endfor
//#     if s.typed_struct
                  /*{- arg_comma() }*/ /*{ s.next_param_decl_with_default -}*/
//#     endif
                  ) :
//#     set initializer_comma = joiner(",")

//#     if s.typed_struct
//#         set arg_comma = joiner(",")
              /*{- initializer_comma() }*/ Parent(
                /*{- arg_comma() -}*/ /*% if s.is_abstract %*/type_ /*% else %*/ /*{- s.struct_type_enum -}*/ /*% endif %*/
//#         for member in visible_members if member.name in s.parent_fields and not is_static_length_string(member)
                /*{- arg_comma() }*/ /*{ member.name + "_" -}*/
//#         endfor
                /*{- arg_comma() }*/ /*{ s.next_param_name -}*/
              )
//#     endif

//#     for member in visible_members if member.name not in s.parent_fields and not is_static_length_string(member)
              /*{- initializer_comma() }*/ /*{ member.name }*/ {/*{ member.name + "_"}*/}
//#     endfor
        {
//#     for member in visible_members if is_static_length_string(member)
            if (nullptr != /*{ member.name + "_" }*/) {
                // FIXME what is the safe way to do this?
                strncpy(/*{ member.name }*/, /*{ member.name + "_" }*/, /*{member.array_count_var}*/);
            }
//#     endfor
        }

//#     if s.is_abstract
    public:
//#     endif
//# endmacro


//# for struct in gen.api_structures if not struct.name.endswith("EventDataBuffer")
//#     set s = project_struct(struct)
    /*{ protect_begin(struct) }*/
    struct XR_MAY_ALIAS /*{ s.cpp_name }*/ /*{ s.struct_parent_decl }*/
    {
//#     if s.typed_struct
    private:
        using Parent = /*{ s.parent_cpp_type }*/;
//#         if not s.is_abstract
    public:
//#         endif
//#     endif

//#     if struct is struct_output and not s.is_abstract
        /*{ _makeReturnOnlyConstructor(s) }*/
//#     else
        /*{ _makeFullInitializingConstructor(struct, s) }*/
//#     endif


//#     if not s.is_abstract
        //! Default copy constructor
        /*{ s.cpp_name }*/(const /*{ s.cpp_name }*/& rhs) = default;
//#     endif


        //! Conversion operator to a reference to const of the original OpenXR type.
        /*{ "operator const " + struct.name }*/ &() const { return *reinterpret_cast<const /*{ struct.name }*/*>(this); }

        //! Conversion operator to a reference to the original OpenXR type.
        /*{ "operator " + struct.name }*/ &() {
            return *reinterpret_cast</*{ struct.name }*/*>(this);
        }

//#     if s.is_derived_type
        //! Accessor for this as a raw, base /*{s.parent_type}*/ const pointer
        /*{s.parent_type}*/ const* get_base() const noexcept {
            return reinterpret_cast</*{s.parent_type}*/ const*>(this);
        }
//#     endif


//#     for member in struct.members if not member is cpp_hidden_member and member.name not in s.parent_fields
        /*{ project_cppdecl(struct, member) }*/;
//#     endfor
    };
    /*{ wrapperSizeStaticAssert(struct.name, s.cpp_name) }*/

//#     filter block_doxygen_comment
    //! @brief Free function accessor for /*{s.cpp_name}*/ const reference as a raw /*{struct.name}*/ pointer to const
    //! @relates /*{s.cpp_name}*/
//#     endfilter
    OPENXR_HPP_INLINE /*{struct.name}*/ const* get(/*{s.cpp_name}*/ const& h) {
        return &(h./*{"operator " + struct.name}*/ const&());
    }

//#     if not s.is_abstract
    //! @brief Free function accessor for passing /*{s.cpp_name}*/ as the address of a raw /*{struct.name}*/
    //! @relates /*{s.cpp_name}*/
    OPENXR_HPP_INLINE /*{ struct.name }*/ * put(/*{s.cpp_name}*/ &h) { return &(h./*{"operator " + struct.name}*/&()); }
//#     endif

//#     if s.is_derived_type
//#         filter block_doxygen_comment
    //! @brief Free function accessor for a reference to const /*{s.cpp_name}*/ as a raw, pointer to const /*{s.parent_type}*/ (the base type)
    //! @relates /*{s.cpp_name}*/
    //! @relates /*{s.parent_cpp_type}*/
//#         endfilter
    OPENXR_HPP_INLINE /*{s.parent_type}*/ const* get_base(/*{s.cpp_name}*/ const& h) {
        return h.get_base();
    }
//#     endif

    /*{ protect_end(struct) }*/

//# endfor

}  // namespace OPENXR_HPP_NAMESPACE
