#include "LibraryManager.h"
#include <iostream>

LibraryManager::LibraryManager() = default;

void LibraryManager::addClient(const std::string& name, const std::string& firstname, const std::string& age, const std::string& address, const std::string& phoneNumber, const std::string& mail, std::string& outputMsg) {
    std::string fullName = name + " " + firstname;
    clients[fullName] = Client(name, firstname, age, address, phoneNumber, mail);
    outputMsg = "Added client: " + fullName + "\n";
}

void LibraryManager::listClients(std::string& outputMsg) {
    if (clients.empty()) {
        outputMsg = "No client found.\n";
    }
    else {
        for (const auto& [fullName, client] : clients) {
            outputMsg += fullName + " (" + client.age + ", " + client.address + ", " + client.phoneNumber + ", " + client.mail + ")\n";
            outputMsg += "Rent :\n" + client.getBorrowedMedia();
        }
    }
}

void LibraryManager::removeClientByName(const std::string& name, std::string& outputMsg) {
    std::string fullName = name;
    if (clients.erase(fullName)) {
        outputMsg = "Remove client : " + fullName + "\n";
    }
    else {
        outputMsg = "Error : client not found.\n";
    }
}

void LibraryManager::removeClientByNameAndFirstname(const std::string& name, const std::string& firstname, std::string& outputMsg) {
    std::string fullName = name + " " + firstname;
    if (clients.erase(fullName)) {
        outputMsg = "Removed client : " + fullName + "\n";
    }
    else {
        outputMsg = "Error : client not found.\n";
    }
}

void LibraryManager::removeClientByMail(const std::string& mail, std::string& outputMsg) {
    bool found = false;
    for (auto it = clients.begin(); it != clients.end(); ) {
        if (it->second.mail == mail) {
            it = clients.erase(it);
            found = true;
        }
        else {
            ++it;
        }
    }
    if (found) {
        outputMsg = "Removed client : " + mail + "\n";
    }
    else {
        outputMsg = "Error : client not found.\n";
    }
}

void LibraryManager::addBook(const std::string& title, const std::string& author, const std::string& isbn, const std::string& ageLimit, std::string& outputMsg) {
    mediaCollection[title] = std::make_shared<Book>(title, author, isbn, ageLimit);
    outputMsg = "Added book : " + title + "\n";
}

void LibraryManager::listBooks(std::string& outputMsg) {
    for (const auto& [title, media] : mediaCollection) {
        if (dynamic_cast<Book*>(media.get()) != nullptr) {
            outputMsg += "Book : " + title + " (ISBN: " + static_cast<Book*>(media.get())->getISBN() + ", Rent : " + (media->isBorrowed() ? "Yes" : "No") + ")\n";
        }
    }
}

void LibraryManager::removeBook(const std::string& title, std::string& outputMsg) {
    if (mediaCollection.find(title) != mediaCollection.end() && dynamic_cast<Book*>(mediaCollection[title].get()) != nullptr) {
        mediaCollection.erase(title);
        outputMsg = "Removed book : " + title + "\n";
    }
    else {
        outputMsg = "Error : book not found.\n";
    }
}

void LibraryManager::addMovie(const std::string& title, const std::string& support, const std::string& ageLimit, std::string& outputMsg) {
    mediaCollection[title] = std::make_shared<Movie>(title, support, ageLimit);
    outputMsg = "Added movie : " + title + "\n";
}

void LibraryManager::listMovies(std::string& outputMsg) {
    for (const auto& [title, media] : mediaCollection) {
        if (dynamic_cast<Movie*>(media.get()) != nullptr) {
            outputMsg += "Movie : " + title + " (Support: " + static_cast<Movie*>(media.get())->getSupport() + ", Age Limitation: " + static_cast<Movie*>(media.get())->getAgeLimit() + ", Rent : " + (media->isBorrowed() ? "Yes" : "No") + ")\n";
        }
    }
}

void LibraryManager::removeMovie(const std::string& title, std::string& outputMsg) {
    if (mediaCollection.find(title) != mediaCollection.end() && dynamic_cast<Movie*>(mediaCollection[title].get()) != nullptr) {
        mediaCollection.erase(title);
        outputMsg = "Removed movie : " + title + "\n";
    }
    else {
        outputMsg = "Error : movie not found.\n";
    }
}

