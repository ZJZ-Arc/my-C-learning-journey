#include <stdio.h>
int main()
{
    int price = 0;
    int bill = 0;
    printf("请输入金额\n");
    scanf("%d",&price);
    printf("请输入票面金额。\n");
    scanf("%d",&bill);
    if(bill>price){
        printf("应该找你%d元.\n",bill - price);
    }else{
        printf("你的钱不够。\n");
    }
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
    printf("按回车键退出...");
    getchar();
    return 0;
}    