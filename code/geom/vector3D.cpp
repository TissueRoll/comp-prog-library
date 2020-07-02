#include "vector2D.cpp"

template <typename T>
struct vector3D {
	T x, y, z;
	vector3D(T _x = 0, T _y = 0, T _z = 0): x(_x), y(_y), z(_z) {}
	vector3D(vector2D<T> xy, T _z = 1): x(xy.x), y(xy.y), z(_z) {}
	vector3D& operator+=(const vector3D& rhs) {x += rhs.x; y += rhs.y; z += rhs.z; return *this;}
	vector3D& operator-=(const vector3D& rhs) {x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this;}
	vector3D& operator*=(const T& rhs) {x *= rhs; y *= rhs; z *= rhs; return *this;}
	vector3D& operator/=(const T& rhs) {x /= rhs; y /= rhs; z /= rhs; return *this;}
	vector3D operator-() const {return vector3D(-x,-y,-z);}
	vector3D operator+(const vector3D& rhs) const { return vector3D(*this) += rhs; }
	vector3D operator-(const vector3D& rhs) const { return vector3D(*this) -= rhs; }
	vector3D operator*(const T& rhs) const { return vector3D(*this) *= rhs; }
	vector3D operator/(const T& rhs) const { return vector3D(*this) /= rhs; }
	T operator*(const vector3D& rhs) const { return x*rhs.x+y*rhs.y+z*rhs.z; }
	vector3D operator%(const vector3D& rhs) const { return vector3D(y*rhs.z-rhs.y*z, z*rhs.x-rhs.z*x, x*rhs.y-rhs.x*y); }
	bool operator==(const vector3D& rhs) const { return abs(x-rhs.x) < EPS and abs(y-rhs.y) < EPS and abs(z-rhs.z) < EPS; }
	bool operator!=(const vector3D& rhs) const { return not (*this == rhs); }
	bool operator<(const vector3D& rhs) const {
		if (abs(x-rhs.x) > EPS) return x < rhs.x;
		if (abs(y-rhs.y) > EPS) return y < rhs.y;
		return z < rhs.z;
	}
	T squared_norm() const {return (*this)*(*this);}
	T norm() const {return sqrt(squared_norm()); }
	T scalar_project(const vector3D& v) const {return (*this)*v/v.norm();}
	vector3D vector_project(const vector3D& v) const {return v*(((*this)*v)/(v*v));}
	vector3D normalized() const {return *this / norm();}
	friend vector3D operator*(const T& lhs, const vector3D& rhs) {return rhs*lhs;}
	friend ostream& operator<<(ostream& o, const vector3D& v) {return o << "(" << v.x << "," << v.y << "," << v.z << ")";}
	friend istream& operator>>(istream& i, vector3D& v) {return i >> v.x >> v.y >> v.z;}
};

template <typename T = double>
using V3 = vector3D<T>;