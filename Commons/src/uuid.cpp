//
// Created by Eniola Olawale on 9/17/2024.
//

#include <random>
#include "uuid.h"

namespace commons{

    static std::random_device s_RandomDevice;
    static std::mt19937_64 s_Engine(s_RandomDevice());
    static std::uniform_int_distribution<uint64_t> s_UniformDistribution;


    PUUID::PUUID() : m_UUID(s_UniformDistribution(s_Engine)){

    }

    PUUID::PUUID(uint64_t id) : m_UUID(id){

    }

    PUUID::PUUID(const PUUID& uuid) : m_UUID(uuid.m_UUID) {

    }
}