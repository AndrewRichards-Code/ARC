#pragma once 

#include <memory>

template<class T>
using Scope = std::unique_ptr<T>;

template<typename T, typename... Args>
constexpr Scope<T> CreateScope(Args&&... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<class T>
using Ref = std::shared_ptr<T>;

template<typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&&... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template<class _Ty1, class _Ty2>
inline constexpr Ref<_Ty1> ref_cast(const Ref<_Ty2>& x) noexcept { return std::dynamic_pointer_cast<_Ty1>(x); }

template<class _Ty1, class _Ty2>
inline constexpr Ref<_Ty1> static_ref_cast(const Ref<_Ty2>& x) noexcept { return std::static_pointer_cast<_Ty1>(x); }