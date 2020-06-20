#include <stdlib.h>
#include <stdio.h>

int main(){
    char* var1 = "cc";
    char* var2 = "cc";
    int result = 0;
    result = strcmp(var1, var2);
    // printf("strcmp(str1, str2) = %d\n", result);
    // char *pch = strstr(lucas_o_maromba, cc);
    printf("%d", result);
}