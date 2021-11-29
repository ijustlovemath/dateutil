#include <inttypes.h>

struct date_struct {
    int32_t year; /* 0-9999, 0 is 0 AD */
    uint8_t month; /* 1-12 */
    uint8_t day; /* 1-31 */
    uint8_t hour; /* 0-23 */
    uint8_t second; /* 0-60 */
    char timezone[24];
};

extern int scan_time(const char *time_string, struct date_struct *date);
