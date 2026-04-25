#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <string>
using namespace std;

class Activity {
private:
    int type;       // Type of activity (1-feeling, 2-thinking, 3-making, 4-celebrating)
    string value;   // Value of the activity (what is being felt, thought about, etc.)

public:
    // Constructors and destructor
    Activity();                              // Default constructor
    Activity(int type, const string& value); // Parameterized constructor
    ~Activity();                             // Destructor

    // Getters
    int getType() const;                     // Returns the activity type
    string getValue() const;                 // Returns the activity value

    // Setters
    void setType(int type);                  // Sets the activity type
    void setValue(const string& value);      // Sets the activity value

    // Utility methods
    string toString() const;                 // Returns activity as a string
    void displayActivity() const;            // Displays the activity info
};

#endif // ACTIVITY_H
