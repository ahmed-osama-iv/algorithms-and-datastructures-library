ll ncr[MAX][MAX];
ll bell[MAX];

void build_ncr(){  // O(n^2)

    for(int i=0; i<MAX; i++){
        ncr[i][0] = 1;
    }

    for(int i=1; i<MAX; i++){
        for(int j=1; j<=i; j++){
            ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
            ncr[i][j] %= MOD;
        }
    }

}

void build_bell(){

    ll sum=0;
    bell[0]=1;
    for(int i=1; i<MAX; i++){
        sum = 0;
        for(int j=0; j<i; j++){
            sum += bell[j] * ncr[i-1][j];
            sum %= MOD;
        }
        bell[i] = sum;
    }

}
