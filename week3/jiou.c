#include <stdio.h>
int main()
{
    int num;
    printf("输入数字。\n");
    if(scanf("%d", &num) != 1)
    {
        printf("输入错误。\n");
        return 1;
    }
    if(num%2==0)
    {
          printf("该数字为偶数。\n");
    }else{
          printf("该数字为奇数。\n");
    }
    
    return 0;
}