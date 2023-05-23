#pragma once
#include "../pch.h"

#include "Matrix.h"
#include "Vector4.h"

namespace Duck
{
	template<typename T>
	struct TMatrix<4, 4, T> final
	{
	private:
		TVector<4, T> value[4];

	public:
		//Component Accesses
		inline constexpr TVector<4, T>& operator[](int i)
		{
			assert(i < 4);
			return this->value[i];
		};

		inline constexpr TVector<4, T> const& operator[](int i) const
		{
			assert(i < 4);
			return this->value[i];
		};

		//Constructors
		inline constexpr TMatrix()
			: value{ TVector<4, T>(1, 0, 0, 0), TVector<4, T>(0, 1, 0, 0), TVector<4, T>(0, 0, 1, 0), TVector<4, T>(0, 0, 0, 1) }
		{};

		inline constexpr TMatrix(TMatrix<4, 4, T> const& m)
			: value{ TVector<4, T>(m[0]), TVector<4, T>(m[1]), TVector<4, T>(m[2]), TVector<4, T>(m[3]) }
		{};

		inline constexpr TMatrix(T const& s)
			: value{ TVector<4, T>(s, 0, 0, 0), TVector<4, T>(0, s, 0, 0), TVector<4, T>(0, 0, s, 0), TVector<4, T>(0, 0, 0, s) }
		{};

		inline constexpr TMatrix
		(
			T const& x0, T const& y0, T const& z0, T const& w0,
			T const& x1, T const& y1, T const& z1, T const& w1,
			T const& x2, T const& y2, T const& z2, T const& w2,
			T const& x3, T const& y3, T const& z3, T const& w3
		)
			: value{
				TVector<4, T>(x0, y0, z0, w0),
				TVector<4, T>(x1, y1, z1, w1),
				TVector<4, T>(x2, y2, z2, w2),
				TVector<4, T>(x3, y3, z3, w3) }
		{};

		inline constexpr TMatrix(TVector<4, T> const& v0, TVector<4, T> const& v1, TVector<4, T> const& v2, TVector<4, T> const& v3)
			: value{ TVector<4, T>(v0), TVector<4, T>(v1), TVector<4, T>(v2), TVector<4, T>(v3) }
		{};

		template<typename U>
		inline constexpr TMatrix(TMatrix<4, 4, U> const& m)
			: value{ TVector<4, T>(m[0]), TVector<4, T>(m[1]), TVector<4, T>(m[2]), TVector<4, T>(m[3]) }
		{};

