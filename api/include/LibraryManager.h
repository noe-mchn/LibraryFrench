#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <string>
#include <map>
#include "Client.h"
#include "InterpreterBuilder.h"
#include "Book.h"
#include "Movie.h"
#include "VideoGames.h"

class LibraryManager {
public:
    LibraryManager();

    void addClient(const std::string& name, const std::string& firstname, const std::string& age, const std::string& address, const std::string& phoneNumber, const std::string& mail, std::string& outputMsg);
    void listClients(std::string& outputMsg);
    void removeClientByName(const std::string& name, std::string& outputMsg);
    void removeClientByNameAndFirstname(const std::string& name, const std::string& firstname, std::string& outputMsg);
    void removeClientByMail(const std::string& mail, std::string& outputMsg);

    void addBook(const std::string& title, const std::string& author, const std::string& isbn, const std::string& ageLimit, std::string& outputMsg);
    void listBooks(std::string& outputMsg);
    void removeBook(const std::string& title, std::string& outputMsg);

    void addMovie(const std::string& title, const std::string& support, const std::string& ageLimit, std::string& outputMsg);
    void listMovies(std::string& outputMsg);
    void removeMovie(const std::string& title, std::string& outputMsg);

    void addVideoGames(const std::string& title, const std::string& developer, const std::string& releaseDate, const std::string& genre, std::string& outputMsg);
    void listVideoGames(std::string& outputMsg);
    void removeVideoGames(const std::string& title, std::string& outputMsg);

    void rentMedia(const std::string& clientName, const std::string& clientFirstname, const std::string& clientMail, const std::string& mediaTitle, std::string& outputMsg);
    void returnMedia(const std::string& clientName, const std::string& clientFirstname, const std::string& clientMail, const std::string& mediaTitle, std::string& outputMsg);


    void listAllMedia(std::string& outputMsg);

    void executeCommand(const std::string& command);

private:
    std::map<std::string, Client> clients;
    std::map<std::string, std::shared_ptr<Media>> mediaCollection;

    InterpreterBuilder interpreterbuilder;
};

#endif // LIBRARYMANAGER_H
