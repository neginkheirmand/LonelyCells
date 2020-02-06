#include <stdio.h>
#include <windows.h>

void hello(){
    printf("hello in the function\n");
    return;
}

int main(){
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for(int i=1; i<252; i++){
        SetConsoleTextAttribute(hConsole, i);
        printf(" %d ) hello", i);
        SetConsoleTextAttribute(hConsole, 7);
        printf("\n");
    }
}