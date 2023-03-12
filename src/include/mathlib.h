#pragma once

#include <string>
#include <cmath>
#include <algorithm>
#include <random>
#include <ctime>
#include "stringlib.h"

namespace mathlib {

	// Extra Methods //
	int randomInt(int min, int max) {
		static std::default_random_engine e;
		static std::uniform_real_distribution<> dis(0, 1); // rage 0 - 1
		float v = min + ((max - min) * dis(e));
		return std::floor(v);
	}

	std::string randomString(int len) {
		std::string str;
		for (int i = 0; i < len; i++) {
			char ch = 'A' + rand() % 26;
			str.push_back(ch);
		}
		return str;
	}

	// Structs //
	struct EularXYZ {
		float x, y, z;
	};

	struct CFrameComponents {
		float x, y, z, m11, m12, m13, m21, m22, m23, m31, m32, m33;
	};

	struct Quaternion4 {
		float w, i, j, k;
	};

	// Classes //
	class Vector2f {
		public:
			float x;
			float y;

			Vector2f();
			Vector2f(int x, int y);
			Vector2f(float x, float y);
			~Vector2f();

			void toDefault();
			Vector2f* clone();

			Vector2f* add(Vector2f* other);
			Vector2f* add(int v);
			Vector2f* add(float v);
			Vector2f* sub(Vector2f* other);
			Vector2f* sub(int v);
			Vector2f* sub(float v);
			Vector2f* mult(int v);
			Vector2f* mult(float v);
			Vector2f* div(Vector2f* other);
			Vector2f* div(int v);
			Vector2f* div(float v);
			float dot(Vector2f* v2);
			float dot(float other);
			float dot(int other);
			
			float magnitude();
			Vector2f* unit();

			std::string* toString();
	};

	class Vector3f {
		public:
			float x;
			float y;
			float z;

			Vector3f();
			Vector3f(int x, int y, int);
			Vector3f(float x, float y, float z);
			~Vector3f();

			void toDefault();
			Vector3f* clone();

			Vector3f* add(Vector3f* other);
			Vector3f* add(int v);
			Vector3f* add(float v);
			Vector3f* sub(Vector3f* other);
			Vector3f* sub(int v);
			Vector3f* sub(float v);
			Vector3f* mult(int v);
			Vector3f* mult(float v);
			Vector3f* div(Vector3f* other);
			Vector3f* div(int v);
			Vector3f* div(float v);
			float dot(Vector3f* v2);
			float dot(float other);
			float dot(int other);

			Vector3f* lerp(Vector3f* other, float t);
			float magnitude();
			Vector3f* unit();
			Vector3f* cross(Vector3f* other);

			std::string* toString();
	};

	class CFrame {
		public:
			static Vector3f* vectorAxisAngle(Vector3f* n, Vector3f* v, float t);
			static float getDeterminant(CFrame* a);
			static CFrame* invert4x4(CFrame* a);
			static Quaternion4 quaternionFromCFrame(CFrame* a);
			static CFrame* lerpinternal(CFrame* a, CFrame* b, float t);

			static const Vector3f* RIGHT;
			static const Vector3f* UP;
			static const Vector3f* BACK;
			static const float m41;
			static const float m42;
			static const float m43;
			static const float m44;

			// Rotation Matrix //
			float m11, m12, m13, m14;
			float m21, m22, m23, m24;
			float m31, m32, m33, m34;
			
			// Position Values //
			float x;
			float y;
			float z;

			Vector3f* Position;
			Vector3f* LookVector;
			Vector3f* UpVector;
			Vector3f* RightVector;

			// Constructors //
			CFrame();
			CFrame(float nx, float ny, float nz);
			CFrame(Vector3f* pos);
			CFrame(Vector3f* position, Vector3f* lookAt);
			CFrame(float nx, float ny, float nz, float i, float j, float k, float w);
			CFrame(float n14, float n24, float n34, float n11, float n12, float n13, float n21, float n22, float n23, float n31, float n32, float n33);
			~CFrame();

			// Methods //
			void toDefault();

