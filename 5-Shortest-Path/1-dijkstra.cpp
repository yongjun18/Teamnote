// O(ElogV)
// 음수 간선이 있는 그래프의 경우 그 정당성이 보장되지 않음

struct Edge{ int next, w; };
struct QNode{
	int now, wsum;
	bool operator <(const QNode& rhs) const { return wsum > rhs.wsum; }
};

vector<Edge> adj[20001];

void add_edge(int u, int v, int w){
	adj[u].push_back({v, w});
}

vector<int> dist;

void dijkstra(int n, int start){
	dist = vector<int>(n, INF);
	dist[start] = 0;
	priority_queue<QNode> pq;
	pq.push({start, 0});

	while(pq.size()){
		int now = pq.top().now;
		int wsum = pq.top().wsum;
		pq.pop();

		if(dist[now] < wsum) continue;

		for(Edge e : adj[now]){
			int next = e.next;
			int next_dist = wsum + e.w;
			if(dist[next] > next_dist){
				dist[next] = next_dist;
				pq.push({next, next_dist});
			}
		}
	}
}
