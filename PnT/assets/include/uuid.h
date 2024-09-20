//
// Created by Eniola Olawale on 9/17/2024.
//

#pragma once

//#include <xhash>
#include "pnt_core_pch.h"

namespace pnt{
    class PUUID {
    public:
        PUUID();
        explicit PUUID(uint64_t id);
        PUUID(const PUUID&) = default;

        operator uint64_t() const { return m_UUID;}
        operator std::string() const {
            std::ostringstream stream;
            stream << m_UUID;
//            stream << std::hex << std::setfill('0') << std::setw(16) << m_UUID;
            return stream.str();
            return stream.str();
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
    struct hash<pnt::PUUID>{
        std::size_t operator()(const pnt::PUUID& uuid) const{
            return hash<uint64_t>()((uint64_t)uuid);
        }
    };
}
