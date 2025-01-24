#include "Media.h"

Media::Media(const std::string& title, const std::string& ageLimit)
    : title(title), ageLimit(ageLimit), borrowed(false) {}

std::string Media::getTitle() const {
    return title;
}

std::string Media::getAgeLimit() const {
    return ageLimit;
}

bool Media::isBorrowed() const {
    return borrowed;
}

void Media::setBorrowed(bool borrowed) {
    this->borrowed = borrowed;
}