			Vector3f* mult(Vector3f* other);
			CFrame* mult(CFrame* other);
			CFrame* add(Vector3f* other);
			CFrame* sub(Vector3f* other);
			CFrame* inverse();
			CFrame* lerp(CFrame* cf2, float t);
			CFrame* ToWorldSpace(CFrame* cf2);
			CFrame* ToObjectSpace(CFrame* cf2);
			Vector3f* pointToWorldSpace(Vector3f* v);
			Vector3f* pointToObjectSpace(Vector3f* v);
			Vector3f* vectorToWorldSpace(Vector3f* v);
			Vector3f* vectorToObjectSpace(Vector3f* v);
			EularXYZ toEulerAnglesXYZ();
			CFrameComponents components();

			std::string* toString();

			// Class Methods //
			static CFrame* fromEularAnglesXYZ(float x, float y, float z);
			static CFrame* Angles(float x, float y, float z);
			static CFrame* Angles(double x, double y, double z);
			static CFrame* fromEulerAnglesYXZ(float rx, float ry, float rz);
			static CFrame* fromAxisAngle(Vector3f* axis, float theta);
	};
	
	// Constant Sets //
	const float CFrame::m41 = 0;
	const float CFrame::m42 = 0;
	const float CFrame::m43 = 0;
	const float CFrame::m44 = 1;
	const Vector3f* CFrame::RIGHT = new Vector3f(1, 0, 0);
	const Vector3f* CFrame::UP = new Vector3f(0, 1, 0);
	const  Vector3f* CFrame::BACK = new Vector3f(0, 0, 1);

	// Vector2f //
	Vector2f::Vector2f() {
		this->toDefault();
	}

	Vector2f::Vector2f(int x, int y) {
		this->x = (float) x;
		this->y = (float) y;
	};

	Vector2f::Vector2f(float x, float y) {
		this->x = x;
		this->y = y;
	};

	Vector2f::~Vector2f() {

	};

	void Vector2f::toDefault() {
		this->x = 0.0f;
		this->y = 0.0f;
	}

	Vector2f* Vector2f::add(Vector2f* other) {
		return new Vector2f(
			(float) (this->x + other->x),
			(float) (this->y + other->y)
		);
	};

	Vector2f* Vector2f::add(int v) {
		return new Vector2f(
			(float) (this->x + v),
			(float) (this->y + v)
		);
	};

	Vector2f* Vector2f::add(float v) {
		return new Vector2f(
			(float) (this->x + v),
			(float) (this->y + v)
		);
	};

	Vector2f* Vector2f::sub(Vector2f* other) {
		return new Vector2f(
			(float) (this->x - other->x),
			(float) (this->y - other->y)
		);
	};

	Vector2f* Vector2f::sub(int v) {
		return new Vector2f(
			(float) (this->x - v),
			(float) (this->y - v)
		);
	};

	Vector2f* Vector2f::sub(float v) {
		return new Vector2f(
			(float) (this->x - v),
			(float) (this->y - v)
		);
	};

	Vector2f* Vector2f::mult(int v) {
		return new Vector2f(
			(float) (this->x * v),
			(float) (this->y * v)
		);
	};

	Vector2f* Vector2f::mult(float v) {
		return new Vector2f(
			(float) (this->x * v),
			(float) (this->y * v)
		);
	};

	Vector2f* Vector2f::div(Vector2f* other) {
		float x = other->x == 0 ? 0 : (float) (this->x / other->x);
		float y = other->y == 0 ? 0 : (float) (this->y / other->y);
		return new Vector2f(x, y);
	};

	Vector2f* Vector2f::div(int v) {
		if (v == 0) {
			return new Vector2f();
		}
		return new Vector2f(
			(float) (this->x / v),
			(float) (this->y / v)
		);
	};

	Vector2f* Vector2f::div(float v) {
		if (v == 0.0f) {
			return new Vector2f();
		}
		return new Vector2f(
			(float) (this->x / v),
			(float) (this->y / v)
		);
	};

	float Vector2f::magnitude() {
		if (this->x == 0 || this->y == 0) {
			return 0.0f;
		}
		return std::sqrt( std::pow(this->x, 2) + std::pow(this->y, 2) );
	};

	float Vector2f::dot(Vector2f* v2) {
		return (this->x * v2->x) + (this->y * v2->y);
	};

	float Vector2f::dot(float other) {
		return (this->x * other) + (this->y * other);
	};

