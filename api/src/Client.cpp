#include "Client.h"
#include <sstream>

Client::Client(const std::string& name, const std::string& firstname, const std::string& age, const std::string& address, const std::string& phoneNumber, const std::string& mail)
    : name(name), firstname(firstname), age(age), address(address), phoneNumber(phoneNumber), mail(mail) {}

bool Client::canBorrow() const {
    return borrowedMedia.size() < 5;
}

void Client::rentMedia(std::shared_ptr<Media> media) {
    if (canBorrow()) {
        borrowedMedia.push_back(media);
        media->setBorrowed(true);
    }
}

void Client::returnMedia(const std::string& title) {
    for (auto it = borrowedMedia.begin(); it != borrowedMedia.end(); ++it) {
        if ((*it)->getTitle() == title) {
            (*it)->setBorrowed(false);
            borrowedMedia.erase(it);
            return;
        }
    }
}

std::string Client::getBorrowedMedia() const {
    std::ostringstream oss;
    for (const auto& media : borrowedMedia) {
        oss << media->getTitle() << "\n";
    }
    return oss.str();
}

// Implémentation de la méthode getBorrowedMediaList
std::vector<std::shared_ptr<Media>>& Client::getBorrowedMediaList() {
    return borrowedMedia;
}