/*
    *
    * Build a function that returns an array of integers from n to 1 where n>0.
    *
    * Example : n=5 --> [5,4,3,2,1]
    * 
    * Note: allocate memory yourself
    *
*/

#include <stdlib.h>

unsigned short *reverse_seq(unsigned short num) {
    unsigned short *arr = (unsigned short*)malloc(num * sizeof(unsigned short));
    for(size_t i = 0; num != 0; i++) arr[i] = num--;
    return arr;
}
