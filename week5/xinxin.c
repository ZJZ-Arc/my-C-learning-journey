#include <stdio.h>
int main(void)
{
    int n;
    printf("输入数字n。\n");
    scanf("%d",&n);
    int star = 2 * n - 1;
    int space = 0;
    for(int i = 1;i <= n; i++ ){
        for(int i = 1; i <= space; i++){
            printf(" ");
        }
        
        for(int i = 1;i <= star ; i++){
            printf("*");
        } 
        printf("\n");
        space++;
        star = star - 2;
    }
    return 0;
}