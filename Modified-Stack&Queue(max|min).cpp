#include <bits/stdc++.h>
using namespace std;


inline int op(int a, int b){
    return max(a,b);
}

static const int I = INT_MIN; // -inf for minimum op , +inf for maximum op

struct m_stack{

    stack<pair<int,int> > st;

    void push(int item){
        if(!st.empty())
            st.push({item, op(item, st.top().second)});
        else
            st.push({item, item});
    }

    void pop(){
        st.pop();
    }

    int getM(){
        if(!st.empty())
            return st.top().second;
        return I;
    }

    int top(){
        if(!st.empty())
            return st.top().first;
        return 0;
    }

    bool empty(){
        return st.empty();
    }

    int size(){
        return st.size();
    }
};

struct m_queue{

    m_stack in,out;

    void push(int x){
        in.push(x);
    }

    void pop(){
        if(out.empty())
            while(!in.empty())
                out.push(in.top()),in.pop();
        out.pop();
    }

    int getM(){
        return op(in.getM(),out.getM());
    }

    int size(){
        return in.size()+out.size();
    }

    bool empty(){
        return !size();
    }
};
