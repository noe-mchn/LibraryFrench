#include "Console.h"
#include <sstream>

Console::Console() {
    consoleFramebuffer.initialize();
    registerCommands();
}

void Console::run() {
    std::string input;
    std::string outputMsg;

    consoleFramebuffer.println("Welcome to the French Media Library, to access the command, type help.\n", Color::Blue);

    while (true) {
        consoleFramebuffer.print("> ", Color::White);
        consoleFramebuffer.show();

        consoleFramebuffer.writeConsole();
        input = consoleFramebuffer.getLastCommand();

        if (input == "exit") break;

        outputMsg.clear();
        parseCommand(input, outputMsg);

        if (!outputMsg.empty()) {
            consoleFramebuffer.println(outputMsg, Color::Blue);
            consoleFramebuffer.show();
        }
    }
}

void Console::parseCommand(const std::string& input, std::string& outputMsg) {
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }

    if (tokens.empty()) return;

    auto it = commands.find(tokens[0]);
    if (it != commands.end()) {
        it->second(tokens, outputMsg);
    }
    else if (tokens[0] == "help") {
        listCommands(outputMsg); 
    }
    else {
        outputMsg = "Unknown command: " + tokens[0] + "\n";
    }
}


void Console::listCommands(std::string& outputMsg) {
    outputMsg = "\nAvailable commands, each information is enclosed in quotation marks :\n\n";
    for (const auto& cmd : commandDescriptions) {
        outputMsg += cmd.first + " : " + cmd.second + "\n \n";
    }
}

void Console::registerCommands() {
    commands["addClient"] = [this](const std::vector<std::string>& args, std::string& outputMsg) {
        if (args.size() != 7) {
            outputMsg = "How : addClient name firstname age address phoneNumber mail\n";
            return;
        }
        manager.addClient(args[1], args[2], args[3], args[4], args[5], args[6], outputMsg);
        };
    commandDescriptions["addClient"] = "Add a new client (Name, Firstname, age, adress, phone and mail).";


    commands["listClient"] = [this](const std::vector<std::string>& args, std::string& outputMsg) {
        manager.listClients(outputMsg);
        };
    commandDescriptions["listClient"] = "List all clients.";


    commands["removeClientByName"] = [this](const std::vector<std::string>& args, std::string& outputMsg) {
        if (args.size() != 2) {
            outputMsg = "How : removeClientByName name\n";
            return;
        }
        manager.removeClientByName(args[1], outputMsg);
        };
    commandDescriptions["removeClientByName"] = "Remove a client by name.";


    commands["removeClientByNameAndFirstname"] = [this](const std::vector<std::string>& args, std::string& outputMsg) {
        if (args.size() != 3) {
            outputMsg = "How : removeClientByNameAndFirstname name firstname\n";
            return;
        }
        manager.removeClientByNameAndFirstname(args[1], args[2], outputMsg);
        };
    commandDescriptions["removeClientByNameAndFirstname"] = "Remove a client by name and firstname.";


    commands["removeClientByMail"] = [this](const std::vector<std::string>& args, std::string& outputMsg) {
        if (args.size() != 2) {
            outputMsg = "How : removeClientByMail mail\n";
            return;
        }
        manager.removeClientByMail(args[1], outputMsg);
        };
    commandDescriptions["removeClientByMail"] = "Remove a client by a mail.";


    commands["addBook"] = [this](const std::vector<std::string>& args, std::string& outputMsg) {
        if (args.size() != 5) {
            outputMsg = "How : addBook title author isbn ageLimit\n";
            return;
        }
        manager.addBook(args[1], args[2], args[3], args[4], outputMsg);
        };
    commandDescriptions["addBook"] = "Add a book (Title, author, isbn, age limitation).";


    commands["listBook"] = [this](const std::vector<std::string>& args, std::string& outputMsg) {
        manager.listBooks(outputMsg);
        };
    commandDescriptions["listBook"] = "List all books.";


    commands["removeBook"] = [this](const std::vector<std::string>& args, std::string& outputMsg) {
        if (args.size() != 2) {
            outputMsg = "How : removeBook title\n";
            return;
        }
        manager.removeBook(args[1], outputMsg);
        };
    commandDescriptions["removeBook"] = "Remove a book by title.";


    commands["addMovie"] = [this](const std::vector<std::string>& args, std::string& outputMsg) {
        if (args.size() != 4) {
            outputMsg = "How : addMovie title support ageLimit\n";
            return;
        }
        manager.addMovie(args[1], args[2], args[3], outputMsg);
        };
    commandDescriptions["addMovie"] = "Add a movie (Title, support, age limitation).";


    commands["listMovie"] = [this](const std::vector<std::string>& args, std::string& outputMsg) {
        manager.listMovies(outputMsg);
        };
    commandDescriptions["listMovie"] = "List all movies.";


    commands["removeMovie"] = [this](const std::vector<std::string>& args, std::string& outputMsg) {
        if (args.size() != 2) {
            outputMsg = "How : removeMovie title\n";
            return;
        }
        manager.removeMovie(args[1], outputMsg);
        };
    commandDescriptions["removeMovie"] = "Remove a movie by title.";


    commands["addVideoGames"] = [this](const std::vector<std::string>& args, std::string& outputMsg) {
        if (args.size() != 5) {
            outputMsg = "How : addVideoGames title studio pegi type\n";
            return;
        }
        manager.addVideoGames(args[1], args[2], args[3], args[4], outputMsg);
        };
    commandDescriptions["addVideoGames"] = "Add a video game (Title, studio, pegi, type).";


    commands["listVideoGames"] = [this](const std::vector<std::string>& args, std::string& outputMsg) {
        manager.listVideoGames(outputMsg);
        };
    commandDescriptions["listVideoGames"] = "List all video games.";


    commands["removeVideoGames"] = [this](const std::vector<std::string>& args, std::string& outputMsg) {
        if (args.size() != 2) {
            outputMsg = "How : removeVideoGames title\n";
            return;
        }
        manager.removeVideoGames(args[1], outputMsg);
        };
    commandDescriptions["removeVideoGames"] = "Remove a video game by title.";


    commands["rentMedia"] = [this](const std::vector<std::string>& args, std::string& outputMsg) {
        if (args.size() != 5) {
            outputMsg = "How : rentMedia clientName clientFirstname clientMail mediaTitle\n";
            return;
        }
        manager.rentMedia(args[1], args[2], args[3], args[4], outputMsg);
        };
    commandDescriptions["rentMedia"] = "Rent a media (Name, firstname, mail, media title).";


    commands["returnMedia"] = [this](const std::vector<std::string>& args, std::string& outputMsg) {
        if (args.size() != 5) {
            outputMsg = "How : returnMedia clientName clientFirstname clientMail mediaTitle\n";
            return;
        }
        manager.returnMedia(args[1], args[2], args[3], args[4], outputMsg);
        };
    commandDescriptions["returnMedia"] = "Return a rent media (Name, firstname, mail, media title.";


    commands["listAllMedia"] = [this](const std::vector<std::string>& args, std::string& outputMsg) {
        manager.listAllMedia(outputMsg);
        };
    commandDescriptions["listAllMedia"] = "List all media.";
}