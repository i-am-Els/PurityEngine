//
// Created by Eniola Olawale on 9/17/2024.
//

#pragma once

//#include <xhash>
#include "common_macros.h"
#include <sstream>

namespace commons{
    class COMMON_API PUUID {
    public:
        PUUID();
        explicit PUUID(uint64_t id);
        PUUID(const PUUID& uuid);

        operator uint64_t() const { return m_UUID;}
        operator std::string() const {
            std::ostringstream stream;
            stream << m_UUID;
//            stream << std::hex << std::setfill('0') << std::setw(16) << m_UUID;
            return stream.str();
            return stream.str();
        }

        static PUUID fromString(std::string str) {
            uint64_t id;
            std::istringstream istream(str);
            istream >> id;
            return PUUID(static_cast<uint64_t>(id));
        }

        PUUID& operator=(PUUID id){
            m_UUID = static_cast<uint64_t>(id);
            return *this;
        }

        bool operator==(PUUID id) const{
            return m_UUID == static_cast<uint64_t>(id);
        }

//        bool operator==(const PUUID id) const{
//            return m_UUID == static_cast<uint64_t>(id);
//        }

    private:
        uint64_t m_UUID;
    };

}

namespace std{
    template<>
    struct hash<commons::PUUID>{
        std::size_t operator()(const commons::PUUID& uuid) const{
            return hash<uint64_t>()((uint64_t)uuid);
        }
    };
}