	float Vector2f::dot(int other) {
		return (this->x * other) + (this->y * other);
	};

	Vector2f* Vector2f::unit() {
		float mag = this->magnitude();
		if (mag == 0) {
			return new Vector2f();
		}
		return new Vector2f(this->x / mag, this->y / mag);
	};

	std::string* Vector2f::toString() {
		return string_format("Vector2f(%d, %d)", this->x, this->y);
	};

	Vector2f* Vector2f::clone() {
		return new Vector2f(this->x, this->y);
	};

	// Vector3f //
	Vector3f::Vector3f() {
		this->toDefault();
	}

	Vector3f::Vector3f(int x, int y, int z) {
		this->x = (float) x;
		this->y = (float) y;
		this->z = (float) z;
	};

	Vector3f::Vector3f(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	};

	Vector3f::~Vector3f() {

	};

	void Vector3f::toDefault() {
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
	}

	Vector3f* Vector3f::add(Vector3f* other) {
		return new Vector3f(
			(float) (this->x + other->x),
			(float) (this->y + other->y),
			(float) (this->z + other->z)
		);
	};

	Vector3f* Vector3f::add(int v) {
		return new Vector3f(
			(float) (this->x + v),
			(float) (this->y + v),
			(float) (this->z + v)
		);
	};

	Vector3f* Vector3f::add(float v) {
		return new Vector3f(
			(float) (this->x + v),
			(float) (this->y + v),
			(float) (this->z + v)
		);
	};

	Vector3f* Vector3f::sub(Vector3f* other) {
		return new Vector3f(
			(float) (this->x - other->x),
			(float) (this->y - other->y),
			(float) (this->z - other->z)
		);
	};

	Vector3f* Vector3f::sub(int v) {
		return new Vector3f(
			(float) (this->x - v),
			(float) (this->y - v),
			(float) (this->z - v)
		);
	};

	Vector3f* Vector3f::sub(float v) {
		return new Vector3f(
			(float) (this->x - v),
			(float) (this->y - v),
			(float) (this->z - v)
		);
	};

	Vector3f* Vector3f::mult(int v) {
		return new Vector3f(
			(float) (this->x * v),
			(float) (this->y * v),
			(float) (this->z * v)
		);
	};

	Vector3f* Vector3f::mult(float v) {
		return new Vector3f(
			(float) (this->x * v),
			(float) (this->y * v),
			(float) (this->z * v)
		);
	};

	Vector3f* Vector3f::div(Vector3f* other) {
		float x = other->x == 0 ? 0 : (float) (this->x / other->x);
		float y = other->y == 0 ? 0 : (float) (this->y / other->y);
		float z = other->z == 0 ? 0 : (float) (this->z / other->z);
		return new Vector3f(x, y, z);
	};

	Vector3f* Vector3f::div(int v) {
		if (v == 0) {
			return new Vector3f();
		}
		return new Vector3f(
			(float) (this->x / v),
			(float) (this->y / v),
			(float) (this->z / v)
		);
	};

	Vector3f* Vector3f::div(float v) {
		if (v == 0.0f) {
			return new Vector3f();
		}
		return new Vector3f(
			(float) (this->x / v),
			(float) (this->y / v),
			(float) (this->z / v)
		);
	};

	float Vector3f::magnitude() {
		if (this->x == 0 && this->y == 0 && this->z == 0) {
			return 0.0f;
		}
		return (float) std::sqrt( this->dot(this) );
	};

	float Vector3f::dot(Vector3f* v2) {
		return (this->x * v2->x) + (this->y * v2->y) + (this->y * v2->y);
	};

	float Vector3f::dot(float other) {
		return (this->x * other) + (this->y * other) + (this->z * other);
	};

	float Vector3f::dot(int other) {
		return (this->x * other) + (this->y * other) + (this->z * other);
	};

	Vector3f* Vector3f::lerp(Vector3f* other, float t) {
		return this->mult((1-t))->add(other->mult(t));
	};

	Vector3f* Vector3f::unit() {
		float m = this->magnitude();
		if (m == 0) {
			return new Vector3f(NAN, NAN, NAN);
		}
		return new Vector3f(this->x / m, this->y / m, this->z / m);
	};

