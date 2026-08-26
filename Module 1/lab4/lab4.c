#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

/* -----------------------------
 * Capability bits
 * ----------------------------- */

#define CAP_BIT0 (1U << 0)
#define CAP_BIT1 (1U << 1)
#define CAP_BIT2 (1U << 2)
#define CAP_BIT3 (1U << 3)

/* -----------------------------
 * IE handler function type
 * ----------------------------- */

typedef int (*ie_handler_t)(const uint8_t *data, uint8_t len);

/* -----------------------------
 * IE handlers
 * ----------------------------- */

static int handle_ssid(const uint8_t *data, uint8_t len)
{
    printf("SSID handler: length=%u\n", len);

    if (len > 0)
        printf("First byte = %02x\n", data[0]);

    return 0;
}

static int handle_rates(const uint8_t *data, uint8_t len)
{
    printf("Rates handler: length=%u\n", len);

    if (len > 0)
        printf("First rate byte = %02x\n", data[0]);

    return 0;
}

/* -----------------------------
 * Dispatch table
 * ----------------------------- */

static ie_handler_t dispatch[256];

/* -----------------------------
 * Register handlers
 * ----------------------------- */

static void register_handlers(void)
{
    dispatch[0] = handle_ssid;
    dispatch[1] = handle_rates;
}

/* -----------------------------
 * Parse IEs
 * ----------------------------- */

static int parse_ies(const uint8_t *buf, size_t buflen)
{
    size_t off = 0;

    while (off + 2 <= buflen)
    {
        uint8_t id = buf[off];
        uint8_t len = buf[off + 1];

        printf("\nFound IE: id=%u len=%u\n", id, len);

        /* Check for truncated IE */
        if (off + 2 + len > buflen)
        {
            printf("ERROR: IE is truncated\n");
            return -1;
        }

        /* Check whether handler exists */
        if (dispatch[id] != NULL)
        {
            dispatch[id](buf + off + 2, len);
        }
        else
        {
            printf("No handler registered for IE %u\n", id);
        }

        off += 2 + len;
    }

    if (off != buflen)
    {
        printf("ERROR: leftover bytes\n");
        return -1;
    }

    return 0;
}

/* -----------------------------
 * Main
 * ----------------------------- */

int main(void)
{
    uint8_t capabilities = 0;

    /* Enable capability bit 0 */
    capabilities |= CAP_BIT0;

    /* Enable capability bit 2 */
    capabilities |= CAP_BIT2;

    printf("Capabilities = 0x%02x\n", capabilities);

    if (capabilities & CAP_BIT0)
        printf("Capability 0 is enabled\n");

    if (capabilities & CAP_BIT1)
        printf("Capability 1 is enabled\n");

    if (capabilities & CAP_BIT2)
        printf("Capability 2 is enabled\n");

    register_handlers();

    /* Fake Wi-Fi IEs */
    const uint8_t ies[] =
    {
        0x00, 0x03, 'l', 'a', 'b',
        0x05, 0x01, 0x8c
    };

    if (parse_ies(ies, sizeof(ies)) != 0)
    {
        printf("Parsing failed\n");
        return 1;
    }

    printf("\nParsing successful\n");

    return 0;
}
