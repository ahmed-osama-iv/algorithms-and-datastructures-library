const int MAXV = 1e5 + 5;

vector<int> *vec[MAXV];
vector <vector <int> > g(MAXV);
int col[MAXV], sz[MAXV], cnt[MAXV];


int subTreeSize(int u, int p){

    sz[u] = 1;
    for(auto v : g[u]) {
        if(v != p) {
            sz[u] += subTreeSize(v, u);
        }
    }

    return sz[u];
}


void dfs(int u, int p, bool keep){
    
    int mx = -1, bigChild = -1;
    
    for(auto v : g[u])
       if(v != p && sz[v] > mx)
           mx = sz[v], bigChild = v;
           
    for(auto v : g[u])
       if(v != p && v != bigChild)
           dfs(v, u, 0);
           
    if(bigChild != -1)
        dfs(bigChild, u, 1), vec[u] = vec[bigChild];
    else
        vec[u] = new vector<int> ();
        
    vec[u]->push_back(u);
    cnt[ col[u] ]++;
    
    for(auto v : g[u]) {
       if(v != p && v != bigChild) {
           for(auto x : *vec[v]) {
               cnt[ col[x] ]++;
               vec[u] -> push_back(x);
           }
        }
    }
    
    //now (*cnt[v])[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.
    // note that in this step *vec[v] contains all of the subtree of vertex v.
    
    if(keep == 0) {
        for(auto v : *vec[u]) {
            cnt[ col[v] ]--;
        }
    }
}
