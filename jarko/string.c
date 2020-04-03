#include <stdio.h>
#include <string.h>

int main() {
    char string[256];
    scanf("%s", string);
    int len = strlen(string);
    for (int i = 0; i < len; i++)
        printf("%c", string[i]);
    printf("\n");
    if (strcmp(string, "penis") == 0)
        printf("je to penis\n");
    else
        printf("je to pussy\n");
}