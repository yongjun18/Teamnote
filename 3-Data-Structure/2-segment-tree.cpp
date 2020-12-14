ll arr[1000100];
ll tree[4000400];

ll build(int no, int nl, int nr) {
	if (nl + 1 == nr) return tree[no] = arr[nl];
	int mid = (nl + nr) / 2;
	return tree[no] = build(2 * no, nl, mid) + build(2 * no + 1, mid, nr);
}
ll build(int n) { return build(1, 0, n); }

// [l, r) 구간에 대해 구간합 쿼리
ll query(int l, int r, int no, int nl, int nr) {
	if (r <= nl || nr <= l) return 0;
	if (l <= nl && nr <= r) return tree[no];
	int mid = (nl + nr) / 2;
	return query(l, r, 2 * no, nl, mid) + query(l, r, 2 * no + 1, mid, nr);
}
ll query(int l, int r, int n) { return query(l, r, 1, 0, n); }

ll update(int idx, ll val, int no, int nl, int nr) {
	if (idx < nl || nr <= idx) return tree[no];
	if (nl + 1 == nr && nl == idx) return tree[no] = val;
	int mid = (nl + nr) / 2;
	return tree[no] = update(idx, val, 2 * no, nl, mid) + update(idx, val, 2 * no + 1, mid, nr);
}
ll update(int idx, ll val, int n) { return update(idx, val, 1, 0, n); }
