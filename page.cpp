#include "page.h"
#include "user.h"
#include <iostream>
using namespace std;

// Default constructor
Page::Page() :
    uniqueID(""),
    title(""),
    owner(nullptr),
    timeline(nullptr),
    postCount(0),
    likedBy(nullptr),
    likeCount(0) {

    // Initialize arrays
    timeline = new Post*[100]; // Assume max 100 posts
    likedBy = new User*[100];  // Assume max 100 likes
}

// Parameterized constructor
Page::Page(const string& id, const string& t, User* o) :
    uniqueID(id),
    title(t),
    owner(o),
    timeline(nullptr),
    postCount(0),
    likedBy(nullptr),
    likeCount(0) {

    // Initialize arrays
    timeline = new Post*[100]; // Assume max 100 posts
    likedBy = new User*[100];  // Assume max 100 likes
}

// Destructor
Page::~Page() {
    // Delete all posts in the timeline
    for (int i = 0; i < postCount; i++) {
        delete timeline[i];
    }

    // Delete arrays (not the users they point to)
    delete[] timeline;
    delete[] likedBy;
}

// Returns the unique ID of the page
string Page::getUniqueID() const {
    return uniqueID;
}

// Returns the title of the page
string Page::getTitle() const {
    return title;
}

// Returns the owner of the page
User* Page::getOwner() const {
    return owner;
}

// Returns the number of likes on the page
int Page::getLikeCount() const {
    return likeCount;
}

// Returns the timeline of posts
Post** Page::getTimeline() const {
    return timeline;
}

// Returns the number of posts in the timeline
int Page::getPostCount() const {
    return postCount;
}

// Sets the page ID
void Page::setUniqueID(const string& id) {
    uniqueID = id;
}

// Sets the page title
void Page::setTitle(const string& t) {
    title = t;
}

// Sets the page owner
void Page::setOwner(User* o) {
    owner = o;
}

// Adds a user who likes this page
bool Page::addLikedBy(User* user) {
    // Check if user already liked this page
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

// Returns array of users who liked the page
User** Page::getLikedBy() const {
    return likedBy;
}

// Checks if page is liked by a specific user
bool Page::isLikedBy(User* user) const {
    for (int i = 0; i < likeCount; i++) {
        if (likedBy[i] == user) {
            return true;
        }
    }
    return false;
}

// Adds a post to the page timeline
bool Page::addPost(Post* post) {
    // Add post to timeline
    timeline[postCount] = post;
    postCount++;
    return true;
}

// Shares a new post on the page
void Page::sharePost(const string& postID, const string& content, const Date& date) {
    Post* post = new Post(postID, content, date);
    addPost(post);
}

// Shares a new post with activity on the page
void Page::sharePost(const string& postID, const string& content, const Date& date, Activity* activity) {
    Post* post = new Post(postID, content, date);
    post->setActivity(activity);
    addPost(post);
}

// Adds a comment to a post on the page
bool Page::commentOnPost(const string& postID, const string& commentText) {
    // Find the post with given ID
    for (int i = 0; i < postCount; i++) {
        if (timeline[i]->getUniqueID() == postID) {
            // Add comment to the post
            return timeline[i]->addComment(commentText, this);
        }
    }
    return false;
}

// Displays page information
void Page::displayPage() const {
    cout << title << endl;
    displayTimeline();
}

// Displays the page timeline
void Page::displayTimeline() const {
    for (int i = 0; i < postCount; i++) {
        cout << "--- " << title << " ";

        // If this post has an activity
        if (timeline[i]->getActivity() != nullptr) {
            cout << "is " << timeline[i]->getActivity()->toString() << ".";
        }

        cout << " ... (" << timeline[i]->getSharedDate().toString() << ")" << endl;
        cout << " \"" << timeline[i]->getDescription() << "\"" << endl;

        // Display comments
        timeline[i]->displayComments();
    }
}
