#include <stdio.h>

// Add data value [val] in position [pos] of array [arr] with length [len].

int* set_position(int* arr, size_t len, size_t pos, size_t val) {

    pos--;

    for(size_t i = len-1; i >= pos; i--)
        arr[i+1]=arr[i];
    
    arr[pos] = val;

    return arr;
}

// Delete data value in position [pos] of array [arr] with length [len] 

int* delete_position(int* arr, size_t len, size_t pos) {
    
    pos--;

    for(size_t i = pos; i <= len-2; i++)
        arr[i]=arr[i+1];
    
    arr[len-1] = 0;

    return arr;
}

