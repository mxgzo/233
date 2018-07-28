#pragma once
#include<math.h>

namespace myMath
{

#define PI 3.141592653

#define float4 Vector4<float>
#define float3 Vector3<float>
	

	template <typename T>
	struct Vector3
	{
		T x, y, z;

		/************************构造函数***********************/
		Vector3() :
			x(T(0)),
			y(T(0)),
			z(T(0))
		{};
		template<typename U, typename V, typename Z>
		Vector3(U v1, V v2, Z v3) :
			x(T(v1)),
			y(T(v2)),
			z(T(v3))
		{}


		template <typename U>
		Vector3(Vector3<U> v) :
			x(T(v.x)),
			y(T(v.y)),
			z(T(v.z))
		{}
		/************************END构造函数***********************/


		/**************************************************旋转**************************************************/
		template <typename U>
		Vector3<T> rotateX(U angle)
		{
			Vector3<T> res(this->x, this->y, this->z);
			float a = (float(angle) / 180.0*PI);
			T c = cos(a);
			T s = sin(a);

			res.y = y * c - z * s;
			res.z = z * c + y * s;
			return res;
		}

		template <typename U>
		Vector3<T> rotateY(U angle)
		{
			Vector3<T> res(this->x, this->y, this->z);
			float a = (float(angle) / 180.0*PI);
			T c = cos(a);
			T s = sin(a);

			res.x = x * c + z * s;
			res.z = z * c - x * s;
			return res;

		}

		template <typename U>
		Vector3<T> rotateZ(U angle)
		{

			Vector3<T> res(this->x, this->y, this->z);
			float a = (float(angle) / 180.0*PI);
			T c = cos(a);
			T s = sin(a);

			res.x = x * c - y * s;
			res.y = x * s + y * c;
			return res;
		}
		/*******************END*******************/
		/*******************旋转*******************/


		/****************重载加减乘除等运算符****************/

		Vector3<T>& operator= (Vector3<T> const & v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			return *this;
		}
		template <typename U>
		Vector3<T>& operator= (Vector3<U> const & v)
		{
			this->x = T(v.x);
			this->y = T(v.y);
			this->z = T(v.z);
			return *this;
		}

		template <typename U>
		Vector3<T> operator+(U const & s)
		{
			return Vector3<T>(
				x + T(s),
				y + T(s),
				z + T(s));
		}

		template <typename T>
		friend Vector3<T> operator+ (T const & s, Vector3<T> const & v)
		{
			return Vector3<T>(
				T(s) + v.x,
				T(s) + v.y,
				T(s) + v.z);
		}

		template <typename T>
		friend Vector3<T> operator+ (Vector3<T> const & v1, Vector3<T> const & v2)
		{
			return Vector3<T>(
				v1.x + T(v2.x),
				v1.y + T(v2.y),
				v1.z + T(v2.z));
		}

		template <typename U>
		Vector3<T> operator- (U const & s)
		{
			return Vector3<T>(
				x - T(s),
				y - T(s),
				z - T(s));
		}

		template <typename T>
		friend Vector3<T> operator- (T const & s, Vector3<T> const & v)
		{
			return Vector3<T>(
				T(s) - v.x,
				T(s) - v.y,
				T(s) - v.z);
		}


		Vector3<T> operator- (Vector3<T> const & v)
		{
			return Vector3<T>(
				x - T(v.x),
				y - T(v.y),
				z - T(v.z));
		}

		template <typename U>
		Vector3<T> operator*(U const & s)
		{
			return Vector3<T>(
				x * T(s),
				y * T(s),
				z * T(s));
		}

		template <typename T>
		friend Vector3<T> operator* (T const & s, Vector3<T> const & v)
		{
			return Vector3<T>(
				T(s) * v.x,
				T(s) * v.y,
				T(s) * v.z);
		}

		//数量积
		template <typename U>
		 Vector3<T> operator* ( Vector3<U> const & v)
		{
			return Vector3<T>(
				x * T(v.x),
				y * T(v.y),
				z * T(v.z));
		}
		//向量积
		template <typename U>
		friend Vector3<U> vectorX(Vector3<U> const & v1, Vector3<U> const & v2)
		{
			return Vector3<U>(
				v1.y*v2.z - v1.z*v2.y,
				v1.z*v2.x - v1.x*v2.z,
				v1.x*v2.y - v1.y*v2.x);
		}

