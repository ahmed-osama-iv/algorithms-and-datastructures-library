struct DSU {

    int *id, *sz, Size;

    DSU(int _Size){
        Size = _Size;
        id = new int[Size];
        sz = new int[Size];
        for(int i = 0; i < Size; i++) {
            id[i] = i, sz[i] = 1;
        }
    }

    int root(int i) {
        while(i != id[i]) {
            i = id[i] = id[id[i]]; // path compression.
        }
        return i;
    }

    bool unite(int a , int b) {
        a = root(a), b = root(b);
        if(a == b) return 0;
        if (sz[a] < sz[b]) swap(a, b); // union by rank.
        if (sz[a] == sz[b]) ++sz[a];
        id[b] = a;
        return 1;
    }
};
