int mex(set<int> &s){ // using set
    int mx = 0;
    for(auto it = s.begin(); it != s.end(); mx++, it++)
        if( *it != mx)
            break;
    return mx;
}

int mex(unordered_set<int> &s){ // using unorderd set
    int mx = 0;
    while(s.find(mx) != s.end())
        mx++;
    return mx;
}

// the fastest way
int mex(bool s[]){
    int mx = 0;
    while(s[mx]) ++mx;
    return mx;
    // in grundy() use : bool s[32]= {}; to initialize with zero
    // and fill occupied valid values by 1
}


bool nim(vector<int> &v){
    int ans = 0;
    for(int i = 0; i < (int)v.size(); ++i)
        ans ^= v[i];
    return ans != 0;
}


//normal nim except when all piles are zeros or ones.
bool misere(vector<int> &v){
    int ans = 0;
    bool lastlv = 1;
    for(int i = 0; i < (int)v.size(); ++i){
        ans ^= v[i];
        lastlv &= v[i] <= 1;
    }
    if(lastlv)
        return ans == 0;
    return ans != 0;
}

//nim-k
//generalization of nim.
//players can pick from at least one pile and at most k piles
//represent all piles in binary.
//for every bit calculate the sum of all values in it's column.
//all cul sums % (k+1) == 0 <=> first player lose.
bool nimk(vector<int>&v, int k){
    int c[32] = {};
    for(int i = 0; i < 32; i++){
        for(int j = 0; j < (int)v.size(); j++){
            c[i]+= (v[j]&(1<<i))>>i;
        }
        c[i] %= k+1;
        if(c[i]) // if all columns are divisible by k+1 then first player loses.
            return 1;
    }
    return 0;
}




//if com(i) = 0^1^2^…..^i then
//com(i) is defined as follows :

ll com(ll i) {
    ll a[] = {i, 1, i+1, 0};
    return a[i%4];
}

//and the value of (i)^(i+1)^….^(j) is :
//com(j)^com(i-1).