		template <typename U>
		Vector3<T> operator/ (U const & s)
		{
			return Vector3<T>(
				v.x / T(s),
				v.y / T(s),
				v.z / T(s));
		}

		template <typename T>
		friend Vector3<T> operator/ (T const & s, Vector3<T> const & v)
		{
			return Vector3<T>(
				T(s) / v.x,
				T(s) / v.y,
				T(s)a / v.z);
		}




		Vector3<T> operator- ()
		{
			return Vector3<T>(
				-x,
				-y,
				-z);
		}
		/***********************END***********************/
		/****************重载加减乘除运算符****************/
		T    length() const
		{
			return (T)sqrtf(x * x + y * y + z * z);
		}
		Vector3<T>& normalize()
		{

			this->x = this->x * ((float)1.0 / this->length());
			this->y = this->y * ((float)1.0 / this->length());
			this->z = this->z * ((float)1.0 / this->length());
			return *this;
		}
	};


	template <typename T>
	struct Vector4
	{


		T x, y, z, w;

		T & operator[](int i)
		{
			return (&x)[i];
		}
		T const& operator[](int i)const
		{
			return (&x)[i];
		}
		/***********************构造函数***********************/
		Vector4() :
			x(T(0)),
			y(T(0)),
			z(T(0)),
			w(T(0))
		{}
		template<typename U1, typename U2>
		Vector4(Vector3<U1> const& v, U2 s) :
			x(T(v.x)),
			y(T(v.y)),
			z(T(v.z)),
			w(T(s))
		{}
		template<typename U>
		Vector4(U s) :
			x(T(s)),
			y(T(s)),
			z(T(s)),
			w(T(s))
		{}
		template<typename U>
		Vector4(Vector4<U> const & v) :
			x(T(v.x)),
			y(T(v.y)),
			z(T(v.z)),
			w(T(v.w))
		{}


		template<typename U1, typename U2, typename U3, typename U4>
		Vector4(U1 s1, U2 s2, U3 s3, U4 s4) :
			x(T(s1)),
			y(T(s2)),
			z(T(s3)),
			w(T(s4))
		{}
		/****************************END构造函数*******************************/


		/***************************运算符重载**************************/
		template <typename U>
		Vector4<T> & operator= (Vector4<U> const & v)
		{
			this->x = T(v.x);
			this->y = T(v.y);
			this->z = T(v.z);
			this->w = T(v.w);
			return *this;
		}
		template <typename U>
		Vector4<T> operator+ (U const & s)
		{
			return Vector4<T>(
				x + T(s),
				y + T(s),
				z + T(s),
				w + T(s));
		}

		template <typename U1, typename U2>
		friend Vector4<T> operator+ (U1 const & s, Vector4<U2> const & v)
		{
			return Vector4<T>(
				s + v.x,
				s + v.y,
				s + v.z,
				s + v.w);
		}

		template <typename U>
		Vector4<T> operator+ (Vector4<U> const & v)
		{
			return Vector4<T>(
				x + v.x,
				y + v.y,
				z + v.z,
				w + v.w);
		}

		template <typename U>
		Vector4<T> operator- (U const & s)
		{
			return Vector4<T>(
				x - T(s),
				y - T(s),
				z - T(s),
				w - T(s));
		}

		template <typename U1, typename U2>
		friend Vector4<T> operator-  (U1 const & s, Vector4<U2> const & v)
		{
			return Vector4<T>(
				s - v.x,
				s - v.y,
				s - v.z,
				s - v.w);
		}

		template <typename U>
		Vector4<T> operator-(Vector4<U> const & v)
		{
			return Vector4<T>(
				x - v.x,
				y - v.y,
				z - v.z,
				w - v.w);
		}

		template <typename U>
		Vector4<T> operator* (U const & s)
		{
			return Vector4<T>(
				x * T(s),
				y * T(s),
				z * T(s),
				w * T(s));
		}

		template <typename U1, typename U2>
		friend Vector4<T> operator* (U1 const & s, Vector4<U2> const & v)
		{
			return Vector4<T>(
				s * v.x,
				s * v.y,
				s * v.z,
				s * v.w);
		}

