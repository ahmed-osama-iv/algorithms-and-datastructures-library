ll Bell[MAX];

// O(n^2)
void build_bell() {
    ll sum = 0;
    Bell[0] = 1;
    for(int i = 1; i < MAX; i++) {
        sum = 0;
        for(int j = 0; j < i; j++) {
            sum += Bell[j] * C[i-1][j];
            sum %= MOD;
        }
        Bell[i] = sum;
    }
}
