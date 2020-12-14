// O(VE)

// matchA[a] : A그룹의 a번 정점과 매칭된 B그룹 정점 번호
// matchB[b] : B그룹의 b번 정점과 매칭된 A그룹 정점 번호
int matchA[1000], matchB[1000];

// adj[a] : A그룹의 a번 정점과 인접한 B그룹 정점 번호
vector<int> adj[1000];
int visit[1000];

int dfs(int a) {
	visit[a] = 1;
	for (int b : adj[a]) {
		if (matchB[b] == -1 || (!visit[matchB[b]] && dfs(matchB[b]))) {
			matchA[a] = b;
			matchB[b] = a;
			return 1;
		}
	}
	return 0;
}

// n : A번 그룹의 정점 개수
int bipartite_matching(int n) {
	int match = 0;
	memset(matchA, -1, sizeof(matchA));
	memset(matchB, -1, sizeof(matchB));

	for (int i = 0; i < n; i++) {
		if (matchA[i] == -1) {
			memset(visit, 0, sizeof(visit));
			if (dfs(i)) match++;
		}
	}
	return match;
}
