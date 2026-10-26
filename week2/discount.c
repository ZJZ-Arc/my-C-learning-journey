#include <stdio.h>
int main()
{
    const double UNIT_PRICE = 12.5;
    int amount = 0;
    double discount = 0.0;
    printf("输入购买数量和折扣。\n");
    scanf("%d %lf", &amount, &discount);
    printf("总价为%.2f,折后%.2f。\n",amount * UNIT_PRICE,amount * UNIT_PRICE*discount);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    printf("按回车键退出...");
    getchar();
    return 0;
}