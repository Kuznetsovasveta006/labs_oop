#ifndef ABILITY_MANAGER_HPP
#define ABILITY_MANAGER_HPP

#include <queue>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <stdexcept>
#include <random>

#include "AbilityFactory.hpp"
#include "IAbility.hpp"
#include "AbilityVisitor.hpp"



class AbilityManager {
public:
    AbilityManager();
    AbilityManager(std::queue<AbilityStatus>& abilities);

    ~AbilityManager() = default;

    std::queue<AbilityStatus> getQueue();
    void addAbility();
    void useAbility(AbilitySettings& settings); 
    AbilityStatus getAvaliableAbility() const;


    AbilityManager(const AbilityManager& other);
    AbilityManager& operator=(const AbilityManager& other);

private:
    std::queue<AbilityStatus> avaliable_abilities;
    AbilityFactory factory;
    AbilityVisitor visitor;

    Ability* buildAbility(AbilitySettings* settings);
};


#endif // ABILITY_MANAGER_HPP