// Z[i] : str[0....k) == str[i...i+k)인 가장 큰 k의 값 (i>0)
// Z[i] : str의 prefix이면서 str[i...]의 prefix인 prefix중 가장 긴 것의 길이
int Z[1000100];

void get_Z(int len, char* str){
	// [l, r] = 0<l<i에서 구하고자 했던 부분 문자열 str[l, r] 중 가장 r이 큰 것 
	int l = -1, r = -1;
	for(int i=1; i<len; i++){
		if(r < i) Z[i] = 0;
		else Z[i] = min(Z[i-l], r-i+1);

		while(i+Z[i] < len && str[i+Z[i]] == str[Z[i]]) Z[i]++;
		if(r < i+Z[i]-1) l = i, r = i+Z[i]-1;
	}
}
