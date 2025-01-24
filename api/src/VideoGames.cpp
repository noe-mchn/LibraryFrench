#include "VideoGames.h"

VideoGames::VideoGames(const std::string& title, const std::string& studio, const std::string& pegi, const std::string& genre)
    : Media(title,""), studio(studio), pegi(pegi), genre(genre) {}

std::string VideoGames::getStudio() const {
    return studio;
}

std::string VideoGames::getPegi() const {
    return pegi;
}

std::string VideoGames::getGenre() const {
    return genre;
}