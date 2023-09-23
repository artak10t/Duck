#pragma once
#include "Vector3.h"
#include "Matrix4.h"
#include "Quaternion.h"
#include "Trigonometry.h"

namespace Duck
{
	template<int L, typename T> struct TTransform;

	template<typename T>
	struct TTransform<3, T> final
	{
	private:
		//Cached Data
		TVector<3, T> cached_Position;
		TQuaternion<T> cached_Rotation;
		TVector<3, T> cached_Scale;
		TMatrix<4, 4, T> cached_LocalToWorld;

	public:
		//Data
		TVector<3, T> position;
		TQuaternion<T> rotation;
		TVector<3, T> scale;

		TTransform<3, T>* parent = NULL;

		//Constructors
		inline constexpr TTransform() : 
			position(0), 
			rotation(0, 0, 0, 1), 
			scale(1)
		{}

		inline constexpr TTransform(TTransform<3, T> const& t) :
			position(t.position),
			rotation(t.rotation),
			scale(t.scale)
		{}

		inline constexpr TTransform(TVector<3, T> const& p, TQuaternion<T> const& r, TVector<3, T> const& s) :
			position(p), 
			rotation(r), 
			scale(s)
		{}

		inline constexpr TTransform(TVector<3, T> const& p, TVector<3, T> const& r, TVector<3, T> const& s) :
			position(p),
			rotation(r),
			scale(s)
		{}

		//Unary Arithmetic Operators
		template<typename U>
		inline constexpr TTransform<3, T>& operator=(TTransform<3, U> const& t)
		{
			this->position = t.position;
			this->rotation = t.rotation;
			this->scale = t.scale;
			return *this;
		}

		//Matrices
		TMatrix<4, 4, T> LocalToWorld()
		{
			if (cached_Position != position || cached_Rotation != rotation || cached_Scale != scale)
			{
				TMatrix<4, 4, T> t = Matrix::Translate(TMatrix<4, 4, T>(), position);
				TMatrix<4, 4, T> r = Matrix::Rotate(TMatrix<4, 4, T>(), rotation);
				TMatrix<4, 4, T> s = Matrix::Scale(TMatrix<4, 4, T>(), scale);
				cached_Position = position;
				cached_Rotation = rotation;
				cached_Scale = scale;
				cached_LocalToWorld = t * r * s;
			}

			if (parent)
				return parent->LocalToWorld() * cached_LocalToWorld;

			return cached_LocalToWorld;
		}

		//Directions
		inline TVector<3, T> Right()
		{
			TMatrix<4, 4, T> m = LocalToWorld();
			TVector<3, T> v(m[0][0], m[0][1], m[0][2]);
			return v;
		}

		inline TVector<3, T> Up()
		{
			TMatrix<4, 4, T> m = LocalToWorld();
			TVector<3, T> v(m[1][0], m[1][1], m[1][2]);
			return v;
		}

		inline TVector<3, T> Forward()
		{
			TMatrix<4, 4, T> m = LocalToWorld();
			TVector<3, T> v(m[2][0], m[2][1], m[2][2]);
			return v;
		}
	};

	//Type Definitions
	typedef TTransform<3, float> Transform;
	typedef TTransform<3, double> dTransform;
}