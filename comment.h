#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include "forwarddeclarations.h"
using namespace std;

class Comment {
private:
    string text;        // Text content of the comment
    User* userCommenter;// Pointer to User if comment made by a user
    Page* pageCommenter;// Pointer to Page if comment made by a page

public:
    // Constructors and destructor
    Comment();                              // Default constructor
    Comment(const string& text, User* user);// Constructor for user comment
    Comment(const string& text, Page* page);// Constructor for page comment
    ~Comment();                             // Destructor

    // Getters
    string getText() const;                 // Returns the comment text
    User* getUserCommenter() const;         // Returns the user who commented (nullptr if page)
    Page* getPageCommenter() const;         // Returns the page that commented (nullptr if user)

    // Utility methods
    bool isUserComment() const;             // Checks if comment was made by a user
    bool isPageComment() const;             // Checks if comment was made by a page
    void displayComment() const;            // Displays the comment information
};

#endif // COMMENT_H
