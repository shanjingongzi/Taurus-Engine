#pragma once
#define KINDA_SMALL_NUMBER	(1.e-4f)

template<typename T>
static constexpr inline T Abs(T A)noexcept
{
	return (A = A > 0 ? A : -A);
}

template<typename T>
static constexpr inline T Max(const T A, const T B)noexcept
{
	return (A >= B) ? A : B;
}

template<typename T>
static constexpr inline T Min(const T A, const T B)noexcept
{
	return (A <= B) ? A : B;
}