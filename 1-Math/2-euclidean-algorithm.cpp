ll gcd(ll m, ll n){
	while (n != 0) {
		ll t = m % n;
		m = n;
		n = t;
	}
	return m;
}

ll lcm(ll a, ll b)  {
	return a * (b / gcd(a, b));
}
