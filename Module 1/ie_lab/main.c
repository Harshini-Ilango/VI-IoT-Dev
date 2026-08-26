#include <stdio.h>
#include <stdint.h>

#include "ie_parse.h"

int main(void)
{
    const uint8_t ies[] =
    {
        0x00, 0x03, 'l', 'a', 'b',
        0x01, 0x01, 0x8c
    };

    int result = foreach_ie(ies, sizeof(ies));

    if (result != 0)
    {
        printf("Parse error\n");
        return 1;
    }

    printf("Parsing completed  successful\n");

    return 0;
}
