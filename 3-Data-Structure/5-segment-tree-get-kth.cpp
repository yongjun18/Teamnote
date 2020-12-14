const int MX = 1000100;
ll tree[MX*4];

ll update(int idx, ll val, int no, int nl, int nr) {
	if (idx < nl || nr <= idx) return tree[no];
	if (nl + 1 == nr && nl == idx) return tree[no] = val;
	int mid = (nl + nr) / 2;
	return tree[no] = update(idx, val, 2 * no, nl, mid) + update(idx, val, 2 * no + 1, mid, nr);
}
ll update(int idx, ll val){ return update(idx, val, 1, 0, MX); }

int get_kth(ll k, int no, int nl, int nr){
	if(tree[no] < k) return -1;
	if(nl+1 == nr) return nl;
	int mid = (nl+nr)/2;
	if(tree[2*no] >= k) return get_kth(k, 2*no, nl, mid);
	else return get_kth(k - tree[2*no], 2*no+1, mid, nr);
}
int get_kth(ll k){ return get_kth(k, 1, 0, MX); }
