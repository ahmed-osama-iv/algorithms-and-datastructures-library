const int MAXN = 1e5+5;
int BIT[MAXN+1]; // max idx 1-based

int get(int idx) { // get sum of element in range [1, idx].
    int sum = 0;
    while(idx) {
        sum += BIT[idx];
        idx -= (idx & -idx);
    }
    return sum;
}

void update(int idx, int val) { // add val to element at idx
    while(idx <= MAXN) {
        BIT[idx] += val;
        idx += (idx & -idx);
    }
}
