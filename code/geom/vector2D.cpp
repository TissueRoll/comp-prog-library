template <typename T>
struct vector2D {
	T x, y;
	vector2D(T _x = 0, T _y = 0): x(_x), y(_y) {}
	vector2D& operator+=(const vector2D& rhs) { x += rhs.x; y += rhs.y; return *this; }
	vector2D& operator-=(const vector2D& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
	vector2D& operator*=(const T& rhs) { x *= rhs; y *= rhs; return *this; }
	vector2D& operator/=(const T& rhs) { x /= rhs; y /= rhs; return *this; }
	vector2D operator-() const { return vector2D(-x,-y); }
	vector2D operator+(const vector2D& rhs) const { return vector2D(*this) += rhs; }
	vector2D operator-(const vector2D& rhs) const { return vector2D(*this) -= rhs; }
	vector2D operator*(const T& rhs) const { return vector2D(*this) *= rhs; }
	vector2D operator/(const T& rhs) const { return vector2D(*this) /= rhs; }
	T operator*(const vector2D& rhs) const { return x*rhs.x+y*rhs.y; } // dot
	T operator%(const vector2D& rhs) const { return x*rhs.y-rhs.x*y; } // cross
	bool operator==(const vector2D& rhs) const { return abs(x-rhs.x) < EPS and abs(y-rhs.y) < EPS; }
	bool operator!=(const vector2D& rhs) const { return not (*this == rhs); }
	bool operator<(const vector2D& rhs) const { return x < rhs.x-EPS or (abs(x-rhs.x) < EPS and y < rhs.y-EPS); }
	vector2D perp() const { return vector2D(-y,x); }
	T angle() const {return atan2(y,x);}
	T squared_norm() const { return (*this)*(*this); }
	T norm() const {return sqrt(squared_norm()); }
	T scalar_project(const vector2D& v) const {return (*this)*v/v.norm();}
	vector2D vector_project(const vector2D& v) const {return v*(((*this)*v)/(v*v));}
	vector2D normalized() const {return *this/norm(); }
	vector2D rotate(const T& a) const {return vector2D(cos(a)*x-sin(a)*y,sin(a)*x+cos(a)*y); }
	friend vector2D operator*(const T& lhs, const vector2D& rhs) {return rhs*lhs; }
	friend ostream& operator<<(ostream& o, const vector2D& v) {return o << "(" << v.x << "," << v.y << ")"; }
	friend istream& operator>>(istream& i, vector2D& v) {return i >> v.x >> v.y;}
};

template <typename T = double>
using P = vector2D<T>;