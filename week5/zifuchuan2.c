#include <stdio.h>
int main(void)
{
    char null[20];
    int number1 = 0,number2 = 0;
    int num = 0;
    printf("输入字符。\n");
    fgets(null,sizeof(null),stdin);
    for(int i = 0;null[i] != '\0' ;i++){
        if(null[i] >= 'a' && null[i] <= 'z'){
            number1 ++;
        }
        if(null[i] >= 'A' && null[i] <= 'Z'){
            number2 ++;
        }
        if(null[i] >= '0' && null[i] <= '9'){
            num++;
        }
    }
    printf("有%d个小写字符,有%d个大写字符,有个%d数字,共%d个字符。\n",number1,number2,num,number1 + number2+num);
    return 0;
}