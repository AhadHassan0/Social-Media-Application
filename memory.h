#ifndef MEMORY_H
#define MEMORY_H

#include "post.h"
using namespace std;

class Memory : public Post {
private:
    Post* originalPost;  // Pointer to the original post this memory refers to

public:
    // Constructors and destructor
    Memory();                                                       // Default constructor
    Memory(const string& id, const string& desc, const Date& date, Post* original); // Parameterized constructor
    ~Memory();                                                      // Destructor

    // Getters
    Post* getOriginalPost() const;                                  // Returns the original post

    // Setters
    void setOriginalPost(Post* post);                               // Sets the original post

    // Display method override
    void displayPost() const override;                              // Displays memory with original post
};

#endif // MEMORY_H
