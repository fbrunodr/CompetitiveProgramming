#ifndef FBRUNODR_BINARY_SEARCH
#define FBRUNODR_BINARY_SEARCH

#include "../header.hpp"

int firstTrue(int low, int high, function<bool(int)> op){
    while(low < high){
        int mid = (low + high) / 2;
        if(op(mid))
            high = mid;
        else
            low = mid + 1;
    }
    return low;
}

int lastTrue(int low, int high, function<bool(int)> op){
    while(low < high){
        int mid = (low + high + 1) / 2;
        if(op(mid))
            low = mid;
        else
            high = mid - 1;
    }
    return low;
}

#endif
