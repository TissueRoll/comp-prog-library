#include "vector3D.cpp"

template <typename T>
struct Quat {
	T s;
	V3<T> v;
	Quat(T _s = 0, V3<T> _v = V3<T>(0,0,0)): s(_s), v(_v) {}
	Quat operator!() const {return Quat(s, -v);} // conjugate
	Quat operator+=(const Quat &rhs) {s += rhs.s; v += rhs.v; return *this; }
	Quat operator-=(const Quat &rhs) {s -= rhs.s; v -= rhs.v; return *this; }
	Quat operator*=(const Quat &rhs) {
		T ts = s; V3<T> tv = v;
		s = ts*rhs.s-tv*rhs.v;
		v = rhs.v*ts + tv*rhs.s + tv%rhs.v;
		return *this;
	}
	Quat operator*=(const T& rhs) {s *= rhs; v *= rhs; return *this;}
	Quat operator/=(const T& rhs) {s /= rhs; v /= rhs; return *this;}
	Quat operator+(const Quat &rhs) const {return Quat(*this)+=rhs;}
	Quat operator-(const Quat &rhs) const {return Quat(*this)-=rhs;}
	Quat operator*(const Quat &rhs) const {return Quat(*this)*=rhs;}
	Quat operator*(T c) const {return Quat(*this)*=c;}
	Quat operator/(T c) const {return Quat(*this)/=c;}
	Quat conjugate() const {return !Quat(*this);}
	T squared_norm() const {return s*s + v*v;}
	T norm() const {return sqrt(squared_norm());}
	Quat inv() const {return Quat(conjugate()/squared_norm());}
	Quat operator/=(const Quat &rhs) {
		Quat r = rhs.inv();
		T ts = s; V3<T> tv = v;
		s = ts*r.s-tv*r.v;
		v = r.v*ts + tv*r.s + tv%r.v;
		return *this;
	}
	Quat operator/(const Quat &rhs) const { return Quat(*this)/=rhs; }
	Quat operator^(const Quat &rhs) const {
		// q(this)^p(rhs)
		if (squared_norm() == 0) 
			return Quat(0,V3<T>(0,0,0));
		V3<T> tv = v;
		V3<T> qvn = (tv.norm() <= 1e-9 ? tv : tv/tv.norm());
		Quat lnq(log(norm()),qvn*atan2(tv.norm(), s));
		Quat omega = rhs*lnq;
		V3<T> ovn = (omega.v.norm() <= 1e-9 ? omega.v : omega.v/omega.v.norm());
		Quat result = Quat(cos(omega.v.norm())*exp(omega.s), ovn*sin(omega.v.norm())*exp(omega.s));
		return result;
	}
	friend Quat operator*(const T& lhs, const Quat& rhs) {return rhs*lhs; }
	friend ostream& operator<<(ostream& o, const Quat& q) {return o << "<" << q.s << "," << q.v << ">";}
	friend istream& operator>>(istream& i, Quat& q) {return i >> q.s >> q.v;}
};

using Q = Quat<double>;