#pragma once
#include "../pch.h"
#include "Vector.h"

namespace Duck
{
	template<typename T>
	struct TVector<4, T>
	{
		//Data
		union { T x, r; };
		union { T y, g; };
		union { T z, b; };
		union { T w, a; };

		//Component Accesses
		inline constexpr T& operator[](int i)
		{
			assert(i >= 0 && i < 4);
			switch (i)
			{
			default:
			case 0:
				return this->x;
			case 1:
				return this->y;
			case 2:
				return this->z;
			case 3:
				return this->w;
			}
		};

		inline constexpr T const& operator[](int i) const
		{
			assert(i >= 0 && i < 4);
			switch (i)
			{
			default:
			case 0:
				return this->x;
			case 1:
				return this->y;
			case 2:
				return this->z;
			case 3:
				return this->w;
			}
		};

		//Implicit Constructors
		constexpr TVector()
			: x(0)
			, y(0)
			, z(0)
			, w(0)
		{};

		constexpr TVector(TVector<4, T> const& v)
			: x(v.x)
			, y(v.y)
			, z(v.z)
			, w(v.w)
		{};

		//Explicit Constructors
		constexpr TVector(T scalar)
			: x(scalar)
			, y(scalar)
			, z(scalar)
			, w(scalar)
		{};

		constexpr TVector(T x, T y, T z, T w)
			: x(x)
			, y(y)
			, z(z)
			, w(w)
		{};

		//Conversion Scalar Constructors
		template<typename X, typename Y, typename Z, typename W>
		inline constexpr TVector(X x, Y y, Z z, W w)
			: x(static_cast<T>(x))
			, y(static_cast<T>(y))
			, z(static_cast<T>(z))
			, w(static_cast<T>(w))
		{};

		//Conversion Vector Constructors
		template<typename A, typename B, typename C>
		inline constexpr TVector(TVector<2, A> const& xy, B z, C w)
			: x(static_cast<T>(xy.x))
			, y(static_cast<T>(xy.y))
			, z(static_cast<T>(z))
			, w(static_cast<T>(w))
		{};

		template<typename A, typename B, typename C>
		inline constexpr TVector(A x, TVector<2, B> const& yz, C w)
			: x(static_cast<T>(x))
			, y(static_cast<T>(yz.x))
			, z(static_cast<T>(yz.y))
			, w(static_cast<T>(w))
		{};

		template<typename A, typename B, typename C>
		inline constexpr TVector(A x, B y, TVector<2, C> const& zw)
			: x(static_cast<T>(x))
			, y(static_cast<T>(y))
			, z(static_cast<T>(zw.x))
			, w(static_cast<T>(zw.y))
		{};

		template<typename A, typename B>
		inline constexpr TVector(TVector<3, A> const& xyz, B w)
			: x(static_cast<T>(xyz.x))
			, y(static_cast<T>(xyz.y))
			, z(static_cast<T>(xyz.z))
			, w(static_cast<T>(w))
		{};

		template<typename A, typename B>
		inline constexpr TVector(A x, TVector<3, B> const& yzw)
			: x(static_cast<T>(x))
			, y(static_cast<T>(yzw.x))
			, z(static_cast<T>(yzw.y))
			, w(static_cast<T>(yzw.z))
		{};

		template<typename A, typename B>
		inline constexpr TVector(TVector<2, A> const& xy, TVector<2, B> const& zw)
			: x(static_cast<T>(xy.x))
			, y(static_cast<T>(xy.y))
			, z(static_cast<T>(zw.x))
			, w(static_cast<T>(zw.y))
		{};

		template<typename U>
		inline constexpr TVector(TVector<4, U> const& v)
			: x(static_cast<T>(v.x))
			, y(static_cast<T>(v.y))
			, z(static_cast<T>(v.z))
			, w(static_cast<T>(v.w))
		{};

		//Unary Arithmetic Operators
		inline constexpr TVector<4, T>& operator=(TVector<4, T> const& v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			this->w = v.w;
			return *this;
		};

