#include<bits/stdc++.h>
using namespace std;

struct BIT{

    static const int length = 3000;
    int BIT1[length], BIT2[length];

    int getSum(int BITree[], int index){

        int sum = 0;
        while (index>0){
            sum += BITree[index];
            index -= index & (-index);
        }
        return sum;
    }

    void updateBIT(int BITree[], int index, int val){

        while (index <= length){
            BITree[index] += val;
            index += index & (-index);
        }
    }

    int sum(int x, int BITTree1[], int BITTree2[]){
        return (getSum(BITTree1, x) * x) - getSum(BITTree2, x);
    }


    void updateRange(int l, int r, int val){
        updateBIT(BIT1,l,val);
        updateBIT(BIT1,r+1,-val);

        updateBIT(BIT2,l,val*(l-1));
        updateBIT(BIT2,r+1,-val*r);
    }

    int rangeSum(int l, int r){
        return sum(r, BIT1, BIT2) - sum(l-1, BIT1, BIT2);
    }

};

BIT tree;

int main(){


    tree.updateRange(1, 10, 10);
    cout << tree.rangeSum(1, 1) << endl;;
    tree.updateRange(2, 5, 5);
    cout << tree.rangeSum(2, 6) << endl;
}
