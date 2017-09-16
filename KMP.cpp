    #include<bits/stdc++.h>
    #define MAX_Pattern_length 100
    using namespace std;
    typedef long long ll;
     
    int f[MAX_Pattern_length];
     
    void calc_F(string p){
     
        f[0]=0;
        for(int i=1, k=0; i<p.size(); i++){
     
            while(k>0 && p[i]!=p[k])
                k = f[k-1];
     
            if(p[k]==p[i])
                f[i] = ++k;
            else
            	f[i] = k;
        }
    }
     
    void kmp(string s, string p){
     
        calc_F(p);
     
        for(int i=0, k=0; i<s.size(); i++){
     
            while(k>0 && p[k]!=s[i])
                k = f[k-1];
     
            if(p[k]==s[i])
                k++;
     
            if(k==p.size()){
                cout << i-k+1 << endl; // the index of occurance (first char)
                k = f[k-1];
            }
        }
    }
     
     
    int main () {
     
        string s, p;
        s = "abxababaaba";
        p = "aba";
     
        kmp(s, p);
     
    }
