//
// Created by emman on 8/2/2024.
//

#include <fstream>
#include "fileio.h"
#include "log.h"

namespace pnt{

    /// @brief Extract Source code from file.
    /// @param path - The relative path to the file.
    /// @return A std::string contained in the file.
    /// @note Works with Absolute paths too.
    std::string PFileIO::extractSourceFromFile(const char *path) {
        std::fstream file(path);
        std::string source;

        if(file.is_open())
        {
            std::string line;
            while(std::getline(file, line)){
                source += line + "\n";
            }
        }
        file.close();
        PLog::echoMessage(source.c_str());
        return source;
    }
}
