#include <bits/stdc++.h>
#define ll long long
#define MAX 200005
#define inf 1000000009
 
using namespace std; 
 
struct seg_tree{
 
    const static int n=1<<20; //size of array
    int tree[2*n];
    int e=0; //identity
 
    int (*op)(int,int); // function of get
 
    int get(int a, int b) {
        a += n; b += n;
        int s = e;
        while (a <= b) {
            if (a%2 == 1) s = op(s, tree[a++]);
            if (b%2 == 0) s = op(s, tree[b--]);
            a /= 2; b /= 2;
        }
        return s;
    }
 
 
    void update(int k, int x){ //update index k by value x
        k += n;
        tree[k] = x;
        for (k /= 2; k >= 1; k /= 2) {
            tree[k] = op(tree[2*k], tree[2*k+1]);
        }
    }
 
};
 
int sum(int a, int b){return a+b;}
int maxx(int a, int b){return max(a,b);}
 
seg_tree seg1, seg2;
 
int main(){
 
 
    //segment tree of sum
    seg1.e=0, seg1.op=&sum;
    seg1.update(1, 1);
    seg1.update(2, 2);
    seg1.update(3, 3);
    cout << seg1.get(2, 8) << endl;
 
 
 
    //segment tree of max
    seg2.e=-inf, seg2.op=&maxx;
    seg2.update(1, 123);
    seg2.update(2, 23);
    seg2.update(3, 60);
    cout << seg2.get(2, 3) << endl;
 
}
