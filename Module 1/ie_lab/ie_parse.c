#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#include "ie_parse.h"

int foreach_ie(const uint8_t *buf, size_t buflen)
{
    size_t off = 0;

    while (off + 2 <= buflen)
    {
        uint8_t id = buf[off];
        uint8_t len = buf[off + 1];

        if (off + 2 + len > buflen)
        {
            return -1;
        }

        printf("IE id=%u len=%u\n", id, len);

        off += 2 + len;
    }

    if (off != buflen)
    {
        return -1;
    }

    return 0;
}
