const int MX = 1000100;
ll arr[MX];
ll tree[2 * MX];

void build() {
	for (int i = 0; i < MX; i++)
		tree[MX + i] = arr[i];
	for (int i = MX - 1; i > 0; i--) 
		tree[i] = tree[i << 1] + tree[i << 1 | 1];
}

void update(int idx, ll val) {
	for (tree[idx += MX] = val; idx > 1; idx >>= 1)
		tree[idx >> 1] = tree[idx] + tree[idx ^ 1];
}

// [l, r) 구간에 대해 구간합 쿼리
ll query(int l, int r) {
	ll res = 0;
	for (l += MX, r += MX; l < r; l >>= 1, r >>= 1){
		if (l & 1) res += tree[l++];
		if (r & 1) res += tree[--r];
	}
	return res;
}
