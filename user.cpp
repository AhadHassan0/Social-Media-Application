#include "user.h"
#include "memory.h"
#include <iostream>
using namespace std;

// Default constructor
User::User() :
    uniqueID(""),
    name(""),
    friendsList(nullptr),
    friendCount(0),
    likedPages(nullptr),
    likedPageCount(0),
    timeline(nullptr),
    postCount(0) {

    // Initialize arrays
    friendsList = new User*[100]; // Assume max 100 friends
    likedPages = new Page*[100];  // Assume max 100 liked pages
    timeline = new Post*[100];    // Assume max 100 posts
}

// Parameterized constructor
User::User(const string& id, const string& n) :
    uniqueID(id),
    name(n),
    friendsList(nullptr),
    friendCount(0),
    likedPages(nullptr),
    likedPageCount(0),
    timeline(nullptr),
    postCount(0) {

    // Initialize arrays
    friendsList = new User*[100]; // Assume max 100 friends
    likedPages = new Page*[100];  // Assume max 100 liked pages
    timeline = new Post*[100];    // Assume max 100 posts
}

// Destructor
User::~User() {
    // Delete all posts in the timeline
    for (int i = 0; i < postCount; i++) {
        delete timeline[i];
    }

    // Delete arrays (not the objects they point to)
    delete[] friendsList;
    delete[] likedPages;
    delete[] timeline;
}

// Returns the user's unique ID
string User::getUniqueID() const {
    return uniqueID;
}

// Returns the user's name
string User::getName() const {
    return name;
}

// Returns the user's friends list
User** User::getFriendsList() const {
    return friendsList;
}

// Returns the number of friends
int User::getFriendCount() const {
    return friendCount;
}

// Returns the pages liked by the user
Page** User::getLikedPages() const {
    return likedPages;
}

// Returns the number of liked pages
int User::getLikedPageCount() const {
    return likedPageCount;
}

// Returns the user's timeline
Post** User::getTimeline() const {
    return timeline;
}

// Returns the number of posts in the timeline
int User::getPostCount() const {
    return postCount;
}

// Sets the user's unique ID
void User::setUniqueID(const string& id) {
    uniqueID = id;
}

// Sets the user's name
void User::setName(const string& n) {
    name = n;
}

// Adds another user as a friend
bool User::addFriend(User* friend_) {
    // Check if already friends
    for (int i = 0; i < friendCount; i++) {
        if (friendsList[i] == friend_) {
            return false;
        }
    }

    // Add to friends list
    friendsList[friendCount] = friend_;
    friendCount++;
    return true;
}

// Checks if this user is friends with another user
bool User::isFriendsWith(User* user) const {
    for (int i = 0; i < friendCount; i++) {
        if (friendsList[i] == user) {
            return true;
        }
    }
    return false;
}

// Displays the user's friends list
void User::displayFriendsList() const {
    cout << "-------------------------------------------------------------------------------------------------------------" << endl;
    cout << name << " - Friend List" << endl;

    for (int i = 0; i < friendCount; i++) {
        cout << friendsList[i]->getUniqueID() << " - " << friendsList[i]->getName() << endl;
    }

    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
}

// Likes a page
bool User::likePage(Page* page) {
    // Check if already liked
    for (int i = 0; i < likedPageCount; i++) {
        if (likedPages[i] == page) {
            return false;
        }
    }

    // Add to liked pages
    likedPages[likedPageCount] = page;
    likedPageCount++;

    // Add user to page's likedBy list
    page->addLikedBy(this);

    return true;
}

// Checks if user has liked a page
bool User::isLikedPage(Page* page) const {
    for (int i = 0; i < likedPageCount; i++) {
        if (likedPages[i] == page) {
            return true;
        }
    }
    return false;
}

// Displays the pages liked by the user
void User::displayLikedPages() const {
    cout << "-------------------------------------------------------------------------------------------------------------" << endl;
    cout << name << " - Liked Pages" << endl;

    for (int i = 0; i < likedPageCount; i++) {
        cout << likedPages[i]->getUniqueID() << " - " << likedPages[i]->getTitle() << endl;
    }

    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
}

// Adds a post to the user's timeline
bool User::addPost(Post* post) {
    // Add post to timeline
    timeline[postCount] = post;
    postCount++;
    return true;
}

// Shares a new post
void User::sharePost(const string& postID, const string& content, const Date& date) {
    Post* post = new Post(postID, content, date);
    addPost(post);
}

// Shares a new post with activity
void User::sharePost(const string& postID, const string& content, const Date& date, Activity* activity) {
    Post* post = new Post(postID, content, date);
    post->setActivity(activity);
    addPost(post);
}

