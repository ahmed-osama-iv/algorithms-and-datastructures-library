    struct Bitmask {
     
    	int setBit(int S, int j) { return S | (1 << j); } // set j-th bit to 1 - (0-indexed )
     
    	int clearBit(int S, int j) { return S & ~(1 << j); } // set j-th bit to 0 - (0-indexed )
     
    	int toggleBit(int S, int j) { return S ^ (1 << j); } // toggle j-th bit to - (0-indexed )
     
    	bool isOn(int S, int j) { return (S & (1 << j) )!= 0; } // check if j-th bit is 1 - (0-indexed )
     
    	int turnOnLastZero(int S) { return S | (S + 1); } // turn on right-most 0 to 1 , Eg 1100 to 1101 
     
    	int turnOnLastConsecutiveZeroes(int S) { return S | (S - 1); } // turn on right-most consecutive zeroes to 1 if there is any .  Eg 10100 to 10111 
     
    	int turnOffLastBit(int S) { return S & (S - 1); } // turn off right-most 1 to 0 , Eg 111 to 110 
     
    	int turnOffLastConsecutiveBits(int S) { return S & (S + 1); } // turn off right-most consecutive ones to 0 if there is any , Eg 1011 to 1000 
     
    	int lowBit(int S) { return S & (-S); } // returns all the zeros on right tell the first 1 occurs Eg: 10000 or 100
     
    	int setAll(int N) { return (1 << N) - 1; } //sets right-most N bits to 1 , N < 32
     
    	int modulo(int S, int N) { return S & (N - 1); } //return S%N where N is a power of 2
     
    	bool isPowerOfTwo(int S) { return (S & (S - 1)) == 0; }  // checks if S is power of 2 , S > 0
     
     
    	//##########################################################################
    	// __builtin_clz // Returns the number of leading 0-bits in x, starting at the most significant bit position. If x is 0, the result is undefined.
    	// __builtin_ctz // Returns the number of trailing 0-bits in x, starting at the least significant bit position. If x is 0, the result is undefined. 
    	// __builtin_popcount // Returns the number of 1-bits in x. 
    	//##########################################################################
     
    	//########################################################## for long long :
        // __builtin_clzll
        // __builtin_ctzll 
        // __builtin_popcountll 
        //##########################################################################
     
};
