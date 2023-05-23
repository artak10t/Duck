#pragma once
#include "../pch.h"

#include "Vector.h"
#include "Trigonometry.h"

namespace Duck
{
	template<typename T>
	struct TQuaternion final
	{
		//Data
		union { T x; };
		union { T y; };
		union { T z; };
		union { T w; };

		//Component Accesses
		inline constexpr T& operator[](int i)
		{
			assert(i >= 0 && i < 4);
			return (&x)[i];
		}

		inline constexpr T const& operator[](int i) const
		{
			assert(i >= 0 && i < 4);
			return (&x)[i];
		}

		//Implicit Constructors
		inline constexpr TQuaternion() :
			x(0),
			y(0),
			z(0),
			w(1)
		{};

		inline constexpr TQuaternion(TQuaternion<T> const& q) :
			x(q.x),
			y(q.y),
			z(q.z),
			w(q.w)
		{};

		//Explicit Constructors
		inline constexpr TQuaternion(TVector<3, T> const& v, T s) :
			x(v.x),
			y(v.y),
			z(v.z),
			w(s)
		{};

		inline constexpr TQuaternion(T x, T y, T z, T w) :
			x(x),
			y(y),
			z(z),
			w(w)
		{};

		//Static Methods
		static inline T Angle(TQuaternion<T> const& x)
		{
			if (std::abs(x.w) > COS_ONE_OVER_TWO)
			{
				return std::asin(std::sqrt(x.x * x.x + x.y * x.y + x.z * x.z)) * static_cast<T>(2);
			}

			return std::acos(x.w) * static_cast<T>(2);
		}

		static inline T Dot(TQuaternion<T> const& x, TQuaternion<T> const& y)
		{
			TVector<4, T> tmp(x.x * y.x, x.y * y.y, x.z * y.z, x.w * y.w);
			return tmp.x + tmp.y + tmp.z + tmp.w;
		}

		static inline T Magnitude(TQuaternion<T> const& q)
		{
			return std::sqrt(Dot(q, q));
		}

		static inline TQuaternion<T> Normalize(TQuaternion<T> const& q)
		{
			T len = Magnitude(q);
			if (len <= static_cast<T>(0))
				return TQuaternion<T>(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));

			T oneOverLen = static_cast<T>(1) / len;
			return TQuaternion<T>(q.x * oneOverLen, q.y * oneOverLen, q.z * oneOverLen, q.w * oneOverLen);
		}

		static inline TQuaternion<T> Cross(TQuaternion<T> const& q1, TQuaternion<T> const& q2)
		{
			return TQuaternion<T>(
				q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
				q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z,
				q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x,
				q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z);
		}

		static inline TQuaternion<T> AngleAxis(T const& angle, TVector<3, T> const& v)
		{
			T const a(Math::ToRadians(angle));
			T const s = std::sin(a * static_cast<T>(0.5));

			return TQuaternion<T>(v * s, std::cos(a * static_cast<T>(0.5)));
		}

		static inline TQuaternion<T> Conjugate(TQuaternion<T> const& q)
		{
			return TQuaternion<T>(-q.x, -q.y, -q.z, q.w);
		}

		static inline TQuaternion<T> Inverse(TQuaternion<T> const& q)
		{
			return Conjugate(q) / Dot(q, q);
		}

		static inline TQuaternion<T> Lerp(TQuaternion<T> const& a, TQuaternion<T> const& b, T x)
		{
			static_assert(std::numeric_limits<T>::is_iec559, "'Lerp' only accept floating-point inputs");
			x = std::clamp(x, T(0), T(1));

			T const cosTheta = Dot(a, b);

			if (cosTheta > static_cast<T>(1) - std::numeric_limits<T>::epsilon())
			{

				return TQuaternion<T>(
					std::lerp(a.x, b.x, x),
					std::lerp(a.y, b.y, x),
					std::lerp(a.z, b.z, x),
					std::lerp(a.w, b.w, x));
			}
			else
			{
				T angle = std::acos(cosTheta);
				return (std::sin((static_cast<T>(1) - x) * angle) * a + std::sin(x * angle) * b) / std::sin(angle);
			}
		}