	Vector3f* Vector3f::cross(Vector3f* other) {
		return new Vector3f(
			(this->y * other->z) - (other->y * this->z),
			(this->z * other->x) - (other->z * this->x),
			(this->x * other->y) - (other->x * this->y)
		);
	};

	std::string* Vector3f::toString() {
		return string_format("Vector3f(%f, %f, %f)", this->x, this->y, this->z);
	};

	Vector3f* Vector3f::clone() {
		return new Vector3f(this->x, this->y, this->z);
	};

	CFrame::CFrame() {
		this->toDefault(); // set defaults first
	};

	CFrame::~CFrame() {

	};

	CFrame::CFrame(float nx, float ny, float nz) {
		this->toDefault(); // set defaults first

		this->x = this->m14 = nx;
		this->y = this->m24 = ny;
		this->z = this->m34 = nz;
		
		this->Position = new Vector3f(nx, ny, nz);
		this->LookVector = new Vector3f(-this->m13, -this->m23, -this->m33);
		this->RightVector = new Vector3f(this->m11, this->m21, this->m31);
		this->UpVector = new Vector3f(this->m12, this->m22, this->m32);
	};

	CFrame::CFrame(Vector3f* pos) {
		this->toDefault(); // set defaults first

		this->x = this->m14 = pos->x;
		this->y = this->m24 = pos->y;
		this->z = this->m34 = pos->z;
		
		this->Position = new Vector3f(pos->x, pos->y, pos->z);
		this->LookVector = new Vector3f(-this->m13, -this->m23, -this->m33);
		this->RightVector = new Vector3f(this->m11, this->m21, this->m31);
		this->UpVector = new Vector3f(this->m12, this->m22, this->m32);
	};

	CFrame::CFrame(Vector3f* pos, Vector3f* lookAt) {
		this->toDefault(); // set defaults first

		Vector3f upConst = *CFrame::UP;

		Vector3f* zAxis = pos->sub(lookAt)->unit();
		Vector3f* xAxis = upConst.cross(zAxis);
		Vector3f* yAxis = zAxis->cross(xAxis);
		if (xAxis->magnitude() == 0) {
			if (zAxis->y < 0) {
				xAxis = new Vector3f(0, 0, -1);
				yAxis = new Vector3f(1, 0, 0);
				zAxis = new Vector3f(0, -1, 0);
			} else {
				xAxis = new Vector3f(0, 0, 1);
				yAxis = new Vector3f(1, 0, 0);
				zAxis = new Vector3f(0, 1, 0);
			}
		}

		this->m11 = xAxis->x; this->m12 = yAxis->x; this->m13 = zAxis->x; this->m14 = pos->x;
		this->m21 = xAxis->y; this->m22 = yAxis->y; this->m23 = zAxis->y; this->m24 = pos->y;
		this->m31 = xAxis->z; this->m32 = yAxis->z; this->m33 = zAxis->z; this->m34 = pos->z;
		this->x = pos->x; this->y = pos->y; this->z = pos->z;
		this->Position = pos->clone();
		this->LookVector = new Vector3f(-zAxis->x, -zAxis->y, -zAxis->z);
		this->RightVector = new Vector3f(xAxis->x, xAxis->y, xAxis->z);
		this->UpVector = new Vector3f(yAxis->x, yAxis->y, yAxis->z);
	};

	CFrame::CFrame(float nx, float ny, float nz, float i, float j, float k, float w) {
		this->toDefault(); // set defaults first

		this->m14 = nx; this->m24 = ny; this->m34 = nz;
		this->m11 = 1 - 2 * (float) pow(j, 2) - 2 * (float) pow(k, 2);
		this->m12 = 2 * (i * j - k * w);
		this->m13 = 2 * (i * k + j * w);
		this->m21 = 2 * (i * j + k * w);
		this->m22 = 1 - 2 * (float) pow(i, 2) - 2 * (float) pow(k, 2);
		this->m23 = 2 * (j * k - i * w);
		this->m31 = 2 * (i * k - j * w);
		this->m32 = 2 * (j * k + i * w);
		this->m33 = 1 - 2 * (float) pow(i, 2) - 2 * (float) pow(j, 2);
		this->x = m14; this->y = m24; this->z = m34;
		this->Position = new Vector3f(this->x, this->y, this->z);
		this->LookVector = new Vector3f(-this->m13, -this->m23, -this->m33);
		this->RightVector = new Vector3f(this->m11, this->m21, this->m31);
		this->UpVector = new Vector3f(this->m12, this->m22, this->m32);
	};

