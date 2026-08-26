#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int counter = 0;

    while (1)
    {
        counter++;

        printf("Counter = %d\n", counter);
        fflush(stdout);

        sleep(1);
    }

    return 0;
}
