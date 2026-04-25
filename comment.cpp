#include "comment.h"
#include "user.h"
#include "page.h"
#include <iostream>
using namespace std;

// Default constructor
Comment::Comment() : text(""), userCommenter(nullptr), pageCommenter(nullptr) {
}

// Constructor for user comment
Comment::Comment(const string& t, User* user) :
    text(t), userCommenter(user), pageCommenter(nullptr) {
}

// Constructor for page comment
Comment::Comment(const string& t, Page* page) :
    text(t), userCommenter(nullptr), pageCommenter(page) {
}

// Destructor
Comment::~Comment() {
    // Don't delete the commenter pointers as they are owned elsewhere
}

// Returns the comment text
string Comment::getText() const {
    return text;
}

// Returns the user who made the comment (if any)
User* Comment::getUserCommenter() const {
    return userCommenter;
}

// Returns the page that made the comment (if any)
Page* Comment::getPageCommenter() const {
    return pageCommenter;
}

// Checks if comment was made by a user
bool Comment::isUserComment() const {
    return userCommenter != nullptr;
}

// Checks if comment was made by a page
bool Comment::isPageComment() const {
    return pageCommenter != nullptr;
}

// Displays the comment information
void Comment::displayComment() const {
    if (isUserComment()) {
        cout << " " << userCommenter->getName() << " wrote: \"" << text << "\"" << endl;
    } else if (isPageComment()) {
        cout << " " << pageCommenter->getTitle() << " wrote: \"" << text << "\"" << endl;
    } else {
        cout << " Anonymous wrote: \"" << text << "\"" << endl;
    }
}
