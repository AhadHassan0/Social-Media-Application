#include "socialnetworkapp.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <QDebug>
using namespace std;

// Constructor
SocialNetworkApp::SocialNetworkApp(QObject *parent) :
    QObject(parent),
    currentUser(nullptr),
    users(nullptr),
    userCount(0),
    maxUsers(100),
    pages(nullptr),
    pageCount(0),
    maxPages(100),
    postIDCounter(1) {

    // Initialize arrays
    users = new User*[maxUsers];
    pages = new Page*[maxPages];

    // Set default date
    currentDate.setDate(15, 11, 2017);
}

// Destructor
SocialNetworkApp::~SocialNetworkApp() {
    // Delete all users
    for (int i = 0; i < userCount; i++) {
        delete users[i];
    }
    delete[] users;

    // Delete all pages
    for (int i = 0; i < pageCount; i++) {
        delete pages[i];
    }
    delete[] pages;

    // Note: Posts are owned by users and pages, so they will be deleted there
}

// Main initialization method
void SocialNetworkApp::Run() {
    // Try to load data from files first
    try {
        loadUsersFromFile("users.txt");
        loadPagesFromFile("pages.txt");
    } catch (...) {
        // If loading fails, initialize sample data
        initializeSampleData();
    }

    // The main UI interaction will happen through slots connected to the UI
}

// Finds a user by ID
User* SocialNetworkApp::findUser(const string& userID) {
    for (int i = 0; i < userCount; i++) {
        if (users[i]->getUniqueID() == userID) {
            return users[i];
        }
    }
    return nullptr;
}

// Finds a page by ID
Page* SocialNetworkApp::findPage(const string& pageID) {
    for (int i = 0; i < pageCount; i++) {
        if (pages[i]->getUniqueID() == pageID) {
            return pages[i];
        }
    }
    return nullptr;
}

// Finds a post by ID
Post* SocialNetworkApp::findPost(const string& postID) {
    // Check all users' posts
    for (int i = 0; i < userCount; i++) {
        Post* post = users[i]->findPostByID(postID);
        if (post) return post;
    }

    // Check all pages' posts
    for (int i = 0; i < pageCount; i++) {
        Post** timeline = pages[i]->getTimeline();
        int postCount = pages[i]->getPostCount();

        for (int j = 0; j < postCount; j++) {
            if (timeline[j]->getUniqueID() == postID) {
                return timeline[j];
            }
        }
    }

    return nullptr;
}

// Sets current user
void SocialNetworkApp::setCurrentUser(const string& userID) {
    User* user = findUser(userID);

    stringstream output;
    if (user) {
        currentUser = user;
        output << user->getName() << " successfully set as Current User";
        emit currentUserChanged(QString::fromStdString(user->getName()));
    } else {
        output << "User with ID " << userID << " not found.";
    }

    emit outputGenerated(QString::fromStdString(output.str()));
}

// Sets current date
void SocialNetworkApp::setCurrentDate(int day, int month, int year) {
    currentDate.setDate(day, month, year);

    stringstream output;
    output << "System Date: " << currentDate.toString();
    emit outputGenerated(QString::fromStdString(output.str()));
}

// Views home page for current user
void SocialNetworkApp::viewHome() {
    stringstream output;

    if (currentUser) {
        // Redirect cout to our stringstream to capture output
        streambuf* oldCoutBuffer = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        currentUser->displayHomePage(currentDate);

        // Restore cout
        cout.rdbuf(oldCoutBuffer);
    } else {
        output << "No user is currently set.";
    }

    emit outputGenerated(QString::fromStdString(output.str()));
}

// Likes a post
void SocialNetworkApp::likePost(const string& postID) {
    stringstream output;

    if (!currentUser) {
        output << "No user is currently set.";
        emit outputGenerated(QString::fromStdString(output.str()));
        return;
    }

    Post* post = findPost(postID);

    if (post) {
        if (post->addLike(currentUser)) {
            output << "Post liked successfully.";
        } else {
            output << "Failed to like post. You may have already liked it or it has reached maximum likes.";
        }
    } else {
        output << "Post with ID " << postID << " not found.";
    }

    emit outputGenerated(QString::fromStdString(output.str()));
}

