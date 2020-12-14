vector<int> adj[1000];
vector<int> order;

// O(N)
// 사이클이 존재하면 0을 반환, 위상정렬 성공하면 1을 반환
int topological_sort(int n) {
	vector<int> indegree(n, 0);
	queue<int> que;
	order.clear();

	for (int i = 0; i < n; i++) {
		for (int next : adj[i])
			indegree[next]++;
	}

	for (int i = 0; i < n; i++) {
		if (indegree[i] == 0) que.push(i);
	}

	for (int t = 0; t < n; t++) {
		if (que.empty()) break;
		int now = que.front(); que.pop();

		order.push_back(now);
		for (int next : adj[now]) {
			indegree[next]--;
			if (indegree[next] == 0) que.push(next);
		}
	}
	return (order.size() == n);
}
