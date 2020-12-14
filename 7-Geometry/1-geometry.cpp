const double PI = 2.0 * acos(0.0);

struct vec {
	double x, y;
	explicit vec(double x, double y) { this->x = x; this->y = y; }
	vec() { x = 0; y = 0; }
	
	bool operator == (const vec& rhs) { return x == rhs.x && y == rhs.y; }
	bool operator < (const vec& rhs) { if (x != rhs.x) return x < rhs.x; return y < rhs.y; }
	vec operator + (const vec& rhs) { return vec(x + rhs.x, y + rhs.y); }
	vec operator - (const vec& rhs) { return vec(x - rhs.x, y - rhs.y); }
	vec operator * (double rhs) const { return vec(x * rhs, y * rhs); }
	
	// 벡터의 길이 반환
	double norm() const { return hypot(x, y); }
	
	// 방향이 같고 길이가 1인 단위 벡터 반환
	// 영벡터일 경우 반환값은 정의되지 않는다.
	vec normalize() const { double n = norm(); return vec(x / n, y / n); }
	
	// x축의 양의 방향으로부터 벡터까지 반시계방향으로 잰 각도 [0, 2*PI)
	double polar() const { return fmod(atan2(y, x) + 2 * PI, 2 * PI); }
	
	// 내적 a.b = lal*lbl*cos
	// 용도 : 사이각 구하기, 직각 여부 확인, 벡터 사영
	// 내각이 90도면 내적값은 0
	double dot(const vec& rhs) const { return x * rhs.x + y * rhs.y; }
	
	// 벡터를 rhs에 사영
	vec project(const vec& rhs) const {
		vec r = rhs.normalize();
		return r * r.dot(*this);
	}

	// 외적 axb = lal*lbl*sin
	// 용도 : 면적계산(평행사변형), ccw
	double cross(const vec& rhs) const { return x * rhs.y - rhs.x * y; }
};

// 벡터 a를 기준으로 벡터 b가 반시계 방향이면 양수, 시계 방향이면 음수, 평행이면 0
double ccw(vec a, vec b) {
	return a.cross(b);
}

// 점 p->a를 기준으로 a->b가 반시계 방향이면 양수, 시계 방향이면 음수, 평행이면 0
double ccw(vec p, vec a, vec b) {
	return ccw(a - p, b - p);
}

// 두 직선의 교차점 판별. 
// 각 직선을 a + p*d1, c + q*d2 로 나타내어 연립방정식을 푼다.
// p = (c-a)xd / d1xd2
// 두 직선이 평행하면 false, 평행하지 않으면 true 반환후 ret에 교차점 반환
bool line_intersection(vec a, vec b, vec c, vec d, vec& ret) {
	double bxd = (b - a).cross(d - c);
	if (bxd == 0) return false;
	ret = a + (b - a) * ((c - a).cross(d - c) / bxd);
	return true;
}

// 두 선분의 교차점 판별
// 평행한지 먼저 판단 
// 평행하면서 겹치면 true & 아무 점이나 반환, 안 겹치면 false
// 평행하지 않으면서 겹치면 true & 교차점 반환, 안 겹치면 false
bool parallel_segments(vec a, vec b, vec c, vec d, vec& ret) {
	// 평행할 경우 교차점 판별하는 함수
	if (b < a) swap(a, b);
	if (d < c) swap(c, d);
	// 안 겹침
	if (b < c || d < a) return false;
	// 겹침
	if (a < c) ret = c;
	else ret = a;
	return true;
}

// 점 a와 b를 꼭짓점으로 하고 각 변이 x축과 y축에 평행한 사각형 내부에 p가 있다.
// ****** a,b,p 가 일직선 상에 있다고 가정 ******
bool is_bounding_rectangle(vec p, vec a, vec b) {
	if (b < a) swap(a, b);
	return p == a || p == b || (a < p && p < b);
}

// a-b 선분과 c-d 선분의 교점을 p에 반환
// 교점이 여러개일 경우 아무거나 반환
// 교차 안하면 false 반환
bool segment_intersection(vec a, vec b, vec c, vec d, vec& p) {
	if (!line_intersection(a, b, c, d, p)) return parallel_segments(a, b, c, d, p);
	// p가 두 선분에 포함되어 있는 경우에만 참 반환
	// 위 조건문에서 참일 경우 p에 교점이 이미 들어가 있다.
	return is_bounding_rectangle(p, a, b) && is_bounding_rectangle(p, c, d);
}

// 교차점이 필요없는 경우 두 선분의 접촉(교차 + 끝점이 스치듯 만남) 여부
// a-b 기준으로 c와 d가 다른 방향 && c-d 기준으로 a와 b가 다른 방향
// 스치듯이 만나면 ccw가 0이 된다.
bool segment_intersection(vec a, vec b, vec c, vec d) {
	double ab = ccw(a, b, c) * ccw(a, b, d);
	double cd = ccw(c, d, a) * ccw(c, d, b);
	// 두 선분이 한 직선에 있음
	if (ab == 0 && cd == 0) {
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}

// 점과 선 사이의 거리 계산
// 점 p에서 직선 a-b에 내린 수선의 발
vec perpendicular_foot(vec p, vec a, vec b) {
	return a + (p - a).project(b - a);
}

// 점 p와 직선 a-b 사이의 거리
double point_to_line(vec p, vec a, vec b) {
	return (p - perpendicular_foot(p, a, b)).norm();
}

// 점 p와 선분 a-b 사이의 거리
double point_to_segment(vec p, vec a, vec b) {
	if (b < a) swap(a, b);
	vec pf = perpendicular_foot(p, a, b);
	// 수선의 발 존재
	if (pf == a || pf == b || (a < pf && pf < b))
		return (p-pf).norm();
	return min((p - a).norm(), (p - b).norm());
}
