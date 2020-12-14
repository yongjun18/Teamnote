// O(EV^2)
// 매 단계마다 차단 유량이 거치는 간선의 개수는 최소 1개는 증가한다. 
// 단계는 최대 V-1번 진행되고 차단유량 찾는 데는 최악의 경우 O(VE).

struct Edge {
	int from, to, capacity, flow;
	Edge* reverse;
};

vector<Edge*> adj[600];
int level[600];
int work[600];

void add_edge(int u, int v, int capacity) {
	Edge* ef = new Edge();
	Edge* er = new Edge();
	*ef = { u, v, capacity, 0, er };
	*er = { v, u, 0, 0, ef };
	adj[u].push_back(ef);
	adj[v].push_back(er);
}

int bfs(int source, int sink) {
	memset(level, -1, sizeof(level));
	level[source] = 0;

	queue<int> q;
	q.push(source);
	while (!q.empty()) {
		int now = q.front(); q.pop();
		for (Edge* e : adj[now]) {
			if (level[e->to] == -1 && e->capacity - e->flow > 0) {
				level[e->to] = level[now] + 1;
				q.push(e->to);
			}
		}
	}
	return (level[sink] != -1);
}

int dfs(int now, int dest, int flow) {
	if (now == dest) return flow;

	for (int &i = work[now]; i < adj[now].size(); i++) {
		Edge* e = adj[now][i];
		if (level[e->to] == level[now] + 1 && e->capacity - e->flow > 0) {
			int amount = dfs(e->to, dest, min(e->capacity - e->flow, flow));
			if (amount > 0) {
				e->flow += amount;
				e->reverse->flow -= amount;
				return amount;
			}
		}
	}
	return 0;
}

int dinic(int source, int sink) {
	int total_flow = 0;
	while (bfs(source, sink)) {
		memset(work, 0, sizeof(work));
		while (1) {
			int flow = dfs(source, sink, INF);
			if (flow == 0) break;
			total_flow += flow;
		}
	}
	return total_flow;
}
