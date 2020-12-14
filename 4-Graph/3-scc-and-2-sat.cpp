// f = (!x1 v x2) ^ (!x2 v x3) ^ (x1 v x3) ...
// 모든 절이 참이어야 한다.
// (x1 v x3)에서 x1이 거짓이면 x3은 참,  x3이 거짓이면 x1은 참이 되어야 한다.

// SCC로 묶었을 때, 어떤 원소가 참이라면 같은 SCC의 모든 원소가 참이 되어야한다.
// SCC 하나에 x1과 !x1이 같이 있다면 전체 식을 참으로 만들 수 없다.

// 어떤 것을 참으로 만들고 거짓으로 만들지 결정할 때는
// SCC를 위상정렬 한 후 훑으면서 처음 만나는 정점은 false로 설정하면 된다.

vector<int> adj[20000];
vector< vector<int> > SCC;

// dfsn[x] : dfs 탐색 순서 번호
int dfsn[20000];
int visit[20000];
int finish[20000];
int cnt = 0;
stack<int> st;

// snum[i] : i번 원소가 속해있는 SCC 번호
int snum[20000];
int scnt = 0;

// 전체 식을 참으로 만들기 위한 각 정점의 boolean 값
int result[20000];

// x의 dfsn 값을 반환
int dfs(int x) {
	visit[x] = 1;
	dfsn[x] = cnt++;
	st.push(x);

	int minv = dfsn[x];
	for (int next : adj[x]) {
		if (!visit[next]) minv = min(minv, dfs(next));
		else if (!finish[next]) minv = min(minv, dfsn[next]);
	}

	if (minv == dfsn[x]) {
		vector<int> now_scc;
		while (1) {
			int top = st.top(); st.pop();
			snum[top] = scnt;

			now_scc.push_back(top);
			finish[top] = 1;
			if (top == x) break;
		}
		SCC.push_back(now_scc);
		scnt++;
	}
	return minv;
}

int get_SCC(int n) {
	for (int i = 0; i < n; i++) {
		if (!visit[i]) dfs(i);
	}
	return SCC.size();
}

// 2-SAT를 위한 절 처리 함수
void closure(int x, int xbool, int y, int ybool) {
	adj[x * 2 + !xbool].push_back(y * 2 + ybool);
	adj[y * 2 + !ybool].push_back(x * 2 + xbool);
}

// 전체 식을 참으로 만들 수 없다면 0 반환
int get_result(int n) {
	for (int i = 0; i < n; i++) {
		if (snum[2*i] == snum[2*i + 1])
			return 0;
	}

	memset(result, -1, sizeof(result));
	for (int i = scnt - 1; i >= 0; i--) {
		for (int now : SCC[i]) {
			if (result[now] != -1) continue;
			result[now] = 0;
			result[now ^ 1] = 1;
		}
	}
	return 1;
}
