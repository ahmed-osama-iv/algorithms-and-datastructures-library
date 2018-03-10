#include<bits/stdc++.h>
#define MAX 5005
#define MOD 1000000007
#define inf 10000000010

typedef long long ll;
using namespace std;

struct node{

    node *child[128], *fail;
    vector <int> ptrnIdx;
    char ch;
};

struct aho_corasick{

    vector <int> res;
    int ptrnsCounter = 0;
    node *root = new node();

    void add(char *ch){

        node *cur = root;
        for(; *ch; ch++){
            if(cur->child[*ch]){
                cur = cur->child[*ch];
            }else{
                cur->child[*ch] = new node();
                cur = cur->child[*ch];
                cur->ch = *ch;
            }
        }

        cur->ptrnIdx.push_back(ptrnsCounter++);
        res.push_back(0);
    }

    node *move(node *cur, char ch){
        cur = cur->fail;
        while(!cur->child[ch])
            cur = cur->fail;
        return cur->child[ch];
    }


    void build(){

        node *k, *f;
        queue <node*> q;
        root->fail = root;

        for(int i=0; i<128; i++){
            if(root->child[i]){
                root->child[i]->fail = root;
                q.push(root->child[i]);
            }else{
                root->child[i] = root;
            }
        }

        while(!q.empty()){
            k = q.front();
            q.pop();
            for(int i=0; i<128; i++){
                if(k->child[i]){
                    f = move(k, k->child[i]->ch);
                    k->child[i]->fail = f;
                    k->child[i]->ptrnIdx.insert(k->child[i]->ptrnIdx.end(), f->ptrnIdx.begin(), f->ptrnIdx.end());
                    q.push(k->child[i]);
                }
            }
        }

    }

    void answer(char *ch){

        node *cur = root, *prev;
        for(; *ch; ch++){

            if(cur->child[*ch]){
                cur = cur->child[*ch];
            }else{
                cur = move(cur, *ch);
            }

            for(auto ptrn:cur->ptrnIdx){
                res[ptrn]++;
            }
        }
    }
};

int main(){

    aho_corasick *aho = new aho_corasick;

    int n;
    cin >> n;

    string s, ptrn;
    for(int i=0; i<n; i++){
        cin >> ptrn;
        aho->add(&ptrn[0]);
    }

    aho->build();
    cin >> s;
    aho->answer(&s[0]);

    for(auto counter:aho->res){
        cout << counter << endl;
    }

    return 0;
}

