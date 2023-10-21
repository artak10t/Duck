#pragma once
#include "../pch.h"
#include "Vector.h"

namespace Duck
{
	template<typename T>
	struct TVector<3, T> final
	{
		//Data
		T x, y, z;

		//Component Accesses
		inline constexpr T& operator[](int i)
		{
			assert(i >= 0 && i < 3);
			switch (i)
			{
			default:
			case 0:
				return this->x;
			case 1:
				return this->y;
			case 2:
				return this->z;
			}
		};

		inline constexpr T const& operator[](int i) const
		{
			assert(i >= 0 && i < 3);
			switch (i)
			{
			default:
			case 0:
				return this->x;
			case 1:
				return this->y;
			case 2:
				return this->z;
			}
		};

		//Implicit Constructors
		constexpr TVector()
			: x(0)
			, y(0)
			, z(0)
		{};

		constexpr TVector(TVector<3, T> const& v)
			: x(v.x)
			, y(v.y)
			, z(v.z)
		{};

		//Explicit Constructors
		constexpr TVector(T scalar)
			: x(scalar)
			, y(scalar)
			, z(scalar)
		{};

		constexpr TVector(T x, T y, T z)
			: x(x)
			, y(y)
			, z(z)
		{};

		//Conversion Scalar Constructors
		template<typename X, typename Y, typename Z>
		inline constexpr TVector(X x, Y y, Z z)
			: x(static_cast<T>(x))
			, y(static_cast<T>(y))
			, z(static_cast<T>(z))
		{};

		//Conversion Vector Constructors
		template<typename A, typename B>
		inline constexpr TVector(TVector<2, A> const& xy, B z)
			: x(static_cast<T>(xy.x))
			, y(static_cast<T>(xy.y))
			, z(static_cast<T>(z))
		{};

		template<typename A, typename B>
		inline constexpr TVector(A x, TVector<2, B> const& yz)
			: x(static_cast<T>(x))
			, y(static_cast<T>(yz.x))
			, z(static_cast<T>(yz.y))
		{};

		template<typename U>
		inline constexpr TVector(TVector<3, U> const& v)
			: x(static_cast<T>(v.x))
			, y(static_cast<T>(v.y))
			, z(static_cast<T>(v.z))
		{};

		template<typename U>
		inline constexpr TVector(TVector<4, U> const& v)
			: x(static_cast<T>(v.x))
			, y(static_cast<T>(v.y))
			, z(static_cast<T>(v.z))
		{};

		//Unary Arithmetic Operators
		inline constexpr TVector<3, T>& operator=(TVector<3, T> const& v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			return *this;
		};

