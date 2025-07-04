#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <iterator>
#include <type_traits>

namespace Softadastra {

    template <typename Container>
    void print(const Container& coll) {
        using std::begin;
        using std::end;

        static_assert(
            std::is_same<decltype(begin(coll)), decltype(end(coll))>::value,
            "Container must have matching begin() and end()"
        );

        auto it = begin(coll);
        auto itEnd = end(coll);

        if (it == itEnd) {
            std::cout << "Collection is empty\n";
            return;
        }

        std::cout << *it;
        ++it;
        for (; it != itEnd; ++it) {
            std::cout << ',' << *it;
        }
        std::cout << '\n';
    }

    enum class LogLevel {
        INFO,
        WARNING,
        ERROR
    };

    // Activer/desactiver les couleurs
    void enableColor(bool value);      
    // Activer/desactiver les fichiers de log
    void enableFileLogging(bool value); 
    void enableDailyLogRotation(bool value);

    std::string getCurrentTime();
    void log(LogLevel level, const std::string& message);
}

#endif // LOGGER_HPP


  