		//Conversions
		template<
			typename X1, typename Y1, typename Z1, typename W1,
			typename X2, typename Y2, typename Z2, typename W2,
			typename X3, typename Y3, typename Z3, typename W3,
			typename X4, typename Y4, typename Z4, typename W4>
			inline constexpr TMatrix
			(
				X1 const& x1, Y1 const& y1, Z1 const& z1, W1 const& w1,
				X2 const& x2, Y2 const& y2, Z2 const& z2, W2 const& w2,
				X3 const& x3, Y3 const& y3, Z3 const& z3, W3 const& w3,
				X4 const& x4, Y4 const& y4, Z4 const& z4, W4 const& w4
			)
			: value{ TVector<4, T>(x1, y1, z1, w1), TVector<4, T>(x2, y2, z2, w2), TVector<4, T>(x3, y3, z3, w3), TVector<4, T>(x4, y4, z4, w4) }
		{
			static_assert(std::numeric_limits<X1>::is_iec559 || std::numeric_limits<X1>::is_integer, "'Matrix4' constructor only takes float and integer types, 1st parameter type invalid.");
			static_assert(std::numeric_limits<Y1>::is_iec559 || std::numeric_limits<Y1>::is_integer, "'Matrix4' constructor only takes float and integer types, 2nd parameter type invalid.");
			static_assert(std::numeric_limits<Z1>::is_iec559 || std::numeric_limits<Z1>::is_integer, "'Matrix4' constructor only takes float and integer types, 3rd parameter type invalid.");
			static_assert(std::numeric_limits<W1>::is_iec559 || std::numeric_limits<W1>::is_integer, "'Matrix4' constructor only takes float and integer types, 4th parameter type invalid.");

			static_assert(std::numeric_limits<X2>::is_iec559 || std::numeric_limits<X2>::is_integer, "'Matrix4' constructor only takes float and integer types, 5th parameter type invalid.");
			static_assert(std::numeric_limits<Y2>::is_iec559 || std::numeric_limits<Y2>::is_integer, "'Matrix4' constructor only takes float and integer types, 6th parameter type invalid.");
			static_assert(std::numeric_limits<Z2>::is_iec559 || std::numeric_limits<Z2>::is_integer, "'Matrix4' constructor only takes float and integer types, 7th parameter type invalid.");
			static_assert(std::numeric_limits<W2>::is_iec559 || std::numeric_limits<W2>::is_integer, "'Matrix4' constructor only takes float and integer types, 8th parameter type invalid.");

			static_assert(std::numeric_limits<X3>::is_iec559 || std::numeric_limits<X3>::is_integer, "'Matrix4' constructor only takes float and integer types, 9th parameter type invalid.");
			static_assert(std::numeric_limits<Y3>::is_iec559 || std::numeric_limits<Y3>::is_integer, "'Matrix4' constructor only takes float and integer types, 10th parameter type invalid.");
			static_assert(std::numeric_limits<Z3>::is_iec559 || std::numeric_limits<Z3>::is_integer, "'Matrix4' constructor only takes float and integer types, 11th parameter type invalid.");
			static_assert(std::numeric_limits<W3>::is_iec559 || std::numeric_limits<W3>::is_integer, "'Matrix4' constructor only takes float and integer types, 12th parameter type invalid.");

			static_assert(std::numeric_limits<X4>::is_iec559 || std::numeric_limits<X4>::is_integer, "'Matrix4' constructor only takes float and integer types, 13th parameter type invalid.");
			static_assert(std::numeric_limits<Y4>::is_iec559 || std::numeric_limits<Y4>::is_integer, "'Matrix4' constructor only takes float and integer types, 14th parameter type invalid.");
			static_assert(std::numeric_limits<Z4>::is_iec559 || std::numeric_limits<Z4>::is_integer, "'Matrix4' constructor only takes float and integer types, 15th parameter type invalid.");
			static_assert(std::numeric_limits<W4>::is_iec559 || std::numeric_limits<W4>::is_integer, "'Matrix4' constructor only takes float and integer types, 16th parameter type invalid.");
		};

		template<typename V1, typename V2, typename V3, typename V4>
		inline constexpr TMatrix(TVector<4, V1> const& v1, TVector<4, V2> const& v2, TVector<4, V3> const& v3, TVector<4, V4> const& v4)
			: value{ TVector<4, T>(v1), TVector<4, T>(v2), TVector<4, T>(v3), TVector<4, T>(v4) }
		{
			static_assert(std::numeric_limits<V1>::is_iec559 || std::numeric_limits<V1>::is_integer, "'Matrix4' constructor only takes float and integer types, 1st parameter type invalid.");
			static_assert(std::numeric_limits<V2>::is_iec559 || std::numeric_limits<V2>::is_integer, "'Matrix4' constructor only takes float and integer types, 2nd parameter type invalid.");
			static_assert(std::numeric_limits<V3>::is_iec559 || std::numeric_limits<V3>::is_integer, "'Matrix4' constructor only takes float and integer types, 3rd parameter type invalid.");
			static_assert(std::numeric_limits<V4>::is_iec559 || std::numeric_limits<V4>::is_integer, "'Matrix4' constructor only takes float and integer types, 4th parameter type invalid.");
		};

		//Unary Arithmetic Operators
		template<typename U>
		inline TMatrix<4, 4, T>& operator=(TMatrix<4, 4, U> const& m)
		{
			this->value[0] = m[0];
			this->value[1] = m[1];
			this->value[2] = m[2];
			this->value[3] = m[3];
			return *this;
		};

		template<typename U>
		inline TMatrix<4, 4, T>& operator+=(U s)
		{
			this->value[0] += s;
			this->value[1] += s;
			this->value[2] += s;
			this->value[3] += s;
			return *this;
		};

		template<typename U>
		inline TMatrix<4, 4, T>& operator+=(TMatrix<4, 4, U> const& m)
		{
			this->value[0] += m[0];
			this->value[1] += m[1];
			this->value[2] += m[2];
			this->value[3] += m[3];
			return *this;
		};

		template<typename U>
		inline TMatrix<4, 4, T>& operator-=(U s)
		{
			this->value[0] -= s;
			this->value[1] -= s;
			this->value[2] -= s;
			this->value[3] -= s;
			return *this;
		};

