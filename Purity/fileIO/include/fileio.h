//
// Created by emman on 8/2/2024.
//

#pragma once

//#include <assimp/IOStream.hpp>
//#include <assimp/IOSystem.hpp>
#include <iostream>
#include <string.h>


namespace purity::fileIO{

    //class PIOStream : public Assimp::IOStream {
    //    friend class PIOSystem;
    //protected:
    //    // Constructor protected for private usage by MyIOSystem
    //    PIOStream();

    //public:
    //    ~PIOStream();
    //    size_t Read(void* pvBuffer, size_t pSize, size_t pCount) { return 0; }
    //    size_t Write(const void* pvBuffer, size_t pSize, size_t pCount) { return 0; }
    //    aiReturn Seek(size_t pOffset, aiOrigin pOrigin) { return aiReturn_FAILURE; }
    //    size_t Tell() const { return 0; }
    //    size_t FileSize() const { return 0; }
    //    void Flush() { }
    //};

    //
    //// Fisher Price - My First Filesystem
    //class PIOSystem : public Assimp::IOSystem {
    //    PIOSystem() { ... }
    //    ~PIOSystem() { ... }

    //    // Check whether a specific file exists
    //    bool Exists(const std::string& pFile) const {
    //    
    //    }

    //    // Get the path delimiter character we'd like to see
    //    char GetOsSeparator() const {
    //        return '/';
    //    }

    //    // ... and finally a method to open a custom stream
    //    IOStream* Open(const std::string& pFile, const std::string& pMode) {
    //        return new PIOStream(...);
    //    }

    //    void Close(IOStream* pFile) { delete pFile; }
    //};

    class PURITY_API PFileIO{
    public:
        static std::string extractSourceFromFile(const char *path);

        static std::string getProjectRoot();


    };
}

