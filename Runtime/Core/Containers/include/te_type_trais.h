
namespace TE
{
#define TE_TEMPLATE_NULL template<>

#ifndef TE_TYPE_TRAITS
#define TE_TYPE_TRAITS
	struct __true_type {
	};

	struct __false_type{
	};

	template <typename _Tp>
	struct __type_traits {
		typedef __true_type this_dummy_member_must_be_first;
		typedef __false_type has_trivial_default_constructor;
		typedef __false_type has_trivial_copy_constructor;
		typedef __false_type has_trivial_assignment_operator;
		typedef __false_type has_trivial_destructor;
		typedef __false_type is_POD_type;
	};

	template<>
	struct __type_traits<bool> {
		typedef __true_type has_trivial_default_constructor;
		typedef __true_type has_trivial_copy_constructor;
		typedef __true_type has_trivial_assignment_operator;
		typedef __true_type has_trivial_destructor;
		typedef __true_type is_POD_type;
	};

	template<>
	struct __type_traits<char> {
		typedef __true_type has_trivial_default_constructor;
		typedef __true_type has_trivial_copy_constructor;
		typedef __true_type has_trivial_assignment_operator;
		typedef __true_type has_trivial_destructor;
		typedef __true_type is_POD_type;
	};
	template<>
	struct __type_traits<signed char> {
		typedef __true_type has_trivial_default_constructor;
		typedef __true_type has_trivial_copy_constructor;
		typedef __true_type has_trivial_assignment_operator;
		typedef __true_type has_trivial_destructor;
		typedef __true_type is_POD_type;
	};
	template<>
	struct __type_traits<unsigned char> {
		typedef __true_type has_trivial_default_constructor;
		typedef __true_type has_trivial_copy_constructor;
		typedef __true_type has_trivial_assignment_operator;
		typedef __true_type has_trivial_destructor;
		typedef __true_type is_POD_type;
	};

	template<>
	struct __type_traits<wchar_t> {
		typedef __true_type has_trivial_default_constructor;
		typedef __true_type has_trivial_copy_constructor;
		typedef __true_type has_trivial_assignment_operator;
		typedef __true_type has_trivial_destructor;
		typedef __true_type is_POD_type;
	};

	template<>
	 struct __type_traits<short> {
		typedef __true_type    has_trivial_default_constructor;
		typedef __true_type    has_trivial_copy_constructor;
		typedef __true_type    has_trivial_assignment_operator;
		typedef __true_type    has_trivial_destructor;
		typedef __true_type    is_POD_type;
	};

	TE_TEMPLATE_NULL struct __type_traits<unsigned short> {
		typedef __true_type    has_trivial_default_constructor;
		typedef __true_type    has_trivial_copy_constructor;
		typedef __true_type    has_trivial_assignment_operator;
		typedef __true_type    has_trivial_destructor;
		typedef __true_type    is_POD_type;
	};

	TE_TEMPLATE_NULL struct __type_traits<int> {
		typedef __true_type    has_trivial_default_constructor;
		typedef __true_type    has_trivial_copy_constructor;
		typedef __true_type    has_trivial_assignment_operator;
		typedef __true_type    has_trivial_destructor;
		typedef __true_type    is_POD_type;
	};

	TE_TEMPLATE_NULL struct __type_traits<unsigned int> {
		typedef __true_type    has_trivial_default_constructor;
		typedef __true_type    has_trivial_copy_constructor;
		typedef __true_type    has_trivial_assignment_operator;
		typedef __true_type    has_trivial_destructor;
		typedef __true_type    is_POD_type;
	};

	TE_TEMPLATE_NULL struct __type_traits<long> {
		typedef __true_type    has_trivial_default_constructor;
		typedef __true_type    has_trivial_copy_constructor;
		typedef __true_type    has_trivial_assignment_operator;
		typedef __true_type    has_trivial_destructor;
		typedef __true_type    is_POD_type;
	};

	TE_TEMPLATE_NULL struct __type_traits<unsigned long> {
		typedef __true_type    has_trivial_default_constructor;
		typedef __true_type    has_trivial_copy_constructor;
		typedef __true_type    has_trivial_assignment_operator;
		typedef __true_type    has_trivial_destructor;
		typedef __true_type    is_POD_type;
	};

#ifdef __STL_LONG_LONG

	TE_TEMPLATE_NULL struct __type_traits<long long> {
		typedef __true_type    has_trivial_default_constructor;
		typedef __true_type    has_trivial_copy_constructor;
		typedef __true_type    has_trivial_assignment_operator;
		typedef __true_type    has_trivial_destructor;
		typedef __true_type    is_POD_type;
	};

	TE_TEMPLATE_NULL struct __type_traits<unsigned long long> {
		typedef __true_type    has_trivial_default_constructor;
		typedef __true_type    has_trivial_copy_constructor;
		typedef __true_type    has_trivial_assignment_operator;
		typedef __true_type    has_trivial_destructor;
		typedef __true_type    is_POD_type;
	};

#endif /* __STL_LONG_LONG */

	TE_TEMPLATE_NULL struct __type_traits<float> {
		typedef __true_type    has_trivial_default_constructor;
		typedef __true_type    has_trivial_copy_constructor;
		typedef __true_type    has_trivial_assignment_operator;
		typedef __true_type    has_trivial_destructor;
		typedef __true_type    is_POD_type;
	};

