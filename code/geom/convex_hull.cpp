// WARNING: UNTESTED

#include "vector2D.cpp"

template <typename T = double>
vector<P<T>> convex_hull(vector<P<T>> pts) {
	sort(pts.begin(), pts.end());
	int top = 0;
	vector<P<T>> stk(2*pts.size());
	for (int i = 0; i < pts.size(); ++i) {
		while (top >= 2 and (stk[top-1]-stk[top-2])%(pts[i]-stk[top-2]) <= 0) top--;
		stk[top++] = pts[i];
	}
	for (int i = pts.size()-2, t = top+1; i >= 0; --i) {
		while (top >= t and (stk[top-1]-stk[top-2])%(pts[i]-stk[top-2]) <= 0) top--;
		stk[top++] = pts[i];
	}
	stk.resize(top-1);
	return stk;
}