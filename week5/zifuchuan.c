#include <stdio.h>
int main(void)
{
    char name[20];
    printf("输入名字\n");
    fgets(name,sizeof(name),stdin);
    for(int i = 0; i < 20 ; i++){
        if(name[i] == '\n'){
            name[i] = '\0';break;
        }
    }
    printf("你的名字是：%s",name);
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
    printf("按回车键退出...");
    getchar();
    return 0 ;
}