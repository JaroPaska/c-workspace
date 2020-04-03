#include <stdio.h>
#include <string.h>

int main(){
    char string[256];
    scanf("%s", string);
    int len = strlen(string);
    for(int i = 0; i < len; i++){
        printf("%c", string[i]);
    }
    printf("\n");
    if(strcmp(string, "janka") == 0){
        printf("Je to janka\n");
    } 
    else {
        printf("je to jarko\n");
    }    
}