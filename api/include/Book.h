#ifndef BOOK_H
#define BOOK_H

#include "Media.h"

class Book : public Media {
public:
    Book(const std::string& title, const std::string& author, const std::string& isbn, const std::string& ageLimit);
    std::string getISBN() const;
	std::string getAuthor() const;
	std::string getAgeLimit() const;

private:
    std::string isbn;
    std::string author;
	std::string ageLimit;
};

#endif // BOOK_H