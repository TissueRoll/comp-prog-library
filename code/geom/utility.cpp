int sign (int x) {return x >= 0 ? x ? 1 : 0 : -1;}
int dcmp (double x, double y) {return abs(x-y) < EPS ? 0 : x > y ? 1 : -1;}

template <typename T = double>
T squared_dist(P<T> u, P<T> v) {return (v-u).squared_norm();}

template <typename T = double>
T dist(P<T> u, P<T> v) {return (v-u).norm();}

// special -- UVA453
template <typename T = double>
T fixangle(T t) {return t > 1 ? 1 : t < -1 ? -1 : t;}

double get_angle(double a, double b, double c) {
	double t = b*b+c*c-a*a;
	t /= (2*b*c);
	return acos(fixangle<double>(t));
}

/*
	DANGER: UNTESTED COMPUTATIONAL GEOMETRY AHEAD
*/

// VECTORS ONLY
template <typename T>
T proj(const T& u, const T& v) {
	return v*((u*v)/(v*v));
}

// VECTORS ONLY
template <typename T>
T perp(const T& u, const T& v) {
	return u-proj(u,v);
}