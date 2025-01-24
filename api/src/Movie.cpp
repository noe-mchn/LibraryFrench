#include "Movie.h"

Movie::Movie(const std::string& title, const std::string& support, const std::string& ageLimit)
    : Media(title, ""), support(support), ageLimit(ageLimit) {}

std::string Movie::getSupport() const {
    return support;
}

std::string Movie::getAgeLimit() const {
    return ageLimit;
}