#include "vector2D.cpp"
#include "vector3D.cpp"

template <typename T>
struct line2D {
	P<T> p0, p1, v;
	V3<T> implicit;
	line2D(P<T> _p0 = P<T>(), P<T> _p1 = P<T>(), bool is_2pt = 1) {
		p0 = _p0;
		(is_2pt ? p1 : v) = _p1;
		(is_2pt ? v : p1) = (is_2pt ? _p0-_p1 : _p0+_p1);
		implicit = V3<T>(_p0,1)%V3<T>(_p1,is_2pt);
	}
	line2D(V3<T> u) {
		implicit = u;
		T d = -u.z/(u*u-u.z*u.z);
		p0 = P<T>(u.x*d, u.y*d);
		v = P<T>(u.y,-u.x);
		p1 = p0+v;
	}
	T turn(const P<T>& p) const {return v%(p-p0);}
	bool contains(const P<T>& p) const {return turn(p) == 0;}
	T dist(const P<T>& p) const {return implicit.normalized()*V3<T>(p,1);}
	T squared_dist(const P<T>& p) const {return dist(p)*dist(p);}
	line2D perp(const P<T>& p) const {return line2D(p, v.perp(), 0);}
	P<T> closest_to_origin() const {
		T f = implicit.z/(implicit*implicit-implicit.z*implicit.z); 
		return P<T>(-implicit.x*f,-implicit.y*f);
	}
	bool operator==(const line2D& rhs) const {return abs(v%rhs.v) < EPS and contains(rhs.p0);}
	bool operator!=(const line2D& rhs) const {return not (*this == rhs);}
	bool intersects(const line2D& rhs) const {return abs(v%rhs.v) > EPS or *this == rhs;}
	pair<bool,P<T>> intersection(const line2D& rhs) const {
		V3<T> res = implicit%rhs.implicit;
		return res.z == 0 ? make_pair(0,p0) : make_pair(1,P<T>(res.x/res.z,res.y/res.z));
	}
	friend ostream& operator<<(ostream& o, const line2D& l) {
		return o << "p0: " << l.p0 << "\np1: " << l.p1 << "\nv: " << l.v << "\nimplicit: " << l.implicit;
	}
};

// convert 2 pt or parametric to implicit
// p1 cross p2 or p1 cross v1
// remember points have z = 1 and vectors have z = 0
// intersection of 2 infinite lines is L1%L2, if res.z == 0, then no intersection