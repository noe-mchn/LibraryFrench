#ifndef MOVIE_H
#define MOVIE_H

#include "Media.h"

class Movie : public Media {
public:
    Movie(const std::string& title, const std::string& support, const std::string& ageLimit);

    std::string getSupport() const;
    std::string getAgeLimit() const;

private:
    std::string support;
    std::string ageLimit;
};

#endif // MOVIE_H