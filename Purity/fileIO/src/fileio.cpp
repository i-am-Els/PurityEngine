//
// Created by emman on 8/2/2024.
//

#include <fstream>
#include "fileio.h"
#include "log.h"

namespace purity::fileIO{

    /// @brief Extract Source code from file.
    /// @param path - The relative path to the file.
    /// @return A std::string contained in the file.
    /// @note Works with Absolute paths too.
    std::string PFileIO::extractSourceFromFile(const char *path) {
        // Open file with RAII; automatically closes when out of scope.
        std::ifstream file(path, std::ios::in);
        if (!file) {
            throw std::runtime_error(exceptions::FileReadError(path).what());
        }

        // Read the entire file into a string using a stringstream.
        std::ostringstream sourceStream;
        sourceStream << file.rdbuf();
        std::string source = sourceStream.str();

        // Log the content and return the string.
        PLog::echoMessage(source.c_str());
        return source;
    }
}
