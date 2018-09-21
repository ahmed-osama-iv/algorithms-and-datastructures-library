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

int P[e5], st[e5], nd[e5];
int anc[e5][20];


int k2_anc(int u, int k){

    if(anc[u][k] != 0) return anc[u][k];
    if(k == 0) return anc[u][0] = P[u];
    return anc[u][k] = k2_anc( k2_anc(u,k-1) , k-1);

}

int kth_anc(int u, int k){

    int res = u, h = 0;
    while(k){
        if(k&1) res = k2_anc(res, h);
        k/=2, h++;
    }

    return res;
}



vector< pair<int,int> > adj[e5];
int x, y;
int curTime = 0;
ll r_u[e5], u_r[e5];

map < pair<int,int> , int > cost;

void dfs(int u, int p, int cost1, int cost2){

    P[u] = p;
    st[u] = curTime;
    r_u[u] = cost1;
    u_r[u] = cost2;

    for(auto edge : adj[u]){
        if(edge.F != p){
            curTime++;
            dfs(edge.F, u, cost1 + edge.S, cost2 + cost[{edge.F, u}]);
        }
    }

    nd[u] = curTime;

}

bool valid(int lca, int u, int v){
    bool uu = (st[u] >= st[lca] && st[u] <= nd[lca]);
    bool vv = (st[v] >= st[lca] && st[v] <= nd[lca]);
    return uu && vv;
}

int lca(int u, int v){

    if(valid(v, u, v)) return v;
    if(valid(u, u, v)) return u;

    int lo=1, hi=e5, mid, lca;
    while(lo<hi){
        mid = (lo + hi)/2;
        lca = kth_anc(u, mid);

        if(valid(lca, u, v)){
            hi = mid;
        }else{
            lo = mid+1;
        }
    }

    return lca;
}


int main(){

    int T = in();

    while(T--){

        cost.clear();
        curTime = 0;
        memset(anc, 0, sizeof anc);
        for(int i=0; i<e5; i++) adj[i].clear();

        int n = in();
        ll sum = 0;
        for(int i=0; i<n-1; i++){
            int u=in(), v=in(), uv=in(), vu=in();
            adj[u].push_back({v, uv});
            adj[v].push_back({u, vu});
            cost[{u,v}] = uv;
            cost[{v,u}] = vu;
            sum += uv + vu;
        }

        st[0] = 0, nd[0] = e6;
        dfs(1, -1, 0, 0);

        int Q = in();
        while(Q--){
            x = in(), y = in();
            int l = lca(x, y);

            printf("%lld\n", sum - (r_u[x] - r_u[l] + u_r[y] - u_r[l]) );
        }


    }

}
