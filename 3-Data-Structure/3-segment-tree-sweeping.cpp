// 화성지도 
// https://www.acmicpc.net/problem/3392

#include <stdio.h>
#include <memory.h>
#include <stack>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

const int MX = 40100;
ll tree[MX * 4];
ll cnt[MX * 4];

ll update(int l, int r, ll val, int no, int nl, int nr){
	if (r <= nl || nr <= l) return tree[no];
	if (l <= nl && nr <= r){ 
		cnt[no] += val;
		if (cnt[no] > 0) return tree[no] = nr - nl;
		if (nl + 1 < nr) return tree[no] = tree[2 * no] + tree[2 * no + 1];
		return tree[no] = 0;
	}
	int mid = (nl + nr) / 2;
	update(l, r, val, 2 * no, nl, mid);
	update(l, r, val, 2 * no + 1, mid, nr);
	
	if (cnt[no] > 0) return tree[no];
	else return tree[no] = tree[2 * no] + tree[2 * no + 1];
}
void update(int l, int r, ll val, int n){ update(l, r, val, 1, 0, n); }

struct Range{
	int y, x1, x2, t;
	bool operator < (const Range& rhs) const{
		return y < rhs.y;
	}
};

vector<Range> rg;

int main() 
{
	int n;
	ll ans;
	
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		rg.push_back({ y1, x1, x2, 1 });
		rg.push_back({ y2, x1, x2, -1 });
	}
	sort(rg.begin(), rg.end());

	ans = 0;
	for (int i = 0; i < rg.size(); i++){
		if (i > 0 && rg[i - 1].y != rg[i].y){
			ans += tree[1] * (rg[i].y - rg[i - 1].y);
		}
		update(rg[i].x1, rg[i].x2, rg[i].t, MX);
	}
	printf("%lld\n", ans);
	return 0;
}
