#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 5;
typedef long long ll;

vector <int> adj[MAX];
int h[MAX], d[MAX], p[MAX];
bool cutVertex[MAX];
set <pair<int, int> > cutEdge;
stack <pair<int, int> > stk;
int Time;

void dfs(int u) {

    d[u] = h[u] = ++Time;
    int number_of_children = 0;

    for(int v : adj[u]) {
        if(!h[v]) {
            number_of_children++;
            p[v] = u;
            stk.push({u, v});
            dfs(v);
            d[u] = min(d[u], d[v]);

//then the vertex u is a cut vertex
            if(d[v] >= h[u] && (u != 1 || number_of_children > 1)) {
                cutVertex[u] = true;
                while(stk.top().first != u || stk.top().second != v) {
                    cout << stk.top().first << "-" << stk.top().second << "  ";
                    stk.pop();
                }
                cout << stk.top().first << "-" << stk.top().second << endl;
                stk.pop();
            }

//then the edge u-v is a cut edge
            if(d[v] > h[u]) {
                cutEdge.insert({min(u, v), max(u, v)});
            }
        } else if(v != p[u]) {
            d[u] = min(d[u], h[v]);
            if (h[v] < h[u]) {
                stk.push({u, v});
            }
        }
    }
}



void bcc() {

    for(int i = 1; i < MAX; i++) {
        if(!h[i]) dfs(i);
    }

    while(!stk.empty()) {
        cout << stk.top().first << "-" << stk.top().second << "  ";
        stk.pop();
    }
    cout << endl;
}


int cmpId[MAX];  //stores component Id of vertex i start form 1
int cmp = 1;
queue <int> q[MAX];
vector <int> bridge_tree[MAX]; //the result Bridge tree

void build_bridge_tree(int v) {

    int curCmp = cmp;
    q[curCmp].push(v);
    cmpId[v] = curCmp;
    while(!q[curCmp].empty()) {
        int u = q[curCmp].front();
        q[curCmp].pop();

        for(int w : adj[u]) {
            if(!cmpId[w]) {
                if(cutEdge.count({min(u,w), max(u,w)})) {
                    cmp++;
                    bridge_tree[curCmp].push_back(cmp);
                    bridge_tree[cmp].push_back(curCmp);
                    build_bridge_tree(w);
                } else {
                    q[curCmp].push(w);
                    cmpId[w] = curCmp;
                }
            }
        }
    }
}

int main() {

    adj[1].push_back(2);

    adj[2].push_back(1);
    adj[2].push_back(3);
    adj[2].push_back(4);
    adj[2].push_back(5);

    adj[3].push_back(2);
    adj[3].push_back(4);

    adj[4].push_back(2);
    adj[4].push_back(3);

    adj[5].push_back(2);
    adj[5].push_back(6);
    adj[5].push_back(7);

    adj[6].push_back(2);
    adj[6].push_back(5);
    adj[6].push_back(7);

    adj[7].push_back(5);
    adj[7].push_back(6);

    adj[7].push_back(8);

    adj[8].push_back(7);
    adj[8].push_back(12);
    adj[8].push_back(14);
    adj[8].push_back(15);

    adj[12].push_back(8);
    adj[12].push_back(13);

    adj[13].push_back(12);
    adj[13].push_back(14);
    adj[13].push_back(15);

    adj[14].push_back(8);
    adj[14].push_back(13);

    adj[15].push_back(8);
    adj[15].push_back(13);

    dfs(1);
    build_bridge_tree(1);

    for(int i = 1; i < 16; i++) {
        cout << i << " "  << cutVertex[i] << " " << cmpId[i] << endl;
    }

    cout << "------------------------------" << endl;
    bcc();
}
