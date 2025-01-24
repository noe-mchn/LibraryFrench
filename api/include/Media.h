#ifndef MEDIA_H
#define MEDIA_H

#include <string>

class Media {
public:
    Media(const std::string& title, const std::string& ageLimit);

    virtual ~Media() = default;

    std::string getTitle() const;
    std::string getAgeLimit() const;
    bool isBorrowed() const;
    void setBorrowed(bool borrowed);

private:
    std::string title;
    std::string ageLimit;
    bool borrowed;
};

#endif // MEDIA_H
