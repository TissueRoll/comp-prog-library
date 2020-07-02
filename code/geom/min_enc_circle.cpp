// WARNING: UNTESTED

// implemented based on KTH team notebook
template<typename T = double>
pair<T,P<T>> mec2(vector<P<T>>& S, P<T> a, P<T> b, int n) {
	T hi = 1e18, lo = -hi;
	for (int i = 0; i < n; ++i) {
		T si = (b-a)%(S[i]-a);
		if (abs(si) < EPS)
			continue;
		P<T> m = ccCenter(a,b,S[i]);
		T cr = (b-a)%(m-a);
		if (si < 0)
			hi = min(hi, cr);
		else
			lo = max(lo, cr);
	}
	T v = (0 < lo ? lo : hi < 0 ? hi : 0);
	P<T> c = (a+b)/2.0 + (b-a).perp()*v/(b-a).squared_norm();
	return make_pair((a-c).squared_norm(), c);
}

template<typename T = double>
pair<T,P<T>> mec(vector<P<T>>& S, P<T> a, int n) {
	random_shuffle(S.begin(), S.begin()+n);
	P<T> b = S[0], c = (a+b)/2.0;
	T r = (a-c).squared_norm();
	for (int i = 1; i < n; ++i) {
		if ((S[i]-c).squared_norm() > r*(1+1e-8)) {
			tie(r,c) = (n == S.size() ? mec(S,S[i],i) : mec2(S,a,S[i],i));
		}
	}
	return make_pair(r,c);
}

template<typename T = double>
pair<T,P<T>> welzl(vector<P<T>> S) {
	pair<T,P<T>> r = mec(S,S[0],S.size());
	return make_pair(sqrt(r.fi),r.se);
}