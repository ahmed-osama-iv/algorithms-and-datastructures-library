#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5+5;

ll dp[N], a[N], b[N], p[N];

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
    }
    p[1] = 1;
    int k = 1, j = 1;
    for(int i = 2; i <= n; i++) {
        while(j < k && dp[p[j]] + a[i] * b[p[j]] > dp[p[j+1]] + a[i] * b[p[j+1]]) {        
            j++;
        }
        dp[i] = dp[p[j]] + a[i] * b[p[j]];
        k++;
        p[k] = i;
        while(k > j+1 && (dp[p[k]] - dp[p[k-1]]) / (b[p[k-1]] - b[p[k]]) <= (dp[p[k-1]] - dp[p[k-2]]) / (b[p[k-2]] - b[p[k-1]])) {
            p[k-1] = p[k];
            k--;
        }
    }
    cout << dp[n];
}