		template<typename U>
		inline TMatrix<4, 4, T>& operator-=(TMatrix<4, 4, U> const& m)
		{
			this->value[0] -= m[0];
			this->value[1] -= m[1];
			this->value[2] -= m[2];
			this->value[3] -= m[3];
			return *this;
		};

		template<typename U>
		inline TMatrix<4, 4, T>& operator*=(U s)
		{
			this->value[0] *= s;
			this->value[1] *= s;
			this->value[2] *= s;
			this->value[3] *= s;
			return *this;
		};

		template<typename U>
		inline TMatrix<4, 4, T>& operator*=(TMatrix<4, 4, U> const& m)
		{
			return (*this = *this * m);
		};

		template<typename U>
		inline TMatrix<4, 4, T>& operator/=(U s)
		{
			this->value[0] /= s;
			this->value[1] /= s;
			this->value[2] /= s;
			this->value[3] /= s;
			return *this;
		};

		template<typename U>
		inline TMatrix<4, 4, T>& operator/=(TMatrix<4, 4, U> const& m)
		{
			static_assert(std::numeric_limits<T>::is_iec559, "'Inverse' only accept floating-point inputs");
			return *this *= Inverse(m);
		};

		//Increment Decrement Operators
		inline TMatrix<4, 4, T>& operator++()
		{
			++this->value[0];
			++this->value[1];
			++this->value[2];
			++this->value[3];
			return *this;
		};

		inline TMatrix<4, 4, T>& operator--()
		{
			--this->value[0];
			--this->value[1];
			--this->value[2];
			--this->value[3];
			return *this;
		};

		inline TMatrix<4, 4, T> operator++(int)
		{
			TMatrix<4, 4, T> Result(*this);
			++* this;
			return Result;
		};

		inline TMatrix<4, 4, T> operator--(int)
		{
			TMatrix<4, 4, T> Result(*this);
			--* this;
			return Result;
		};

		//Unary Operators
		inline TMatrix<4, 4, T> operator+()
		{
			return TMatrix<4, 4, T>(
				this[0],
				this[1],
				this[2],
				this[3]);
		};

		inline TMatrix<4, 4, T> operator-()
		{
			return TMatrix<4, 4, T>(
				-this[0],
				-this[1],
				-this[2],
				-this[3]);
		};

		//Binary Arithmetic Operators
		friend inline TMatrix<4, 4, T> operator+(TMatrix<4, 4, T> const& m, T const& s)
		{
			return TMatrix<4, 4, T>(
				m[0] + s,
				m[1] + s,
				m[2] + s,
				m[3] + s);
		}

		friend inline TMatrix<4, 4, T> operator+(T const& s, TMatrix<4, 4, T> const& m)
		{
			return TMatrix<4, 4, T>(
				m[0] + s,
				m[1] + s,
				m[2] + s,
				m[3] + s);
		}

		friend inline TMatrix<4, 4, T> operator+(TMatrix<4, 4, T> const& m1, TMatrix<4, 4, T> const& m2)
		{
			return TMatrix<4, 4, T>(
				m1[0] + m2[0],
				m1[1] + m2[1],
				m1[2] + m2[2],
				m1[3] + m2[3]);
		}

		friend inline TMatrix<4, 4, T> operator-(TMatrix<4, 4, T> const& m, T const& s)
		{
			return TMatrix<4, 4, T>(
				m[0] - s,
				m[1] - s,
				m[2] - s,
				m[3] - s);
		}

		friend inline TMatrix<4, 4, T> operator-(T const& s, TMatrix<4, 4, T> const& m)
		{
			return TMatrix<4, 4, T>(
				s - m[0],
				s - m[1],
				s - m[2],
				s - m[3]);
		}

		friend inline TMatrix<4, 4, T> operator-(TMatrix<4, 4, T> const& m1, TMatrix<4, 4, T> const& m2)
		{
			return TMatrix<4, 4, T>(
				m1[0] - m2[0],
				m1[1] - m2[1],
				m1[2] - m2[2],
				m1[3] - m2[3]);
		}

		friend inline TMatrix<4, 4, T> operator*(TMatrix<4, 4, T> const& m, T const& s)
		{
			return TMatrix<4, 4, T>(
				m[0] * s,
				m[1] * s,
				m[2] * s,
				m[3] * s);
		}

		friend inline TMatrix<4, 4, T> operator*(T const& s, TMatrix<4, 4, T> const& m)
		{
			return TMatrix<4, 4, T>(
				m[0] * s,
				m[1] * s,
				m[2] * s,
				m[3] * s);
		}

