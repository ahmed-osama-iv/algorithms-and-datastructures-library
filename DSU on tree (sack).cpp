vector<int> *vec[maxn];
vector <vector <int> > g(maxn);
int col[maxn], sz[maxn], cnt[maxn];


int subTreeSize(int v, int p){

    sz[v]=1;
    for(auto u : g[v])
        if(u!=p)
            sz[v] += subTreeSize(u, v);

    return sz[v];

}


void dfs(int v, int p, bool keep){
    
    int mx = -1, bigChild = -1;
    
    for(auto u : g[v])
       if(u != p && sz[u] > mx)
           mx = sz[u], bigChild = u;
           
    for(auto u : g[v])
       if(u != p && u != bigChild)
           dfs(u, v, 0);
           
    if(bigChild != -1)
        dfs(bigChild, v, 1), vec[v] = vec[bigChild];
    else
        vec[v] = new vector<int> ();
        
    vec[v]->push_back(v);
    cnt[ col[v] ]++;
    
    for(auto u : g[v])
       if(u != p && u != bigChild)
           for(auto x : *vec[u]){
               cnt[ col[x] ]++;
               vec[v] -> push_back(x);
           }
           
           
    //now (*cnt[v])[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.
    // note that in this step *vec[v] contains all of the subtree of vertex v.
    
    if(keep == 0)
        for(auto u : *vec[v])
            cnt[ col[u] ]--;
}
