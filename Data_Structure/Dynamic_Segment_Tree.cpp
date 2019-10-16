#include<bits/stdc++.h>
using namespace std;

//-------------------------------------------------------

const int MAX = 1e9;

struct Node {

    int val, lazy=0;
    int st, ed;
    Node *left=0, *right=0;

    Node(int Start, int End, int Value) {
        st = Start, ed = End, val = Value;
    }

    void extend() {
        if(!left && st != ed) {
            int m = (st + ed) >> 1;
            left = new Node(st, m, 0);
            right = new Node(m+1, ed, 0);
        }
    }

    void propagate() {
        extend();
        if(left){
            left->lazy += lazy;
            right->lazy += lazy;
        }
        val += lazy * (ed - st + 1);
        lazy = 0;
    }

    int get(int l, int r) {
        if (r < st || l > ed) return 0;
        propagate();
        if (l <= st && r >= ed) return val;
        return left->get(l, r) + right->get(l, r);
    }

    void update(int l, int r, int v) {
        propagate();
        if (r < st || l > ed) return;
        if (l <= st && r >= ed){
            lazy = v;
            propagate();
            return;
        }
        left->update(l, r, v) , right->update(l, r, v);
        val = left->val + right->val;
    }
};

int main(){

    Node segTree(-MAX, MAX, 0);
    segTree.update(1, 3, 5);
    cout << segTree.get(-10, 10) << endl;
    segTree.update(-8, -5, 3);
    cout << segTree.get(-6, 0) << endl;
    segTree.update(-6, 2, 2);
    cout << segTree.get(-5, 1) << endl;

    return 0;
}
