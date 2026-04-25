#include "date.h"
#include <sstream>
#include <iomanip>
using namespace std;

// Default constructor - sets to a default date
Date::Date() : day(1), month(1), year(2017) {
}

// Parameterized constructor
Date::Date(int d, int m, int y) : day(d), month(m), year(y) {
}

// Destructor
Date::~Date() {
    // No dynamic memory to release
}

// Returns the day
int Date::getDay() const {
    return day;
}

// Returns the month
int Date::getMonth() const {
    return month;
}

// Returns the year
int Date::getYear() const {
    return year;
}

// Sets the day
void Date::setDay(int d) {
    day = d;
}

// Sets the month
void Date::setMonth(int m) {
    month = m;
}

// Sets the year
void Date::setYear(int y) {
    year = y;
}

// Sets the complete date
void Date::setDate(int d, int m, int y) {
    day = d;
    month = m;
    year = y;
}

// Returns date as a string in format "dd/mm/yyyy"
string Date::toString() const {
    stringstream ss;
    ss << day << "/" << month << "/" << year;
    return ss.str();
}

// Checks if two dates are equal
bool Date::isEqual(const Date& other) const {
    return (day == other.day && month == other.month && year == other.year);
}

// Checks if dates are on the same day
bool Date::isInSameDay(const Date& other) const {
    return (day == other.day && month == other.month && year == other.year);
}

// Checks if date is within last 24 hours of the given current date
bool Date::isWithinLast24Hours(const Date& currentDate) const {
    // Simple implementation - just check if it's same day or previous day
    if (year == currentDate.year && month == currentDate.month) {
        if (day == currentDate.day || day == currentDate.day - 1) {
            return true;
        }
    }
    // Check for month boundary (e.g., April 30 vs May 1)
    else if (year == currentDate.year && month == currentDate.month - 1) {
        // If current date is 1st of month and this date is last day of previous month
        if (currentDate.day == 1 && (
                (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day == 31 ||
                (month == 4 || month == 6 || month == 9 || month == 11) && day == 30 ||
                (month == 2 && day == 28) // Simplified, not handling leap years
                )) {
            return true;
        }
    }
    return false;
}
