#include <stdio.h>

void change(int x)
{
    x = 0;  // 改的是函数里的副本
}

int main(void)
{
    int value = 5;
    change(value);
    int *p = &value;
    printf("%d\n", value);
    return 0;
}