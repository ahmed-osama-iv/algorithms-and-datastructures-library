#include<bits/stdc++.h>
#define F first
#define S second
#define SZ size()

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair <ld, ld> point;

int in(){int a; scanf("%d", &a); return a;}
ll inll(){ll a; scanf("%lld", &a); return a;}
double ind(){double a; scanf("%lf", &a); return a;}
ld inld(){ld a; scanf("%Lf", &a); return a;}

const ll MOD = 1000000009;
const ll INF = 1e18;
const ld PI = acosl(-1);
const ld EPS = 1e-9;
const int MAX = 10004;
const int e3 = 1003;
const int e4 = 10004;
const int e5 = 100005;
const int e6 = 1000006;
const int e7 = 10000007;
const int e8 = 100000008;
const int e9 = 1000000009;


//------------------------------------------

struct edge{
    int to, c1, c2;
};

vector < edge > adj[e5];
int E[2*e5], st[e5], stInv[2*e5];
int curTime = 0;
int r_u[e5], u_r[e5];
pair <int,int> tree[1<<19];


void segTreeSet(int idx, int val){
    tree[idx + (1<<18)].F = val;
}

void segTreeBuild(){

    for(int i=1<<18; i<1<<19; i++){
        tree[i].S = i - (1<<18);
    }

    for(int i=(1<<18)-1; i>0; i--){
        tree[i] = min(tree[2*i], tree[2*i + 1]);
    }
}

int segTreeGet(int l, int r){
    if(l > r) swap(l, r);
    l += (1<<18); r += (1<<18);
    pair<int,int> res = {e6, e6};
    while(l <= r){
        if (l%2 == 1) res = min(res, tree[l++]);
        if (r%2 == 0) res = min(res, tree[r--]);
        l /= 2; r /= 2;
    }
    return res.S;
}

void dfs(int u, int p, int lvl, int cost1, int cost2){

    st[u] = curTime;
    stInv[curTime] = u;

    E[curTime] = lvl;
    segTreeSet(curTime++, lvl);

    r_u[u] = cost1;
    u_r[u] = cost2;

    for(auto edg : adj[u]){
        if(edg.to != p){
            dfs(edg.to, u, lvl+1, edg.c1+cost1, edg.c2+cost2);
            E[curTime] = lvl;
            stInv[curTime] = u;
            segTreeSet(curTime++, lvl);

        }
    }
}

int lca(int u, int v){
    return stInv[segTreeGet(st[u], st[v])] ;
}

int main(){

    int T = in();

    while(T--){

        for(int i=0; i<(1<<19); i++) tree[i] = {0,0};
        curTime = 0;
        for(int i=0; i<e5; i++) adj[i].clear();

        int n = in();
        ll sum = 0;
        for(int i=0; i<n-1; i++){
            int u=in(), v=in(), uv=in(), vu=in();
            adj[u].push_back({v, uv, vu});
            adj[v].push_back({u, vu, uv});
            sum += uv + vu;
        }

        dfs(1, -1, 0, 0, 0);
        segTreeBuild();

        int Q = in();
        while(Q--){
            int x = in(), y = in();
            int l = lca(x, y);
            printf("%lld\n", sum - (r_u[x] - r_u[l] + u_r[y] - u_r[l]));
        }
    }
}
