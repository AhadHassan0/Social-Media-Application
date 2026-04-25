#ifndef PAGE_H
#define PAGE_H

#include "forwarddeclarations.h"
#include <string>
#include "post.h"
using namespace std;

class Page {
private:
    string uniqueID;   // Unique identifier for page
    string title;      // Title/name of the page
    User* owner;       // User who owns this page
    Post** timeline;   // Array of posts shared by page
    int postCount;     // Number of posts in timeline
    User** likedBy;    // Array of users who liked this page
    int likeCount;     // Number of users who liked

public:
    // Constructors and destructor
    Page();                                            // Default constructor
    Page(const string& id, const string& title, User* owner); // Parameterized constructor
    ~Page();                                           // Destructor

    // Getters
    string getUniqueID() const;                        // Returns page ID
    string getTitle() const;                           // Returns page title
    User* getOwner() const;                            // Returns page owner
    int getLikeCount() const;                          // Returns number of likes
    Post** getTimeline() const;                        // Returns page timeline
    int getPostCount() const;                          // Returns post count

    // Setters
    void setUniqueID(const string& id);                // Sets page ID
    void setTitle(const string& title);                // Sets page title
    void setOwner(User* owner);                        // Sets page owner

    // Like functionality
    bool addLikedBy(User* user);                       // Adds user to likes
    User** getLikedBy() const;                         // Returns users who liked
    bool isLikedBy(User* user) const;                  // Checks if liked by user

    // Post functionality
    bool addPost(Post* post);                          // Adds post to timeline
    void sharePost(const string& postID, const string& content, const Date& date); // Shares a post
    void sharePost(const string& postID, const string& content, const Date& date, Activity* activity); // Shares post with activity

    // Comment functionality
    bool commentOnPost(const string& postID, const string& commentText); // Comments on a post

    // View methods
    void displayPage() const;                          // Displays page info
    void displayTimeline() const;                      // Displays timeline
};

#endif // PAGE_H