		static inline TQuaternion<T> Slerp(TQuaternion<T> const& a, TQuaternion<T> const& b, T x)
		{
			static_assert(std::numeric_limits<T>::is_iec559, "'slerp' only accept floating-point inputs");
			x = std::clamp(x, T(0), T(1));

			TQuaternion<T> z = b;

			T cosTheta = Dot(a, b);

			if (cosTheta < static_cast<T>(0))
			{
				z = -b;
				cosTheta = -cosTheta;
			}

			if (cosTheta > static_cast<T>(1) - std::numeric_limits<T>::epsilon())
			{
				return TQuaternion<T>(
					std::lerp(a.x, z.x, x),
					std::lerp(a.y, z.y, x),
					std::lerp(a.z, z.z, x),
					std::lerp(a.w, z.w, x));
			}
			else
			{
				T angle = std::acos(cosTheta);
				return (std::sin((static_cast<T>(1) - x) * angle) * a + std::sin(x * angle) * z) / std::sin(angle);
			}
		}
		
		static inline TVector<3, T> Euler(TQuaternion<T> const& q)
		{

			return TVector<3, T>(Pitch(q), Yaw(q), Roll(q));
		}

		//InDegrees
		static inline T Roll(TQuaternion<T> const& q)
		{
			return Math::ToDegrees(static_cast<T>(std::atan2(static_cast<T>(2) * (q.x * q.y + q.w * q.z), q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z)));
		}

		//InDegrees
		static inline T Pitch(TQuaternion<T> const& q)
		{
			return Math::ToDegrees(static_cast<T>(std::atan2(static_cast<T>(2) * (q.y * q.z + q.w * q.x), q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z)));
		}

		//InDegrees
		static inline T Yaw(TQuaternion<T> const& q)
		{
			return Math::ToDegrees(std::asin(std::clamp(static_cast<T>(-2) * (q.x * q.z - q.w * q.y), static_cast<T>(-1), static_cast<T>(1))));
		}

		//Conversion Constructors
		template<typename U>
		inline constexpr TQuaternion(TQuaternion<U> const& q) :
			x(static_cast<T>(q.x)),
			y(static_cast<T>(q.y)),
			z(static_cast<T>(q.z)),
			w(static_cast<T>(q.w))
		{};

		inline TQuaternion(TVector<3, T> const& u, TVector<3, T> const& v)
		{
			T norm_u_norm_v = std::sqrt(Vector::Dot(u, u) * Vector::Dot(v, v));
			T real_part = norm_u_norm_v + Vector::Dot(u, v);
			TVector<3, T> t;

			if (real_part < static_cast<T>(1.e-6f) * norm_u_norm_v)
			{

				real_part = static_cast<T>(0);
				t = std::abs(u.x) > std::abs(u.z) ? TVector<3, T>(-u.y, u.x, static_cast<T>(0)) : TVector<3, T>(static_cast<T>(0), -u.z, u.y);
			}
			else
				t = Vector::Cross(u, v);

			*this = Normalize(TQuaternion<T>(t.x, t.y, t.z, real_part));
		};

		//ZYX Order
		inline constexpr TQuaternion(TVector<3, T> const& eulerAngle)
		{
			TVector<3, T> const& e = TVector<3, T>(Math::ToRadians(eulerAngle.x), Math::ToRadians(eulerAngle.y), Math::ToRadians(eulerAngle.z)) * T(0.5);
			TVector<3, T> c = TVector<3, T>(std::cos(e.x), std::cos(e.y), std::cos(e.z));
			TVector<3, T> s = TVector<3, T>(std::sin(e.x), std::sin(e.y), std::sin(e.z));

			this->w = c.x * c.y * c.z + s.x * s.y * s.z;
			this->x = s.x * c.y * c.z - c.x * s.y * s.z;
			this->y = c.x * s.y * c.z + s.x * c.y * s.z;
			this->z = c.x * c.y * s.z - s.x * s.y * c.z;
		};

		//Unary Arithmetic Operators
		inline constexpr TQuaternion<T>& operator=(TQuaternion<T> const& q)
		{
			this->w = q.w;
			this->x = q.x;
			this->y = q.y;
			this->z = q.z;
			return *this;
		}

		template<typename U>
		inline constexpr TQuaternion<T>& operator=(TQuaternion<U> const& q)
		{
			this->w = static_cast<T>(q.w);
			this->x = static_cast<T>(q.x);
			this->y = static_cast<T>(q.y);
			this->z = static_cast<T>(q.z);
			return *this;
		}

