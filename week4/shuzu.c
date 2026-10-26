#include <stdio.h>
int main(void)
{
    int day ;
    printf("请输入要记录的天数。\n");
    scanf("%d",&day);
    while(day <= 0 ||day > 30 ){
        printf("输入错误，请重新输入。\n");
        scanf("%d",&day);
    }
    double hours[day];
    double total = 0.0;
    double average = 0.0;
    
    for(int a = 0;a < day;a++){
        printf("请输入第%d天学习时间:\n",a + 1);
        scanf("%lf",&hours[ a ]);
        while(hours[a] < 0 || hours[ a ] > 24){
            printf("错误，请重新输入。\n");
            scanf("%lf",&hours[ a ]);
        }
        total = total + hours[ a ];
    }
    double max_hours = hours[ 0 ];
    for(int b = 1;b < day;b++){
         if(max_hours < hours[ b ]){
            max_hours = hours[ b ];
         }
    }
    average = total / day;
    printf("总天数为：%d\n",day);

    for(int i = 0;i < day;i++){
        printf("第%d天学习%.1f小时\n",i + 1,hours[ i ]);
    }
    printf("总时长:%.1f\n平均时长:%.1f\n最长时长:%.1f\n",total,average,max_hours);
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
    printf("按回车键退出...");
    getchar();
    
    return 0;
}