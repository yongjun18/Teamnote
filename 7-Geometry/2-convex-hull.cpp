// O(NlogN)

struct vec{
	double x, y;
	vec operator -(const vec &rhs) const { return {x-rhs.x, y-rhs.y}; }
	bool operator <(const vec &rhs) const {
		if(y != rhs.y) return y < rhs.y;
		return x < rhs.x;
	}
	double cross(const vec& rhs) const { return x * rhs.y - rhs.x * y; }
};
double ccw(vec a, vec b){ return a.cross(b); }
double ccw(vec p, vec a, vec b){ return ccw(a-p, b-p); }

// 각정렬을 위한 기준점 s
// 기준점과 a, b가 일직선 상에 있는 경우 기준점에 더 가까운 점이 정렬 시 더 앞쪽으로 오도록 해야함.
vec s;
bool cmp(vec a, vec b){
	if(ccw(a-s, b-s) != 0) return ccw(a-s, b-s) > 0;
	return a < b;
}

vector<vec> convex_hull(vector<vec>& p){
	if(p.size() == 0) return vector<vec>();
	if(p.size() == 1) return vector<vec>(1, p[0]);
	vector<vec> ret;

	sort(p.begin(), p.end());
	s = p[0];
	sort(p.begin()+1, p.end(), cmp);
	ret.push_back(p[0]);
	ret.push_back(p[1]);

	for(int now=2; now<p.size(); now++){
		while(ret.size() >= 2){
			vec last1 = *(ret.end() - 1);
			vec last2 = *(ret.end() - 2);

			if(ccw(last2, last1, p[now]) > 0) break;
			ret.pop_back();
		}
		ret.push_back(p[now]);
	}
	return ret;
}
