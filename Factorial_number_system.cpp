/*
    Given 2 permutations P and Q print  Perm( (Ord(P) + Ord(Q) mod n! )
    
    1 - represent them as numbers in "factorial number system"
    2 - get the sum of these numbers
    3 - convert the sum to a permutation
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef tree<int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update> ordered_set;
int in(){int a; scanf("%d", &a); return a;}
ll inll(){ll a; scanf("%lld", &a); return a;}

const int MAX_N = 2e5 + 5; // max array length

int N;

int p[MAX_N], q[MAX_N]; // permutations P and Q
int p_fact[MAX_N], q_fact[MAX_N]; // convert permutations P and Q to factoradic form (factorial number system).
int sum_fact[MAX_N];
int res[MAX_N]; // the result permutation

void permutation_to_factoradic(int p[], int f[]){

    ordered_set s;
    for(int i=0; i<N; i++) s.insert(i);

    for(int i=N-1; i>=0; i--){
        f[i] = s.order_of_key(p[i]);
        s.erase(p[i]);
    }
}

void factoradic_sum(int a[], int b[], int res[]){ // (factoradic a + factoradic b) mod n! = res

    for(int i=0; i<N; i++){ // if you don't need it modulo let condition i<=N
        res[i] += a[i] + b[i];
        if(res[i] > i){
            res[i+1] += res[i] / (i + 1);
            res[i] %= i + 1;
        }
    }

}

void factoradic_to_permutation(int f[], int p[]){

    ordered_set s;
    for(int i=0; i<N; i++) s.insert(i);

    for(int i=N-1; i>=0; i--){
        p[i] = *(s.find_by_order(f[i]));
        s.erase(p[i]);
    }
}


int main()
{

    N = in();
    for(int i=N-1; i>=0; i--) p[i] = in();
    for(int i=N-1; i>=0; i--) q[i] = in();

    permutation_to_factoradic(p, p_fact);
    permutation_to_factoradic(q, q_fact);
    factoradic_sum(p_fact, q_fact, sum_fact);
    factoradic_to_permutation(sum_fact, res);

    for(int i=N-1; i>=0; i--) printf("%d ", res[i]);

}
