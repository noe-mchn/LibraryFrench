#include "Book.h"

Book::Book(const std::string& title,  const std::string& author, const std::string& isbn, const std::string& ageLimit)
    : Media(title, ""), author(author), isbn(isbn), ageLimit(ageLimit) {}

std::string Book::getISBN() const {
    return isbn;
}

std::string Book::getAuthor() const {
	return author;
}

std::string Book::getAgeLimit() const {
	return ageLimit;
}