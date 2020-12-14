// 구간 [x, y] 에서 solve가 참이 되는 최소값을 찾는다. 없을 경우 y+1 리턴
// [ 거짓 ... 거짓, 참 ... 참 ] 인 꼴에서 사용
ll parametric_search(ll x, ll y){
	ll lo = x - 1;
	ll hi = y + 1;
	while (lo + 1 < hi){
		ll mid = (lo + hi) / 2;
		if (solve(mid)) hi = mid;
		else lo = mid;
	}
	return hi;
}

// 구간 [x, y] 에서 solve가 참이 되는 최대값을 찾는다. 없을경우 x-1리턴
// [참 ... 참, 거짓 ... 거짓] 인 꼴에서 사용
ll parametric_search(ll x, ll y) {
	ll lo = x - 1;
	ll hi = y + 1;
	while (lo + 1 < hi) {
		ll mid = (lo + hi) / 2;
		if (solve(mid)) lo = mid;
		else hi = mid;
	}
	return lo;
}
