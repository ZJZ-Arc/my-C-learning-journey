#include <stdio.h>
int main(void)
{
    char first_name[20];
    char last_name[20];
    printf("输入一个名字。\n");
    scanf("%19s %19s",first_name,last_name);
    printf("你的名字是：%s %s\n",first_name,last_name);
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
    printf("按回车键退出...");
    getchar();
    return 0;
}