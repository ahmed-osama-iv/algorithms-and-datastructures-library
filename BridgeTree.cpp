 
vector <int> adj[2*e5];
int h[2*e5], d[2*e5], p[2*e5];
bool cutVertex[2*e5];
set <pair<int, int> > cutEdge;
 
int Time;
 
void dfs(int u){
 
    d[u] = h[u] = ++Time;
    int number_of_children = 0;
 
    for(int v : adj[u]){
        if(!h[v]){
            number_of_children++;
            p[v] = u;
            dfs(v);
            d[u] = min(d[u], d[v]);
            if(d[v] >= h[u] && (u != 1 || number_of_children > 1)){ //then the vertex u is a cut vertex
                cutVertex[u] = true;
            }
 
            if(d[v] > h[u]){    //then the edge u-v is a cut edge
                cutEdge.insert({min(u, v), max(u, v)});
            }
        }else if(v != p[u]){
            d[u] = min(d[u], h[v]);
        }
    }
}
 
int cmpId[2*e5];  //stores component Id of vertex i start form 1
int cmp = 1;
queue <int> q[2*e5];
vector <int> bridge_tree[2*e5]; //the result Bridge tree
void build_bridge_tree(int v){
 
    int curCmp = cmp;
    q[curCmp].push(v);
    cmpId[v] = curCmp;
    while(!q[curCmp].empty()){
        int u = q[curCmp].front();
        q[curCmp].pop();
 
        for(int w : adj[u]){
            if(!cmpId[w]){
                if(cutEdge.count({min(u,w), max(u,w)})){
                    cmp++;
                    bridge_tree[curCmp].push_back(cmp);
                    bridge_tree[cmp].push_back(curCmp);
                    build_bridge_tree(w);
                }else{
                    q[curCmp].push(w);
                    cmpId[w] = curCmp;
                }
            }
        }
    }
 
}
 
