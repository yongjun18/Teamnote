// O(V^3)
// 음 사이클만 없다면 음의 가중치가 있어도 사용 가능

int adj[100][100];
// dis[k][i][j] = 0~k번 정점을 거쳐서 i에서 j로 가는 최단경로
int dis[100][100];

void floyd(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if(i == j) dis[i][j] = 0;
			else dis[i][j] = adj[i][j];
		}
	}
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
		}
	}
}
