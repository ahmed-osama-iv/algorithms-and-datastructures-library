#include <bits/stdc++.h>
using namespace std;

const int MAXN = 140; // max # of nodes
int cap[MAXN][MAXN]; // capacity
int N; // exact number of nodes.


int path[MAXN]; // global array of getPath()
int pathLen; // global var for getPath() // with last path's length
bool visited[MAXN];

// Implement in anyway that get a path: DFS, BFS, Dijkstra...whatever
int getPath(int stNode, int edNode, int curLen,int maxCap) {
    path[curLen] = stNode;
    if (stNode == edNode) {
        pathLen = curLen+1;
        return maxCap;
    }

    int res = 0;
    visited[stNode] = 1;

    for(int i = 0; i < N; i++) {
        if(visited[i] || cap[stNode][i] <= 0) continue;
        res = getPath(i, edNode, curLen+1, min(maxCap, cap[stNode][i]));
        if(res > 0) break;    // We found a path with flow
    }
    return res;
}

int maxFlow(int src, int sink) { // in O(E max|f|).
    int totalFlow = 0;
    while(1) {
        memset(visited, 0, sizeof visited);
        int newFlow = getPath(src, sink, 0, INT_MAX);

        if (!newFlow) break; // no more paths exist.

        for(int i = 1; i < pathLen; i++) {
            int m = path[i-1], n = path[i];
            cap[m][n] -= newFlow; // remove edge cost we used.
            cap[n][m] += newFlow; // add reverse edge with same cost.
        }
        totalFlow += newFlow;
    }
    return totalFlow;
}
