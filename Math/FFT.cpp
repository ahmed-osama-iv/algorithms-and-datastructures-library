#include <bits/stdc++.h>
using namespace std;

vector<complex<double> > recursive_fft(vector<complex<double> > &a, bool inv = 0) { // givin vector of x0, x1, ..., xn-1 returns corresponding y0, y1, ..., yn-1
    const int n = (int)a.size();
    if(n == 1) return a; // base case
    // wn = e^(2*pi*i/n);
    // e^(theta*i) = cos(theta) + i* sin(theta)
    // wn = e^((2*pi/n)*i) = cos(2*M_PI/n) + i*sin(2*M_PI/n)
    complex<double> wn, w;
    vector<complex<double> > aEven, aOdd, yEven, yOdd, y(n);
    if(inv) {
        wn = complex<double>(cos(-2*M_PI/n), sin(-2*M_PI/n));
    } else {
        wn = complex<double>(cos(2*M_PI/n), sin(2*M_PI/n));
    }
    w = complex<double>(1.0, 0.0);
    for(int i = 0; i < n/2; ++i) { // n is always power of 2
        aEven.push_back(a[2*i]);
        aOdd.push_back(a[2*i+1]);
    }
    yEven = recursive_fft(aEven, inv), yOdd = recursive_fft(aOdd, inv);
    for(int k = 0; k < n/2; ++k) {
        y[k] = yEven[k] + w*yOdd[k];
        y[k+n/2] = yEven[k] - w*yOdd[k];
        w *= wn;
    }
    return y;
}

vector<int> poly_mul(vector<int> &ca, vector<int> &cb, int n) {
    int nxtP2 = 1; // calculate next power of 2
    while (nxtP2 < n) {
        nxtP2 <<= 1;
    }
    int m = nxtP2<<1;
    vector<complex<double> > a(m), b(m), c(m), ya, yb, yc(m);
    for(int i = 0; i < n; ++i) {
        a[i] = complex<double>(ca[i], 0);
        b[i] = complex<double>(cb[i], 0);
    }
    ya = recursive_fft(a, 0);
    yb = recursive_fft(b, 0);
    for (int i = 0; i < m; ++i) {
        yc[i] = ya[i] * yb[i];
    }
    c = recursive_fft(yc, 1); //finds Inv-FFT of yc but we also need to devide by m
    //C(x) = A(x) * B(x)
    //deg(A) = nxtP2-1, deg(B) = nxtP2-1 => deg(C) = 2nxtP2-2
    vector<int> cc(m-1);
    for (int i = 0; i <= m-2; ++i) {
        cc[i] = int(round(c[i].real()/m));
    }
    return cc;
}

int main() {
    int n;
    cin >> n;
    //A(x), B(x) are polys of deg n-1 where ca is integer coefs of A, cb is integer coefs of B
    vector<int> ca(n), cb(n), cc;
    for(int i = 0; i < n; ++i) {
        cin >> ca[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> cb[i];
    }
    cc = poly_mul(ca, cb, n);
    for(int i = 0; i < (int)cc.size(); ++i) {
        cout << cc[i] << " ";
    }
    cout << endl;
}
