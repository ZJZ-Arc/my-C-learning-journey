#include <stdio.h>
double calculate_total(double items[], int num){
    double total = 0.0;
    for(int i = 0 ; i < num ; i++ ){
        total = total + items[ i ];
    }
    return total;
}
int main(void){
    int num ;
    printf("输入买的数量。\n");
    scanf("%d",&num);
    while(num <= 0 || num > 30){
        printf("错误，重新输入。\n");
        scanf("%d",&num);
    }
    double items[num];
    for(int i = 0; i< num ; i++){
        printf("输入第%d件商品的价格。\n",i + 1);
        scanf("%lf",&items[i]);
        while(items[i] < 0 ){
            printf("错误，重新输入。\n");
            scanf("%lf",&items[i]);
        }
    }
    int expensive_count = 0;
    double average = 0.0 ,total = 0.0 ,max_price = items[0];
    total = calculate_total(items,num);
    average = total / num;
    for(int i = 0; i < num;i++){
        if(max_price < items[i]){
           max_price = items[i];
        }
    }
    for(int i = 0; i < num ; i++){
        if(items[i] >= 100){
            expensive_count++;
        }
    }
    
    printf("总价格:%.1f\n平均价格:%.1f\n最高价格:%.1f\n价格不低于100元的商品数量:%d",total,average,max_price,expensive_count);
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
    printf("按回车键退出...");
    getchar();
    return 0;
}
