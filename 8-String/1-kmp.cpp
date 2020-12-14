// O(strlen(H) + strlen(N))

// fail[last] : f[0...last] 문자열의 가장 긴 접미사이면서 접두사
// ex) "abaabaa"-> 0 0 1 1 2 3 4
vector<int> get_fail(int m, const char* f) {
	vector<int> fail(m, 0);
	int match = 0;
	for (int last=1; last<m; last++) {
		while (match > 0 && f[last] != f[match])
			match = fail[match - 1];
		if (f[last] == f[match]) match++;
		fail[last] = match;
	}
	return fail;
}

vector<int> kmp(const char* a, const char* f) {
	int n = strlen(a), m = strlen(f);
	vector<int> ret;
	vector<int> fail = get_fail(m, f);

	int match = 0;
	for (int last=0; last<n; last++) {
		while (match > 0 && a[last] != f[match])
			match = fail[match - 1];

		if (a[last] == f[match]) match++;
		if (match == m) {
			ret.push_back(last - match + 1);
			match = fail[match - 1];
		}
	}
	return ret;
}