// Views users who liked a post
void SocialNetworkApp::viewLikedList(const string& postID) {
    stringstream output;

    Post* post = findPost(postID);

    if (post) {
        // Redirect cout to our stringstream to capture output
        streambuf* oldCoutBuffer = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        post->displayLikedBy();

        // Restore cout
        cout.rdbuf(oldCoutBuffer);
    } else {
        output << "Post with ID " << postID << " not found.";
    }

    emit outputGenerated(QString::fromStdString(output.str()));
}

// Comments on a post
void SocialNetworkApp::commentOnPost(const string& postID, const string& comment) {
    stringstream output;

    if (!currentUser) {
        output << "No user is currently set.";
        emit outputGenerated(QString::fromStdString(output.str()));
        return;
    }

    if (currentUser->commentOnPost(postID, comment)) {
        output << "Comment added successfully.";
    } else {
        output << "Failed to add comment. Post with ID " << postID << " not found or maximum comments reached.";
    }

    emit outputGenerated(QString::fromStdString(output.str()));
}

// Views a post
void SocialNetworkApp::viewPost(const string& postID) {
    stringstream output;

    Post* post = findPost(postID);

    if (post) {
        // Redirect cout to our stringstream to capture output
        streambuf* oldCoutBuffer = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        post->displayPost();

        // Restore cout
        cout.rdbuf(oldCoutBuffer);
    } else {
        output << "Post with ID " << postID << " not found.";
    }

    emit outputGenerated(QString::fromStdString(output.str()));
}

// Shares a memory
void SocialNetworkApp::shareMemory(const string& postID, const string& text) {
    stringstream output;

    if (!currentUser) {
        output << "No user is currently set.";
        emit outputGenerated(QString::fromStdString(output.str()));
        return;
    }

    Post* original = findPost(postID);

    if (original) {
        currentUser->shareMemory(generateUniquePostID(), text, currentDate, original);
        output << "Memory shared successfully.";
    } else {
        output << "Post with ID " << postID << " not found.";
    }

    emit outputGenerated(QString::fromStdString(output.str()));
}

// Views current user's profile
void SocialNetworkApp::viewProfile() {
    stringstream output;

    if (currentUser) {
        // Redirect cout to our stringstream to capture output
        streambuf* oldCoutBuffer = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        currentUser->displayTimeline();

        // Restore cout
        cout.rdbuf(oldCoutBuffer);
    } else {
        output << "No user is currently set.";
    }

    emit outputGenerated(QString::fromStdString(output.str()));
}

// Views current user's friend list
void SocialNetworkApp::viewFriendList() {
    stringstream output;

    if (currentUser) {
        // Redirect cout to our stringstream to capture output
        streambuf* oldCoutBuffer = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        currentUser->displayFriendsList();

        // Restore cout
        cout.rdbuf(oldCoutBuffer);
    } else {
        output << "No user is currently set.";
    }

    emit outputGenerated(QString::fromStdString(output.str()));
}

// Views a page
void SocialNetworkApp::viewPage(const string& pageID) {
    stringstream output;

    Page* page = findPage(pageID);

    if (page) {
        // Redirect cout to our stringstream to capture output
        streambuf* oldCoutBuffer = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        page->displayPage();

        // Restore cout
        cout.rdbuf(oldCoutBuffer);
    } else {
        output << "Page with ID " << pageID << " not found.";
    }

    emit outputGenerated(QString::fromStdString(output.str()));
}

// Shows memories for current user
void SocialNetworkApp::seeYourMemories() {
    stringstream output;

    if (currentUser) {
        // Redirect cout to our stringstream to capture output
        streambuf* oldCoutBuffer = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        currentUser->seeMemories(currentDate);

        // Restore cout
        cout.rdbuf(oldCoutBuffer);
    } else {
        output << "No user is currently set.";
    }

    emit outputGenerated(QString::fromStdString(output.str()));
}

