#include <stdio.h>

unsigned char clear_bit(unsigned char value, int position){
    return ~(1 << position) & value;
}

int main(){
    int clear_position;
    printf("Clear Position: ");
    scanf("%d", &clear_position);
    unsigned char before_value = 127; // 0111 1111

    for(int i = 7; i >= 0; i--) {
        printf("%d", (before_value >> i) & 1);
    }puts("\n");

    unsigned char after_value = clear_bit(before_value, clear_position);

    for(int i = 7; i >= 0; i--) {
        printf("%d", (after_value >> i) & 1);
    }puts("\n");

    return 0;
}