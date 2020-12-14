// 그래프에 존재하는 모든 간선을 정확히 1번씩만 방문하는 경로
// 시작점과 도착점이 같으면 오일러 회로, 아닐 경우 오일러경로

struct Edge {
	int to, cnt;
	Edge* reverse;
};

int n;
vector<Edge*> adj[1000];
int visit[1000];

int start;
vector<int> euler_circuit;

// 양방향 간선 u---(cnt)---v
void add_edge(int u, int v, int cnt) {
	Edge* ef = new Edge();
	Edge* er = new Edge();
	*ef = { v, cnt ,er };
	*er = { u, cnt, ef };
	adj[u].push_back(ef);
	adj[v].push_back(er);
}

void dfs(int now) {
	for (Edge* e : adj[now]) if (!visit[e->to]) {
		visit[e->to] = 1;
		dfs(e->to);
	}
}

// 오일러 회로 존재 여부 확인
int exist() {
	for (int i = 0; i < n; i++) {
		int degree = 0;
		for (Edge* e : adj[i])
			degree += e->cnt;
		if (degree % 2 == 1) return 0;
	}

	for (int i = 0; i < n; i++) if (adj[i].size()) {
		start = i;
		dfs(i);
		break;
	}
	for (int i = 0; i < n; i++) if (adj[i].size() && !visit[i])
		return 0;

	return 1;
}

// 오일러 회로 찾기
void get_euler_circuit(int now) {
	for (Edge* e : adj[now]) if (e->cnt) {
		e->cnt--;
		e->reverse->cnt--;
		get_euler_circuit(e->to);
	}
	euler_circuit.push_back(now);
}
