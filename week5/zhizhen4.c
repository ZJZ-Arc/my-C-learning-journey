#include <stdio.h>
int max(int *nums,int number){
    int MAX = 0;
    for(int i = 0; i < number ; i ++){
        if(*(nums + i) < *(nums+(i + 1))){
            MAX =*(nums+(i+1));
        }
    }
    return MAX;
}
int main(void)
{
    int number = 0;
    printf("输入数组的模.\n");
    scanf("%d",number);
    int nums[number];
    for(int i = 0; i < number ; i++){
        printf("输入数字.\n");
        scanf("%d",*(nums + i));
    }
    int MAX=0;
    MAX = max(nums,number);
    printf("%d",MAX);
    return 0 ;
}