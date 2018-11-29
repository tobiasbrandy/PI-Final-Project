#include "process.h"

weekday dateToWeekday(tDate date){

	struct tm time;

	time.tm_year = date.year - 1900;
   	time.tm_mon = date.month - 1;
   	time.tm_mday = date.day;
   	time.tm_hour = 0;
   	time.tm_min = 0;
   	time.tm_sec = 1;
   	time.tm_isdst = -1;

   	int err = mktime(&time);
   	if(err == -1){
   		printf("ohno\n");
   		return -1;
   	}

   	return time.tm_wday;
}