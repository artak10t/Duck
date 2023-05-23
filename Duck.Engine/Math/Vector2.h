#pragma once
#include "../pch.h"
#include "Vector.h"

namespace Duck
{
	template<typename T>
	struct TVector<2, T> final
	{
		//Data
		union { T x, r; };
		union { T y, g; };

		//Component Accesses
		inline constexpr T& operator[](int i)
		{
			assert(i >= 0 && i < 2);
			switch (i)
			{
			default:
			case 0:
				return this->x;
			case 1:
				return this->y;
			}
		};

		inline constexpr T const& operator[](int i) const
		{
			assert(i >= 0 && i < 2);
			switch (i)
			{
			default:
			case 0:
				return this->x;
			case 1:
				return this->y;
			}
		};

		//Implicit Constructors
		constexpr TVector() 
			: x(0)
			, y(0) 
		{};

		constexpr TVector(TVector<2, T> const& v) 
			: x(v.x)
			, y(v.y) 
		{};

		//Explicit Constructors
		constexpr TVector(T scalar)
			: x(scalar)
			, y(scalar)
		{};

		constexpr TVector(T x, T y)
			: x(x)
			, y(y)
		{};

		//Conversion Scalar Constructors
		template<typename A, typename B>
		inline constexpr TVector(A x, B y)
			: x(static_cast<T>(x))
			, y(static_cast<T>(y))
		{};

		//Conversion Vector Constructors
		template<typename U>
		inline constexpr TVector(TVector<2, U> const& v)
			: x(static_cast<T>(v.x))
			, y(static_cast<T>(v.y))
		{};

		template<typename U>
		inline constexpr TVector(TVector<3, U> const& v)
			: x(static_cast<T>(v.x))
			, y(static_cast<T>(v.y))
		{};

		template<typename U>
		inline constexpr TVector(TVector<4, U> const& v)
			: x(static_cast<T>(v.x))
			, y(static_cast<T>(v.y))
		{};

		//Unary Arithmetic Operators
		inline constexpr TVector<2, T>& operator=(TVector<2, T> const& v)
		{
			this->x = v.x;
			this->y = v.y;
			return *this;
		};

