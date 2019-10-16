ll fast_pow(ll base, ll power, ll mod=MOD) {
    
    base %= mod;
    ll result = 1;
    
    while(power > 0) {

        if(power & 1) { // power % 2 == 1
            result = (result*base) % mod;
        }
        base = (base * base) % mod;
        power >>= 1; // power = power / 2;
    }
    return result;
}
