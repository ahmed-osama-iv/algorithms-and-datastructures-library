#include <bits/stdc++.h>
using namespace std;


const int MOD = 1e9+7;

vector<vector<int> > matrixMult(const vector<vector<int> > &A,const vector<vector<int> > &B, const int N, const int R, const int M ){ //where A is NxR & B is RxM
    vector<vector<int> > C (N);

    for(int i = 0; i < N; ++i)
        C[i].resize(M,0);

    for(int i = 0; i < N; ++i)
        for(int j = 0; j < M; ++j)
            for(int k = 0; k < R; ++k){
                C[i][j]=(C[i][j]+(A[i][k]*1LL*B[k][j])%MOD)%MOD;

            }
    return C;
}

vector<vector<vector<int> > > matrix_Gen(int N, int M, int mod, int r){ // generates r NxM matrix 0 <= elements < mod ;
    srand(time(0));
    vector<vector<vector<int> > > A (r);

    int mod2 = 1210883; // must deffir from mod & must be prime

    for(int s = 0; s < r; ++s){
        A[s].resize(N);
        for(int i = 0; i < N; ++i){
            A[s][i].resize(M,0);
            for(int j = 0; j < M; ++j){
                A[s][i][j] = (rand()*1LL*mod2)%mod; // mod2 must be prime
            }
        }
    }
    return A;
}


bool matrix_Equ(const vector<vector<int> > &A, const vector<vector<int> > &B, const int N, const int M){ // Checks Equality

    for(int i = 0; i < N; ++i)
        for(int j = 0; j < M; ++j)
            if(A[i][j]!=B[i][j])
                return 0;
    return 1;
}


int main(){
    int n;
    scanf("%d", &n);
    vector<vector<int> >A(n),B(n),C(n);
    for(int i = 0; i < n; ++i){
        A[i].resize(n);
        for(int j = 0; j < n; ++j)
            scanf("%d", &A[i][j]);
    }
    for(int i = 0; i < n; ++i){
        B[i].resize(n);
        for(int j = 0; j < n; ++j)
            scanf("%d", &B[i][j]);
    }

    for(int i = 0; i < n; ++i){
        C[i].resize(n);
        for(int j = 0; j < n; ++j)
            scanf("%d", &C[i][j]);
    }

    int r = 2;
    vector<vector<vector<int> > > Gend = matrix_Gen(n,1,MOD,r);

    for(int i = 0; i < r; ++i)
        if (!matrix_Equ(matrixMult(A,matrixMult(B,Gend[i],n,n,1),n,n,1), matrixMult(C,Gend[i],n,n,1),n,1)){
            puts("NO");
            return 0;
        }
    puts("YES");

}
