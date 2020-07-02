// POSSIBLY IMPRECISE
template <typename T = double>
int CLintersection(const P<T>& c1, const double& r1,
	const line2D<T>& ln,
	P<T>& res1, P<T>& res2) {
	if (abs(ln.dist(c1)) > r1+EPS)
		return 0;
	if (abs(abs(ln.dist(c1))-r1) < EPS) {
		res1 = ln.p0+(c1-ln.p0).vector_project(ln.v);
		return 1;
	}
	P<T> near = ln.p0+(c1-ln.p0).vector_project(ln.v);
	T vd = (c1-near).squared_norm();
	T f = sqrt(r1*r1-vd);
	P<T> u = ln.v.normalized()*f;
	res1 = near+u;
	res2 = near-u;
	return 2;
}