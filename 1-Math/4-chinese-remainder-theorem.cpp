// 3으로 나누었을 때 2가 남고, 5로 나누었을 때 3이 남고, 7로 나누었을 때 2가 남는 수는 무엇인가?
// 위와 같은 질문에 대한 해답을 구하는 법

// gcd(ni,nj)=1, i!=j 이면 다음 연립 합동식은
// x = a1(mod n1)
// x = a2(mod n2)
// x = a3(mod n3)
// ...
// x = ak(mod nk)
// 은 법 n1n2n3...nk에 대하여 유일한 해를 갖는다.

// N = n1*n1*n2*...*nk
// Ni = N/ni 일때, Ni와 ni가 서로소이므로 베주항등식에 따라 MiNi + mini = 1을 만족하는 Mi, mi가 존재
// x = sum(1~k)(ai*Mi*Ni) 라고 두면
// x = ai*Mi*Ni = ai(1-mi*ni) = ai (mod ni)이다.
// Mi만 확장 유클리드 알고리즘으로 구해주자.

// n1,n2,n3...nk가 서로소가 아닐 경우 각 모듈러값들을 소인수 분해한 뒤 합동식을 분리한다.
// x = a (mod p1^q1 * p2^ q2 * ... * pk^qk) --> x = a1(mod p1^q1) x = a2(mod p2^q2) ...
// 같은 소인수에 대한 합동식은 큰 차수를 가지는 합동식으로 모순체크를 하며 합쳐준다.
// 그 후 똑같이 CRT

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

ll modinv(ll a, ll b) {
	ll gcdv, x, y;
	gcdv = extended_gcd(a, b, x, y);
	if (gcdv != 1) return -1;
	if (x < 0) x = ((x % b) + b) % b;
	return x;
}

// gcd(n[i], n[j]) == 1
// x == a[i] (mod n[i]) ... 의 해를 구한다.
ll CRT(vector<ll>& a, vector<ll>& n) {
	ll ret = 0, N = 1;
	for (ll now : n) N *= now;
	for (int i = 0; i < a.size(); i++) {
		ll Ni = N / n[i];
		ll Mi = modinv(Ni, n[i]);
		if (Mi == -1) return -1;
		ret += a[i] * Mi * Ni;
		ret %= N;
	}
	return ret;
}	
