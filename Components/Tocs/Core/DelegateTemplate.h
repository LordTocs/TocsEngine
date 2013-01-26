/*
	(c) Sergey Ryazanov (http://home.onego.ru/~ryazanov)

	Template file. May be included many times with different predefined macros.
*/
#if TOCS_DELEGATE_PARAM_COUNT > 0
#define TOCS_DELEGATE_SEPARATOR ,
#else
#define TOCS_DELEGATE_SEPARATOR
#endif

// see BOOST_JOIN for explanation
#define TOCS_DELEGATE_JOIN_MACRO( X, Y) TOCS_DELEGATE_DO_JOIN( X, Y )
#define TOCS_DELEGATE_DO_JOIN( X, Y ) TOCS_DELEGATE_DO_JOIN2(X,Y)
#define TOCS_DELEGATE_DO_JOIN2( X, Y ) X##Y

namespace Tocs {

#ifdef TOCS_DELEGATE_PREFERRED_SYNTAX
#define TOCS_DELEGATE_CLASS_NAME Delegate
#define TOCS_DELEGATE_INVOKER_CLASS_NAME DelegateInvoker
#else
#define TOCS_DELEGATE_CLASS_NAME TOCS_DELEGATE_JOIN_MACRO(Delegate,TOCS_DELEGATE_PARAM_COUNT)
#define TOCS_DELEGATE_INVOKER_CLASS_NAME TOCS_DELEGATE_JOIN_MACRO(DelegateInvoker,TOCS_DELEGATE_PARAM_COUNT)
	template <typename R TOCS_DELEGATE_SEPARATOR TOCS_DELEGATE_TEMPLATE_PARAMS>
	class TOCS_DELEGATE_INVOKER_CLASS_NAME;
#endif

	template <typename R TOCS_DELEGATE_SEPARATOR TOCS_DELEGATE_TEMPLATE_PARAMS>
#ifdef TOCS_DELEGATE_PREFERRED_SYNTAX
	class TOCS_DELEGATE_CLASS_NAME<R (TOCS_DELEGATE_TEMPLATE_ARGS)>
#else
	class TOCS_DELEGATE_CLASS_NAME
#endif
	{
	public:
		typedef R return_type;
#ifdef TOCS_DELEGATE_PREFERRED_SYNTAX
		typedef return_type (TOCS_DELEGATE_CALLTYPE *signature_type)(TOCS_DELEGATE_TEMPLATE_ARGS);
#else
#endif

		TOCS_DELEGATE_CLASS_NAME()
			: object_ptr(0)
			, stub_ptr(0)
		{}

		template <return_type (*TMethod)(TOCS_DELEGATE_TEMPLATE_ARGS)>
		static TOCS_DELEGATE_CLASS_NAME FromFunction()
		{
			return from_stub(0, &function_stub<TMethod>);
		}

		template <class T, return_type (T::*TMethod)(TOCS_DELEGATE_TEMPLATE_ARGS)>
		static TOCS_DELEGATE_CLASS_NAME FromMethod(T* object_ptr)
		{
			return from_stub(object_ptr, &method_stub<T, TMethod>);
		}

		template <class T, return_type (T::*TMethod)(TOCS_DELEGATE_TEMPLATE_ARGS) const>
		static TOCS_DELEGATE_CLASS_NAME FromConstMethod(T const* object_ptr)
		{
			return from_stub(const_cast<T*>(object_ptr), &const_method_stub<T, TMethod>);
		}

		return_type operator()(TOCS_DELEGATE_PARAMS) const
		{
			if (stub_ptr)
				return (*stub_ptr)(object_ptr TOCS_DELEGATE_SEPARATOR TOCS_DELEGATE_ARGS);
		}

		operator bool () const
		{
			return stub_ptr != 0;
		}

		bool operator!() const
		{
			return !(operator bool());
		}

	private:
		
		typedef return_type (TOCS_DELEGATE_CALLTYPE *stub_type)(void* object_ptr TOCS_DELEGATE_SEPARATOR TOCS_DELEGATE_PARAMS);

		void* object_ptr;
		stub_type stub_ptr;

		static TOCS_DELEGATE_CLASS_NAME from_stub(void* object_ptr, stub_type stub_ptr)
		{
			TOCS_DELEGATE_CLASS_NAME d;
			d.object_ptr = object_ptr;
			d.stub_ptr = stub_ptr;
			return d;
		}

		template <return_type (*TMethod)(TOCS_DELEGATE_TEMPLATE_ARGS)>
		static return_type TOCS_DELEGATE_CALLTYPE function_stub(void* TOCS_DELEGATE_SEPARATOR TOCS_DELEGATE_PARAMS)
		{
			return (TMethod)(TOCS_DELEGATE_ARGS);
		}

		template <class T, return_type (T::*TMethod)(TOCS_DELEGATE_TEMPLATE_ARGS)>
		static return_type TOCS_DELEGATE_CALLTYPE method_stub(void* object_ptr TOCS_DELEGATE_SEPARATOR TOCS_DELEGATE_PARAMS)
		{
			T* p = static_cast<T*>(object_ptr);
			return (p->*TMethod)(TOCS_DELEGATE_ARGS);
		}

		template <class T, return_type (T::*TMethod)(TOCS_DELEGATE_TEMPLATE_ARGS) const>
		static return_type TOCS_DELEGATE_CALLTYPE const_method_stub(void* object_ptr TOCS_DELEGATE_SEPARATOR TOCS_DELEGATE_PARAMS)
		{
			T const* p = static_cast<T*>(object_ptr);
			return (p->*TMethod)(TOCS_DELEGATE_ARGS);
		}
	};
}

#undef TOCS_DELEGATE_CLASS_NAME
#undef TOCS_DELEGATE_SEPARATOR
#undef TOCS_DELEGATE_JOIN_MACRO
#undef TOCS_DELEGATE_DO_JOIN
#undef TOCS_DELEGATE_DO_JOIN2
