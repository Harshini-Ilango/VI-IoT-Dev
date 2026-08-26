#include <stdio.h>

int main(void)
{
    int *p = 0;

    printf("Program is running...\n");

    *p = 42;

    printf("This line will never execute.\n");

    return 0;
}
