vector < pair<int,int> > adj[maxV];

int P[maxV], lvl[maxV];
int anc[maxV][20];
int ans[maxV][20];

void buildLCA(int v, int p) { // O(NlogN)

	anc[v][0] = p;
    lvl[v] = lvl[p] + 1;

    for(int i = 0; i < maxLog-1; i++){
        anc[v][i+1] = anc[anc[v][i]][i];
        ans[v][i+1] = min(ans[v][i], ans[anc[v][i]][i]);
    }

	for(auto e : adj[v]){
        int u = e.F;
        int cost = e.S;
        if(u != p){
            ans[u][0] = cost;
            buildLCA(u, v);
        }
	}
}

int LCA(int v,int u) { // O(LogN)
	if(lvl[v] < lvl[u])
		swap(v, u);
	for(int i = maxLog-1; i>=0; i--)
		if(anc[v][i] + 1 && lvl[anc[v][i]] >= lvl[u])
			v = anc[v][i];

	if(v == u)
		return v;
	for(int i = maxLog-1; i >= 0; i--)
		if(anc[v][i] - anc[u][i])
			v = anc[v][i], u = anc[u][i];
	return anc[v][0];
}

int pathAns(int u, int v){  // O(LogN)
    int lca = LCA(u, v);
    int res = INF;

    for(int i = maxLog-1; i>=0; i--){
        if(lvl[anc[u][i]] >= lvl[lca]){
            res = min(res, ans[u][i]);
            u = anc[u][i];
        }
    }

    for(int i = maxLog-1; i>=0; i--){
        if(lvl[anc[v][i]] >= lvl[lca]){
            res = min(res, ans[v][i]);
            v = anc[v][i];
        }
    }

    return res;
}
