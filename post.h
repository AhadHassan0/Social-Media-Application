#ifndef POST_H
#define POST_H

#include "forwarddeclarations.h"
#include "date.h"
#include "comment.h"
#include "activity.h"
#include <string>
using namespace std;

class Post {
private:
    string uniqueID;     // Unique identifier for post
    string description;  // Text content of post
    Date sharedDate;     // Date when post was shared
    User** likedBy;      // Array of users who liked this post
    int likeCount;       // Current number of likes
    int maxLikes;        // Maximum number of likes allowed
    Comment** comments;  // Array of comments on post
    int commentCount;    // Current number of comments
    int maxComments;     // Maximum number of comments allowed
    Activity* activity;  // Activity associated with post (optional)

public:
    // Constructors and destructor
    Post();                                                   // Default constructor
    Post(const string& id, const string& desc, const Date& date); // Parameterized constructor
    virtual ~Post();                                          // Virtual destructor for inheritance

    // Getters
    string getUniqueID() const;                               // Returns post ID
    string getDescription() const;                            // Returns post description
    Date getSharedDate() const;                               // Returns shared date
    int getLikeCount() const;                                 // Returns number of likes
    Activity* getActivity() const;                            // Returns associated activity

    // Setters
    void setUniqueID(const string& id);                       // Sets post ID
    void setDescription(const string& desc);                  // Sets post description
    void setSharedDate(const Date& date);                     // Sets shared date
    void setActivity(Activity* activity);                     // Sets associated activity

    // Like functionality
    bool addLike(User* user);                                 // Adds a like from a user
    User** getLikedBy() const;                                // Returns array of users who liked
    bool isLikedBy(User* user) const;                         // Checks if liked by specific user

    // Comment functionality
    bool addComment(const string& text, User* user);          // Adds comment from user
    bool addComment(const string& text, Page* page);          // Adds comment from page
    Comment** getComments() const;                            // Returns array of comments
    int getCommentCount() const;                              // Returns number of comments

    // Display methods
    virtual void displayPost() const;                         // Displays post content
    void displayComments() const;                             // Displays post comments
    void displayLikedBy() const;                              // Displays users who liked
};

#endif // POST_H
