ll comb[MAX][MAX];
ll bell[MAX];

void build_nCr(){  // O(n^2)

    comb[0][0] = 1;
    
    for(int i=1; i<MAX; i++){
        comb[i][0] = 1;
        for(int j=1; j<=i; j++){
            comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
            comb[i][j] %= MOD;
        }
    }

}

//  [https://github.com/AhmadElsagheer/Competitive-programming-library/blob/master/math/combinatorics/BinomialCoefficient.java]

//  [https://en.wikipedia.org/wiki/Bell_number]
void build_bell(){  // O(n^2)

    ll sum=0;
    bell[0]=1;
    for(int i=1; i<MAX; i++){
        sum = 0;
        for(int j=0; j<i; j++){
            sum += bell[j] * comb[i-1][j];
            sum %= MOD;
        }
        bell[i] = sum;
    }

}