// Loads users from file
void SocialNetworkApp::loadUsersFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Failed to open file: " + filename);
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name;

        getline(ss, id, ',');
        getline(ss, name);

        User* user = new User(id, name);
        users[userCount++] = user;
    }

    file.close();
}

// Loads pages from file
void SocialNetworkApp::loadPagesFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Failed to open file: " + filename);
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, title, ownerID;

        getline(ss, id, ',');
        getline(ss, title, ',');
        getline(ss, ownerID);

        User* owner = findUser(ownerID);
        Page* page = new Page(id, title, owner);
        pages[pageCount++] = page;
    }

    file.close();
}

// Saves users to file
void SocialNetworkApp::saveUsersToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Failed to open file for writing: " + filename);
    }

    for (int i = 0; i < userCount; i++) {
        file << users[i]->getUniqueID() << "," << users[i]->getName() << endl;
    }

    file.close();
}

// Continuing socialnetworkapp.cpp from where it left off

// Saves pages to file
void SocialNetworkApp::savePagesToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Failed to open file for writing: " + filename);
    }

    for (int i = 0; i < pageCount; i++) {
        User* owner = pages[i]->getOwner();
        file << pages[i]->getUniqueID() << "," << pages[i]->getTitle() << ","
             << (owner ? owner->getUniqueID() : "") << endl;
    }

    file.close();
}

// Generates a unique post ID
string SocialNetworkApp::generateUniquePostID() {
    return "post" + to_string(postIDCounter++);
}

// Initialize sample data for testing
void SocialNetworkApp::initializeSampleData() {
    // Create users
    User* u2 = new User("u2", "Amna Akram");
    User* u3 = new User("u3", "Waheed Khan");
    User* u4 = new User("u4", "Burhan Tahir");
    User* u7 = new User("u7", "Abdullah Nadeem");
    User* u11 = new User("u11", "Ahsan Ali");
    User* u12 = new User("u12", "Ali Ahmed");

    // Add to users array
    users[userCount++] = u2;
    users[userCount++] = u3;
    users[userCount++] = u4;
    users[userCount++] = u7;
    users[userCount++] = u11;
    users[userCount++] = u12;

    // Create pages
    Page* p1 = new Page("p1", "Food Fusion", u7);
    Page* p2 = new Page("p2", "Al Jazeera English", u7);
    Page* p5 = new Page("p5", "Rumi Quotes", u7);
    Page* p9 = new Page("p9", "BBC News", u7);

    // Add to pages array
    pages[pageCount++] = p1;
    pages[pageCount++] = p2;
    pages[pageCount++] = p5;
    pages[pageCount++] = p9;

    // Setup friendships
    u7->addFriend(u3);
    u7->addFriend(u11);
    u7->addFriend(u12);

    u3->addFriend(u7);
    u11->addFriend(u7);
    u12->addFriend(u7);

    // Setup page likes
    u7->likePage(p1);
    u7->likePage(p2);
    u7->likePage(p5);
    u7->likePage(p9);

    // Create some posts

    // Waheed's post
    Date nov15(15, 11, 2017);
    Activity* activity1 = new Activity(1, "excited");
    u3->sharePost("post1", "OOP Project Started Yayy...", nov15, activity1);
    Post* post1 = u3->findPostByID("post1");
    post1->addComment("Best of Luck", u2);
    post1->addComment("Interesting", u7);

    // Ahsan's post
    u11->sharePost("post2", "Waiting for Weekend", nov15);
    Post* post2 = u11->findPostByID("post2");
    post2->addComment("Any plans for Get Together?", u4);
    post2->addComment("Yes BBQ", u7);
    post2->addComment("Lunch Buffet please", u2);

    // Ali's post
    u12->sharePost("post3", "Waiting for Result", nov15);

    // Food Fusion post
    Activity* activity2 = new Activity(3, "Kashmiri Chai (Pink Tea)");
    p1->sharePost("post4", "Try this at home...", nov15, activity2);
    Post* post4 = p1->getTimeline()[0];
    post4->addComment("Followers please try this recipe and give your feedback", p1);
    post4->addComment("Yummy", u2);
    post4->addComment("One pink tea for me", u11);

    // Al Jazeera post
    p2->sharePost("post5", "Oil drilling in Alaska's indigenous communities is on the table again.", nov15);
    Post* post5 = p2->getTimeline()[0];
    post5->addLike(u2);
    post5->addLike(u3);
    post5->addLike(u4);

    // Rumi Quotes post
    p5->sharePost("post6", "Be free of possessing things - Rumi", nov15);
    Post* post6 = p5->getTimeline()[0];
    post6->addComment("Rumi sucks at poetry ", u12);

    // Abdullah's posts
    Date nov14(14, 11, 2017);
    Activity* activity3 = new Activity(4, "a birthday");
    u7->sharePost("post8", "Happy Birthday to my dear Mom", nov14, activity3);
    Post* post8 = u7->findPostByID("post8");
    post8->addComment("Happy Birthday Aunty", u3);

    Date oct14(14, 10, 2017);
    Activity* activity4 = new Activity(4, "a birthday");
    u7->sharePost("post9", "Happy Birthday to my dear Father", oct14, activity4);
    Post* post9 = u7->findPostByID("post9");
    post9->addComment("Happy Birthday Uncle", u11);

    Date nov15_2015(15, 11, 2015);
    Activity* activity5 = new Activity(4, "Success");
    u7->sharePost("post10", "Got D in toughest subject... Thanks God I am Pass finally...", nov15_2015, activity5);
    Post* post10 = u7->findPostByID("post10");
    post10->addComment("Celebrations???", u11);

    // Food Fusion another post
    Date nov10(10, 11, 2017);
    Activity* activity6 = new Activity(3, "Halwa Puri");
    p1->sharePost("post11", "Sunday Special Breakfast for our followers...", nov10, activity6);

    // Increment post ID counter
    postIDCounter = 12;
}
// Views current user's liked pages
  void SocialNetworkApp::viewLikedPages() {
    stringstream output;

    if (currentUser) {
        // Redirect cout to our stringstream to capture output
        streambuf* oldCoutBuffer = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        currentUser->displayLikedPages();

        // Restore cout
        cout.rdbuf(oldCoutBuffer);
    } else {
        output << "No user is currently set.";
    }

    emit outputGenerated(QString::fromStdString(output.str()));
  }
  // Slot to handle view liked pages action
  void SocialNetworkApp::onViewLikedPagesClicked() {
      viewLikedPages();
  }
