#include<bits/stdc++.h>
#define MAX 10004

typedef long long ll;
using namespace std;


int LongestIncreasingSubsequenceLength(std::vector<int> &v) {
    if (v.size() == 0)
        return 0;
 
    std::vector<int> tail(v.size(), 0);
    int length = 1; // always points empty slot in tail
 
    tail[0] = v[0];
    for (size_t i = 1; i < v.size(); i++) {
        if (v[i] < tail[0])
            // new smallest value
            tail[0] = v[i];
        else if (v[i] > tail[length-1])
            // v[i] extends largest subsequence
            tail[length++] = v[i];
        else
            // v[i] will become end candidate of an existing subsequence or
            // Throw away larger elements in all LIS, to make room for upcoming grater elements than v[i]
            // (and also, v[i] would have already appeared in one of LIS, identify the location and replace it)
            tail[CeilIndex(tail, -1, length-1, v[i])] = v[i];
    }
 
    return length;
}


int CeilIndex(vector<int> &v, vector<int> &t, int l, int r, int key) {
    while (r-l > 1) {
    int m = l + (r-l)/2;
    if (v[t[m]] >= key)
        r = m;
    else
        l = m;
    }

    return r;
}

vector<int> LIS(vector<int> &v) {

    if (v.size() == 0){
        return {};
    }

    vector<int> t(v.size(), 0);
    vector<int> r(v.size(), -1);//to get the array

    int x, length = 1; // always points empty slot in t

    t[0] = 0;

    for (size_t i = 1; i < v.size(); i++) {
        if (v[i] < v[t[0]]){
            t[0] = i;
        }else if (v[i] > v[t[length-1]]){
            t[length] = i;
            r[i]=t[length-1];
            length++;
        }else{
            x = CeilIndex(v, t, -1, length-1, v[i]);
            t[x] = i;
            r[i]=t[x-1];
        }
    }

    vector <int> vec;
    int idx = t[length-1];
    while(idx!=-1){
        vec.push_back(v[idx]);
        idx = r[idx];
    }

    reverse(vec.begin(), vec.end());
    return vec;
}



int main(){

    vector <int> v = {3, 4, -1, 5, 8, 2, 3, 12, 7, 9, 10};

    vector <int> t = LIS(v);
    for(int i=0; i<(int)t.size(); i++){
        cout << t[i] << " ";
    }

    return 0;
}
