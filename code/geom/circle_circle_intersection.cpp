// WARNING: UNTESTED

#include "vector2D.cpp"
#include "vector3D.cpp"
#include "utility.cpp"
#include "circle_line_intersection.cpp"

// IMPRECISE AND BROKEN
template <typename T = double>
int CCintersection (const P<T>& c1, const T& r1, 
	const P<T>& c2, const T& r2, 
	P<T>& res1, P<T>& res2) {

	// infinite intersections
	if (c1 == c2 and dcmp(r1,r2) == 0 and r1 > EPS)
		return 3;
	// same point, no intersections
	if (c1 == c2 and dcmp(r1,r2) != 0 and r1 > EPS)
		return 0;
	// same point, same redius, zero radius
	if (c1 == c2 and dcmp(r1,r2) == 0 and r1 < EPS) {
		res1 = c1;
		return 1;
	}
	// circles too far from each other
	if ((c2-c1).norm() < max(r1,r2)-min(r1,r2) or (c2-c1).norm() > max(r1,r2)+min(r1,r2))
		return 0;
	
	P<T> tc2 = c2-c1;
	V3<T> converted(-2*tc2.x,-2*tc2.y,tc2*tc2+r1*r1-r2*r2);
	line2D<T> ln(converted);
	int ans = CLintersection(P<T>(), r1, ln, res1, res2);
	res1 += c1;
	res2 += c1;
	return ans;
}

// from https://github.com/MeGaCrazy/CompetitiveProgramming/blob/c099628e643065a7bae09af22c4cbce1216e4db9/UVA/UVA_453.cpp
// thank you for ending my suffering
template <typename T = double>
vector<P<T>> CCintersection2(const P<T>& c1, const double& r1,
	const P<T>& c2, const double& r2) {
	if (c1 == c2 and dcmp(r1,r2) == 0 and r1 > EPS)
		return vector<P<T>>();
	double a1 = (c2-c1).angle(), a2 = get_angle(r2,(c2-c1).norm(),r1);
	if (isnan(a2))
		a2 = 0;
	P<T> v(r1*cos(a1+a2),r1*sin(a1+a2));
	vector<P<T>> ret;
	ret.push_back(v+c1);
	if (dcmp(r1*r1,(ret[0]-c1).squared_norm()) != 0 or dcmp(r2*r2,(ret[0]-c2).squared_norm()) != 0)
		return vector<P<T>>(3,P<T>());
	v = P<T>(r1*cos(a1-a2),r1*sin(a1-a2));
	ret.push_back(v+c1);
	if (ret[0] == ret[1])
		ret.pop_back();
	return ret;
}