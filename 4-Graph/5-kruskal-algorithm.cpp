// O(ElogE)

struct DisjointSet {
	vector<int> parent, size;
	
	void init(int n) {
		parent = vector<int>(n);
		size = vector<int>(n, 1);
		for (int i = 0; i < n; i++) parent[i] = i;
	}

	int find(int u) {
		if (u == parent[u]) return u;
		return parent[u] = find(parent[u]);
	}

	void merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) return;
		if (size[u] < size[v]) swap(u, v);
		parent[v] = u;
		size[u] += size[v];
	}
};

struct Edge {
	int u, v, w;
	bool operator <(const Edge &ot) const { return w < ot.w; }
};

vector<Edge> edges;
vector<Edge> mst;

int kruskal(int n) {
	int sum = 0;
	DisjointSet ds;
	
	ds.init(n);
	sort(edges.begin(), edges.end());
	
	for (int i = 0; i < edges.size(); i++) {
		if (mst.size() == n - 1) break;
		Edge now = edges[i];
		
		if (ds.find(now.u) == ds.find(now.v)) continue;
		ds.merge(now.u, now.v);
		sum += now.w;

		mst.push_back(now);
	}
	return sum;
}
