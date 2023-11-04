#pragma once
#include "../pch.h"
#include "Trigonometry.h"

namespace Duck
{
	template<int L, typename T> struct TVector;

	// Methods
	namespace Vector
	{
		// Dot
		template<typename T>
		inline T Dot(TVector<2, T> const& a, TVector<2, T> const& b)
		{
			static_assert(std::numeric_limits<T>::is_iec559, "'Dot' accepts only floating-point inputs");

			TVector<2, T> tmp(a * b);
			return tmp.x + tmp.y;
		}

		template<typename T>
		inline T Dot(TVector<3, T> const& a, TVector<3, T> const& b)
		{
			static_assert(std::numeric_limits<T>::is_iec559, "'Dot' accepts only floating-point inputs");

			TVector<3, T> tmp(a * b);
			return tmp.x + tmp.y + tmp.z;
		}

		template<typename T>
		inline T Dot(TVector<4, T> const& a, TVector<4, T> const& b)
		{
			static_assert(std::numeric_limits<T>::is_iec559, "'Dot' accepts only floating-point inputs");

			TVector<4, T> tmp(a * b);
			return tmp.x + tmp.y + tmp.z + tmp.w;
		}

		// Cross
		template<typename T>
		inline TVector<3, T> Cross(TVector<3, T> const& a, TVector<3, T> const& b)
		{
			static_assert(std::numeric_limits<T>::is_iec559, "'Cross' accepts only floating-point inputs");

			return TVector<3, T>(
				a.y * b.z - b.y * a.z,
				a.z * b.x - b.z * a.x,
				a.x * b.y - b.x * a.y);
		}

		// Magnitude
		template<int L, typename T>
		inline T SqrMagnitude(TVector<L, T> const& v)
		{
			return Dot(v, v);
		}

		template<int L, typename T>
		inline T Magnitude(TVector<L, T> const& v)
		{
			return std::sqrt(Dot(v, v));
		}

		// Distance
		template<int L, typename T>
		inline T Distance(TVector<L, T> const& a, TVector<L, T> const& b)
		{
			return Magnitude(a - b);
		}

		// Normalize
		template<int L, typename T>
		inline TVector<L, T> Normalize(TVector<L, T> const& v)
		{
			static_assert(std::numeric_limits<T>::is_iec559, "'Normalize' accepts only floating-point inputs");

			return v * (static_cast<T>(1) / (Dot(v, v)));
		}

		// Lerp
		template<int L, typename T>
		inline TVector<L, T> Lerp(TVector<L, T> const& a, TVector<L, T> const& b, T x)
		{
			static_assert(std::numeric_limits<T>::is_iec559, "'Lerp' only accept floating-point inputs for the interpolator a");
			x = std::clamp(x, T(0), T(1));
			return TVector<L, T>(TVector<L, T>(a) * (static_cast<T>(1) - x) + TVector<L, T>(b) * x);
		}

		// Angle
		template<int L, typename T>
		inline T Angle(TVector<L, T> const& x, TVector<L, T> const& y)
		{
			static_assert(std::numeric_limits<T>::is_iec559, "'Angle' only accept floating-point inputs");
			return std::acos(std::clamp(Dot(x, y), T(-1), T(1)));
		}
	}
}