// O(max(logA, logB))
// 정수해를 갖는 부정 방정식 Ax+By=C가 주어질 때 A와 B의 최대 공약수를
// 구함과 동시에 이 방정식을 만족하는 x, y 값을 찾아온다.
// 다른 해를 구하려면 A/gcdv = A' B/gcdv = B'이라고 했을때
// x에 k*B'를, y에 k*A'를 더하면 된다(k는 정수).
// 해가 존재하려면 C가 gcd(A,B)의 배수여야한다.

// ax + by = gcd(a, b)
ll extended_gcd(ll a, ll b, ll &retx, ll &rety) {
	ll oldx = 1; ll x = 0;
	ll oldy = 0; ll y = 1;
	ll oldr = a; ll r = b;

	while (r != 0) {
		ll q = oldr / r;
		oldr = oldr - q * r; 	swap(oldr, r);
		oldx = oldx - q * x; 	swap(oldx, x);
		oldy = oldy - q * y; 	swap(oldy, y);
	}
	retx = oldx;
	rety = oldy;
	return oldr;
}

// mod b 계에서 a에 대한 곱셈 역원 구하기
// ax + by = 1 을 만족하는 x, y 를 찾는다.
ll modinv(ll a, ll b) {
	ll gcdv, x, y;
	gcdv = extended_gcd(a, b, x, y);
	if (gcdv != 1) return -1;
	if (x < 0) x = ((x % b) + b) % b;
	return x;
}