void LibraryManager::addVideoGames(const std::string& title, const std::string& studio, const std::string& pegi, const std::string& genre, std::string& outputMsg) {
    mediaCollection[title] = std::make_shared<VideoGames>(title, studio, pegi, genre);
    outputMsg = "Added video game : " + title + "\n";
}

void LibraryManager::listVideoGames(std::string& outputMsg) {
    for (const auto& [title, media] : mediaCollection) {
        if (dynamic_cast<VideoGames*>(media.get()) != nullptr) {
            outputMsg += "Video games : " + title + " (Company : " + static_cast<VideoGames*>(media.get())->getStudio() + ", PEGI: " + static_cast<VideoGames*>(media.get())->getPegi() + ", Type : " + static_cast<VideoGames*>(media.get())->getGenre() + ", Rent : " + (media->isBorrowed() ? "Yes" : "No") + ")\n";
        }
    }
}

void LibraryManager::removeVideoGames(const std::string& title, std::string& outputMsg) {
    if (mediaCollection.find(title) != mediaCollection.end() && dynamic_cast<VideoGames*>(mediaCollection[title].get()) != nullptr) {
        mediaCollection.erase(title);
        outputMsg = "Removed video game: " + title + "\n";
    }
    else {
        outputMsg = "Error: video game not found.\n";
    }
}

void LibraryManager::rentMedia(const std::string& clientName, const std::string& clientFirstname, const std::string& clientMail, const std::string& mediaTitle, std::string& outputMsg) {
    std::string fullName = clientName + " " + clientFirstname + " " + clientMail;
    if (clients.find(fullName) != clients.end() && mediaCollection.find(mediaTitle) != mediaCollection.end()) {
        auto media = mediaCollection[mediaTitle];
        if (media && !media->isBorrowed()) {
            clients[fullName].rentMedia(media);
            media->setBorrowed(true);
            outputMsg = "Rent media : " + mediaTitle + " by " + fullName + "\n";
        }
        else {
            outputMsg = "Error: media already borrowed.\n";
        }
    }
    else {
        outputMsg = "Error: client or media not found.\n";
    }
}

void LibraryManager::returnMedia(const std::string& clientName, const std::string& clientFirstname, const std::string& clientMail, const std::string& mediaTitle, std::string& outputMsg) {
    std::string fullName = clientName + " " + clientFirstname + " " + clientMail;
    if (clients.find(fullName) != clients.end()) {
        auto& client = clients[fullName];
        for (auto it = client.getBorrowedMediaList().begin(); it != client.getBorrowedMediaList().end(); ++it) {
            if ((*it)->getTitle() == mediaTitle) {
                (*it)->setBorrowed(false);
                if (mediaCollection.find(mediaTitle) != mediaCollection.end()) {
                    mediaCollection[mediaTitle]->setBorrowed(false);
                }
                client.getBorrowedMediaList().erase(it);
                outputMsg = "Return media : " + mediaTitle + " by " + fullName + "\n";
                return;
            }
        }
        outputMsg = "Error: media not found.\n";
    }
    else {
        outputMsg = "Error: client not found.\n";
    }
}

void LibraryManager::listAllMedia(std::string& outputMsg) {
    for (const auto& [title, media] : mediaCollection) {
        if (dynamic_cast<Book*>(media.get()) != nullptr) {
            outputMsg += "Book : " + title + " (ISBN: " + static_cast<Book*>(media.get())->getISBN() + ", Rent : " + (media->isBorrowed() ? "Yes" : "No") + ")\n";
        }
        else if (dynamic_cast<Movie*>(media.get()) != nullptr) {
            outputMsg += "Movie : " + title + " (Support: " + static_cast<Movie*>(media.get())->getSupport() + ", Age limitation : " + static_cast<Movie*>(media.get())->getAgeLimit() + ", Rent : " + (media->isBorrowed() ? "Yes" : "No") + ")\n";
        }
        else if (dynamic_cast<VideoGames*>(media.get()) != nullptr) {
            outputMsg += "Video games : " + title + " (Company : " + static_cast<VideoGames*>(media.get())->getStudio() + ", PEGI: " + static_cast<VideoGames*>(media.get())->getPegi() + ", Type : " + static_cast<VideoGames*>(media.get())->getGenre() + ", Rent : " + (media->isBorrowed() ? "Yes" : "No") + ")\n";
        }
    }
}

void LibraryManager::executeCommand(const std::string& command) {
    std::string outputMsg;
    interpreterbuilder.addCommand(command, outputMsg, this);
    interpreterbuilder.executeAndPopCommand(); 
}

