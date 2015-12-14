#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date {
private:
	bool isLeapYear;
	int* dpm;
	void checkLeapYear() {
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			isLeapYear = true;
		else
			isLeapYear = false;

		if (isLeapYear) {
			dpm[1] = 29;
		}
	}

public:
	int day;
	int month;
	int year;

	Date() : day(1), month(1), year(2000) {
		int days_per_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		dpm = days_per_month;
		checkLeapYear();
	}

	Date(int _day, int _month, int _year) : day(_day), month(_month), year(_year) {
		int days_per_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		dpm = days_per_month;
		checkLeapYear();
	}

	Date(const Date& date) : day(date.day), month(date.month), year(date.year) {
		int days_per_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		dpm = days_per_month;
		checkLeapYear();
	}

	~Date() {
	}


	friend std::ostream& operator<< (std::ostream& outs, Date date) {
		outs << date.month << "/" << date.day << "/" << date.year;
		return outs;
	}

	Date operator= (const Date& rhs){
		day = rhs.day; 
		month = rhs.month;
		year = rhs.year;
		return *this;
	}

	bool operator== (const Date& rhs) {
		return (day == rhs.day && month == rhs.month && year == rhs.year);
	}

	bool operator> (const Date& rhs) {
		return (year > rhs.year || (year == rhs.year && month > rhs.month) || (year == rhs.year && month == rhs.month && day > rhs.day));
	}
	
	bool operator< (const Date& rhs) {
		return (year < rhs.year || (year == rhs.year && month < rhs.month) || (year == rhs.year && month == rhs.month && day < rhs.day));
	}

	bool operator<= (const Date& rhs) {
		return !(*this > rhs);
	}

	bool operator>= (const Date& rhs) {
		return !(*this < rhs);
	}
};

#endif // DATE_H