		template<typename U>
		inline constexpr TVector<2, T>& operator=(TVector<2, U> const& v)
		{
			this->x = static_cast<T>(v.x);
			this->y = static_cast<T>(v.y);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<2, T>& operator+=(U scalar)
		{
			this->x += static_cast<T>(scalar);
			this->y += static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<2, T>& operator+=(TVector<2, U> const& v)
		{
			this->x += static_cast<T>(v.x);
			this->y += static_cast<T>(v.y);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<2, T>& operator-=(U scalar)
		{
			this->x -= static_cast<T>(scalar);
			this->y -= static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<2, T>& operator-=(TVector<2, U> const& v)
		{
			this->x -= static_cast<T>(v.x);
			this->y -= static_cast<T>(v.y);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<2, T>& operator*=(U scalar)
		{
			this->x *= static_cast<T>(scalar);
			this->y *= static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<2, T>& operator*=(TVector<2, U> const& v)
		{
			this->x *= static_cast<T>(v.x);
			this->y *= static_cast<T>(v.y);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<2, T>& operator/=(U scalar)
		{
			this->x /= static_cast<T>(scalar);
			this->y /= static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<2, T>& operator/=(TVector<2, U> const& v)
		{
			this->x /= static_cast<T>(v.x);
			this->y /= static_cast<T>(v.y);
			return *this;
		};

		//Increment Decrement Operators
		inline constexpr TVector<2, T>& operator++()
		{
			++this->x;
			++this->y;
			return *this;
		};

		inline constexpr TVector<2, T>& operator--()
		{
			--this->x;
			--this->y;
			return *this;
		};
		
		inline constexpr TVector<2, T> operator++(int)
		{
			TVector<2, T> Result(*this);
			++* this;
			return Result;
		};
		
		inline constexpr TVector<2, T> operator--(int)
		{
			TVector<2, T> Result(*this);
			--* this;
			return Result;
		};

		//Unary Bit Operators
		template<typename U>
		inline constexpr TVector<2, T>& operator%=(U scalar)
		{
			this->x %= static_cast<T>(scalar);
			this->y %= static_cast<T>(scalar);
			return *this;
		};
		
		template<typename U>
		inline constexpr TVector<2, T>& operator%=(TVector<2, U> const& v)
		{
			this->x %= static_cast<T>(v.x);
			this->y %= static_cast<T>(v.y);
			return *this;
		};
		
		template<typename U>
		inline constexpr TVector<2, T>& operator&=(U scalar)
		{
			this->x &= static_cast<T>(scalar);
			this->y &= static_cast<T>(scalar);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<2, T>& operator&=(TVector<2, U> const& v)
		{
			this->x &= static_cast<T>(v.x);
			this->y &= static_cast<T>(v.y);
			return *this;
		};

		template<typename U>
		inline constexpr TVector<2, T>& operator|=(U scalar)
		{
			this->x |= static_cast<T>(scalar);
			this->y |= static_cast<T>(scalar);
			return *this;
		};
		
		template<typename U>
		inline constexpr TVector<2, T>& operator|=(TVector<2, U> const& v)
		{
			this->x |= static_cast<T>(v.x);
			this->y |= static_cast<T>(v.y);
			return *this;
		};
		
		template<typename U>
		inline constexpr TVector<2, T>& operator^=(U scalar)
		{
			this->x ^= static_cast<T>(scalar);
			this->y ^= static_cast<T>(scalar);
			return *this;
		};
		
		template<typename U>
		inline constexpr TVector<2, T>& operator^=(TVector<2, U> const& v)
		{
			this->x ^= static_cast<T>(v.x);
			this->y ^= static_cast<T>(v.y);
			return *this;
		};
		
		template<typename U>
		inline constexpr TVector<2, T>& operator<<=(U scalar)
		{
			this->x <<= static_cast<T>(scalar);
			this->y <<= static_cast<T>(scalar);
			return *this;
		};
		
		template<typename U>
		inline constexpr TVector<2, T>& operator<<=(TVector<2, U> const& v)
		{
			this->x <<= static_cast<T>(v.x);
			this->y <<= static_cast<T>(v.y);
			return *this;
		};
		
		template<typename U>
		inline constexpr TVector<2, T>& operator>>=(U scalar)
		{
			this->x >>= static_cast<T>(scalar);
			this->y >>= static_cast<T>(scalar);
			return *this;
		};
		
		template<typename U>
		inline constexpr TVector<2, T>& operator>>=(TVector<2, U> const& v)
		{
			this->x >>= static_cast<T>(v.x);
			this->y >>= static_cast<T>(v.y);
			return *this;
		};

		//Unary Operators
		inline constexpr TVector<2, T> operator+()
		{
			return TVector<2, T>(
				this->x,
				this->y);
		};
		
		inline constexpr TVector<2, T> operator-()
		{
			return TVector<2, T>(
				-this->x,
				-this->y);
		};

		//Binary Arithmetic Operators
		friend inline constexpr TVector<2, T> operator+(TVector<2, T> const& v, T scalar)
		{
			return TVector<2, T>(
				v.x + scalar,
				v.y + scalar);
		}

		friend inline constexpr TVector<2, T> operator+(T scalar, TVector<2, T> const& v)
		{
			return TVector<2, T>(
				scalar + v.x,
				scalar + v.y);
		}

		friend inline constexpr TVector<2, T> operator+(TVector<2, T> const& v1, TVector<2, T> const& v2)
		{
			return TVector<2, T>(
				v1.x + v2.x,
				v1.y + v2.y);
		}

		friend inline constexpr TVector<2, T> operator-(TVector<2, T> const& v, T scalar)
		{
			return TVector<2, T>(
				v.x - scalar,
				v.y - scalar);
		}

		friend inline constexpr TVector<2, T> operator-(T scalar, TVector<2, T> const& v)
		{
			return TVector<2, T>(
				scalar - v.x,
				scalar - v.y);
		}

		friend inline constexpr TVector<2, T> operator-(TVector<2, T> const& v1, TVector<2, T> const& v2)
		{
			return TVector<2, T>(
				v1.x - v2.x,
				v1.y - v2.y);
		}

		friend inline constexpr TVector<2, T> operator*(TVector<2, T> const& v, T scalar)
		{
			return TVector<2, T>(
				v.x * scalar,
				v.y * scalar);
		}

		friend inline constexpr TVector<2, T> operator*(T scalar, TVector<2, T> const& v)
		{
			return TVector<2, T>(
				scalar * v.x,
				scalar * v.y);
		}

		friend inline constexpr TVector<2, T> operator*(TVector<2, T> const& v1, TVector<2, T> const& v2)
		{
			return TVector<2, T>(
				v1.x * v2.x,
				v1.y * v2.y);
		}

		friend inline constexpr TVector<2, T> operator/(TVector<2, T> const& v, T scalar)
		{
			return TVector<2, T>(
				v.x / scalar,
				v.y / scalar);
		}

		friend inline constexpr TVector<2, T> operator/(T scalar, TVector<2, T> const& v)
		{
			return TVector<2, T>(
				scalar / v.x,
				scalar / v.y);
		}

		friend inline constexpr TVector<2, T> operator/(TVector<2, T> const& v1, TVector<2, T> const& v2)
		{
			return TVector<2, T>(
				v1.x / v2.x,
				v1.y / v2.y);
		}

		//Binary Bit Operators
		friend inline constexpr TVector<2, T> operator%(TVector<2, T> const& v, T scalar)
		{
			return TVector<2, T>(
				v.x % scalar,
				v.y % scalar);
		}

		friend inline constexpr TVector<2, T> operator%(T scalar, TVector<2, T> const& v)
		{
			return TVector<2, T>(
				scalar % v.x,
				scalar % v.y);
		}

		friend inline constexpr TVector<2, T> operator%(TVector<2, T> const& v1, TVector<2, T> const& v2)
		{
			return TVector<2, T>(
				v1.x % v2.x,
				v1.y % v2.y);
		}

		friend inline constexpr TVector<2, T> operator&(TVector<2, T> const& v, T scalar)
		{
			return TVector<2, T>(
				v.x & scalar,
				v.y & scalar);
		}

		friend inline constexpr TVector<2, T> operator&(T scalar, TVector<2, T> const& v)
		{
			return TVector<2, T>(
				scalar & v.x,
				scalar & v.y);
		}

		friend inline constexpr TVector<2, T> operator&(TVector<2, T> const& v1, TVector<2, T> const& v2)
		{
			return TVector<2, T>(
				v1.x & v2.x,
				v1.y & v2.y);
		}

		friend inline constexpr TVector<2, T> operator|(TVector<2, T> const& v, T scalar)
		{
			return TVector<2, T>(
				v.x | scalar,
				v.y | scalar);
		}

		friend inline constexpr TVector<2, T> operator|(T scalar, TVector<2, T> const& v)
		{
			return TVector<2, T>(
				scalar | v.x,
				scalar | v.y);
		}

		friend inline constexpr TVector<2, T> operator|(TVector<2, T> const& v1, TVector<2, T> const& v2)
		{
			return TVector<2, T>(
				v1.x | v2.x,
				v1.y | v2.y);
		}

		friend inline constexpr TVector<2, T> operator^(TVector<2, T> const& v, T scalar)
		{
			return TVector<2, T>(
				v.x ^ scalar,
				v.y ^ scalar);
		}

		friend inline constexpr TVector<2, T> operator^(T scalar, TVector<2, T> const& v)
		{
			return TVector<2, T>(
				scalar ^ v.x,
				scalar ^ v.y);
		}

		friend inline constexpr TVector<2, T> operator^(TVector<2, T> const& v1, TVector<2, T> const& v2)
		{
			return TVector<2, T>(
				v1.x ^ v2.x,
				v1.y ^ v2.y);
		}

		friend inline constexpr TVector<2, T> operator<<(TVector<2, T> const& v, T scalar)
		{
			return TVector<2, T>(
				v.x << scalar,
				v.y << scalar);
		}

		friend inline constexpr TVector<2, T> operator<<(T scalar, TVector<2, T> const& v)
		{
			return TVector<2, T>(
				scalar << v.x,
				scalar << v.y);
		}

		friend inline constexpr TVector<2, T> operator<<(TVector<2, T> const& v1, TVector<2, T> const& v2)
		{
			return TVector<2, T>(
				v1.x << v2.x,
				v1.y << v2.y);
		}

		friend inline constexpr TVector<2, T> operator>>(TVector<2, T> const& v, T scalar)
		{
			return TVector<2, T>(
				v.x >> scalar,
				v.y >> scalar);
		}

		friend inline constexpr TVector<2, T> operator>>(T scalar, TVector<2, T> const& v)
		{
			return TVector<2, T>(
				scalar >> v.x,
				scalar >> v.y);
		};

		friend inline constexpr TVector<2, T> operator>>(TVector<2, T> const& v1, TVector<2, T> const& v2)
		{
			return TVector<2, T>(
				v1.x >> v2.x,
				v1.y >> v2.y);
		};

		inline constexpr TVector<2, T> operator~()
		{
			return TVector<2, T>(
				~this->x,
				~this->y);
		};

		//Boolean Operators
		inline constexpr bool operator==(TVector<2, T> const& v)
		{
			return (this->x == v.x && this->y == v.y);
		};

		inline constexpr bool operator!=(TVector<2, T> const& v)
		{
			return !(this->x == v.x && this->y == v.y);
		};
	};

	//Type Definitions
	typedef TVector<2, float> Vector2;
	typedef TVector<2, double> dVector2;
	typedef TVector<2, int> iVector2;
	typedef TVector<2, unsigned int> uVector2;
}