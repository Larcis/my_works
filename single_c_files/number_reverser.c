#include <stdio.h>


/**
 * @brief reverse first half of the number
 * in: 65741 out: 56741, in: 3456 out: 4356
 * @return int 
 */
int main(void)
{   
    const int n = 1234;
    int i, len = 0, number = n;
    char *a, *b, str[64];

    // save all digits to array (reversed)
    do {
        str[len++] = (char)(number % 10 + 48); 
    } while(number /= 10);
    str[len] = '\0';

    // swap third and forth quarter of the array 
    // (the first half of the number since the array is reversed)
    for(i = 0; i < len / 4; i++) {
        a = str + (len + 1) / 2 + i;
        b = str + len - i - 1;
        *a ^= *b ^= *a ^= *b;
    }

    // print array reversed
    for(i = len -1; i >= 0; i--) 
        printf("%c", str[i]);
    printf(" : %d\n", n);
    
    return 0;
}