	CFrame::CFrame(float n14, float n24, float n34, float n11, float n12, float n13, float n21, float n22, float n23, float n31, float n32, float n33) {
		this->toDefault(); // set defaults first
		
		this->m14 = n14; this->m24 = n24; this->m34 = n34;
		this->m11 = n11; this->m12 = n12; this->m13 = n13;
		this->m21 = n21; this->m22 = n22; this->m23 = n23;
		this->m31 = n31; this->m32 = n32; this->m33 = n33;
		this->x = this->m14; this->y = this->m24; this->z = this->m34;
		this->Position = new Vector3f(this->m14, this->m24, this->m34);
		this->LookVector = new Vector3f(-this->m13, -this->m23, -this->m33);
		this->RightVector = new Vector3f(this->m11, this->m21, this->m31);
		this->UpVector = new Vector3f(this->m12, this->m22, this->m32);
	};
	
	void CFrame::toDefault() {
		this->m11 = 1;
		this->m12 = 0;
		this->m13 = 0;
		this->m14 = 0;
		this->m21 = 0;
		this->m22 = 1;
		this->m23 = 0;
		this->m24 = 0;
		this->m31 = 0;
		this->m32 = 0;
		this->m33 = 1;
		this->m34 = 0;

		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->Position = new Vector3f();

		this->LookVector = new Vector3f(0, 0, -1);
		this->UpVector = new Vector3f(1, 0, 0);
		this->RightVector = new Vector3f(0, 1, 0);
	};

	Vector3f* CFrame::mult(Vector3f* other) {
		CFrameComponents ac = this->components();

		// this.x = ac[0]; this.y = ac[1]; this.z = ac[2];
		float m11 = ac.m11, m12 = ac.m12, m13 = ac.m13;
		float m21 = ac.m21, m22 = ac.m22, m23 = ac.m23;
		float m31 = ac.m31, m32 = ac.m32, m33 = ac.m33;

		Vector3f* right = (new Vector3f(m11, m21, m31)) -> mult(other->x);
		Vector3f* up = (new Vector3f(m12, m22, m32)) -> mult(other->y);
		Vector3f* back = (new Vector3f(m13, m23, m33)) -> mult(other->z);

		return this->Position->add(right)->add(up)->add(back);
	};

	CFrame* CFrame::mult(CFrame* other) {
		CFrameComponents ac = this->components();
		CFrameComponents bc = other->components();

		float n11 = ac.m11 * bc.m11 + ac.m12 * bc.m21 + ac.m13 * bc.m31 + ac.x * m41;
		float n12 = ac.m11 * bc.m12 + ac.m12 * bc.m22 + ac.m13 * bc.m32 + ac.x * m42;
		float n13 = ac.m11 * bc.m13 + ac.m12 * bc.m23 + ac.m13 * bc.m33 + ac.x * m43;
		float n14 = ac.m11 * bc.x + ac.m12 * bc.y + ac.m13 * bc.z + ac.x * m44;

		float n21 = ac.m21 * bc.m11 + ac.m22 * bc.m21 + ac.m23 * bc.m31 + ac.y * m41;
		float n22 = ac.m21 * bc.m12 + ac.m22 * bc.m22 + ac.m23 * bc.m32 + ac.y * m42;
		float n23 = ac.m21 * bc.m13 + ac.m22 * bc.m23 + ac.m23 * bc.m33 + ac.y * m43;
		float n24 = ac.m21 * bc.x + ac.m22 * bc.y + ac.m23 * bc.z + ac.y * m44;

		float n31 = ac.m31 * bc.m11 + ac.m32 * bc.m21 + ac.m33 * bc.m31 + ac.z * m41;
		float n32 = ac.m31 * bc.m12 + ac.m32 * bc.m22 + ac.m33 * bc.m32 + ac.z * m42;
		float n33 = ac.m31 * bc.m13 + ac.m32 * bc.m23 + ac.m33 * bc.m33 + ac.z * m43;
		float n34 = ac.m31 * bc.x + ac.m32 * bc.y + ac.m33 * bc.z + ac.z * m44;

		return new CFrame(n14, n24, n34, n11, n12, n13, n21, n22, n23, n31, n32, n33);
	};

