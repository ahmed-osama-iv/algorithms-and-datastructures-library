#include <bits/stdc++.h>
#define MAX 1005
#define MOD 1000000007
#define inf 1e17
#define ll long long
using namespace std;

ll c[MAX];

void build_catalan_1(){  // O(n^2) "doesn't need mod inverse"
    
    c[0]=1;

    for(int i=0; i<MAX-1; i++){
        c[i+1]=0;

        for(int j=0; j<=i; j++){
            c[i+1] += c[j] * c[i-j] % MOD;
        }
    }

}


void build_catalan_2(){  // O(n)

    c[0]=1;

    for(int i=0; i<MAX-1; i++){
        c[i+1] = 2*(2*i+1)*c[i] % MOD * FAST_POW(i+2, MOD-2, MOD) % MOD;
    }

}
