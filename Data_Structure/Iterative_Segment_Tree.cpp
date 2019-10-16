#include<bits/stdc++.h>
using namespace std;

struct SegTree{

    int n, e, *tree;
    int (*op)(int,int); // function of get

    SegTree(){}

    SegTree(int size, int (*operation)(int,int), int identity){
        n = 1 << size;
        op = operation;
        e = identity;
        tree = new int[2*n];
        clear();
    }

    void clear(){
        for(int i=0; i<2*n; i++) tree[i] = e;
    }

    int get(int idx){
        return tree[idx + n];
    }

    void set(int idx, int val){
        tree[idx + n] = val;
    }

    int get(int l, int r){
        l += n; r += n;
        int res = e;
        while(l <= r){
            if (l%2 == 1) res = op(res, tree[l++]);
            if (r%2 == 0) res = op(res, tree[r--]);
            l /= 2; r /= 2;
        }
        return res;
    }

    void update(int idx, int val){ //update index by value
        idx += n;
        tree[idx] = val;
        for(idx /= 2; idx >= 1; idx /= 2){
            tree[idx] = op(tree[2*idx], tree[2*idx + 1]);
        }
    }

    void build(){
        for(int i=n-1; i>0; i--){
            tree[i] = op(tree[2*i], tree[2*i + 1]);
        }
    }

};

int sum (int a ,int b){return a + b;}
int minn(int a, int b){return min(a, b);}

int main(){

    SegTree segOfSum(20, sum, 0), segOfMin(20, minn, 999999);
    segOfSum.update(2, 5);
    segOfSum.update(4, 10);
    segOfSum.update(10, 20);
    cout << segOfSum.get(1, 11) << " " << segOfSum.get(2, 40) << " " << segOfSum.get(10) << endl;

    segOfMin.set(0, 5);
    segOfMin.set(1, 9);
    segOfMin.set(2, 1);
    segOfMin.set(3, 4);
    segOfMin.set(4, 8);
    segOfMin.build();
    cout << segOfMin.get(1, 4) << " " << segOfMin.get(0, 1) << " " << segOfMin.get(3, 100) << endl;
}