		template <typename U1, typename U2>
		friend Vector4<T> operator*(Vector4<U1> const & v1, Vector4<U2> const & v2)
		{
			return Vector4<T>(
				v1.x * v2.x,
				v1.y * v2.y,
				v1.z * v2.z,
				v1.w * v2.w);
		}
		/***************************END运算符重载**************************/

	};


	template <typename T>
	struct Matrix4
	{
	private:
		Vector4<T>    value[4];
	public:
		void identify()
		{
			this->value[0] = Vector4<T>(1, 0, 0, 0);
			this->value[1] = Vector4<T>(0, 1, 0, 0);
			this->value[2] = Vector4<T>(0, 0, 1, 0);
			this->value[3] = Vector4<T>(0, 0, 0, 1);
		}
		Vector4<T> & operator[](int i)
		{
			return this->value[i];
		}
		Vector4<T> const & operator[](int i)const
		{
			return this->value[i];
		}
/********************构造函数************************/
		Matrix4()
		{
		}
		//生成投影矩阵
		Matrix4(float fovy, float aspect, float zNear, float zFar)
		{
			Matrix4();
			float range = tan(fovy *0.0087266462583) * zNear;//0.0087266462583=float(3.1415926/180.0*(0.5))
			float left = -range * aspect;
			float right = range * aspect;
			float bottom = -range;
			float top = range;
			this->value[0][0] = (2.0 * zNear) / (right - left);
			this->value[1][1] = (2.0 * zNear) / (top - bottom);
			this->value[2][2] = -(zFar + zNear) / (zFar - zNear);
			this->value[2][3] = -1.0;
			this->value[3][2] = -(2.0 * zFar * zNear) / (zFar - zNear);
		}
		Matrix4(float3   eye, float3  center, float3  up)
		{
			float3 f = (center - eye).normalize();
			float3 u = up.normalize();
			float3 s = vectorX(f, u).normalize();
			u = vectorX(s, f).normalize();

			 Matrix4();
			this->value[0][0] = s.x;
			this->value[1][0] = s.y;
			this->value[2][0] = s.z;
			this->value[0][1] = u.x;
			this->value[1][1] = u.y;
			this->value[2][1] = u.z;
			this->value[0][2] = -f.x;
			this->value[1][2] = -f.y;
			this->value[2][2] = -f.z;
			this->value[3][0] = -((s * eye).x + (s * eye).y + (s * eye).z);
			this->value[3][1] = -((u * eye).x + (u * eye).y + (u * eye).z);
			this->value[3][2] = (f * eye).x + (f * eye).y + (f * eye).z;
			this->value[3][3] = 1;
		}

		Matrix4
		(
			T const & x0, T const & y0, T const & z0, T const & w0,
			T const & x1, T const & y1, T const & z1, T const & w1,
			T const & x2, T const & y2, T const & z2, T const & w2,
			T const & x3, T const & y3, T const & z3, T const & w3
		)
		{
			this->value[0] = Vector4<T>(x0, y0, z0, w0);
			this->value[1] = Vector4<T>(x1, y1, z1, w1);
			this->value[2] = Vector4<T>(x2, y2, z2, w2);
			this->value[3] = Vector4<T>(x3, y3, z3, w3);
		}

		Matrix4
		(
			Vector4<T> const & v0,
			Vector4<T> const & v1,
			Vector4<T> const & v2,
			Vector4<T> const & v3
		)
		{
			this->value[0] = v0;
			this->value[1] = v1;
			this->value[2] = v2;
			this->value[3] = v3;
		}

		template <typename U>
		Matrix4(Matrix4<U> const & m)
		{
			this->value[0] = Vector4<T>(m[0]);
			this->value[1] = Vector4<T>(m[1]);
			this->value[2] = Vector4<T>(m[2]);
			this->value[3] = Vector4<T>(m[3]);
		}

