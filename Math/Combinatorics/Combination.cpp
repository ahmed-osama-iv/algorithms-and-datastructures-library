ll C[MAX][MAX];

// O(n^2)
void build_nCr() {
    C[0][0] = 1;
    for(int i = 1; i < MAX; i++) {
        C[i][0] = 1;
        for(int j = 1; j <= i; j++) {
            C[i][j] = C[i-1][j] + C[i-1][j-1];
            C[i][j] %= MOD;
        }
    }
}
