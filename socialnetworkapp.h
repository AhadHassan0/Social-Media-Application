#ifndef SOCIALNETWORKAPP_H
#define SOCIALNETWORKAPP_H

#include <QObject>
#include <string>
#include "user.h"
#include "page.h"
#include "post.h"
#include "date.h"
using namespace std;

class SocialNetworkApp : public QObject {
    Q_OBJECT

private:
    Date currentDate;       // Current system date
    User* currentUser;      // Currently logged-in user

    User** users;           // Array of all users in the system
    int userCount;          // Number of users
    int maxUsers;           // Maximum number of users

    Page** pages;           // Array of all pages in the system
    int pageCount;          // Number of pages
    int maxPages;           // Maximum number of pages

    int postIDCounter;      // Counter for generating unique post IDs

    // Helper methods
    User* findUser(const string& userID);  // Finds user by ID
    Page* findPage(const string& pageID);  // Finds page by ID
    Post* findPost(const string& postID);  // Finds post by ID

    // File I/O methods
    void loadUsersFromFile(const string& filename);  // Loads users from file
    void loadPagesFromFile(const string& filename);  // Loads pages from file
    void saveUsersToFile(const string& filename);    // Saves users to file
    void savePagesToFile(const string& filename);    // Saves pages to file

signals:
    // Signals for UI updates
    void outputGenerated(const QString& output);  // Signal for output text
    void currentUserChanged(const QString& userName);  // Signal for user change

public slots:
    // Slots for UI actions
    void onSetCurrentUserClicked(const QString& userID);  // Set current user
    void onSetCurrentDateClicked(int day, int month, int year);  // Set current date
    void onViewHomeClicked();  // View home page
    void onLikePostClicked(const QString& postID);  // Like a post
    void onViewLikedListClicked(const QString& postID);  // View liked users
    void onCommentOnPostClicked(const QString& postID, const QString& comment);  // Comment on post
    void onViewPostClicked(const QString& postID);  // View a post
    void onShareMemoryClicked(const QString& postID, const QString& text);  // Share a memory
    void onViewProfileClicked();  // View user profile
    void onViewFriendListClicked();  // View friends list
    void onViewPageClicked(const QString& pageID);  // View a page
    void onSeeYourMemoriesClicked();  // See memories
    void onViewLikedPagesClicked(); // View liked pages

public:
    explicit SocialNetworkApp(QObject *parent = nullptr);  // Constructor
    ~SocialNetworkApp();  // Destructor

    void Run();  // Main initialization method

    // Required functionality - these methods will call the appropriate UI update signals
    void setCurrentUser(const string& userID);  // Sets current user
    void setCurrentDate(int day, int month, int year);  // Sets current date
    void viewHome();  // Views home page
    void likePost(const string& postID);  // Likes a post
    void viewLikedList(const string& postID);  // Views users who liked a post
    void commentOnPost(const string& postID, const string& comment);  // Comments on a post
    void viewPost(const string& postID);  // Views a post
    void shareMemory(const string& postID, const string& text);  // Shares a memory
    void viewProfile();  // Views current user's profile
    void viewFriendList();  // Views current user's friend list
    void viewPage(const string& pageID);  // Views a page
    void seeYourMemories();  // Shows memories for current user
    void viewLikedPages(); // Views current user's liked pages

    // Additional helper methods
    void initializeSampleData();  // Initializes sample data for testing
    string generateUniquePostID();  // Generates a unique post ID
};

#endif // SOCIALNETWORKAPP_H
