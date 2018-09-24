//O(EV2)

#include<bits/stdc++.h>
using namespace std;

//-------------------------------------------------------

struct Edge{
    int to, flow, c, rev;
};

class Graph{

    int V;
    int *level;
    int *start;
    vector< Edge > *adj;

    public :
    Graph(int V){
        adj = new vector<Edge>[V];
        this->V = V;
        level = new int[V];
        start = new int[V];
    }


    void addEdge(int u, int v, int c){
        Edge a{v, 0, c, adj[v].size()};
        Edge b{u, 0, 0, adj[u].size()};

        adj[u].push_back(a);
        adj[v].push_back(b);
    }

    bool BFS(int s, int t);
    int sendFlow(int s, int flow, int t);
    int DinicMaxflow(int s, int t);
};

bool Graph::BFS(int s, int t){

    memset(level, -1, sizeof(int) * V);

    level[s] = 0;
    list< int > q;
    q.push_back(s);

    vector<Edge>::iterator i ;
    while (!q.empty()){

        int u = q.front();
        q.pop_front();
        for (i = adj[u].begin(); i != adj[u].end(); i++){

            Edge &e = *i;
            if (level[e.to] < 0  && e.flow < e.c){

                level[e.to] = level[u] + 1;
                q.push_back(e.to);
            }
        }
    }

    return level[t] < 0 ? false : true ;
}


int Graph::sendFlow(int u, int flow, int t){

    if(u == t) return flow;

    for (  ; start[u] < adj[u].size(); start[u]++){

        Edge &e = adj[u][start[u]];

        if (level[e.to] == level[u]+1 && e.flow < e.c){

            int curr_flow = min(flow, e.c - e.flow);
            int temp_flow = sendFlow(e.to, curr_flow, t);
            if (temp_flow > 0){
                e.flow += temp_flow;
                adj[e.to][e.rev].flow -= temp_flow;
                return temp_flow;
            }
        }
    }

    return 0;
}

int Graph::DinicMaxflow(int s, int t){

    if(s == t) return -1;
    int total = 0;

    while(BFS(s, t) == true){

        memset(start, 0, sizeof(int) * V);
        while (int flow = sendFlow(s, INT_MAX, t)) total += flow;
    }

    return total;
}

int main()
{
    Graph g(6);
    g.addEdge(0, 1, 16 );
    g.addEdge(0, 2, 13 );
    g.addEdge(1, 2, 10 );
    g.addEdge(1, 3, 12 );
    g.addEdge(2, 1, 4 );
    g.addEdge(2, 4, 14);
    g.addEdge(3, 2, 9 );
    g.addEdge(3, 5, 20 );
    g.addEdge(4, 3, 7 );
    g.addEdge(4, 5, 4);

    cout << "Maximum flow " << g.DinicMaxflow(0, 5);
    return 0;
}
