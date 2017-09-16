#include <bits/stdc++.h>
#define MAX 1005
#define MOD 1000000007
#define inf 1e17
#define ll long long
using namespace std;

ll cat[MAX];

// [https://en.wikipedia.org/wiki/Catalan_number]
//catalan(n) =~ 4^n / ( n^(3/2) * sqrt(PI) )    grows exponential

void build_catalan_1(){  // O(n^2) "doesn't need mod inverse"
    
    cat[0]=1;

    for(int i=0; i<MAX-1; i++){
        cat[i+1]=0;

        for(int j=0; j<=i; j++){
            cat[i+1] += cat[j] * cat[i-j] % MOD;
        }
    }

}


void build_catalan_2(){  // O(n)

    cat[0]=1;

    for(int i=0; i<MAX-1; i++){
        cat[i+1] = 2*(2*i+1)*cat[i] % MOD * FAST_POW(i+2, MOD-2, MOD) % MOD;
    }

}
