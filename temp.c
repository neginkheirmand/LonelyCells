#include <stdio.h>
#include <stdlib.h>

int main(){
    char a;
    int b;
    scanf("%d", &b);
    printf("this is the num: %d\n", b);
    itoa(b, &a, 10);
    printf("this is the character: %c", a);
}