		template <typename U>
		Matrix4(U const & s)
		{
			this->value[0] = Vector4<T>(T(s), T(0), T(0), T(0));
			this->value[1] = Vector4<T>(T(0), T(s), T(0), T(0));
			this->value[2] = Vector4<T>(T(0), T(0), T(s), T(0));
			this->value[3] = Vector4<T>(T(0), T(0), T(0), T(s));
		}
		template <
			typename X1, typename Y1, typename Z1, typename W1,
			typename X2, typename Y2, typename Z2, typename W2,
			typename X3, typename Y3, typename Z3, typename W3,
			typename X4, typename Y4, typename Z4, typename W4>
			Matrix4
			(
				X1 const & x1, Y1 const & y1, Z1 const & z1, W1 const & w1,
				X2 const & x2, Y2 const & y2, Z2 const & z2, W2 const & w2,
				X3 const & x3, Y3 const & y3, Z3 const & z3, W3 const & w3,
				X4 const & x4, Y4 const & y4, Z4 const & z4, W4 const & w4
			)
		{
			this->value[0] = Vector4<T>(T(x1), T(y1), T(z1), T(w1));
			this->value[1] = Vector4<T>(T(x2), T(y2), T(z2), T(w2));
			this->value[2] = Vector4<T>(T(x3), T(y3), T(z3), T(w3));
			this->value[3] = Vector4<T>(T(x4), T(y4), T(z4), T(w4));
		}
		template <typename V1, typename V2, typename V3, typename V4>
		Matrix4
		(
			Vector4<V1> const & v1,
			Vector4<V2> const & v2,
			Vector4<V3> const & v3,
			Vector4<V4> const & v4
		)
		{
			this->value[0] = Vector4<T>(v1);
			this->value[1] = Vector4<T>(v2);
			this->value[2] = Vector4<T>(v3);
			this->value[3] = Vector4<T>(v4);
		}

/**************************END构造函数*********************************/

/***************************运算符重载********************************/

		template <typename U>
		Matrix4<T>& operator= (Matrix4<U> const & m)
		{
			this->value[0] = m[0];
			this->value[1] = m[1];
			this->value[2] = m[2];
			this->value[3] = m[3];
			return *this;
		}
		template <typename U>
		Matrix4<T> operator* (Matrix4<U> const & m)
		{

			Matrix4<T> res;
			res[0] = value[0] * m[0][0] + value[1] * m[0][1] + value[2] * m[0][2] + value[3] * m[0][3];
			res[1] = value[0] * m[1][0] + value[1] * m[1][1] + value[2] * m[1][2] + value[3] * m[1][3];
			res[2] = value[0] * m[2][0] + value[1] * m[2][1] + value[2] * m[2][2] + value[3] * m[2][3];
			res[3] = value[0] * m[3][0] + value[1] * m[3][1] + value[2] * m[3][2] + value[3] * m[3][3];
			return res;
		}
		template <typename U>
		Vector3<T> operator * (Vector3<U> const& v)
		{
			return  Vector3<T>
				(
					(T)v.x*this->value[0][0] + (T)v.y*this->value[1][0] + (T)v.z*this->value[2][0] + 1 * this->value[3][0],
					(T)v.x*this->value[0][1] + (T)v.y*this->value[1][1] + (T)v.z*this->value[2][1] + 1 * this->value[3][1],
					(T)v.x*this->value[0][2] + (T)v.y*this->value[1][2] + (T)v.z*this->value[2][2] + 1 * this->value[3][2]
					);
		}
		Vector4<T> operator* (Vector4<T> const & v)
		{
			return Vector4<T>(
				this->value[0][0] * v.x + this->value[1][0] * v.y + this->value[2][0] * v.z + this->value[3][0] * v.w,
				this->value[0][1] * v.x + this->value[1][1] * v.y + this->value[2][1] * v.z + this->value[3][1] * v.w,
				this->value[0][2] * v.x + this->value[1][2] * v.y + this->value[2][2] * v.z + this->value[3][2] * v.w,
				this->value[0][3] * v.x + this->value[1][3] * v.y + this->value[2][3] * v.z + this->value[3][3] * v.w);
		}
		template <typename U>
		friend Vector4<T> operator* (Vector4<U> const & v, Matrix4<T> const & m)
		{
			return 	Vector4<T>(
				m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
				m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
				m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
				m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w);
		}
		template <typename U>
		Matrix4<T> operator* (U s)
		{
			return Matrix4<T>(
				this->value[0] * s,
				this->value[1] * s,
				this->value[2] * s,
				this->value[3] * s);
		}
		template <typename U>
		Matrix4<T> operator- (Matrix4<U> const & m)
		{
			return Matrix4<T>(
				this->value[0] - m[0],
				this->value[1] - m[1],
				this->value[2] - m[2],
				this->value[3] - m[3]);
		}
		template <typename U>
		friend Matrix4<T> operator- (U s, Matrix4<T> const & m)
		{
			return Matrix4<T>(
				s - m[0],
				s - m[1],
				s - m[2],
				s - m[3]);
		}
		template <typename U>
		Matrix4<T> operator- (U s)
		{
			return Matrix4<T>(
				this->value[0] - s,
				this->value[1] - s,
				this->value[2] - s,
				this->value[3] - s);
		}
		template <typename U>
		Matrix4<T> operator+ (Matrix4<U> const & m)
		{
			return Matrix4<T>(
				this->value[0] + m[0],
				this->value[1] + m[1],
				this->value[2] + m[2],
				this->value[3] + m[3]);
		}
		template <typename U>
		Matrix4<T> operator+ (U s)
		{
			return Matrix4<T>(
				this->value[0] + s,
				this->value[1] + s,
				this->value[2] + s,
				this->value[3] + s);
		}
		template <typename U>
		friend Matrix4<T> operator+ (U s, Matrix4<T> const & m)
		{
			return Matrix4<T>(
				m[0] + s,
				m[1] + s,
				m[2] + s,
				m[3] + s);
		}
	/*************************************END运算符重载*************************************/

/***************************************旋转变换*****************************************/
		template<typename U>
		Matrix4<T>& translate(U x, U y, U z)
		{
			Matrix4<T> mat( 1, 0, 0, 0,
							0, 1, 0, 0,
							0, 0, 1, 0,
							x, y, z, 1);

			this->value[0] = mat.value[0] * this->value[0][0] + mat.value[1] * this->value[0][1] +
							 mat.value[2] * this->value[0][2] + mat.value[3] * this->value[0][3];

			this->value[1] = mat.value[0] * this->value[1][0] + mat.value[1] * this->value[1][1] +
							 mat.value[2] * this->value[1][2] + mat.value[3] * this->value[1][3];

			this->value[2] = mat.value[0] * this->value[2][0] + mat.value[1] * this->value[2][1] +
						  	 mat.value[2] * this->value[2][2] + mat.value[3] * this->value[2][3];
				
			this->value[3] = mat.value[0] * this->value[3][0] + mat.value[1] * this->value[3][1] +
							 mat.value[2] * this->value[3][2] + mat.value[3] * this->value[3][3];
			return  *this;
		}


