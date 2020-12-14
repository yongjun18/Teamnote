// lazy[no] : 왼쪽, 오른쪽 서브트리에 전파해야 하는 값
// 루트부터 lazy값이 처음으로 0이 아닌 노드는 갱신된 노드이다.
int arr[1000000];
ll sum[4000100];
ll lazy[4000100];

ll build(int no, int nl, int nr){
	if(nl+1 == nr) return sum[no] = arr[nl];
	int mid = (nl+nr)/2;
	return sum[no] = build(2*no, nl, mid) + build(2*no+1, mid, nr);
}
ll build(int n){ return build(1, 0, n); }

// 노드의 lazy값을 자식에게 전파
void propagate(int no, int nl, int nr){
	if(nl+1 != nr){
		int mid = (nl+nr)/2;
		sum[2*no] += lazy[no] * (mid-nl);
		sum[2*no+1] += lazy[no] * (nr-mid);
		lazy[2*no] += lazy[no];
		lazy[2*no+1] += lazy[no];
	}
	lazy[no] = 0;
}

// [l, r) 구간에 val 값을 더한다.
void update(int l, int r, ll val, int no, int nl, int nr){
	if(r <= nl || nr <= l) return;
	if(l <= nl && nr <= r){
		sum[no] += (nr-nl) * val;
		lazy[no] += val;
		return;
	}
	propagate(no, nl, nr);
	int mid = (nl+nr) / 2;
	update(l, r, val, 2*no, nl, mid);
	update(l, r, val, 2*no+1, mid, nr);
	sum[no] = sum[2*no] + sum[2*no+1];
}
void update(int l, int r, ll val, int n){ update(l, r, val, 1, 0, n); }

// [l,r) 구간의 합 쿼리
ll query(int l, int r, int no, int nl, int nr){
	if(r <= nl || nr <= l) return 0;
	if(l <= nl && nr <= r) return sum[no];

	propagate(no, nl, nr);
	int mid = (nl+nr)/2;
	return query(l, r, 2*no, nl, mid) + query(l, r, 2*no+1, mid, nr);
}
ll query(int l, int r, int n) { return query(l, r, 1, 0, n); }
