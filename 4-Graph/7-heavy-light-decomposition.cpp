// 무거운 경로 : 정점 u에서 자식으로 가는 간선 중 서브 트리의 크기가 가장 큰 간선들을 이어놓은 것
// 루트 정점에서 어떤 정점까지의 무거운 경로의 개수는 O(logN)개
// 세그 트리 업데이트 및 쿼리는 O((logN)^2)

const int INF = 1e9;
const int MX = 1e5;

int tree[400000];
int seg_query(int l, int r, int no, int nl, int nr) {
	if (r <= nl || nr <= l) return -INF;
	if (l <= nl && nr <= r) return tree[no];
	int mid = (nl + nr) / 2;
	return max(seg_query(l, r, 2 * no, nl, mid), seg_query(l, r, 2 * no + 1, mid, nr));
}
int seg_query(int l, int r, int n) { return seg_query(l, r, 1, 0, n); }
int seg_update(int idx, int val, int no, int nl, int nr) {
	if (idx < nl || nr <= idx) return tree[no];
	if (nl + 1 == nr && nl == idx) return tree[no] = val;
	int mid = (nl + nr) / 2;
	return tree[no] = max(seg_update(idx, val, 2 * no, nl, mid), seg_update(idx, val, 2 * no + 1, mid, nr));
}
int seg_update(int idx, int val, int n) { return seg_update(idx, val, 1, 0, n); }


vector<int> adj[MX];

// parent[v] : v정점의 부모 정점, 루트(0)의 부모는 그대로 0
// depth[v] : v정점의 깊이, 루트의 깊이는 0
// heavy[v] : v정점에서 자식 중 가장 무거운 정점, v가 리프노드일 경우 -1
// v 간선 : v정점과 부모가 연결된 간선
// head[v] : v간선이 속한 경로(chain)의 제일 상위 간선
// pos[v] : v간선의 세그먼트 트리상의 index
vector<int> parent, depth, heavy, head, pos;
int pcnt;

// parent, depth, heavy 배열 구하기
int dfs(int v) {
	int size = 1;
	int max_child_size = 0;

	for (int next : adj[v]) if (next != parent[v]) {
		parent[next] = v;
		depth[next] = depth[v] + 1;
		
		int next_size = dfs(next);
		size += next_size;
		
		if (max_child_size < next_size) {
			max_child_size = next_size;
			heavy[v] = next;
		}
	}
	return size;
}

// 간선 분리 작업(DFS)
void decompose(int v, int h) {
	head[v] = h;
	pos[v] = pcnt++;

	// v가 리프노드가 아니라면 무거운 간선을 따라서 경로 확장
	if (heavy[v] != -1)
		decompose(heavy[v], h);
	
	// 가벼운 간선 탐색
	// 가벼운 간선은 그가 속한 경로의 head 간선이다.
	for (int next : adj[v]) if (next != parent[v]) {
		if (next != heavy[v])
			decompose(next, next);
	}
}

// 정점의 수 n, 루트는 0으로 고정
void init(int n) {
	parent = vector<int>(n);
	depth = vector<int>(n);
	heavy = vector<int>(n, -1);
	head = vector<int>(n);
	pos = vector<int>(n);
	pcnt = 0;

	dfs(0);
	decompose(0, 0);
}

// v간선 비용을 c로 바꾼다.
void update(int v, int c) {
	seg_update(pos[v], c, MX);
}

// u에서 v로 가는 경로 간선의 비용 중 최대값을 구한다.
int query(int u, int v) {
	int maxv = 0;	
	int path_maxv;

	// u와 v가 다른 경로에 속함
	for (; head[u] != head[v]; v = parent[head[v]]) {
		if (depth[head[u]] > depth[head[v]])
			swap(u, v);
		path_maxv = seg_query(pos[head[v]], pos[v] + 1, MX);
		maxv = max(maxv, path_maxv);
	}
	
	// u와 v가 같은 경로에 속함
	if (depth[u] > depth[v])
		swap(u, v);
	path_maxv = seg_query(pos[u] + 1, pos[v] + 1, MX);
	maxv = max(maxv, path_maxv);
	
	return maxv;
}
