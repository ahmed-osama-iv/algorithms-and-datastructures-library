vector < pair<int,int> > adj[maxV];

int P[maxV], lvl[maxV];
int anc[maxV][maxLog];
int ans[maxV][maxLog];

void buildLCA(int v, int p) { // O(NlogN)

	anc[v][0] = p;
    lvl[v] = lvl[p] + 1;

    for(int i = 0; i < maxLog - 1; i++) {
        anc[v][i+1] = anc[anc[v][i]][i];
        ans[v][i+1] = max(ans[v][i], ans[anc[v][i]][i]);
    }

	for(auto e : adj[v]) {
        int u = e.F;
        int cost = e.S;
        if(u != p) {
            ans[u][0] = cost;
            buildLCA(u, v);
        }
	}
}

int LCA(int u, int v) { // O(LogN)

	if(lvl[u] < lvl[v]) swap(u, v);

	for(int i = maxLog - 1; i >= 0; i--) {
		if(lvl[anc[u][i]] >= lvl[v]) {
			u = anc[u][i];
		}
	}

	if(u == v) return u;

	for(int i = maxLog - 1; i >= 0; i--) {
		if(anc[u][i] != anc[v][i]) {
			u = anc[u][i], v = anc[v][i];
		}
	}

	return anc[u][0];
}

int pathAns(int u, int v) {

    int res = 0;

	if(lvl[u] < lvl[v]) swap(u, v);

	for(int i = maxLog - 1; i >= 0; i--) {
		if(lvl[anc[u][i]] >= lvl[v]) {
			res = max(res, ans[u][i]);
			u = anc[u][i];
		}
	}

	if(u == v) return res;

	for(int i = maxLog - 1; i >= 0; i--) {
		if(anc[u][i] != anc[v][i]) {
			res = max(res, ans[u][i]);
			res = max(res, ans[v][i]);
			u = anc[u][i], v = anc[v][i];
		}
	}
	
	res = max(res, ans[u][0]);
    res = max(res, ans[v][0]);

	return res;
}

