// 평탄한 구간이 극값이 아닌 곳에서 나타나면 사용 불가능. 

// 아래로 볼록한 함수 solve(m)
// [x, y] 구간에서 solve가 최소가 되는 m값을 찾는다. 
// 그러한 m이 여러 개라면 그 중에서도 최소값을 찾는다.
int ternary_search(int x, int y){
	int lo = x-1;
	int hi = y+1;
	while(lo + 2 < hi){
		int m1 = (2*lo + hi)/3;
		int m2 = (lo + 2*hi)/3;

		if(solve[m1] <= solve[m2]) hi = m2;
		else lo = m1;
	}
	return lo+1;
}

// 위로 볼록한 함수 solve(m)
// [x, y] 구간에서 solve가 최대가 되는 m값을 찾는다. 
// 그러한 m이 여러 개라면 그 중에서도 최소값을 찾는다.
int ternary_search(int x, int y){
	int lo = x-1;
	int hi = y+1;
	while(lo + 2 < hi){
		int m1 = (2*lo + hi)/3;
		int m2 = (lo + 2*hi)/3;

		if(solve[m1] >= solve[m2]) hi = m2;
		else lo = m1;
	}
	return lo+1;
}
