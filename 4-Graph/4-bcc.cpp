// BCC에 속한 정점 한 개를 지워도 남은 정점들이 모두 연결되어 있다.

struct Edge { int u, v; };

vector<int> adj[100000];
int bcnt = 0;
vector<vector<Edge> > BCC;
stack<Edge> st;
// bnum[x] == 정점 x가 속한 BCC 번호
vector<int> bnum[100000];

// dfsn[x] : dfs 탐색 순서 번호
int dfsn[100000];
int cnt = 0;
int visit[100000];

// 단절선 : 해당 간선을 없애면 그래프가 두 개 이상으로 나누어짐
vector<Edge> AE;
// 단절점 : 해당 정점을 없애면 그래프가 두 개 이상으로 나누어짐
vector<int> AP;

int dfs(int prev, int now) {
	visit[now] = 1;
	dfsn[now] = cnt++;

	int minv = dfsn[now];
	for (int next : adj[now]) {
		if (next == prev) continue;

		if (!visit[next] || (dfsn[now] > dfsn[next]))
			st.push({ now, next });

		if (visit[next]) 
			minv = min(minv, dfsn[next]);
		else {
			int next_minv = dfs(now, next);
			minv = min(minv, next_minv);

			if (next_minv > dfsn[now]) AE.push_back({ now, next });

			if (next_minv >= dfsn[now]) {
				vector<Edge> new_bcc;
				while (!st.empty()) {
					int u = st.top().u;
					int v = st.top().v; st.pop();
					new_bcc.push_back({ u, v });

					if (bnum[u].empty() || bnum[u].back() != bcnt)
						bnum[u].push_back(bcnt);
					if (bnum[v].empty() || bnum[v].back() != bcnt)
						bnum[v].push_back(bcnt);

					if (u == now && v == next) break;
				}
				BCC.push_back(new_bcc);
				bcnt++;
			}
		}
	}
	return minv;
}

int get_BCC(int n) {
	for (int i = 0; i < n; i++) {
		if (!visit[i]) dfs(-1, i);
	}
	return BCC.size();
}

int get_AP(int n) {
	for (int i = 0; i < n; i++) {
		if (bnum[i].size() > 1)
			AP.push_back(i);
	}
	return AP.size();
}
