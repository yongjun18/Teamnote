const int MX = 1000100;
int fenn;
// 반드시 1-indexed array를 사용해야 함
ll tree[MX];

// [1, x] 구간합
ll sum(int x) {
	ll ret = 0;
	while (x > 0) {
		ret += tree[x];
		x -= (x & -x);
	}
	return ret;
}

// [x, y] 구간합
ll sum(int x, int y){
	return sum(y) - sum(x - 1);
}

// x 위치에 diff를 더한다
void update(int x, ll diff) {
	while (x <= fenn) {
		tree[x] += diff;
		x += (x & -x);
	}
}
