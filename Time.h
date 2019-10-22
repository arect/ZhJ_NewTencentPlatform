/*时间类
/*便捷地管理时间
*/
#pragma once
#include<iostream>
#include<time.h>
#include<string>

class class_Time {
protected:
	unsigned int Year = 1900;
	unsigned int Mon = 1;
	unsigned int Day = 1;
public:
	class_Time() {
		time_t time_seconds = time(0);
		struct tm now_time;
		localtime_s(&now_time, &time_seconds);
		Year += now_time.tm_year;
		Mon += now_time.tm_mon;
		Day = now_time.tm_mday;
	}
	~class_Time(){}
	//修改年份
	int Modify_Year(const int a) {
		if (1900 <= a && a <= 2020)
			Year = a;
		return Year;
	}
	//修改月份
	int Modify_Mon(const int a) {
		if (1 <= a && a <= 12)
			Mon = a;
		return Mon;
	}
	//修改日子
	int Modify_Day(const int a) {
		if ((Mon == 1 || Mon == 3 || Mon == 5 || Mon == 7 || Mon == 8 || Mon == 10 || Mon == 12) && 1 <= a && a <= 31)
			Day = a;
		if ((Mon == 4 || Mon == 6 || Mon == 9 || Mon == 11) && 1 <= a && a <= 30)
			Day = a;
		if (Mon == 2 && 1 <= a && a <= 29) {
			if (Year == 1900 || Year % 4 != 0)
				if (a <= 28) {
					Day = a;
					return Day;
				}
			if (Year % 4 == 0 && Year != 1900)
				Day = a;
		}
		return Day;
	}
	//返回日期
	int OutDate() {
		return Year * 10000 + Mon * 100 + Day;
	}
	int InDate(const int a) {
		if (Modify_Year(a / 10000) != a / 10000)
			return -1;
		if (Modify_Mon((a % 10000) / 100) != (a % 10000) / 100)
			return -2;
		if (Modify_Day(a % 100) != a % 100)
			return -3;
		return 0;
	}
};