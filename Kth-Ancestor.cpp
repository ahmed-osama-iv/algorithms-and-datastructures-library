int P[MAX];
int anc[MAX][LOG];

int k2_anc(int v, int k){     // Return the 2^k ancestor O(k)

    if(anc[v][k]!=-1)return anc[v][k];
    if(k==0)return anc[v][0] = P[v];
    return anc[v][k] = k2_anc(k2_anc(v, k-1), k-1);

}

int kth_anc(int v, int k){   // Return the k-th ancestor O(log k)

    int u=v, h=0;
    while(k){
        if(k&1)u = k2_anc(u, h);
        k/=2, h++;
    }
    
    return u;
}
