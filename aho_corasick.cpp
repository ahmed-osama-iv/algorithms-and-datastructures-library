#include<bits/stdc++.h>
#define MAX 5005
#define MOD 1000000007
#define inf 10000000010

typedef long long ll;
using namespace std;

struct node{

    node *child[128], *fail, *parent;
    vector <int> ptrnIdx;
    char ch;
};

struct aho_corasick{

    vector <int> res;
    int ptrnsCount = 0;
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

        cur->ptrnIdx.push_back(ptrnsCount++);
        res.push_back(0);
    }

    void build(){

        root->fail = root;
        for(int i=0; i<128; i++){
            if(root->child[i]){
                root->child[i]->fail = root;
                dfs(root->child[i]);
            }
        }
    }

    void dfs(node *cur){

        for(int i=0; i<128; i++){
            if(cur->child[i]){
                if(cur->fail->child[cur->child[i]->ch]){
                    cur->child[i]->fail = cur->fail->child[cur->child[i]->ch];

                    for(auto ptrn:cur->fail->child[cur->child[i]->ch]->ptrnIdx){
                        cur->child[i]->ptrnIdx.push_back(ptrn);
                    }

                }else{
                    cur->child[i]->fail = root;
                }

                dfs(cur->child[i]);
            }
        }
    }

    void answer(char *ch){

        node *cur = root, *prev;
        for(; *ch; ch++){
            if(cur->child[*ch]){
                cur = cur->child[*ch];
            }else if(cur->fail->child[*ch]){
                cur = cur->fail->child[*ch];
            }else{
                cur = root;
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

