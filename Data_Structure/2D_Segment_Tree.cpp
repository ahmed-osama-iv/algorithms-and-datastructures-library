struct _2D_segTree{

const int c = 1 << 10;

    int tree[2*c][2*c];
    
    void set(int i, int j, int val) {
        i+=c, j+=c;
        tree[i][j] = val;
    }

    void build() {

        for(int i=c; i<2*c; i++) {
            for(int j=c-1; j>0; j--) {
                tree[i][j] = tree[i][2*j] + tree[i][2*j + 1];
            }
        }

        for(int i=c-1; i>0; i--) {
            for(int j=0; j<2*c; j++) {
                tree[i][j] = tree[2*i][j] + tree[2*i + 1][j];
            }
        }
    }

    int get(int row, int l, int r) {
        l += c, r += c;
        int res = 0;
        while(l <= r) {
            if(l%2 == 1) res += tree[row][l++];
            if(r%2 == 0) res += tree[row][r--];
            l/=2, r/=2;
        }
        return res;
    }

    int get(int u, int d, int l, int r) {
        u += c; d += c;
        int res = 0;
        while(u <= d){
            if (u%2 == 1) res += get(u++, l, r);
            if (d%2 == 0) res += get(d--, l, r);
            u /= 2; d /= 2;
        }
        return res;
    }
};
