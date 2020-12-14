// minf[x] : x의 소인수 중 가장 작은 값
int minf[1000001];

// O(NlglgN)
void eratos(int n) {
	minf[0] = minf[1] = -1;
	for (int i = 2; i <= n; i++) minf[i] = i;

	for (int i = 2; i*i <= n; i++) {
		if (minf[i] == i) {
			for (int j = i*i; j <= n; j += i) {
				if (minf[j] == j) minf[j] = i;
			}
		}
	}
}

// n! 을 소인수 분해하는법
// 소수 p1, p2, p3... 에 대해 n! = p1^x1 * p2^x2 * p3^x3 ... 라면
// xi = 0, while(n != 0){ xi += n/pi; n /= pi; }