		template<typename U>
		Matrix4<T>& translate(Vector3<U> const& pos)
		{

			Matrix4<T> mat( 1, 0, 0, 0,
							0, 1, 0, 0,
							0, 0, 1, 0,
							pos.x, pos.y, pos.z, 1);
			this->value[0] = mat.value[0] * this->value[0][0] + mat.value[1] * this->value[0][1] +
							 mat.value[2] * this->value[0][2] + mat.value[3] * this->value[0][3];

			this->value[1] = mat.value[0] * this->value[1][0] + mat.value[1] * this->value[1][1] +
							 mat.value[2] * this->value[1][2] + mat.value[3] * this->value[1][3];

			this->value[2] = mat.value[0] * this->value[2][0] + mat.value[1] * this->value[2][1] +
							 mat.value[2] * this->value[2][2] + mat.value[3] * this->value[2][3];

			this->value[3] = mat.value[0] * this->value[3][0] + mat.value[1] * this->value[3][1] +
							 mat.value[2] * this->value[3][2] + mat.value[3] * this->value[3][3];
			return  *this;

		}


		template<typename U>
		Matrix4<T>& rotateX(U angle)
		{
			T a = T(angle)*PI / 180.0;
			T c = cos(a);
			T s = sin(a);


			Matrix4<T> mat( 1, 0, 0, 0,
							0, c, s, 0,
							0, -s, c, 0,
							0, 0, 0, 1);
			this->value[0] = mat.value[0] * this->value[0][0] + mat.value[1] * this->value[0][1] +
							 mat.value[2] * this->value[0][2] + mat.value[3] * this->value[0][3];

			this->value[1] = mat.value[0] * this->value[1][0] + mat.value[1] * this->value[1][1] +
							 mat.value[2] * this->value[1][2] + mat.value[3] * this->value[1][3];

			this->value[2] = mat.value[0] * this->value[2][0] + mat.value[1] * this->value[2][1] +
							 mat.value[2] * this->value[2][2] + mat.value[3] * this->value[2][3];

			this->value[3] = mat.value[0] * this->value[3][0] + mat.value[1] * this->value[3][1] +
							 mat.value[2] * this->value[3][2] + mat.value[3] * this->value[3][3];
			return  *this;

		}


