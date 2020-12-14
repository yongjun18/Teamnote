struct Trie{
	Trie* go[26];
	Trie* fail;
	int finish;
	Trie() : go{}, fail(0), finish(0) {}
};
Trie* root;

void trie_insert(const string key){
	Trie* now = root;
	for(int i=0; i<key.size(); i++){
		int nxt = key[i] - 'a';
		if(now->go[nxt] == NULL)
			now->go[nxt] = new Trie();
		now = now->go[nxt];
		}
	now->finish++;
}

void build_fail(){
	root->fail = root;
	queue<Trie*> q;

	for(int i=0; i<26; i++){
		Trie* nxt = root->go[i];
		if(nxt != NULL){
			nxt->fail = root;
			q.push(nxt);
		}
	}
	while(q.size()){
		Trie* now = q.front(); q.pop();

		for(int i=0; i<26; i++){
			Trie* nxt = now->go[i];
			if(nxt != NULL){
				Trie* dest = now->fail;
				while(dest != root && dest->go[i] == NULL)
					dest = dest->fail;
				if(dest->go[i]) dest = dest->go[i];
				nxt->fail = dest;

				if(nxt->fail->finish)
					nxt->finish += nxt->fail->finish;
				q.push(nxt);
			}
		}
	}
}

Trie* step(Trie* now, char ch){
	Trie* pv = now;
	int nxt = ch -'a';
	while(now != root && now->go[nxt] == NULL)
		now = now->fail;
	if(now->go[nxt])
		now = now->go[nxt];
//	pv->go[nxt] = now;

	return now;
}