	CFrame* CFrame::add(Vector3f* other) {
		CFrameComponents ac = this->components();
		return new CFrame(
			ac.x + other->x,
			ac.y + other->y,
			ac.z + other->z,
			ac.m11, ac.m12, ac.m13, ac.m21, ac.m22, ac.m23, ac.m31, ac.m32, ac.m33
		);
	};

	CFrame* CFrame::sub(Vector3f* other) {
		CFrameComponents ac = this->components();
		return new CFrame(ac.x - other->x, ac.y - other->y, ac.z - other->z, ac.m11, ac.m12, ac.m13, ac.m21, ac.m22, ac.m23, ac.m31, ac.m32, ac.m33);
	};

	CFrame* CFrame::inverse() {
		return CFrame::invert4x4(this);
	};

	CFrame* CFrame::lerp(CFrame* cf2, float t) {
		return CFrame::lerpinternal(this, cf2, t);
	};

	CFrame* CFrame::ToWorldSpace(CFrame* cf2) {
		return this->mult(cf2);
	};

	CFrame* CFrame::ToObjectSpace(CFrame* cf2) {
		return this->inverse()->mult(cf2);
	};

	Vector3f* CFrame::pointToWorldSpace(Vector3f* v) {
		return this->mult(v);
	};

	Vector3f* CFrame::pointToObjectSpace(Vector3f* v) {
		return this->inverse()->mult(v);
	};

	Vector3f* CFrame::vectorToWorldSpace(Vector3f* v) {
		return this->sub(this->Position)->mult(v);
	};

	Vector3f* CFrame::vectorToObjectSpace(Vector3f* v) {
		return this->sub(this->Position)->mult(v);
	};

	EularXYZ CFrame::toEulerAnglesXYZ() {
		float x = (float) atan2(-this->m23, this->m33);
		float y = (float) asin(this->m13);
		float z = (float) atan2(-this->m12, this->m11);
		return { x, y, z };
	};

	CFrameComponents CFrame::components() {
		return {
			this->x, this->y, this->z,
			this->m11, this->m12, this->m13,
			this->m21, this->m22, this->m23,
			this->m31, this->m32, this->m33,
		};
	};

	Vector3f* CFrame::vectorAxisAngle(Vector3f* v1, Vector3f* v2, float t) {
		Vector3f* n = v1->unit();

		Vector3f* a = n->mult( v2->dot(n) )->mult( 1 - (float) cos(t) );
		Vector3f* b = n->cross(v2)->mult( (float) sin(t) );
		return v2->mult( (float) cos(t) )->add( a )->add( b );
	};

	float CFrame::getDeterminant(CFrame* a) {
		CFrameComponents ac = a->components();
		float det = (
			ac.m11 * ac.m22 * ac.m33 * CFrame::m44 + ac.m11 * ac.m23 * ac.z * CFrame::m42 + ac.m11 * ac.y * ac.m32 * CFrame::m43
			+ ac.m12 * ac.m21 * ac.z * CFrame::m43 + ac.m12 * ac.m23 * ac.m31 * CFrame::m44 + ac.m12 * ac.y * ac.m33 * CFrame::m41
			+ ac.m13 * ac.m21 * ac.m32 * CFrame::m44 + ac.m13 * ac.m22 * ac.z * CFrame::m41 + ac.m13 * ac.y * ac.m31 * CFrame::m42
			+ ac.x * ac.m21 * ac.m33 * CFrame::m42 + ac.x * ac.m22 * ac.m31 * CFrame::m43 + ac.x * ac.m23 * ac.m32 * CFrame::m41
			- ac.m11 * ac.m22 * ac.z * CFrame::m43 - ac.m11 * ac.m23 * ac.m32 * CFrame::m44 - ac.m11 * ac.y * ac.m33 * CFrame::m42
			- ac.m12 * ac.m21 * ac.m33 * CFrame::m44 - ac.m12 * ac.m23 * ac.z * CFrame::m41 - ac.m12 * ac.y * ac.m31 * CFrame::m43
			- ac.m13 * ac.m21 * ac.z * CFrame::m42 - ac.m13 * ac.m22 * ac.m31 * CFrame::m44 - ac.m13 * ac.y * ac.m32 * CFrame::m41
			- ac.x * ac.m21 * ac.m32 * CFrame::m43 - ac.x * ac.m22 * ac.m33 * CFrame::m41 - ac.x * ac.m23 * ac.m31 * CFrame::m42
		);
		return det;
	};

