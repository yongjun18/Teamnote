// O(E root V)

int matchA[1000001], matchB[1000001];
int level[1000001];
vector<int> adj[1000001];

// A그룹의 정점에 level을 지정. 
void bfs(int n) {
	queue<int> q;
	for (int i = 0; i < n; i++) {
		if (matchA[i] == -1) {
			level[i] = 0;
			q.push(i);
		}
		else level[i] = INF;
	}
	while (!q.empty()) {
		int a = q.front(); q.pop();
		for (int b : adj[a]) {
			if (matchB[b] != -1 && level[matchB[b]] == INF) {
				level[matchB[b]] = level[a] + 1;
				q.push(matchB[b]);
			}
		}
	}
}

int dfs(int a) {
	for (int b : adj[a]) {
		if (matchB[b] == -1 || (level[matchB[b]] == level[a] + 1 && dfs(matchB[b]))) {
			matchA[a] = b;
			matchB[b] = a;
			return 1;
		}
	}
	return 0;
}

int Hopcroft_Karp(int n, int m) {
	int match = 0;
	memset(matchA, -1, sizeof(matchA));
	memset(matchB, -1, sizeof(matchB));

	while (1) {
		bfs(n);
		int flow = 0;
		for (int i = 0; i < n; i++) {
			if (matchA[i] == -1 && dfs(i)) flow++;
		}
		if (flow == 0) break;
		match += flow;
	}
	return match;
}
