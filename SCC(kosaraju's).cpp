#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 5003; // max number of nodes.

vector<int> g[MAXN]; //graph
vector<int> tg[MAXN]; //transpose graph
vector<int> cg[MAXN]; //compnents graph
vector<int> order; //nodes in dfs order.

bool visitedN[MAXN], visitedC[MAXN]; //visited nodes, visited components
int comp[MAXN]; // component of the ith node
int cnt = 0; //global var for the number of SCC discovered yet.

//// kosaraju's st
void dfs1(int nd) {
    visitedN[nd] = 1;
    for(auto to : g[nd]) {
        if(!visitedN[to]) {
            dfs1(to);
        }
    }
    order.push_back(nd);
}

void dfs2(int nd) {
    comp[nd] = cnt;
    for(auto to : tg[nd]) {
        if(comp[to] == -1) {
            dfs2(to);
        }
    }
}
//// kosaraju's ed


int main() {
    int n, m, f, t;
    scanf("%d %d", &n, &m); // number of nodes, number of edges.
    for(int i = 0; i < m; i++) {
        scanf("%d %d", &f, &t); // from , to nodes 1-based.
        g[f].push_back(t);
        tg[t].push_back(f);
    }

    // Finding SCC's using kosaraju's.
    for(int i = 1; i <= n; i++) {
        if(!visitedN[i]) {
            dfs1(i);
        }
    }
    reverse(order.begin(), order.end());

    memset(comp, -1, sizeof comp);
    for(int i = 0; i < n; i++) {
        if(comp[order[i]] == -1) {
            dfs2(order[i]);
            cnt++;
        }
    }
    // End.

    // creating a DAG from SCC's.
    for(int v = 1; v <= n; v++) {
        for(auto to : g[v]) {
            if(comp[v] != comp[to]) {
                cg[comp[v]].push_back(comp[to]);
            }
        }
    }
}
