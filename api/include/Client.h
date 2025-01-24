#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include <memory>
#include "Media.h"

class Client {
public:
    Client() = default;
    Client(const std::string& name, const std::string& firstname, const std::string& age, const std::string& address, const std::string& phoneNumber, const std::string& mail);

    bool canBorrow() const;
    void rentMedia(std::shared_ptr<Media> media);
    void returnMedia(const std::string& title);
    std::string getBorrowedMedia() const;

    std::vector<std::shared_ptr<Media>>& getBorrowedMediaList();

    std::string name;
    std::string firstname;
    std::string age;
    std::string address;
    std::string phoneNumber;
    std::string mail;

private:
    std::vector<std::shared_ptr<Media>> borrowedMedia;
};

#endif // CLIENT_H