
int P[e5], lvl[e5];
int anc[e5][20];


int k2_anc(int u, int k){

    if(anc[u][k] != 0) return anc[u][k];
    if(k == 0) return anc[u][0] = P[u];
    return anc[u][k] = k2_anc( k2_anc(u,k-1) , k-1);

}

int kth_anc(int u, int k){

    int res = u, h = 0;
    while(k){
        if(k&1) res = k2_anc(res, h);
        k/=2, h++;
    }

    return res;
}

int lca(int v,int u) { // O(LogN)
	if(lvl[v] > lvl[u])
		swap(v, u);

    int l = lvl[u] - lvl[v];
    for(int i=0; i<20; i++){
        if((l >> i) & 1) u = k2_anc(u, i);
    }
	if(v == u) return v;

	for(int i = 19; i >= 0; i--)
		if(k2_anc(v, i) != k2_anc(u, i))
			v = anc[v][i], u = anc[u][i];
	return P[v];
}