// Slot to handle set current user action
void SocialNetworkApp::onSetCurrentUserClicked(const QString& userID) {
    setCurrentUser(userID.toStdString());
}

// Slot to handle set current date action
void SocialNetworkApp::onSetCurrentDateClicked(int day, int month, int year) {
    setCurrentDate(day, month, year);
}

// Slot to handle view home action
void SocialNetworkApp::onViewHomeClicked() {
    viewHome();
}

// Slot to handle like post action
void SocialNetworkApp::onLikePostClicked(const QString& postID) {
    likePost(postID.toStdString());
}

// Slot to handle view liked list action
void SocialNetworkApp::onViewLikedListClicked(const QString& postID) {
    viewLikedList(postID.toStdString());
}

// Slot to handle comment on post action
void SocialNetworkApp::onCommentOnPostClicked(const QString& postID, const QString& comment) {
    commentOnPost(postID.toStdString(), comment.toStdString());
}

// Slot to handle view post action
void SocialNetworkApp::onViewPostClicked(const QString& postID) {
    viewPost(postID.toStdString());
}

// Slot to handle share memory action
void SocialNetworkApp::onShareMemoryClicked(const QString& postID, const QString& text) {
    shareMemory(postID.toStdString(), text.toStdString());
}

// Slot to handle view profile action
void SocialNetworkApp::onViewProfileClicked() {
    viewProfile();
}

// Slot to handle view friend list action
void SocialNetworkApp::onViewFriendListClicked() {
    viewFriendList();
}

// Slot to handle view page action
void SocialNetworkApp::onViewPageClicked(const QString& pageID) {
    viewPage(pageID.toStdString());
}

// Slot to handle see your memories action
void SocialNetworkApp::onSeeYourMemoriesClicked() {
    seeYourMemories();
}
