#include<bits/stdc++.h>
#define F first
#define S second
#define SZ size()
using namespace std;
typedef long long ll;

int in(){int a; scanf("%d", &a); return a;}
ll inll(){ll a; scanf("%lld", &a); return a;}

const ll MOD = 998244353;
const int e4 = 10004;
const int e5 = 100005;
const int e6 = 1000006;

//-------------------------------------------------------


vector <int> adj[2*e5];
int h[2*e5], d[2*e5], p[2*e5];
bool cutVertex[2*e5];
set <pair<int, int> > cutEdge;

stack <pair<int, int> > stk;
int Time;

void dfs(int u){

    d[u] = h[u] = ++Time;
    int number_of_children = 0;

    for(int v : adj[u]){
        if(!h[v]){
            number_of_children++;
            p[v] = u;
            stk.push({u, v});
            dfs(v);
            d[u] = min(d[u], d[v]);
            if(d[v] >= h[u] && (u != 1 || number_of_children > 1)){ //then the vertex u is a cut vertex
                cutVertex[u] = true;
                while(stk.top().F != u || stk.top().S != v){
                    cout << stk.top().F << "-" << stk.top().S << "  ";
                    stk.pop();
                }
                cout << stk.top().F << "-" << stk.top().S << endl;
                stk.pop();
            }

            if(d[v] > h[u]){    //then the edge u-v is a cut edge
                cutEdge.insert({min(u, v), max(u, v)});
            }
        }else if(v != p[u]){
            d[u] = min(d[u], h[v]);
            if (h[v] < h[u]) {
                stk.push({u, v});
            }
        }
    }
}


void bcc(){

    for(int i=1; i<2*e5; i++){
        if(!h[i]) dfs(i);
    }

    while(!stk.empty()){
        cout << stk.top().F << "-" << stk.top().S << "  ";
        stk.pop();
    }
    cout << endl;
}


int main(){

    int n = in(), m = in();

    while(m--){
        int u = in(), v = in();
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bcc();
}



