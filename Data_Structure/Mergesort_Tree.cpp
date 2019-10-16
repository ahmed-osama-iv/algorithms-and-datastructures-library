
vector <int> tree[5*MAXN];
int A[MAXN];

void build_tree(int cur ,int l ,int r){

     if(l == r){
        tree[cur].push_back(A[l]);
        return;
     }

     int mid = l+(r-l)/2;
     build_tree(2*cur+1, l, mid ); // Build left tree
     build_tree(2*cur+2, mid+1, r ); // Build right tree
     tree[cur].resize(tree[2*cur+1].size() +  tree[2*cur+2].size());
     merge(tree[2*cur+1].begin(), tree[2*cur+1].end(), tree[2*cur+2].begin(), tree[2*cur+2].end(), tree[cur].begin()); //Merging the two sorted arrays
}

// cur = 0, l = 0, r = MAXN
// how many number within indices [x,y] <= k
int query(int cur, int l, int r, int x, int y, int k) {  // O(log(n) ^ 2)

    if(r < x || l > y){
        return 0; //out of range
    }

    if(x <= l && r <= y){
        //Binary search over the current sorted vector to find elements smaller than K
        return upper_bound(tree[cur].begin(),tree[cur].end(),k)-tree[cur].begin();
    }

    int mid = l + (r-l) / 2;
    return query(2*cur+1, l, mid, x, y, k) + query(2*cur+2, mid+1, r, x, y, k);
}
