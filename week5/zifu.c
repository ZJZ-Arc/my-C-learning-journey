#include <stdio.h>
int main(void)
{
    char grades[3];
    for(int i = 0;i < 3;i++){
        printf("输入字符\n");
        scanf(" %c",&grades[i]);
    }

    for(int i = 0;i < 3;i++){
        printf("所有字符为：%c\n",grades[i]);
    }
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
    printf("按回车键退出...");
    getchar();
    return 0 ;
}