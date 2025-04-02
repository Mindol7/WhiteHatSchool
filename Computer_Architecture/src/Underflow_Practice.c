#include <stdio.h>
#include <limits.h>

int main(){
    // CHAR_MIN == -128
    // Bit 표현 시 1000 0000
    char value = CHAR_MIN;


    printf("Original value: %d\n", value);

    // 1000 0000에 -1을 한다면 
    // 1000 0000 + 1111 1111 = 1 0111 1111 (char은 1Byte 이므로) 최종적으로 0111 1111
    // 즉, 127이 된다.
    value = value - 1;

    printf("Value after adding 1: %d\n", value);

    return 0;
}