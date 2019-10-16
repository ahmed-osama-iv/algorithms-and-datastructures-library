const int MAXV = 1e5 + 5;
const int MAXLG = 20;

vector < pair<int,int> > adj[MAXV];

int lvl[MAXV];
int anc[MAXV][MAXLG];
int ans[MAXV][MAXLG];

void buildLCA(int u, int p) { // O(NlogN)

	anc[u][0] = p;
	lvl[u] = lvl[p] + 1;

	for(int i = 0; i < MAXLG - 1; i++) {
		anc[u][i+1] = anc[anc[u][i]][i];
		ans[u][i+1] = max(ans[u][i], ans[anc[u][i]][i]);
	}

	for(auto e : adj[u]) {
		int v = e.first;
		int cost = e.second;
		if(v != p) {
			ans[v][0] = cost;
			buildLCA(v, u);
		}
	}
}

int kth_anc(int u, int k) { // O(NlogN)

    int cur = u, h = 0;
    while(k) {
        if(k & 1) cur = anc[cur][h];
        k/=2, h++;
    }

    return cur;
}

int LCA(int u, int v) { // O(LogN)

	if(lvl[u] < lvl[v]) swap(u, v);

	for(int i = MAXLG - 1; i >= 0; i--) {
		if(lvl[anc[u][i]] >= lvl[v]) {
			u = anc[u][i];
		}
	}

	if(u == v) return u;

	for(int i = MAXLG - 1; i >= 0; i--) {
		if(anc[u][i] != anc[v][i]) {
			u = anc[u][i], v = anc[v][i];
		}
	}

	return anc[u][0];
}

int pathAns(int u, int v) { // O(LogN)

	int res = 0;

	if(lvl[u] < lvl[v]) swap(u, v);

	for(int i = MAXLG - 1; i >= 0; i--) {
		if(lvl[anc[u][i]] >= lvl[v]) {
			res = max(res, ans[u][i]);
			u = anc[u][i];
		}
	}

	if(u == v) return res;

	for(int i = MAXLG - 1; i >= 0; i--) {
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
