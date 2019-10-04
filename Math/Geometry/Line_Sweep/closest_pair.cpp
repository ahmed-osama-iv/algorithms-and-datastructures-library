#include<bits/stdc++.h>
#define X first
#define Y second
using namespace std;
typedef long long ll;
typedef pair<double, double> point;

const ll INF = 1e18;
const int MAX = 1e5 + 5;

point pnts[MAX], pnts2[MAX];

double dist(point a, point b) {
    return sqrt((a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y));
}

struct cmpY{
    bool operator() (const point &a, const point &b) {
        if(a.Y == b.Y) return a.X < b.X;
        return a.Y < b.Y;
    }
};

double closest_pair(int n) {

    double best = 1e18;
    multiset<point, cmpY> window;
    sort(pnts, pnts + n);

    int left = 0;
    for(int i = 0; i < n; i++) {
        while (left < i && pnts[i].X - pnts[left].X > best) {
            window.erase(window.find(pnts[left++]));
        }

        auto it1 = window.lower_bound(make_pair(-INF, pnts[i].Y - best));
        auto it2 = window.upper_bound(make_pair(-INF, pnts[i].Y + best));
        for(; it1 != it2; it1++) {
            if(dist(pnts[i], *it1) < best) {
                best = dist(pnts[i], *it1);
            }
        }
        window.insert(pnts[i]);
    }

    return best;
}

int main() {

    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%lf %lf", &pnts[i].X, &pnts[i].Y);
        pnts2[i] = pnts[i];
    }

    printf("%0.6f\n", closest_pair(n));
}
