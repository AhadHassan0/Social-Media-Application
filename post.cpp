#include "post.h"
#include "user.h"
#include "page.h"
#include <iostream>
using namespace std;

// Default constructor
Post::Post() :
    uniqueID(""),
    description(""),
    likedBy(nullptr),
    likeCount(0),
    maxLikes(10),
    comments(nullptr),
    commentCount(0),
    maxComments(10),
    activity(nullptr) {

    // Initialize arrays
    likedBy = new User*[maxLikes];
    comments = new Comment*[maxComments];
}

// Parameterized constructor
Post::Post(const string& id, const string& desc, const Date& date) :
    uniqueID(id),
    description(desc),
    sharedDate(date),
    likedBy(nullptr),
    likeCount(0),
    maxLikes(10),
    comments(nullptr),
    commentCount(0),
    maxComments(10),
    activity(nullptr) {

    // Initialize arrays
    likedBy = new User*[maxLikes];
    comments = new Comment*[maxComments];
}

// Destructor - virtual for inheritance
Post::~Post() {
    // Delete allocated memory for comments
    for (int i = 0; i < commentCount; i++) {
        delete comments[i];
    }

    // Delete arrays (not the users they point to, as they're owned elsewhere)
    delete[] likedBy;
    delete[] comments;

    // Delete activity if it exists
    if (activity != nullptr) {
        delete activity;
    }
}

// Returns the unique ID of the post
string Post::getUniqueID() const {
    return uniqueID;
}

// Returns the post description
string Post::getDescription() const {
    return description;
}

// Returns the date when post was shared
Date Post::getSharedDate() const {
    return sharedDate;
}

// Returns the number of likes on the post
int Post::getLikeCount() const {
    return likeCount;
}

// Returns the activity associated with the post (if any)
Activity* Post::getActivity() const {
    return activity;
}

// Sets the post ID
void Post::setUniqueID(const string& id) {
    uniqueID = id;
}

// Sets the post description
void Post::setDescription(const string& desc) {
    description = desc;
}

// Sets the date when post was shared
void Post::setSharedDate(const Date& date) {
    sharedDate = date;
}

// Sets the activity associated with the post
void Post::setActivity(Activity* act) {
    // Delete existing activity if any
    if (activity != nullptr) {
        delete activity;
    }
    activity = act;
}

// Adds a like from a user
bool Post::addLike(User* user) {
    // Check if post already has maximum likes
    if (likeCount >= maxLikes) {
        return false;
    }

    // Check if user already liked this post
    for (int i = 0; i < likeCount; i++) {
        if (likedBy[i] == user) {
            return false;
        }
    }

    // Add user to likedBy array
    likedBy[likeCount] = user;
    likeCount++;
    return true;
}

// Returns array of users who liked the post
User** Post::getLikedBy() const {
    return likedBy;
}

// Checks if post is liked by a specific user
bool Post::isLikedBy(User* user) const {
    for (int i = 0; i < likeCount; i++) {
        if (likedBy[i] == user) {
            return true;
        }
    }
    return false;
}

// Adds a comment from a user
bool Post::addComment(const string& text, User* user) {
    // Check if post already has maximum comments
    if (commentCount >= maxComments) {
        return false;
    }

    // Create new comment
    Comment* comment = new Comment(text, user);

    // Add comment to array
    comments[commentCount] = comment;
    commentCount++;
    return true;
}

// Adds a comment from a page
bool Post::addComment(const string& text, Page* page) {
    // Check if post already has maximum comments
    if (commentCount >= maxComments) {
        return false;
    }

    // Create new comment
    Comment* comment = new Comment(text, page);

    // Add comment to array
    comments[commentCount] = comment;
    commentCount++;
    return true;
}

// Returns array of comments on the post
Comment** Post::getComments() const {
    return comments;
}

// Returns number of comments on the post
int Post::getCommentCount() const {
    return commentCount;
}

// Displays the post content
void Post::displayPost() const {
    cout << "--- ";

    // If there's an activity associated with this post
    if (activity != nullptr) {
        cout << activity->toString();
    }

    cout << endl;
    cout << " \"" << description << "\" ... (" << sharedDate.toString() << ")" << endl;

    // Display comments if any
    displayComments();
}

// Displays all comments on the post
void Post::displayComments() const {
    for (int i = 0; i < commentCount; i++) {
        comments[i]->displayComment();
    }
}

// Displays users who liked the post
void Post::displayLikedBy() const {
    cout << "Post Liked By:" << endl;
    for (int i = 0; i < likeCount; i++) {
        cout << likedBy[i]->getUniqueID() << " - " << likedBy[i]->getName() << endl;
    }
}
