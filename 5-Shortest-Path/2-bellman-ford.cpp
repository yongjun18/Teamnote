// O(VE)

struct Edge{ int next, w; };
vector<Edge> adj[501];

void add_edge(int u, int v, int w){
	adj[u].push_back({v, w});
}
vector<int> dist;

// 음수 사이클이 있을 경우 0 반환, 없으면 1 반환
int bellman_ford(int n, int start){
	dist = vector<int>(n, INF);
	dist[start] = 0;
	int updated;

	for(int t=0; t<n; t++){
		updated = 0;
		for(int now=0; now<n; now++){
			if(dist[now] >= INF) continue;

			for(Edge e : adj[now]){
				int next = e.next;
				int w = e.w;

				if(dist[next] > dist[now] + w){
					dist[next] = dist[now] + w;
					updated = 1;
				}
			}
		}
		if(!updated) break;
	}
	if(updated) return 0;
	else return 1;
}
