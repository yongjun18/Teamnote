// O(NlogN)
// 각 단계에 해당하는 원소들을 정렬된 상태로 가진다.
// 사용된 merge 함수는 정렬된 배열 2개를 매개변수로 전달하면 정렬된 상태로 합쳐준다.

int arr[100100];
vector<int> tree[400400];

void build(int no, int nl, int nr){
	if(nl+1 == nr){
		tree[no].push_back(arr[nl]);
		return;
	}
	int mid = (nl+nr)/2;
	build(2*no, nl, mid);
	build(2*no+1, mid, nr);

	vector<int> &l = tree[2*no];
	vector<int> &r = tree[2*no+1];
	tree[no].resize(l.size() + r.size());
	merge(l.begin(), l.end(), r.begin(), r.end(), tree[no].begin());
}
void build(int n){ build(1, 0, n); }

// [l, r) 구간에서 k보다 큰 값의 개수 출력
int query(int l, int r, int k, int no, int nl, int nr){
	if(r <= nl || nr <= l)
		return 0;
	if(l <= nl && nr <= r)
		return tree[no].end() - upper_bound(tree[no].begin(), tree[no].end(), k);
	int mid = (nl+nr)/2;
	return query(l, r, k, 2*no, nl, mid) + query(l, r, k, 2*no+1, mid, nr);
}
int query(int l, int r, int k, int n){ return query(l, r, k, 1, 0, n); }