	TE_TEMPLATE_NULL struct __type_traits<double> {
		typedef __true_type    has_trivial_default_constructor;
		typedef __true_type    has_trivial_copy_constructor;
		typedef __true_type    has_trivial_assignment_operator;
		typedef __true_type    has_trivial_destructor;
		typedef __true_type    is_POD_type;
	};

	TE_TEMPLATE_NULL struct __type_traits<long double> {
		typedef __true_type    has_trivial_default_constructor;
		typedef __true_type    has_trivial_copy_constructor;
		typedef __true_type    has_trivial_assignment_operator;
		typedef __true_type    has_trivial_destructor;
		typedef __true_type    is_POD_type;
	};
#ifdef __TE_CLASS_PARTIAL_SPECIALIZATION
	template <class _Tp>
	struct __type_traits<_Tp*> {
		typedef __true_type    has_trivial_default_constructor;
		typedef __true_type    has_trivial_copy_constructor;
		typedef __true_type    has_trivial_assignment_operator;
		typedef __true_type    has_trivial_destructor;
		typedef __true_type    is_POD_type;
	};
#else

	TE_TEMPLATE_NULL struct __type_traits<char*> {
		typedef __true_type    has_trivial_default_constructor;
		typedef __true_type    has_trivial_copy_constructor;
		typedef __true_type    has_trivial_assignment_operator;
		typedef __true_type    has_trivial_destructor;
		typedef __true_type    is_POD_type;
	};

	TE_TEMPLATE_NULL struct __type_traits<signed char*> {
		typedef __true_type    has_trivial_default_constructor;
		typedef __true_type    has_trivial_copy_constructor;
		typedef __true_type    has_trivial_assignment_operator;
		typedef __true_type    has_trivial_destructor;
		typedef __true_type    is_POD_type;
	};

	TE_TEMPLATE_NULL struct __type_traits<unsigned char*> {
		typedef __true_type    has_trivial_default_constructor;
		typedef __true_type    has_trivial_copy_constructor;
		typedef __true_type    has_trivial_assignment_operator;
		typedef __true_type    has_trivial_destructor;
		typedef __true_type    is_POD_type;
	};

	TE_TEMPLATE_NULL struct __type_traits<const char*> {
		typedef __true_type    has_trivial_default_constructor;
		typedef __true_type    has_trivial_copy_constructor;
		typedef __true_type    has_trivial_assignment_operator;
		typedef __true_type    has_trivial_destructor;
		typedef __true_type    is_POD_type;
	};

	TE_TEMPLATE_NULL struct __type_traits<const signed char*> {
		typedef __true_type    has_trivial_default_constructor;
		typedef __true_type    has_trivial_copy_constructor;
		typedef __true_type    has_trivial_assignment_operator;
		typedef __true_type    has_trivial_destructor;
		typedef __true_type    is_POD_type;
	};

	TE_TEMPLATE_NULL struct __type_traits<const unsigned char*> {
		typedef __true_type    has_trivial_default_constructor;
		typedef __true_type    has_trivial_copy_constructor;
		typedef __true_type    has_trivial_assignment_operator;
		typedef __true_type    has_trivial_destructor;
		typedef __true_type    is_POD_type;
	};
#endif

	template<class _Tp>
	struct _Is_integer {
		using _Integral = __false_type;
	};


#ifndef __STL_NO_BOOL

	TE_TEMPLATE_NULL struct _Is_integer<bool> {
		typedef __true_type _Integral;
	};

#endif /* __STL_NO_BOOL */

	TE_TEMPLATE_NULL struct _Is_integer<char> {
		typedef __true_type _Integral;
	};

	TE_TEMPLATE_NULL struct _Is_integer<signed char> {
		typedef __true_type _Integral;
	};

	TE_TEMPLATE_NULL struct _Is_integer<unsigned char> {
		typedef __true_type _Integral;
	};

#ifdef __STL_HAS_WCHAR_T

	TE_TEMPLATE_NULL struct _Is_integer<wchar_t> {
		typedef __true_type _Integral;
	};

#endif /* __STL_HAS_WCHAR_T */

	TE_TEMPLATE_NULL struct _Is_integer<short> {
		typedef __true_type _Integral;
	};

	TE_TEMPLATE_NULL struct _Is_integer<unsigned short> {
		typedef __true_type _Integral;
	};

	TE_TEMPLATE_NULL struct _Is_integer<int> {
		typedef __true_type _Integral;
	};

	TE_TEMPLATE_NULL struct _Is_integer<unsigned int> {
		typedef __true_type _Integral;
	};

	TE_TEMPLATE_NULL struct _Is_integer<long> {
		typedef __true_type _Integral;
	};

	TE_TEMPLATE_NULL struct _Is_integer<unsigned long> {
		typedef __true_type _Integral;
	};

#ifdef __STL_LONG_LONG

	TE_TEMPLATE_NULL struct _Is_integer<long long> {
		typedef __true_type _Integral;
	};

	TE_TEMPLATE_NULL struct _Is_integer<unsigned long long> {
		typedef __true_type _Integral;
	};

#endif

#endif 


}
