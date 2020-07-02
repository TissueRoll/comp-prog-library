template<typename T = double>
T ccRadius(const P<T>& a, const P<T>& b, const P<T>& c) {
	return (b-a).norm()*(c-b).norm()*(a-c).norm()/abs((b-a)%(c-a))/2.0;
}

template<typename T = double>
P<T> ccCenter(const P<T>& a, const P<T>& b, const P<T>& c) {
	P<T> u = c-a, v = b-a;
	return a + (u*v.squared_norm()-v*u.squared_norm()).perp()/(u%v)/2.0;
}