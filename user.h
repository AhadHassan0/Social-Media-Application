#ifndef USER_H
#define USER_H

#include "forwarddeclarations.h"
#include <string>
#include "post.h"
#include "page.h"
using namespace std;

class User {
private:
    string uniqueID;     // Unique identifier for user
    string name;         // Name of the user
    User** friendsList;  // Array of friends
    int friendCount;     // Number of friends
    Page** likedPages;   // Array of pages liked by user
    int likedPageCount;  // Number of liked pages
    Post** timeline;     // Array of posts shared by user
    int postCount;       // Number of posts

public:
    // Constructors and destructor
    User();                                      // Default constructor
    User(const string& id, const string& name);  // Parameterized constructor
    ~User();                                     // Destructor

    // Getters
    string getUniqueID() const;                  // Returns user ID
    string getName() const;                      // Returns user name
    User** getFriendsList() const;               // Returns friends list
    int getFriendCount() const;                  // Returns friend count
    Page** getLikedPages() const;                // Returns liked pages
    int getLikedPageCount() const;               // Returns liked page count
    Post** getTimeline() const;                  // Returns timeline
    int getPostCount() const;                    // Returns post count

    // Setters
    void setUniqueID(const string& id);          // Sets user ID
    void setName(const string& name);            // Sets user name

    // Friend functionality
    bool addFriend(User* friend_);               // Adds a friend
    bool isFriendsWith(User* user) const;        // Checks if friends with user
    void displayFriendsList() const;             // Displays friends list

    // Page functionality
    bool likePage(Page* page);                   // Likes a page
    bool isLikedPage(Page* page) const;          // Checks if liked a page
    void displayLikedPages() const;              // Displays liked pages

    // Post functionality
    bool addPost(Post* post);                    // Adds post to timeline
    void sharePost(const string& postID, const string& content, const Date& date); // Shares a post
    void sharePost(const string& postID, const string& content, const Date& date, Activity* activity); // Shares post with activity
    bool likePost(Post* post);                   // Likes a post
    bool commentOnPost(const string& postID, const string& commentText); // Comments on a post
    Post* findPostByID(const string& postID) const; // Finds post by ID
    void shareMemory(const string& memoryID, const string& content, const Date& date, Post* originalPost); // Shares a memory

    // View methods
    void displayTimeline() const;                // Displays user timeline
    void displayHomePage(const Date& currentDate) const; // Displays home page
    void seeMemories(const Date& currentDate) const; // Shows memories
};

#endif // USER_H