		template<typename U>
		inline constexpr TVector<4, T>& operator=(TVector<4, U> const& v)
		{
			this->x = static_cast<T>(v.x);
			this->y = static_cast<T>(v.y);
			this->z = static_cast<T>(v.z);
			this->w = static_cast<T>(v.w);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<4, T>& operator+=(U scalar)
		{
			this->x += static_cast<T>(scalar);
			this->y += static_cast<T>(scalar);
			this->z += static_cast<T>(scalar);
			this->w += static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<4, T>& operator+=(TVector<4, U> const& v)
		{
			this->x += static_cast<T>(v.x);
			this->y += static_cast<T>(v.y);
			this->z += static_cast<T>(v.z);
			this->w += static_cast<T>(v.w);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<4, T>& operator-=(U scalar)
		{
			this->x -= static_cast<T>(scalar);
			this->y -= static_cast<T>(scalar);
			this->z -= static_cast<T>(scalar);
			this->w -= static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<4, T>& operator-=(TVector<4, U> const& v)
		{
			this->x -= static_cast<T>(v.x);
			this->y -= static_cast<T>(v.y);
			this->z -= static_cast<T>(v.z);
			this->w -= static_cast<T>(v.w);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<4, T>& operator*=(U scalar)
		{
			this->x *= static_cast<T>(scalar);
			this->y *= static_cast<T>(scalar);
			this->z *= static_cast<T>(scalar);
			this->w *= static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<4, T>& operator*=(TVector<4, U> const& v)
		{
			this->x *= static_cast<T>(v.x);
			this->y *= static_cast<T>(v.y);
			this->z *= static_cast<T>(v.z);
			this->w *= static_cast<T>(v.w);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<4, T>& operator/=(U scalar)
		{
			this->x /= static_cast<T>(scalar);
			this->y /= static_cast<T>(scalar);
			this->z /= static_cast<T>(scalar);
			this->w /= static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<4, T>& operator/=(TVector<4, U> const& v)
		{
			this->x /= static_cast<T>(v.x);
			this->y /= static_cast<T>(v.y);
			this->z /= static_cast<T>(v.z);
			this->w /= static_cast<T>(v.w);
			return *this;
		};

		//Increment Decrement Operators
		inline constexpr TVector<4, T>& operator++()
		{
			++this->x;
			++this->y;
			++this->z;
			++this->w;
			return *this;
		};

		inline constexpr TVector<4, T>& operator--()
		{
			--this->x;
			--this->y;
			--this->z;
			--this->w;
			return *this;
		};

		inline constexpr TVector<4, T> operator++(int)
		{
			TVector<4, T> Result(*this);
			++* this;
			return Result;
		};

		inline constexpr TVector<4, T> operator--(int)
		{
			TVector<4, T> Result(*this);
			--* this;
			return Result;
		};

		//Unary Bit Operators
		template<typename U>
		inline constexpr TVector<4, T>& operator%=(U scalar)
		{
			this->x %= static_cast<T>(scalar);
			this->y %= static_cast<T>(scalar);
			this->z %= static_cast<T>(scalar);
			this->w %= static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<4, T>& operator%=(TVector<4, U> const& v)
		{
			this->x %= static_cast<T>(v.x);
			this->y %= static_cast<T>(v.y);
			this->z %= static_cast<T>(v.z);
			this->w %= static_cast<T>(v.w);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<4, T>& operator&=(U scalar)
		{
			this->x &= static_cast<T>(scalar);
			this->y &= static_cast<T>(scalar);
			this->z &= static_cast<T>(scalar);
			this->w &= static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<4, T>& operator&=(TVector<4, U> const& v)
		{
			this->x &= static_cast<T>(v.x);
			this->y &= static_cast<T>(v.y);
			this->z &= static_cast<T>(v.z);
			this->w &= static_cast<T>(v.w);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<4, T>& operator|=(U scalar)
		{
			this->x |= static_cast<T>(scalar);
			this->y |= static_cast<T>(scalar);
			this->z |= static_cast<T>(scalar);
			this->w |= static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<4, T>& operator|=(TVector<4, U> const& v)
		{
			this->x |= static_cast<T>(v.x);
			this->y |= static_cast<T>(v.y);
			this->z |= static_cast<T>(v.z);
			this->w |= static_cast<T>(v.w);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<4, T>& operator^=(U scalar)
		{
			this->x ^= static_cast<T>(scalar);
			this->y ^= static_cast<T>(scalar);
			this->z ^= static_cast<T>(scalar);
			this->w ^= static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<4, T>& operator^=(TVector<4, U> const& v)
		{
			this->x ^= static_cast<T>(v.x);
			this->y ^= static_cast<T>(v.y);
			this->z ^= static_cast<T>(v.z);
			this->w ^= static_cast<T>(v.w);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<4, T>& operator<<=(U scalar)
		{
			this->x <<= static_cast<T>(scalar);
			this->y <<= static_cast<T>(scalar);
			this->z <<= static_cast<T>(scalar);
			this->w <<= static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<4, T>& operator<<=(TVector<4, U> const& v)
		{
			this->x <<= static_cast<T>(v.x);
			this->y <<= static_cast<T>(v.y);
			this->z <<= static_cast<T>(v.z);
			this->w <<= static_cast<T>(v.w);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<4, T>& operator>>=(U scalar)
		{
			this->x >>= static_cast<T>(scalar);
			this->y >>= static_cast<T>(scalar);
			this->z >>= static_cast<T>(scalar);
			this->w >>= static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<4, T>& operator>>=(TVector<4, U> const& v)
		{
			this->x >>= static_cast<T>(v.x);
			this->y >>= static_cast<T>(v.y);
			this->z >>= static_cast<T>(v.z);
			this->w >>= static_cast<T>(v.w);
			return *this;
		};

		//Unary Operators
		inline constexpr TVector<4, T> operator+()
		{
			return TVector<4, T>(
				this->x,
				this->y,
				this->z,
				this->w);
		};

		inline constexpr TVector<4, T> operator-()
		{
			return TVector<4, T>(
				-this->x,
				-this->y,
				-this->z,
				-this->w);
		};

		//Binary Arithmetic Operators
		friend inline constexpr TVector<4, T> operator+(TVector<4, T> const& v, T scalar)
		{
			return TVector<4, T>(
				v.x + scalar,
				v.y + scalar,
				v.z + scalar,
				v.w + scalar);
		}

		friend inline constexpr TVector<4, T> operator+(T scalar, TVector<4, T> const& v)
		{
			return TVector<4, T>(
				scalar + v.x,
				scalar + v.y,
				scalar + v.z,
				scalar + v.w);
		}

		friend inline constexpr TVector<4, T> operator+(TVector<4, T> const& v1, TVector<4, T> const& v2)
		{
			return TVector<4, T>(
				v1.x + v2.x,
				v1.y + v2.y,
				v1.z + v2.z,
				v1.w + v2.w);
		}

		friend inline constexpr TVector<4, T> operator-(TVector<4, T> const& v, T scalar)
		{
			return TVector<4, T>(
				v.x - scalar,
				v.y - scalar,
				v.z - scalar,
				v.w - scalar);
		}

		friend inline constexpr TVector<4, T> operator-(T scalar, TVector<4, T> const& v)
		{
			return TVector<4, T>(
				scalar - v.x,
				scalar - v.y,
				scalar - v.z,
				scalar - v.w);
		}

		friend inline constexpr TVector<4, T> operator-(TVector<4, T> const& v1, TVector<4, T> const& v2)
		{
			return TVector<4, T>(
				v1.x - v2.x,
				v1.y - v2.y,
				v1.z - v2.z,
				v1.w - v2.w);
		}

		friend inline constexpr TVector<4, T> operator*(TVector<4, T> const& v, T scalar)
		{
			return TVector<4, T>(
				v.x * scalar,
				v.y * scalar,
				v.z * scalar,
				v.w * scalar);
		}

		friend inline constexpr TVector<4, T> operator*(T scalar, TVector<4, T> const& v)
		{
			return TVector<4, T>(
				scalar * v.x,
				scalar * v.y,
				scalar * v.z,
				scalar * v.w);
		}

		friend inline constexpr TVector<4, T> operator*(TVector<4, T> const& v1, TVector<4, T> const& v2)
		{
			return TVector<4, T>(
				v1.x * v2.x,
				v1.y * v2.y,
				v1.z * v2.z,
				v1.w * v2.w);
		}

		friend inline constexpr TVector<4, T> operator/(TVector<4, T> const& v, T scalar)
		{
			return TVector<4, T>(
				v.x / scalar,
				v.y / scalar,
				v.z / scalar,
				v.w / scalar);
		}

		friend inline constexpr TVector<4, T> operator/(T scalar, TVector<4, T> const& v)
		{
			return TVector<4, T>(
				scalar / v.x,
				scalar / v.y,
				scalar / v.z,
				scalar / v.w);
		}

		friend inline constexpr TVector<4, T> operator/(TVector<4, T> const& v1, TVector<4, T> const& v2)
		{
			return TVector<4, T>(
				v1.x / v2.x,
				v1.y / v2.y,
				v1.z / v2.z,
				v1.w / v2.w);
		}

		//Binary Bit Operators
		friend inline constexpr TVector<4, T> operator%(TVector<4, T> const& v, T scalar)
		{
			return TVector<4, T>(
				v.x % scalar,
				v.y % scalar,
				v.z % scalar,
				v.w % scalar);
		}

		friend inline constexpr TVector<4, T> operator%(T scalar, TVector<4, T> const& v)
		{
			return TVector<4, T>(
				scalar % v.x,
				scalar % v.y,
				scalar % v.z,
				scalar % v.w);
		}

		friend inline constexpr TVector<4, T> operator%(TVector<4, T> const& v1, TVector<4, T> const& v2)
		{
			return TVector<4, T>(
				v1.x % v2.x,
				v1.y % v2.y,
				v1.z % v2.z,
				v1.w % v2.w);
		}

		friend inline constexpr TVector<4, T> operator&(TVector<4, T> const& v, T scalar)
		{
			return TVector<4, T>(
				v.x & scalar,
				v.y & scalar,
				v.z & scalar,
				v.w & scalar);
		}

		friend inline constexpr TVector<4, T> operator&(T scalar, TVector<4, T> const& v)
		{
			return TVector<4, T>(
				scalar & v.x,
				scalar & v.y,
				scalar & v.z,
				scalar & v.w);
		}

		friend inline constexpr TVector<4, T> operator&(TVector<4, T> const& v1, TVector<4, T> const& v2)
		{
			return TVector<4, T>(
				v1.x & v2.x,
				v1.y & v2.y,
				v1.z & v2.z,
				v1.w & v2.w);
		}

		friend inline constexpr TVector<4, T> operator|(TVector<4, T> const& v, T scalar)
		{
			return TVector<4, T>(
				v.x | scalar,
				v.y | scalar,
				v.z | scalar,
				v.w | scalar);
		}

		friend inline constexpr TVector<4, T> operator|(T scalar, TVector<4, T> const& v)
		{
			return TVector<4, T>(
				scalar | v.x,
				scalar | v.y,
				scalar | v.z,
				scalar | v.w);
		}

		friend inline constexpr TVector<4, T> operator|(TVector<4, T> const& v1, TVector<4, T> const& v2)
		{
			return TVector<4, T>(
				v1.x | v2.x,
				v1.y | v2.y,
				v1.z | v2.z,
				v1.w | v2.w);
		}

		friend inline constexpr TVector<4, T> operator^(TVector<4, T> const& v, T scalar)
		{
			return TVector<4, T>(
				v.x ^ scalar,
				v.y ^ scalar,
				v.z ^ scalar,
				v.w ^ scalar);
		}

		friend inline constexpr TVector<4, T> operator^(T scalar, TVector<4, T> const& v)
		{
			return TVector<4, T>(
				scalar ^ v.x,
				scalar ^ v.y,
				scalar ^ v.z,
				scalar ^ v.w);
		}

		friend inline constexpr TVector<4, T> operator^(TVector<4, T> const& v1, TVector<4, T> const& v2)
		{
			return TVector<4, T>(
				v1.x ^ v2.x,
				v1.y ^ v2.y,
				v1.z ^ v2.z,
				v1.w ^ v2.w);
		}

		friend inline constexpr TVector<4, T> operator<<(TVector<4, T> const& v, T scalar)
		{
			return TVector<4, T>(
				v.x << scalar,
				v.y << scalar,
				v.z << scalar,
				v.w << scalar);
		}

		friend inline constexpr TVector<4, T> operator<<(T scalar, TVector<4, T> const& v)
		{
			return TVector<4, T>(
				scalar << v.x,
				scalar << v.y,
				scalar << v.z,
				scalar << v.w);
		}

		friend inline constexpr TVector<4, T> operator<<(TVector<4, T> const& v1, TVector<4, T> const& v2)
		{
			return TVector<4, T>(
				v1.x << v2.x,
				v1.y << v2.y,
				v1.z << v2.z,
				v1.w << v2.w);
		}

		friend inline constexpr TVector<4, T> operator>>(TVector<4, T> const& v, T scalar)
		{
			return TVector<4, T>(
				v.x >> scalar,
				v.y >> scalar,
				v.z >> scalar,
				v.w >> scalar);
		}

		friend inline constexpr TVector<4, T> operator>>(T scalar, TVector<4, T> const& v)
		{
			return TVector<4, T>(
				scalar >> v.x,
				scalar >> v.y,
				scalar >> v.z,
				scalar >> v.w);
		};

		friend inline constexpr TVector<4, T> operator>>(TVector<4, T> const& v1, TVector<4, T> const& v2)
		{
			return TVector<4, T>(
				v1.x >> v2.x,
				v1.y >> v2.y,
				v1.z >> v2.z,
				v1.w >> v2.w);
		};
		
		inline constexpr TVector<4, T> operator~()
		{
			return TVector<4, T>(
				~this->x,
				~this->y,
				~this->z,
				~this->w);
		};

		//Boolean Operators
		inline constexpr bool operator==(TVector<4, T> const& v)
		{
			return (this->x == v.x && this->y == v.y && this->z == v.z && this->w == v.w);
		};

		inline constexpr bool operator!=(TVector<4, T> const& v)
		{
			return !(this->x == v.x && this->y == v.y && this->z == v.z && this->w == v.w);
		};
	};

	//Type Definitions
	typedef TVector<4, float> Vector4;
	typedef TVector<4, double> dVector4;
	typedef TVector<4, int> iVector4;
	typedef TVector<4, unsigned int> uVector4;
}