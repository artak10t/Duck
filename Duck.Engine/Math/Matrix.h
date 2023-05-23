#pragma once
#include "../pch.h"

#include "Vector.h"
#include "Quaternion.h"
#include "Trigonometry.h"

namespace Duck
{
	template<int C, int R, typename T> struct TMatrix;

	//Methods
	namespace Matrix 
	{
		//Inverse
		template<typename T>
		inline TMatrix<4, 4, T> Inverse(TMatrix<4, 4, T> const& m)
		{
			T Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
			T Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
			T Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

			T Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
			T Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
			T Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

			T Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
			T Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
			T Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

			T Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
			T Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
			T Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

			T Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
			T Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
			T Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

			T Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
			T Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
			T Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

			TVector<4, T> Fac0(Coef00, Coef00, Coef02, Coef03);
			TVector<4, T> Fac1(Coef04, Coef04, Coef06, Coef07);
			TVector<4, T> Fac2(Coef08, Coef08, Coef10, Coef11);
			TVector<4, T> Fac3(Coef12, Coef12, Coef14, Coef15);
			TVector<4, T> Fac4(Coef16, Coef16, Coef18, Coef19);
			TVector<4, T> Fac5(Coef20, Coef20, Coef22, Coef23);

			TVector<4, T> Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
			TVector<4, T> Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
			TVector<4, T> Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
			TVector<4, T> Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

			TVector<4, T> Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
			TVector<4, T> Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
			TVector<4, T> Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
			TVector<4, T> Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

			TVector<4, T> SignA(+1, -1, +1, -1);
			TVector<4, T> SignB(-1, +1, -1, +1);
			TMatrix<4, 4, T> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

			TVector<4, T> Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);

			TVector<4, T> Dot0(m[0] * Row0);
			T Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

			T OneOverDeterminant = static_cast<T>(1) / Dot1;

			return Inverse * OneOverDeterminant;
		}

		//Translate
		template<typename T>
		inline TMatrix<4, 4, T> Translate(TMatrix<4, 4, T> const& m, TVector<3, T> const& v)
		{
			TMatrix<4, 4, T> Result(m);
			Result[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
			return Result;
		}

		//Rotate
		template<typename T>
		inline TMatrix<4, 4, T> Rotate(TMatrix<4, 4, T> const& m, T angle, TVector<3, T> const& v)
		{
			T const a = angle;
			T const c = std::cos(a);
			T const s = std::sin(a);

			TVector<3, T> axis(Vector::Normalize(v));
			TVector<3, T> temp((T(1) - c) * axis);

			TMatrix<4, 4, T> Rotate;
			Rotate[0][0] = c + temp[0] * axis[0];
			Rotate[0][1] = temp[0] * axis[1] + s * axis[2];
			Rotate[0][2] = temp[0] * axis[2] - s * axis[1];

			Rotate[1][0] = temp[1] * axis[0] - s * axis[2];
			Rotate[1][1] = c + temp[1] * axis[1];
			Rotate[1][2] = temp[1] * axis[2] + s * axis[0];

			Rotate[2][0] = temp[2] * axis[0] + s * axis[1];
			Rotate[2][1] = temp[2] * axis[1] - s * axis[0];
			Rotate[2][2] = c + temp[2] * axis[2];

			TMatrix<4, 4, T> Result;
			Result[0] = m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2];
			Result[1] = m[0] * Rotate[1][0] + m[1] * Rotate[1][1] + m[2] * Rotate[1][2];
			Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
			Result[3] = m[3];
			return Result;
		}

		template<typename T>
		inline TMatrix<4, 4, T> Rotate(TMatrix<4, 4, T> const& m, TQuaternion<T> const& q)
		{
			T qxx(q.x * q.x);
			T qyy(q.y * q.y);
			T qzz(q.z * q.z);
			T qxz(q.x * q.z);
			T qxy(q.x * q.y);
			T qyz(q.y * q.z);
			T qwx(q.w * q.x);
			T qwy(q.w * q.y);
			T qwz(q.w * q.z);

			TMatrix<4, 4, T> Rotate;
			Rotate[0][0] = (T(1) - T(2) * (qyy + qzz));
			Rotate[0][1] = T(2) * (qxy + qwz);
			Rotate[0][2] = T(2) * (qxz - qwy);

			Rotate[1][0] = T(2) * (qxy - qwz);
			Rotate[1][1] = T(1) - T(2) * (qxx + qzz);
			Rotate[1][2] = T(2) * (qyz + qwx);

			Rotate[2][0] = T(2) * (qxz + qwy);
			Rotate[2][1] = T(2) * (qyz - qwx);
			Rotate[2][2] = T(1) - T(2) * (qxx + qyy);

			TMatrix<4, 4, T> Result(T(1));
			Result[0] = m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2];
			Result[1] = m[0] * Rotate[1][0] + m[1] * Rotate[1][1] + m[2] * Rotate[1][2];
			Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
			Result[3] = m[3];
			return Result;
		}

		//Scale
		template<typename T>
		inline TMatrix<4, 4, T> Scale(TMatrix<4, 4, T> const& m, TVector<3, T> const& v)
		{
			TMatrix<4, 4, T> Result;
			Result[0] = m[0] * v[0];
			Result[1] = m[1] * v[1];
			Result[2] = m[2] * v[2];
			Result[3] = m[3];
			return Result;
		}

		//Orthographic Projection LH Coordinates
		template<typename T>
		inline TMatrix<4, 4, T> Orthographic(T left, T right, T bottom, T top, T zNear, T zFar)
		{
			TMatrix<4, 4, T> Result(1);
			Result[0][0] = static_cast<T>(2) / (right - left);
			Result[1][1] = static_cast<T>(2) / (top - bottom);
			Result[2][2] = static_cast<T>(2) / (zFar - zNear);
			Result[3][0] = -(right + left) / (right - left);
			Result[3][1] = -(top + bottom) / (top - bottom);
			Result[3][2] = -(zFar + zNear) / (zFar - zNear);
			return Result;
		}

		//Perspective Projection LH Coordinates
		template<typename T>
		inline TMatrix<4, 4, T> Perspective(T fovy, T aspect, T zNear, T zFar)
		{
			assert(std::abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));

			T const tanHalfFovy = std::tan(fovy / static_cast<T>(2));

			TMatrix<4, 4, T> Result(static_cast<T>(0));
			Result[0][0] = static_cast<T>(1) / (aspect * tanHalfFovy);
			Result[1][1] = static_cast<T>(1) / (tanHalfFovy);
			Result[2][2] = (zFar + zNear) / (zFar - zNear);
			Result[2][3] = static_cast<T>(1);
			Result[3][2] = -(static_cast<T>(2) * zFar * zNear) / (zFar - zNear);
			return Result;
		}
	}
}