	CFrame* CFrame::invert4x4(CFrame* a) {
		CFrameComponents ac = a->components();
		float det = CFrame::getDeterminant(a);
		if (det == 0) {
			return a;
		}
		float b11 = (ac.m22 * ac.m33 * m44 + ac.m23 * ac.z * m42 + ac.y * ac.m32 * m43 - ac.m22 * ac.z * m43 - ac.m23 * ac.m32 * m44 - ac.y * ac.m33 * m42) / det;
		float b12 = (ac.m12 * ac.z * m43 + ac.m13 * ac.m32 * m44 + ac.x * ac.m33 * m42 - ac.m12 * ac.m33 * m44 - ac.m13 * ac.z * m42 - ac.x * ac.m32 * m43) / det;
		float b13 = (ac.m12 * ac.m23 * m44 + ac.m13 * ac.y * m42 + ac.x * ac.m22 * m43 - ac.m12 * ac.y * m43 - ac.m13 * ac.m22 * m44 - ac.x * ac.m23 * m42) / det;
		float b14 = (ac.m12 * ac.y * ac.m33 + ac.m13 * ac.m22 * ac.z + ac.x * ac.m23 * ac.m32 - ac.m12 * ac.m23 * ac.z - ac.m13 * ac.y * ac.m32 - ac.x * ac.m22 * ac.m33) / det;
		float b21 = (ac.m21 * ac.z * m43 + ac.m23 * ac.m31 * m44 + ac.y * ac.m33 * m41 - ac.m21 * ac.m33 * m44 - ac.m23 * ac.z * m41 - ac.y * ac.m31 * m43) / det;
		float b22 = (ac.m11 * ac.m33 * m44 + ac.m13 * ac.z * m41 + ac.x * ac.m31 * m43 - ac.m11 * ac.z * m43 - ac.m13 * ac.m31 * m44 - ac.x * ac.m33 * m41) / det;
		float b23 = (ac.m11 * ac.y * m43 + ac.m13 * ac.m21 * m44 + ac.x * ac.m23 * m41 - ac.m11 * ac.m23 * m44 - ac.m13 * ac.y * m41 - ac.x * ac.m21 * m43) / det;
		float b24 = (ac.m11 * ac.m23 * ac.z + ac.m13 * ac.y * ac.m31 + ac.x * ac.m21 * ac.m33 - ac.m11 * ac.y * ac.m33 - ac.m13 * ac.m21 * ac.z - ac.x * ac.m23 * ac.m31) / det;
		float b31 = (ac.m21 * ac.m32 * m44 + ac.m22 * ac.z * m41 + ac.y * ac.m31 * m42 - ac.m21 * ac.z * m42 - ac.m22 * ac.m31 * m44 - ac.y * ac.m32 * m41) / det;
		float b32 = (ac.m11 * ac.z * m42 + ac.m12 * ac.m31 * m44 + ac.x * ac.m32 * m41 - ac.m11 * ac.m32 * m44 - ac.m12 * ac.z * m41 - ac.x * ac.m31 * m42) / det;
		float b33 = (ac.m11 * ac.m22 * m44 + ac.m12 * ac.y * m41 + ac.x * ac.m21 * m42 - ac.m11 * ac.y * m42 - ac.m12 * ac.m21 * m44 - ac.x * ac.m22 * m41) / det;
		float b34 = (ac.m11 * ac.y * ac.m32 + ac.m12 * ac.m21 * ac.z + ac.x * ac.m22 * ac.m31 - ac.m11 * ac.m22 * ac.z - ac.m12 * ac.y * ac.m31 - ac.x * ac.m21 * ac.m32) / det;
		return new CFrame(b14, b24, b34, b11, b12, b13, b21, b22, b23, b31, b32, b33);
	};

