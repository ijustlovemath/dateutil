#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "dateutil.h"

int scan_time(const char *time_string, struct date_struct *date)
{
    /* example of just ONE format type */
    char month_abbr[4] = {0};
    int month = -1;
    int day;
    int year;
    int hour;
    int minute;
    char ampm_string [3] = {0};
    int ampm = -1;
    char timezone[4] = {0};
    int result = sscanf(time_string, "%3s %2d, %4d %2d:%2d %2s %3s", month_abbr, &day, &year, &hour, &minute, ampm_string, timezone);


    /* handle these two errors separately! */
    if(result == EOF) {
        return EOF;
    }

    /* sscanf returns how many values it read, we asked for 7
     * so we should expect exactly 7 */
    if(result != 7) {
        return result;
    }

    /* all values read in okay, check theyre in range */
    if(year < 0 || year > 9999) {
        return 7; /* realistically youd define your own error codes here */
    }
    date->year = (int32_t) year;

#define MONTHS \
    MONTH(Jan, 1)\
    MONTH(Feb, 2)\
    MONTH(Mar, 3)\
    MONTH(Apr, 4)\
    MONTH(May, 5)\
    MONTH(Jun, 6)\
    MONTH(Jul, 7)\
    MONTH(Aug, 8)\
    MONTH(Sep, 9)\
    MONTH(Oct, 10)\
    MONTH(Nov, 11)\
    MONTH(Dec, 12)

    /* figure out month with handy x macro */
#define MONTH(name, number) if(!strcmp(#name, month_abbr)) { month = number; }

    MONTHS

#undef MONTH

    if(month <= 0 || month > 12) {
        return 8;
    }
    date->month = (uint8_t) month;

    int biggest_day = 31;
    switch(month) {
    case 2: /* Feb */
        biggest_day = 28;
        break;
    case 4: /* April */
    case 6: /* June */
    case 9: /* September */
    case 11: /* November */
        biggest_day = 30;
        break;
    default:;
    }

    if(day <= 0 || day > biggest_day) {
        return 9;
    }
    date->day = (uint8_t) day;

    /* TODO: add your own checking logic here */
    date->hour = hour;
    date->second = 0; /* not applicable with this format */

    /* timezones are more useful when theyre not strings, but
     * I'm stopping here
     */
    strcpy(date->timezone, timezone);

    return 0;
}
