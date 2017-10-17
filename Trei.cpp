struct trie {

    static const char first = 'a';
    static const int MAX_CHAR = 26; //if MAX_CHAR is big range but not all values are used, use a map instead of static array
	int times, isLeaf;
	trie* child[MAX_CHAR];


	trie() {
	    times=0;
		memset(child, 0, sizeof(child));
		isLeaf = 0;
	}

	void insert(char * str) { // reference to the current char in the char sequence starting at str;
	    times++;
		if(*str == '\0') { // end of char sequence
            isLeaf++;
            return;
		}
        int cur = *str-first;
		if(child[cur] == 0) { // have no child;
			child[cur] = new trie();
		}

		child[cur]->insert(str+1);
	}

	int freq_of_prefex(char * str) {
        if(*str == '\0')
            return times; // end of char seq
        int cur = *str-first;
        if(child[cur]!=0) // have childes;
            return child[cur]->freq_of_prefex(str+1);
        return 0;
	}

    int freq_of_string(char * str) {
        if(*str == '\0')
            return isLeaf; // end of char seq
        int cur = *str-first;
        if(child[cur]!=0) // have childes;
            return child[cur]->freq_of_string(str+1);
        return 0;
	}
};
