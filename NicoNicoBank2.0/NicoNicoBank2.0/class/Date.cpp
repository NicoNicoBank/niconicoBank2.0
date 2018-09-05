#include "Date.h"


ostream& operator<<(ostream& _cout, const Date& date)
{
	_cout << date._year << "/" << date._month << "/" << date._day;
	return _cout;
}

istream& operator>>(istream& _cin, Date& date)
{
	_cin >> date._year >> date._month >> date._day;
	return _cin;
}

Date::Date(int year, int month, int day)
{
	if (year >= 0 && (month >= 0 && month < 13) &&
		(day >= 0 && day <= GetDaysInMonth(year, month)))
	{
		_year = year;
		_month = month;
		_day = day;
	}
	else {
		cout << "the date is illegal\n";
	}
}

Date::Date(const Date& date) : _year(date._year), _month(date._month), _day(date._day) {}

Date& Date::operator=(const Date& date)
{
	if (this != &date) {
		_year = date._year;
		_month = date._month;
		_day = date._day;
	}
	return *this;
}

Date Date::operator+(int day)
{
	Date temp(*this);
	if (day < 0) {
		day = -day;
		return temp - day;
	}
	temp._day += day;
	while (temp._day > GetDaysInMonth(temp._year, temp._month)) {
		temp._day -= GetDaysInMonth(temp._year, temp._month);
		if (temp._month == 12) {
			temp._year++;
			temp._month = 1;
		}
		else {
			temp._month++;
		}
	}
	return temp;
}

Date& Date::operator++()//前置++形如++a
{
	return (*this = *this + 1);
}

Date Date::operator++(int)//后置++形如a++
{
	Date temp(*this);
	*this = *this + 1;
	return temp;
}

Date Date::operator-(int day)
{
	Date temp(*this);
	temp._day -= day;
	while (temp._day <= 0) {
		if (temp._month == 1) {
			temp._year--;
			temp._month = 12;
		}
		else {
			temp._month--;
		}
		temp._day += GetDaysInMonth(temp._year, temp._month);
	}
	return temp;
}

int Date::operator-(const Date& date)
{
	Date maxDate(*this);
	Date minDate(date);
	if (maxDate < minDate) {
		maxDate = date;
		minDate = *this;
	}
	int days = 0;
	while (1) {
		if (minDate + days == maxDate)
			break;
		days++;
	}
	return days;
}

Date& Date::operator--()
{
	return (*this = *this - 1);
}

Date Date::operator--(int)
{
	Date temp(*this);
	*this = *this - 1;
	return temp;
}

void Date::addMonth(int month)
{
	_month += month;
	if (_month > 12) {
		_year += (_month-1) / 12;
	}
	_month = (_month-1) % 12 + 1;
}

bool  Date::operator>(const Date& date)
{
	if (_year > date._year || (_year == date._year && _month > date._month) || (_year == date._year && _month == date._month && _day > date._day))
	{
		return true;
	}
	else
		return false;
}

bool  Date::operator<(const Date& date)
{
	if (_year < date._year || (_year == date._year && _month < date._month) || (_year == date._year && _month == date._month && _day < date._day))
	{
		return true;
	}
	else
		return false;
}

bool  Date::operator==(const Date& date)
{
	return _year == date._year && _month == date._month && _day == date._day;
}

bool  Date::operator!=(const Date& date)
{
	return _year != date._year || _month != date._month || _day != date._day;
}

bool  Date::operator>=(const Date& date)
{
	if (*this < date)
		return false;
	else
		return true;
}

bool  Date::operator<=(const Date& date)
{
	if (*this > date)
		return false;
	else
		return true;
}

void Date::setDate(int year, int month, int day)//0-year
{
	this->_year = year;
	this->_month = month;
	this->_day = day;
}

/*
123123
*/
int Date::get(int type)
{
	switch (type)
	{
	case 0:
		return _year;
	case 1:
		return _month;
	case 2: 
		return _day;
	default:
		return NULL;
	}
	return 0;
}

int Date::get(int type) const
{
	switch (type)
	{
	case 0:
		return _year;
	case 1:
		return _month;
	case 2:
		return _day;
	default:
		return NULL;
	}
	return 0;
}



