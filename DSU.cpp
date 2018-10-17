
const int MAXN = 1e5+5;

struct DSU {

    int id[MAXN], sz[MAXN];

    DSU() {
        for(int i = 0; i < MAXN; i++) {
            id[i] = i, sz[i] = 1;
        }
    }

    int root(int i) {
        while(i != id[i]) {
            i = id[i] = id[id[i]]; // path compression.
        }
        return i;
    }

    void unite(int a , int b) {
        a = root(a), b = root(b);
        if(a == b) return;
        if (sz[a] < sz[b]) swap(a, b); // union by rank.
        if (sz[a] == sz[b]) ++sz[a];
        id[b] = a;
    }
};
