
ll Cat[MAX];

// [https://en.wikipedia.org/wiki/Catalan_number]
//Catalan(n) =~ 4^n / ( n^(3/2) * sqrt(PI) )    grows exponential

void build_catalan() {  // O(n^2) "doesn't need mod inverse"
    
    Cat[0]=1;

    for(int i = 0; i < MAX - 1; i++){
        Cat[i+1]=0;

        for(int j = 0; j <= i; j++){
            Cat[i+1] += Cat[j] * Cat[i-j] % MOD;
            Cat[i+1] %= MOD;
        }
    }
}


void build_catalan(){  // O(n)

    Cat[0] = 1;

    for(int i = 0; i < MAX - 1; i++){
        Cat[i+1] = 2*(2*i+1) * Cat[i] % MOD * fast_pow(i+2, MOD-2, MOD) % MOD;
    }
}
