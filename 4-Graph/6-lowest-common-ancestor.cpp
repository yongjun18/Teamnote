// O(logn)
// 모든 정점들 사이에 경로가 존재하는 트리일 때 적용 가능

vector<int> adj[100000];

// parent[i][k] = i번 정점의 2^k번째 부모 (2^17 = 131,000)
int parent[100000][18];
int depth[100000];

void add_edge(int u, int v) {
	adj[u].push_back(v);
	adj[v].push_back(u);
}

void dfs(int now) {
	for (int next : adj[now]) {
		if (depth[next] != -1) continue;

		depth[next] = depth[now] + 1;
		parent[next][0] = now;
		dfs(next);
	}
}

void build(int n) {
	memset(depth, -1, sizeof(depth));
	memset(parent, -1, sizeof(parent));

	depth[0] = 0;
	dfs(0);

	for (int k = 0; k < 18 - 1; k++) {
		for (int i = 0; i < n; i++) {
			if (parent[i][k] != -1)
				parent[i][k + 1] = parent[parent[i][k]][k];
			
		}
	}
}

int LCA(int u, int v) {
	if (depth[u] < depth[v]) swap(u, v);

	for (int k = 18 - 1; k >= 0; k--) {
		int ancu = parent[u][k];
		if (ancu != -1 && depth[ancu] >= depth[v])
			u = ancu;
	}
	if (u == v) return u;

	for (int k = 18 - 1; k >= 0; k--) {
		int ancu = parent[u][k];
		int ancv = parent[v][k];

		if(ancu == ancv) continue;
		u = ancu;
		v = ancv;
	}

	u = parent[u][0];
	return u;
}
