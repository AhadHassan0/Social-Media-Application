#ifndef DATE_H
#define DATE_H

#include <string>
using namespace std;

class Date {
private:
    int day;    // Day of the month
    int month;  // Month of the year
    int year;   // Year

public:
    // Constructors and destructor
    Date();                                // Default constructor
    Date(int day, int month, int year);    // Parameterized constructor
    ~Date();                               // Destructor

    // Getters
    int getDay() const;                    // Returns the day
    int getMonth() const;                  // Returns the month
    int getYear() const;                   // Returns the year

    // Setters
    void setDay(int day);                  // Sets the day
    void setMonth(int month);              // Sets the month
    void setYear(int year);                // Sets the year
    void setDate(int day, int month, int year); // Sets the complete date

    // Utility methods
    string toString() const;               // Returns date as a string "dd/mm/yyyy"
    bool isEqual(const Date& other) const; // Checks if two dates are equal
    bool isInSameDay(const Date& other) const; // Checks if dates are on the same day
    bool isWithinLast24Hours(const Date& currentDate) const; // Checks if date is within last 24h
};

#endif // DATE_H
