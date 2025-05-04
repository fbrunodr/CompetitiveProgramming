#ifndef FBRUNODR_FIRST_ELEMENT_TO_LEFT
#define FBRUNODR_FIRST_ELEMENT_TO_LEFT

#include "../header.hpp"

template<typename T>
vi firstElementToLeft(vec<T>& arr, f<bool(T,T)> op){
    stack<int> st;
    vi left(arr.size());
    for(int i = 0; i < arr.size(); i++){
        while(!st.empty() && !op(arr[st.top()], arr[i]))
            st.pop();
        if(st.empty())
            left[i] = -1;
        else
            left[i] = st.top();
        st.push(i);
    }
    return left;
}

template<typename T>
vi firstElementToRight(vec<T>& arr, f<bool(T,T)> op){
    reverse(arr.begin(), arr.end());
    vi ans = firstElementToLeft(arr, op);
    reverse(arr.begin(), arr.end());
    reverse(ans.begin(), ans.end());
    for(auto& val : ans)
        val = arr.size() - val - 1;
    return ans;
}


#endif
