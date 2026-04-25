#include "memory.h"
#include <iostream>
using namespace std;

// Default constructor
Memory::Memory() : Post(), originalPost(nullptr) {
}

// Parameterized constructor
Memory::Memory(const string& id, const string& desc, const Date& date, Post* original) :
    Post(id, desc, date), originalPost(original) {
}

// Destructor
Memory::~Memory() {
    // Don't delete originalPost as it's owned elsewhere
}

// Returns the original post this memory refers to
Post* Memory::getOriginalPost() const {
    return originalPost;
}

// Sets the original post this memory refers to
void Memory::setOriginalPost(Post* post) {
    originalPost = post;
}

// Displays memory post with original post
void Memory::displayPost() const {
    cout << "~~~ Memory Shared ~~~ ...(" << getSharedDate().toString() << ")" << endl;
    cout << " \"" << getDescription() << "\"" << endl;

    if (originalPost) {
        int yearsAgo = getSharedDate().getYear() - originalPost->getSharedDate().getYear();
        cout << " (" << yearsAgo << " Years Ago)" << endl;
        originalPost->displayPost();
    } else {
        cout << " (Original post not available)" << endl;
    }

    // Display comments if any
    displayComments();
}
