#ifndef _TIME_UTILS_H_
#define _TIME_UTILS_H_
#include <stdio.h>      
#include <sys/time.h>

//8 * 3600
#define TIME_ZONE_SEC_ADD 28800    //s //东八区
#define TIME_ZONE_MS_ADD  28800000 //ms


class TimeUtils {
public:
//static long sys_time_rough_ms = 0l;
//获取当前us
static long GetCurrentTimeUS() {
	struct timeval tv;
	gettimeofday(&tv,NULL);    //该函数在sys/time.h头文件中
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

//获取当前毫秒
static long GetCurrentTimeMS() {
	struct timeval tv;      
	gettimeofday(&tv,NULL);    //该函数在sys/time.h头文件中  
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

static int DayOfWeek() { //最好不好每次都去取
	long t = GetCurrentTimeMS() + TIME_ZONE_MS_ADD;
	return (t / 1000 / 3600 / 24 + 4)% 7; //+4因为1970-1-1->周四
}
static int HourOfDay() { //最好不好每次都去取
	long t = GetCurrentTimeMS() + TIME_ZONE_MS_ADD;
	return (t / 1000 / 3600) % 24;
}
};



#endif
