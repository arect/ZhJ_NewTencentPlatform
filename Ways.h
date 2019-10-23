/*常用函数*/
#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<time.h>
using namespace std;
//字符串转数字 错误返回0
int Str2Num(const string a) {
	int num = 0;
	for (unsigned int i = 1; i < a.size(); i++) {
		if (a[i] < '0' || '9' < a[i])
			return 0;
	}
	if (a[0] == '-') {
		for (unsigned int i = 1; i < a.size(); i++) {
			num *= 10;
			num += (a[i] - '0');
		}
		return (-1 * num);
	}
	else if ('0' <= a[0] && a[0] <= '9') {
		for (unsigned int i = 0; i < a.size(); i++) {
			num *= 10;
			num += (a[i] - '0');
		}
		return num;
	}
	return 0;
}
//数字转字符
string Num2Str(const int c) {
	string b;
	int a = c;
	b.push_back(a % 10 + '0');
	a /= 10;
	while (a != 0) {
		b.insert(b.begin(),a % 10 + '0');
		a /= 10;
	}
	return b;
}
//日志
void WriteLog(const string a) {
	ofstream Log;
	Log.open("Log.txt", ios::app);
	time_t time_seconds = time(0);
	struct tm now_time;
	localtime_s(&now_time, &time_seconds);
	Log.seekp(ios::end);
	if (Log.is_open()) {
		Log << now_time.tm_year + 1900 << "/" << now_time.tm_mon + 1 << "/" << now_time.tm_mday + 1 << " " << now_time.tm_hour << ":" << now_time.tm_min << ":" << now_time.tm_sec << " ";
		Log << a << "\n";
		Log.close();
	}
	else {
		cout << "日志启动失败";
	}
}