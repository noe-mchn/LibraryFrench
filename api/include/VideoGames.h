#ifndef VIDEOGAMEs_H
#define VIDEOGAMEs_H

#include "Media.h"

class VideoGames : public Media {
public:
    VideoGames(const std::string& title, const std::string& studio, const std::string& pegi, const std::string& genre);

    std::string getStudio() const;
    std::string getPegi() const;
    std::string getGenre() const;

private:
    std::string studio;
    std::string pegi;
    std::string genre;
};

#endif // VIDEOGAMEs_H