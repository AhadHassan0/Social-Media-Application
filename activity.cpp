#include "activity.h"
#include <iostream>
using namespace std;

// Default constructor
Activity::Activity() : type(0), value("") {
}

// Parameterized constructor
Activity::Activity(int t, const string& v) : type(t), value(v) {
}

// Destructor
Activity::~Activity() {
    // No dynamic memory to release
}

// Returns the activity type
int Activity::getType() const {
    return type;
}

// Returns the activity value
string Activity::getValue() const {
    return value;
}

// Sets the activity type
void Activity::setType(int t) {
    type = t;
}

// Sets the activity value
void Activity::setValue(const string& v) {
    value = v;
}

// Returns activity as a string based on type and value
string Activity::toString() const {
    string activityType;

    switch(type) {
    case 1:
        activityType = "feeling";
        break;
    case 2:
        activityType = "thinking about";
        break;
    case 3:
        activityType = "making";
        break;
    case 4:
        activityType = "celebrating";
        break;
    default:
        activityType = "doing";
    }

    return activityType + " " + value;
}

// Displays the activity information to console
void Activity::displayActivity() const {
    cout << toString() << endl;
}
