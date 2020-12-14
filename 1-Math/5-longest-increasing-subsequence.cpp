// O(NlogN)
vector<int> subs;
int LIS(vector<int>& arr) {
	vector<int> num, idx; 
	vector<int> prev(arr.size(), -1);

	for (int i = 0; i < arr.size(); i++) {
		int pos;
		pos = lower_bound(num.begin(), num.end(), arr[i]) - num.begin();

		if (pos == num.size()) {
			num.push_back(arr[i]);
			idx.push_back(i);
		}
		else {
			num[pos] = arr[i];
			idx[pos] = i;
		}
		if (pos == 0) prev[i] = -1;
		else prev[i] = idx[pos - 1];
	}

	for (int i = idx[idx.size() - 1]; i != -1; i = prev[i])
		subs.push_back(arr[i]);
	reverse(subs.begin(), subs.end());

	return subs.size();
}
