// SA : O(N logN logN)
// LCP : O(N)

// gap=1부터 시작해서 gap*=2하며 매번 접미사의 gap*2글자로만 정렬한다. 
// 각 루프마다 서로 같다고 생각되는 문자열끼리 그룹을 만들고 그룹 번호를 붙인다.
// 그룹의 개수가 n이 됐을 때 종료한다.

int n;
char str[500001];

// SA[x] = v : 접미사를 정렬했을 때 x번째 접미사는 str[v, n-1]
// tmp[i] = SA[i]가 받게될 새로운 그룹번호
// ex) str = "banana", SA = { 5, 3, 1, 0, 4, 2 };
int SA[500000], tmp[500000];

// pos[x] : 접미사 str[x, n-1]가 가진 그룹 번호
int pos[500000];
int gap;

// LCP[x] : SA[x]와 SA[x+1]의 최장 공통 접두사 길이
// ex) str = "banana", LCP = { 1, 3, 0, 0, 2, x };
int LCP[500000];

bool cmp(int i, int j) {
	if (pos[i] != pos[j]) return pos[i] < pos[j];
	i += gap; j += gap;

	if (i < n && j < n) return pos[i] < pos[j];
	else return i > j;
}

void build_SA() {
	n = strlen(str);
	for (int i = 0; i < n; i++) {
		SA[i] = i;
		pos[i] = str[i];
	}
	for (gap = 1;; gap *= 2) {
		sort(SA, SA + n, cmp);

		tmp[0] = 0;
		for (int i = 0; i < n - 1; i++)
			tmp[i + 1] = tmp[i] + cmp(SA[i], SA[i + 1]);

		for (int i = 0; i < n; i++)
			pos[SA[i]] = tmp[i];
		if (tmp[n - 1] == n - 1) break;
	}
}

// "ana"와 "anana"를 비교한 뒤(LCP[1]=3) 한 글자를 떼면 "na"와 "nana"는 LCP[1]-1 글자가 겹친다.
// 한 글자를 뗀 "na와 "nana" 사이에 다른 suffix가 있을 수 있으나, 그 또한 최소 LCP[1]-1 글자 겹친다.
void build_LCP() {
	int match = 0;
	for (int i = 0; i < n; i++) {
		if (match) match--;
		if (pos[i] == n - 1) continue;

		int j = SA[pos[i] + 1];
		while (str[i + match] == str[j + match]) match++;
		LCP[pos[i]] = match;
	}
}
