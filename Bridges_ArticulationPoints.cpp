
vector <int> adj[e4];
int h[e4], d[e4], p[e4];
bool cutVertex[e4];
set <pair<int, int> > cutEdge;

void dfs(int v, int root){

    if(v == root){  //init
        memset(h, 0, sizeof h);
        memset(p, 0, sizeof p);
        memset(d, 0, sizeof d);
        h[root] = 1;
    }

    d[v] = h[v];
    int number_of_children = 0;
    for(int u : adj[v]){
        if(!h[u]){
            number_of_children++;
            p[u] = v;
            h[u] = h[v] + 1;
            dfs(u, root);
            d[v] = min(d[v], d[u]);
            if(d[u] >= h[v] && (v != 1 || number_of_children > 1)){   //then the vertex v is a cut vertex
                cutVertex[v] = true;
            }
            
            if(d[u] > h[v]){    //then the edge v-u is a cut edge
                cutEdge.insert({min(u, v), max(u, v)});
            }
        }else if(u != p[v]){
            d[v] = min(d[v], h[u]);
        }
    }
}