	Quaternion4 CFrame::quaternionFromCFrame(CFrame* a) {
		CFrameComponents ac = a->components();

		float trace = ac.m11 + ac.m22 + ac.m33;
		float w = 1, i = 0, j = 0, k = 0;
		if (trace > 0) {
			float s = (float) sqrt(1 + trace);
			float r = 0.5f / s;
			w = s * 0.5f; i = (ac.m32 - ac.m23) * r; j = (ac.m13 - ac.m31) * r; k = (ac.m21 - ac.m12) * r;
		} else {
			float big = std::max(std::max(ac.m11, ac.m22), ac.m33);
			if (big == ac.m11) {
				float s = (float)sqrt(1 + ac.m11 - ac.m22 - ac.m33);
				float r = 0.5f / s;
				w = (ac.m32 - ac.m23) * r; i = 0.5f * s; j = (ac.m21 + ac.m12) * r; k = (ac.m13 + ac.m31) * r;
			} else if (big == ac.m22) {
				float s = (float)sqrt(1 - ac.m11 + ac.m22 - ac.m33);
				float r = 0.5f / s;
				w = (ac.m13 - ac.m31) * r; i = (ac.m21 + ac.m12) * r; j = 0.5f * s; k = (ac.m32 + ac.m23) * r;
			} else if (big == ac.m33) {
				float s = (float)sqrt(1 - ac.m11 - ac.m22 + ac.m33);
				float r = 0.5f / s;
				w = (ac.m21 - ac.m12) * r; i = (ac.m13 + ac.m31) * r; j = (ac.m32 + ac.m23) * r; k = 0.5f * s;
			}
		}
		return { w, i, j, k };
	};

	CFrame* CFrame::lerpinternal(CFrame* a, CFrame* b, float t) {
		CFrame* cf = a->inverse()->mult(b);
		Quaternion4 q = quaternionFromCFrame(cf);
		float theta = (float) acos(q.w) * 2;
		Vector3f* v = new Vector3f(q.i, q.j, q.k);
		Vector3f* p = a->Position->lerp(b->Position, t);
		if (theta != 0) {
			CFrame* v2 = CFrame::fromAxisAngle(v, theta * t);
			CFrame* r = a->mult( v2 );
			return r->sub(r->Position)->add(p);
		} else {
			return a->sub(a->Position)->add(p);
		}
	};

	CFrame* CFrame::fromEularAnglesXYZ(float x, float y, float z) {
		return CFrame::Angles(x, y, z);
	};

	CFrame* CFrame::Angles(float x, float y, float z) {
		Vector3f rightConst = *CFrame::RIGHT;
		Vector3f upConst = *CFrame::UP;
		Vector3f backConst = *CFrame::BACK;
		
		CFrame* cfx = CFrame::fromAxisAngle(&rightConst, x);
		CFrame* cfy = CFrame::fromAxisAngle(&upConst, y);
		CFrame* cfz = CFrame::fromAxisAngle(&backConst, z);
		return cfx->mult(cfy)->mult(cfz);
	};

	CFrame* CFrame::Angles(double x, double y, double z) {
		return CFrame::Angles((float) x, (float) y, (float) z);
	};

	CFrame* CFrame::fromEulerAnglesYXZ(float rx, float ry, float rz) {
		return CFrame::Angles(rx, ry, rz);
	};

	CFrame* CFrame::fromAxisAngle(Vector3f* axis, float theta) {
		Vector3f rightConst = *CFrame::RIGHT;
		Vector3f upConst = *CFrame::UP;
		Vector3f backConst = *CFrame::BACK;
		
		Vector3f* r = vectorAxisAngle(axis, &rightConst, theta);
		Vector3f* u = vectorAxisAngle(axis, &upConst, theta);
		Vector3f* b = vectorAxisAngle(axis, &backConst, theta);
		return new CFrame(0, 0, 0, r->x, u->x, b->x, r->y, u->y, b->y, r->z, u->z, b->z);
	};

	std::string* CFrame::toString() {
		CFrameComponents ac = this->components();
		return string_format("CFrame(%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d)",
			ac.x, ac.y, ac.z,
			ac.m11, ac.m12, ac.m13,
			ac.m21, ac.m22, ac.m23,
			ac.m31, ac.m32, ac.m33
		);
	};

};
