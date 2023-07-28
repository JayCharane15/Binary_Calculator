#include<stdio.h>
#include<ctype.h>
int main()
{
    char ch = getchar();
    printf("%d\n", isdigit(ch));
    int x = ch -'0';
    printf("%d", x);
}