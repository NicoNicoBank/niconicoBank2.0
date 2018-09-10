#pragma once
#include <iostream>
using namespace std;
class Date {
public:
	Date(int year = 1949, int month = 10, int day = 1);
	Date(const Date& date);
	//基本运算
	Date& operator=(const Date& date);
	Date operator+(int day);
	Date& operator++();
	Date operator++(int);
	Date operator-(int day);
	int operator-(const Date& date);
	Date& operator--();
	Date operator--(int);
	void addMonth(int month);
	bool operator>(const Date& date);
	bool operator<(const Date& date);
	bool operator==(const Date& date);
	void setDate(int year, int month, int day);
	/*
	获取相关值
	type:0-year, 1-month, 2-day
	*/
	int get(int type);
	int get(int type) const;
	bool checkIllegle(int year, int month, int day);
private:
	bool IsLeapYear(int year);
	int GetDaysInMonth(int year, int month);
private:
	int _year;
	int _month;
	int _day;
};