		template<typename U>
		Matrix4<T>& rotateY(U angle)
		{
			T a = T(angle)*PI / 180.0;
			T c = cos(a);
			T s = sin(a);
			Matrix4<T> mat( c, 0, -s, 0,
						    0, 1, 0, 0,
						    s, 0, c, 0,
						    0, 0, 0, 1);
			this->value[0] =mat.value[0] * this->value[0][0]	+	mat.value[1] * this->value[0][1] +
						    mat.value[2] * this->value[0][2]	+	mat.value[3] * this->value[0][3];

			this->value[1] =mat.value[0] * this->value[1][0]	+	mat.value[1] * this->value[1][1] +
							mat.value[2] * this->value[1][2]	+	mat.value[3] * this->value[1][3];

			this->value[2] =mat.value[0] * this->value[2][0]	+	mat.value[1] * this->value[2][1] +
							mat.value[2] * this->value[2][2]	+	mat.value[3] * this->value[2][3];

			this->value[3] =mat.value[0] * this->value[3][0]	+	mat.value[1] * this->value[3][1] +
							mat.value[2] * this->value[3][2]	+	mat.value[3] * this->value[3][3];
			return  *this;

		}

		template<typename U>
		Matrix4<T>& rotateZ(U angle)
		{
			T a = T(angle)*PI / 180.0;

			T c = cos(a);
			T s = sin(a);

			Matrix4<T> mat( c, s, 0, 0,
						   -s, c, 0, 0,
							0, 0, 1, 0,
							0, 0, 0, 1);

			this->value[0] = mat.value[0] * this->value[0][0] + mat.value[1] * this->value[0][1] +
							 mat.value[2] * this->value[0][2] + mat.value[3] * this->value[0][3];

			this->value[1] = mat.value[0] * this->value[1][0] + mat.value[1] * this->value[1][1] +
						 	 mat.value[2] * this->value[1][2] + mat.value[3] * this->value[1][3];

			this->value[2] = mat.value[0] * this->value[2][0] + mat.value[1] * this->value[2][1] +
							 mat.value[2] * this->value[2][2] + mat.value[3] * this->value[2][3];

			this->value[3] = mat.value[0] * this->value[3][0] + mat.value[1] * this->value[3][1] +
							 mat.value[2] * this->value[3][2] + mat.value[3] * this->value[3][3];
			return  *this;

		}

		template<typename U>
		Matrix4<T> rotateYXZ(U yaw, U pitch, U roll)
		{
			T tmp_ch = cos(T(yaw)*PI / 180.0);
			T tmp_sh = sin(T(yaw)*PI / 180.0);
			T tmp_cp = cos(T(pitch)*PI / 180.0);
			T tmp_sp = sin(T(pitch)*PI / 180.0);
			T tmp_cb = cos(T(roll)*PI / 180.0);
			T tmp_sb = sin(T(roll)*PI / 180.0);

			Matrix4<T> Result;
			this->value[0][0] = tmp_ch * tmp_cb + tmp_sh * tmp_sp * tmp_sb;
			this->value[0][1] = tmp_sb * tmp_cp;
			this->value[0][2] = -tmp_sh * tmp_cb + tmp_ch * tmp_sp * tmp_sb;
			this->value[0][3] = T(0);
			this->value[1][0] = -tmp_ch * tmp_sb + tmp_sh * tmp_sp * tmp_cb;
			this->value[1][1] = tmp_cb * tmp_cp;
			this->value[1][2] = tmp_sb * tmp_sh + tmp_ch * tmp_sp * tmp_cb;
			this->value[1][3] = T(0);
			this->value[2][0] = tmp_sh * tmp_cp;
			this->value[2][1] = -tmp_sp;
			this->value[2][2] = tmp_ch * tmp_cp;
			this->value[2][3] = T(0);
			this->value[3][0] = T(0);
			this->value[3][1] = T(0);
			this->value[3][2] = T(0);
			this->value[3][3] = T(1);

			return  *this;
		}
		//..................................................
		template<typename U,typename V>
		Matrix4<T>& rotate(U angle, Vector3<V> const & v)
		{
			T a = T(angle)*PI / 180.0;
			T c = cos(a);
			T s = sin(a);

			Vector3<T> axis = v.normalize();

			Vector3<T> temp = (T(1) - c) * axis;

			Matrix4<T> res;
			this->value[0][0] = c + temp[0] * axis[0];
			this->value[0][1] = 0 + temp[0] * axis[1] + s * axis[2];
			this->value[0][2] = 0 + temp[0] * axis[2] - s * axis[1];
			this->value[0][3] = 0;

			this->value[1][0] = 0 + temp[1] * axis[0] - s * axis[2];
			this->value[1][1] = c + temp[1] * axis[1];
			this->value[1][2] = 0 + temp[1] * axis[2] + s * axis[0];
			this->value[1][3] = 0;

			this->value[2][0] = 0 + temp[2] * axis[0] + s * axis[1];
			this->value[2][1] = 0 + temp[2] * axis[1] - s * axis[0];
			this->value[2][2] = c + temp[2] * axis[2];
			this->value[2][3] = 0;

			this->value[3][0] = 0;
			this->value[3][1] = 0;
			this->value[3][2] = 0;
			this->value[3][3] = 1;
			return  *this;
		}