		friend inline TVector<4, T> operator*(TMatrix<4, 4, T> const& m, TVector<4, T> const& v)
		{
			TVector<4, T> const Mov0(v[0]);
			TVector<4, T> const Mov1(v[1]);
			TVector<4, T> const Mul0 = m[0] * Mov0;
			TVector<4, T> const Mul1 = m[1] * Mov1;
			TVector<4, T> const Add0 = Mul0 + Mul1;
			TVector<4, T> const Mov2(v[2]);
			TVector<4, T> const Mov3(v[3]);
			TVector<4, T> const Mul2 = m[2] * Mov2;
			TVector<4, T> const Mul3 = m[3] * Mov3;
			TVector<4, T> const Add1 = Mul2 + Mul3;
			TVector<4, T> const Add2 = Add0 + Add1;
			return Add2;
		}

		friend inline TVector<4, T> operator*(TVector<4, T> const& v, TMatrix<4, 4, T> const& m)
		{
			return TVector<4, T>(
				m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2] + m[0][3] * v[3],
				m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2] + m[1][3] * v[3],
				m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2] + m[2][3] * v[3],
				m[3][0] * v[0] + m[3][1] * v[1] + m[3][2] * v[2] + m[3][3] * v[3]);
		}

		friend inline TMatrix<4, 4, T> operator*(TMatrix<4, 4, T> const& m1, TMatrix<4, 4, T> const& m2)
		{
			TVector<4, T> const SrcA0 = m1[0];
			TVector<4, T> const SrcA1 = m1[1];
			TVector<4, T> const SrcA2 = m1[2];
			TVector<4, T> const SrcA3 = m1[3];

			TVector<4, T> const SrcB0 = m2[0];
			TVector<4, T> const SrcB1 = m2[1];
			TVector<4, T> const SrcB2 = m2[2];
			TVector<4, T> const SrcB3 = m2[3];

			TMatrix<4, 4, T> Result;
			Result[0] = SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1] + SrcA2 * SrcB0[2] + SrcA3 * SrcB0[3];
			Result[1] = SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1] + SrcA2 * SrcB1[2] + SrcA3 * SrcB1[3];
			Result[2] = SrcA0 * SrcB2[0] + SrcA1 * SrcB2[1] + SrcA2 * SrcB2[2] + SrcA3 * SrcB2[3];
			Result[3] = SrcA0 * SrcB3[0] + SrcA1 * SrcB3[1] + SrcA2 * SrcB3[2] + SrcA3 * SrcB3[3];
			return Result;
		}

		friend inline TMatrix<4, 4, T> operator/(TMatrix<4, 4, T> const& m, T const& s)
		{
			return TMatrix<4, 4, T>(
				m[0] / s,
				m[1] / s,
				m[2] / s,
				m[3] / s);
		}

		friend inline TMatrix<4, 4, T> operator/(T const& s, TMatrix<4, 4, T> const& m)
		{
			return TMatrix<4, 4, T>(
				s / m[0],
				s / m[1],
				s / m[2],
				s / m[3]);
		}

		friend inline TVector<4, T> operator/(TMatrix<4, 4, T> const& m, TVector<4, T> const& v)
		{
			static_assert(std::numeric_limits<T>::is_iec559, "'Inverse' only accept floating-point inputs");
			return Inverse(m) * v;
		}

		friend inline TVector<4, T> operator/(TVector<4, T> const& v, TMatrix<4, 4, T> const& m)
		{
			static_assert(std::numeric_limits<T>::is_iec559, "'Inverse' only accept floating-point inputs");
			return v * Inverse(m);
		}

		friend inline TMatrix<4, 4, T> operator/(TMatrix<4, 4, T> const& m1, TMatrix<4, 4, T> const& m2)
		{
			TMatrix<4, 4, T> m1_copy(m1);
			return m1_copy /= m2;
		}

		//Boolean Operators
		inline bool operator==(TMatrix<4, 4, T> const& m)
		{
			return (this[0] == m[0]) && (this[1] == m[1]) && (this[2] == m[2]) && (this[3] == m[3]);
		}

		inline bool operator!=(TMatrix<4, 4, T> const& m)
		{
			return (this[0] != m[0]) || (this[1] != m[1]) || (this[2] != m[2]) || (this[3] != m[3]);
		}
	};

	//Type Definitions
	typedef TMatrix<4, 4, float> Matrix4;
	typedef TMatrix<4, 4, double> dMatrix4;
}