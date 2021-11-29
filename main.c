#include <stdio.h>
#include <stdlib.h> /* exit */

#include "dateutil.h"

int main(int argc, char *argv[])
{
    struct date_struct date = {0}; /* zero init or timezone will have issues */
    if(scan_time("Sep 16, 2010 4:39 AM UTC", &date)) {
        puts("problem scanning date");
        exit(1);
    }
    printf("%d/%d/%d %s\n", date.year, date.month, date.day, date.timezone);

    return 0;
}