		Matrix4<T>& scale(Vector3<T> const& s)
		{
			//Vector4<T>(s[0], 0, 0, 0);
			//Vector4<T>(0, s[1], 0, 0);
			//Vector4<T>(0, 0, s[2], 0);
			//Vector4<T>(0, 0, 0, 1);
			Matrix4<T> mat( s[0], 0, 0, 0,
							0, s[1], 0, 0,
							0, 0, s[2], 0,
							0,  0,  0,  1);
			this->value[0] = mat.value[0] * this->value[0][0] + mat.value[1] * this->value[0][1] +
							 mat.value[2] * this->value[0][2] + mat.value[3] * this->value[0][3];

			this->value[1] = mat.value[0] * this->value[1][0] + mat.value[1] * this->value[1][1] +
							 mat.value[2] * this->value[1][2] + mat.value[3] * this->value[1][3];

			this->value[2] = mat.value[0] * this->value[2][0] + mat.value[1] * this->value[2][1] +
							 mat.value[2] * this->value[2][2] + mat.value[3] * this->value[2][3];

			this->value[3] = mat.value[0] * this->value[3][0] + mat.value[1] * this->value[3][1] +
							 mat.value[2] * this->value[3][2] + mat.value[3] * this->value[3][3];
			return  *this;


		}

		template<typename U, typename V, typename W>
		Matrix4<T>& scale(U x, V y, W z)
		{

			Matrix4<T> mat( T(x), 0, 0, 0,
							0, T(y), 0, 0,
							0, 0, T(z), 0,
							0, 0, 0, 1);

			this->value[0] = mat.value[0] * this->value[0][0] + mat.value[1] * this->value[0][1] +
							 mat.value[2] * this->value[0][2] + mat.value[3] * this->value[0][3];

			this->value[1] = mat.value[0] * this->value[1][0] + mat.value[1] * this->value[1][1] +
							 mat.value[2] * this->value[1][2] + mat.value[3] * this->value[1][3];

			this->value[2] = mat.value[0] * this->value[2][0] + mat.value[1] * this->value[2][1] +
							 mat.value[2] * this->value[2][2] + mat.value[3] * this->value[2][3];

			this->value[3] = mat.value[0] * this->value[3][0] + mat.value[1] * this->value[3][1] +
							 mat.value[2] * this->value[3][2] + mat.value[3] * this->value[3][3];
			return  *this;
	}

		Matrix4<T> transpose() const
		{
			return  transpose<T>(
				this->value[0][0], this->value[1][0], this->value[2][0], this->value[3][0],
				this->value[0][1], this->value[1][1], this->value[2][1], this->value[3][1],
				this->value[0][2], this->value[1][2], this->value[2][2], this->value[3][2],
				this->value[0][3], this->value[1][3], this->value[2][3], this->value[3][3]
				);
		}
		/***************************************END旋转变换*****************************************/


	};



}


