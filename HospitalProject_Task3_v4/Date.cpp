#include "Date.h"

using namespace std;

// Constructor for the Date class.
Date::Date(int d, int m, int y)
{
	setDay(d);
	setMonth(m);
	setYear(y);
}

// Sets the day of the date object.
void Date::setDay(int d)
{
	if ((d < 1) || (d > 31))
		throw invalid_argument("Invalid day value!");
	day = d;
}

// Sets the month of the date object.
void Date::setMonth(int m) 
{
	if ((m < 1) || (m > 12))
		throw invalid_argument("Invalid month value!");
	month = m;
}

// Sets the year of the date object.
void Date::setYear(int y) noexcept(true)
{
	year = y;
}

// Displays the date in the format "DD/MM/YYYY".
void Date::show() const
{
	cout << day << "/" << month << "/" << year;
}