// Likes a post
bool User::likePost(Post* post) {
    return post->addLike(this);
}

// Comments on a post
bool User::commentOnPost(const string& postID, const string& commentText) {
    // First check user's own posts
    for (int i = 0; i < postCount; i++) {
        if (timeline[i]->getUniqueID() == postID) {
            return timeline[i]->addComment(commentText, this);
        }
    }

    // Check friends' posts
    for (int i = 0; i < friendCount; i++) {
        Post* post = friendsList[i]->findPostByID(postID);
        if (post) {
            return post->addComment(commentText, this);
        }
    }

    // Check liked pages' posts
    for (int i = 0; i < likedPageCount; i++) {
        Post** pageTimeline = likedPages[i]->getTimeline();
        int pagePostCount = likedPages[i]->getPostCount();

        for (int j = 0; j < pagePostCount; j++) {
            if (pageTimeline[j]->getUniqueID() == postID) {
                return pageTimeline[j]->addComment(commentText, this);
            }
        }
    }

    return false; // Post not found
}

// Finds a post by ID in the user's timeline
Post* User::findPostByID(const string& postID) const {
    for (int i = 0; i < postCount; i++) {
        if (timeline[i]->getUniqueID() == postID) {
            return timeline[i];
        }
    }
    return nullptr; // Post not found
}

// Shares a memory post
void User::shareMemory(const string& memoryID, const string& content, const Date& date, Post* originalPost) {
    Memory* memory = new Memory(memoryID, content, date, originalPost);
    addPost(memory);
}

// Displays the user's timeline
void User::displayTimeline() const {
    cout << "-------------------------------------------------------------------------------------------------------------" << endl;
    cout << name << " - Time Line" << endl;

    for (int i = 0; i < postCount; i++) {
        timeline[i]->displayPost();
    }

    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
}

// Displays the user's home page with recent posts
void User::displayHomePage(const Date& currentDate) const {
    cout << "-------------------------------------------------------------------------------------------------------------" << endl;
    cout << name << " - Home Page" << endl;

    // Display friends' posts from last 24 hours
    for (int i = 0; i < friendCount; i++) {
        Post** friendTimeline = friendsList[i]->getTimeline();
        int friendPostCount = friendsList[i]->getPostCount();

        for (int j = 0; j < friendPostCount; j++) {
            if (friendTimeline[j]->getSharedDate().isWithinLast24Hours(currentDate)) {
                cout << "--- " << friendsList[i]->getName() << " ";

                // If this post has an activity
                if (friendTimeline[j]->getActivity() != nullptr) {
                    cout << "is " << friendTimeline[j]->getActivity()->toString();
                } else {
                    cout << "shared";
                }

                cout << endl;
                cout << " \"" << friendTimeline[j]->getDescription() << "\"" << endl;

                // Display comments
                friendTimeline[j]->displayComments();
            }
        }
    }

    // Display liked pages' posts from last 24 hours
    for (int i = 0; i < likedPageCount; i++) {
        Post** pageTimeline = likedPages[i]->getTimeline();
        int pagePostCount = likedPages[i]->getPostCount();

        for (int j = 0; j < pagePostCount; j++) {
            if (pageTimeline[j]->getSharedDate().isWithinLast24Hours(currentDate)) {
                cout << "--- " << likedPages[i]->getTitle() << " ";

                // If this post has an activity
                if (pageTimeline[j]->getActivity() != nullptr) {
                    cout << "is " << pageTimeline[j]->getActivity()->toString();
                } else {
                    cout << "shared";
                }

                cout << endl;
                cout << " \"" << pageTimeline[j]->getDescription() << "\"" << endl;

                // Display comments
                pageTimeline[j]->displayComments();
            }
        }
    }

    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
}

// Shows memories from past years on same day
void User::seeMemories(const Date& currentDate) const {
    cout << "We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those" << endl;
    cout << "long ago." << endl;
    cout << "On this Day" << endl;

    bool foundMemory = false;

    // Check for posts from same day in previous years
    for (int i = 0; i < postCount; i++) {
        Date postDate = timeline[i]->getSharedDate();

        // Check if post is from the same day and month but different year
        if (postDate.getDay() == currentDate.getDay() &&
            postDate.getMonth() == currentDate.getMonth() &&
            postDate.getYear() < currentDate.getYear()) {

            int yearsAgo = currentDate.getYear() - postDate.getYear();

            cout << yearsAgo << " Years Ago" << endl;
            timeline[i]->displayPost();

            foundMemory = true;
        }
    }

    if (!foundMemory) {
        cout << "No memories found for today." << endl;
    }

    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
}