		template<typename U>
		inline constexpr TQuaternion<T>& operator+=(TQuaternion<U> const& q)
		{
			this->w += static_cast<T>(q.w);
			this->x += static_cast<T>(q.x);
			this->y += static_cast<T>(q.y);
			this->z += static_cast<T>(q.z);
			return *this;
		}

		template<typename U>
		inline constexpr TQuaternion<T>& operator-=(TQuaternion<U> const& q)
		{
			this->w -= static_cast<T>(q.w);
			this->x -= static_cast<T>(q.x);
			this->y -= static_cast<T>(q.y);
			this->z -= static_cast<T>(q.z);
			return *this;
		}

		template<typename U>
		inline constexpr TQuaternion<T>& operator*=(TQuaternion<U> const& r)
		{
			TQuaternion<T> const p(*this);
			TQuaternion<T> const q(r);

			this->w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
			this->x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
			this->y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
			this->z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
			return *this;
		}

		template<typename U>
		inline constexpr TQuaternion<T>& operator*=(U s)
		{
			this->w *= static_cast<T>(s);
			this->x *= static_cast<T>(s);
			this->y *= static_cast<T>(s);
			this->z *= static_cast<T>(s);
			return *this;
		}

		template<typename U>
		inline constexpr TQuaternion<T>& operator/=(U s)
		{
			this->w /= static_cast<T>(s);
			this->x /= static_cast<T>(s);
			this->y /= static_cast<T>(s);
			this->z /= static_cast<T>(s);
		}

		//Unary Bit Operators
		friend inline constexpr TQuaternion<T> operator+(TQuaternion<T> const& q)
		{
			return q;
		}

		friend inline constexpr TQuaternion<T> operator-(TQuaternion<T> const& q)
		{
			return TQuaternion<T>(-q.x, -q.y, -q.z, -q.w);
		}

		//Binary Arithmetic Operators
		friend inline constexpr TQuaternion<T> operator+(TQuaternion<T> const& q, TQuaternion<T> const& p)
		{
			return TQuaternion<T>(q) += p;
		}

		friend inline constexpr TQuaternion<T> operator-(TQuaternion<T> const& q, TQuaternion<T> const& p)
		{
			return TQuaternion<T>(q) -= p;
		}

		friend inline constexpr TQuaternion<T> operator*(TQuaternion<T> const& q, TQuaternion<T> const& p)
		{
			return TQuaternion<T>(q) *= p;
		}

		friend inline constexpr TVector<3, T> operator*(TQuaternion<T> const& q, TVector<3, T> const& v)
		{
			TVector<3, T> const quat(q.x, q.y, q.z);
			TVector<3, T> const uv(Cross(quat, v));
			TVector<3, T> const uuv(Cross(quat, uv));

			return v + ((uv * q.w) + uuv) * static_cast<T>(2);
		}

		friend inline constexpr TVector<3, T> operator*(TVector<3, T> const& v, TQuaternion<T> const& q)
		{
			return Inverse(q) * v;
		}

		friend inline constexpr TVector<4, T> operator*(TQuaternion<T> const& q, TVector<4, T> const& v)
		{
			return TVector<4, T>(q * TVector<3, T>(v), v.w);
		}

		friend inline constexpr TVector<4, T> operator*(TVector<4, T> const& v, TQuaternion<T> const& q)
		{
			return Inverse(q) * v;
		}

		friend inline constexpr TQuaternion<T> operator*(TQuaternion<T> const& q, T const& s)
		{
			return TQuaternion<T>(q.x * s, q.y * s, q.z * s, q.w * s);
		}

		friend inline constexpr TQuaternion<T> operator*(T const& s, TQuaternion<T> const& q)
		{
			return q * s;
		}

		friend inline constexpr TQuaternion<T> operator/(TQuaternion<T> const& q, T const& s)
		{
			return TQuaternion<T>(q.x / s, q.y / s, q.z / s, q.w / s);
		}

		//Boolean Operators
		inline constexpr bool operator==(TQuaternion<T> const& q)
		{
			return this->x == q.x && this->y == q.y && this->z == q.z && this->w == q.w;
		}

		inline constexpr bool operator!=(TQuaternion<T> const& q)
		{
			return this->x != q.x || this->y != q.y || this->z != q.z || this->w != q.w;
		}
	};

	//Type Definitions
	typedef TQuaternion<float> Quaternion;
	typedef TQuaternion<float> dQuaternion;
}