		template<typename U>
		inline constexpr TVector<3, T>& operator=(TVector<3, U> const& v)
		{
			this->x = static_cast<T>(v.x);
			this->y = static_cast<T>(v.y);
			this->z = static_cast<T>(v.z);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<3, T>& operator+=(U scalar)
		{
			this->x += static_cast<T>(scalar);
			this->y += static_cast<T>(scalar);
			this->z += static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<3, T>& operator+=(TVector<3, U> const& v)
		{
			this->x += static_cast<T>(v.x);
			this->y += static_cast<T>(v.y);
			this->z += static_cast<T>(v.z);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<3, T>& operator-=(U scalar)
		{
			this->x -= static_cast<T>(scalar);
			this->y -= static_cast<T>(scalar);
			this->z -= static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<3, T>& operator-=(TVector<3, U> const& v)
		{
			this->x -= static_cast<T>(v.x);
			this->y -= static_cast<T>(v.y);
			this->z -= static_cast<T>(v.z);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<3, T>& operator*=(U scalar)
		{
			this->x *= static_cast<T>(scalar);
			this->y *= static_cast<T>(scalar);
			this->z *= static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<3, T>& operator*=(TVector<3, U> const& v)
		{
			this->x *= static_cast<T>(v.x);
			this->y *= static_cast<T>(v.y);
			this->z *= static_cast<T>(v.z);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<3, T>& operator/=(U scalar)
		{
			this->x /= static_cast<T>(scalar);
			this->y /= static_cast<T>(scalar);
			this->z /= static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<3, T>& operator/=(TVector<3, U> const& v)
		{
			this->x /= static_cast<T>(v.x);
			this->y /= static_cast<T>(v.y);
			this->z /= static_cast<T>(v.z);
			return *this;
		};

		//Increment Decrement Operators
		inline constexpr TVector<3, T>& operator++()
		{
			++this->x;
			++this->y;
			++this->z;
			return *this;
		};

		inline constexpr TVector<3, T>& operator--()
		{
			--this->x;
			--this->y;
			--this->z;
			return *this;
		};

		inline constexpr TVector<3, T> operator++(int)
		{
			TVector<3, T> Result(*this);
			++* this;
			return Result;
		};

		inline constexpr TVector<3, T> operator--(int)
		{
			TVector<3, T> Result(*this);
			--* this;
			return Result;
		};

		//Unary Bit Operators
		template<typename U>
		inline constexpr TVector<3, T>& operator%=(U scalar)
		{
			this->x %= static_cast<T>(scalar);
			this->y %= static_cast<T>(scalar);
			this->z %= static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<3, T>& operator%=(TVector<3, U> const& v)
		{
			this->x %= static_cast<T>(v.x);
			this->y %= static_cast<T>(v.y);
			this->z %= static_cast<T>(v.z);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<3, T>& operator&=(U scalar)
		{
			this->x &= static_cast<T>(scalar);
			this->y &= static_cast<T>(scalar);
			this->z &= static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<3, T>& operator&=(TVector<3, U> const& v)
		{
			this->x &= static_cast<T>(v.x);
			this->y &= static_cast<T>(v.y);
			this->z &= static_cast<T>(v.z);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<3, T>& operator|=(U scalar)
		{
			this->x |= static_cast<T>(scalar);
			this->y |= static_cast<T>(scalar);
			this->z |= static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<3, T>& operator|=(TVector<3, U> const& v)
		{
			this->x |= static_cast<T>(v.x);
			this->y |= static_cast<T>(v.y);
			this->z |= static_cast<T>(v.z);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<3, T>& operator^=(U scalar)
		{
			this->x ^= static_cast<T>(scalar);
			this->y ^= static_cast<T>(scalar);
			this->z ^= static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<3, T>& operator^=(TVector<3, U> const& v)
		{
			this->x ^= static_cast<T>(v.x);
			this->y ^= static_cast<T>(v.y);
			this->z ^= static_cast<T>(v.z);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<3, T>& operator<<=(U scalar)
		{
			this->x <<= static_cast<T>(scalar);
			this->y <<= static_cast<T>(scalar);
			this->z <<= static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<3, T>& operator<<=(TVector<3, U> const& v)
		{
			this->x <<= static_cast<T>(v.x);
			this->y <<= static_cast<T>(v.y);
			this->z <<= static_cast<T>(v.z);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<3, T>& operator>>=(U scalar)
		{
			this->x >>= static_cast<T>(scalar);
			this->y >>= static_cast<T>(scalar);
			this->z >>= static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<3, T>& operator>>=(TVector<3, U> const& v)
		{
			this->x >>= static_cast<T>(v.x);
			this->y >>= static_cast<T>(v.y);
			this->z >>= static_cast<T>(v.z);
			return *this;
		};

		//Unary Operators
		inline constexpr TVector<3, T> operator+()
		{
			return TVector<3, T>(
				this->x,
				this->y,
				this->z);
		};

		inline constexpr TVector<3, T> operator-()
		{
			return TVector<3, T>(
				-this->x,
				-this->y,
				-this->z);
		};

		//Binary Arithmetic Operators
		friend inline constexpr TVector<3, T> operator+(TVector<3, T> const& v, T scalar)
		{
			return TVector<3, T>(
				v.x + scalar,
				v.y + scalar,
				v.z + scalar);
		}

		friend inline constexpr TVector<3, T> operator+(T scalar, TVector<3, T> const& v)
		{
			return TVector<3, T>(
				scalar + v.x,
				scalar + v.y,
				scalar + v.z);
		}

		friend inline constexpr TVector<3, T> operator+(TVector<3, T> const& v1, TVector<3, T> const& v2)
		{
			return TVector<3, T>(
				v1.x + v2.x,
				v1.y + v2.y,
				v1.z + v2.z);
		}

		friend inline constexpr TVector<3, T> operator-(TVector<3, T> const& v, T scalar)
		{
			return TVector<3, T>(
				v.x - scalar,
				v.y - scalar,
				v.z - scalar);
		}

		friend inline constexpr TVector<3, T> operator-(T scalar, TVector<3, T> const& v)
		{
			return TVector<3, T>(
				scalar - v.x,
				scalar - v.y,
				scalar - v.z);
		}

		friend inline constexpr TVector<3, T> operator-(TVector<3, T> const& v1, TVector<3, T> const& v2)
		{
			return TVector<3, T>(
				v1.x - v2.x,
				v1.y - v2.y,
				v1.z - v2.z);
		}

		friend inline constexpr TVector<3, T> operator*(TVector<3, T> const& v, T scalar)
		{
			return TVector<3, T>(
				v.x * scalar,
				v.y * scalar,
				v.z * scalar);
		}

		friend inline constexpr TVector<3, T> operator*(T scalar, TVector<3, T> const& v)
		{
			return TVector<3, T>(
				scalar * v.x,
				scalar * v.y,
				scalar * v.z);
		}

		friend inline constexpr TVector<3, T> operator*(TVector<3, T> const& v1, TVector<3, T> const& v2)
		{
			return TVector<3, T>(
				v1.x * v2.x,
				v1.y * v2.y,
				v1.z * v2.z);
		}

		friend inline constexpr TVector<3, T> operator/(TVector<3, T> const& v, T scalar)
		{
			return TVector<3, T>(
				v.x / scalar,
				v.y / scalar,
				v.z / scalar);
		}

		friend inline constexpr TVector<3, T> operator/(T scalar, TVector<3, T> const& v)
		{
			return TVector<3, T>(
				scalar / v.x,
				scalar / v.y,
				scalar / v.z);
		}

		friend inline constexpr TVector<3, T> operator/(TVector<3, T> const& v1, TVector<3, T> const& v2)
		{
			return TVector<3, T>(
				v1.x / v2.x,
				v1.y / v2.y,
				v1.z / v2.z);
		}

		//Binary Bit Operators
		friend inline constexpr TVector<3, T> operator%(TVector<3, T> const& v, T scalar)
		{
			return TVector<3, T>(
				v.x % scalar,
				v.y % scalar,
				v.z % scalar);
		}

		friend inline constexpr TVector<3, T> operator%(T scalar, TVector<3, T> const& v)
		{
			return TVector<3, T>(
				scalar % v.x,
				scalar % v.y,
				scalar % v.z);
		}

		friend inline constexpr TVector<3, T> operator%(TVector<3, T> const& v1, TVector<3, T> const& v2)
		{
			return TVector<3, T>(
				v1.x % v2.x,
				v1.y % v2.y,
				v1.z % v2.z);
		}

		friend inline constexpr TVector<3, T> operator&(TVector<3, T> const& v, T scalar)
		{
			return TVector<3, T>(
				v.x & scalar,
				v.y & scalar,
				v.z & scalar);
		}

		friend inline constexpr TVector<3, T> operator&(T scalar, TVector<3, T> const& v)
		{
			return TVector<3, T>(
				scalar & v.x,
				scalar & v.y,
				scalar & v.z);
		}

		friend inline constexpr TVector<3, T> operator&(TVector<3, T> const& v1, TVector<3, T> const& v2)
		{
			return TVector<3, T>(
				v1.x & v2.x,
				v1.y & v2.y,
				v1.z & v2.z);
		}

		friend inline constexpr TVector<3, T> operator|(TVector<3, T> const& v, T scalar)
		{
			return TVector<3, T>(
				v.x | scalar,
				v.y | scalar,
				v.z | scalar);
		}

		friend inline constexpr TVector<3, T> operator|(T scalar, TVector<3, T> const& v)
		{
			return TVector<3, T>(
				scalar | v.x,
				scalar | v.y,
				scalar | v.z);
		}

		friend inline constexpr TVector<3, T> operator|(TVector<3, T> const& v1, TVector<3, T> const& v2)
		{
			return TVector<3, T>(
				v1.x | v2.x,
				v1.y | v2.y,
				v1.z | v2.z);
		}

		friend inline constexpr TVector<3, T> operator^(TVector<3, T> const& v, T scalar)
		{
			return TVector<3, T>(
				v.x ^ scalar,
				v.y ^ scalar,
				v.z ^ scalar);
		}

		friend inline constexpr TVector<3, T> operator^(T scalar, TVector<3, T> const& v)
		{
			return TVector<3, T>(
				scalar ^ v.x,
				scalar ^ v.y,
				scalar ^ v.z);
		}

		friend inline constexpr TVector<3, T> operator^(TVector<3, T> const& v1, TVector<3, T> const& v2)
		{
			return TVector<3, T>(
				v1.x ^ v2.x,
				v1.y ^ v2.y,
				v1.z ^ v2.z);
		}

		friend inline constexpr TVector<3, T> operator<<(TVector<3, T> const& v, T scalar)
		{
			return TVector<3, T>(
				v.x << scalar,
				v.y << scalar,
				v.z << scalar);
		}

		friend inline constexpr TVector<3, T> operator<<(T scalar, TVector<3, T> const& v)
		{
			return TVector<3, T>(
				scalar << v.x,
				scalar << v.y,
				scalar << v.z);
		}

		friend inline constexpr TVector<3, T> operator<<(TVector<3, T> const& v1, TVector<3, T> const& v2)
		{
			return TVector<3, T>(
				v1.x << v2.x,
				v1.y << v2.y,
				v1.z << v2.z);
		}

		friend inline constexpr TVector<3, T> operator>>(TVector<3, T> const& v, T scalar)
		{
			return TVector<3, T>(
				v.x >> scalar,
				v.y >> scalar,
				v.z >> scalar);
		}

		friend inline constexpr TVector<3, T> operator>>(T scalar, TVector<3, T> const& v)
		{
			return TVector<3, T>(
				scalar >> v.x,
				scalar >> v.y,
				scalar >> v.z);
		};

		friend inline constexpr TVector<3, T> operator>>(TVector<3, T> const& v1, TVector<3, T> const& v2)
		{
			return TVector<3, T>(
				v1.x >> v2.x,
				v1.y >> v2.y,
				v1.z >> v2.z);
		};

		inline constexpr TVector<3, T> operator~()
		{
			return TVector<3, T>(
				~this->x,
				~this->y,
				~this->z);
		};

		//Boolean Operators
		inline constexpr bool operator==(TVector<3, T> const& v)
		{
			return (this->x == v.x && this->y == v.y && this->z == v.z);
		};

		inline constexpr bool operator!=(TVector<3, T> const& v)
		{
			return !(this->x == v.x && this->y == v.y && this->z == v.z);
		};
	};

	//Type Definitions
	typedef TVector<3, float> Vector3;
	typedef TVector<3, double> dVector3;
	typedef TVector<3, int> iVector3;
	typedef TVector<3, unsigned int> uVector3;
}