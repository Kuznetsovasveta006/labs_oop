#include "AbilityManager.hpp"
#include "NoAbilityError.hpp"


AbilityManager::AbilityManager()
    : visitor(factory) {
    std::vector<AbilityStatus> abilities_vector =  {AbilityStatus::DoubleDamage, AbilityStatus::Scanner, AbilityStatus::Shelling};

    std::random_shuffle(abilities_vector.begin(), abilities_vector.end());
    
    for(auto i: abilities_vector)
        avaliable_abilities.push(i);
}

AbilityManager::AbilityManager(std::queue<AbilityStatus>& abilities)
    : avaliable_abilities(abilities), visitor(factory)
{}

std::queue<AbilityStatus> AbilityManager::getQueue() {
    return avaliable_abilities;
}

void AbilityManager::addAbility() {
    int randomStatus = rand() % 3;
    AbilityStatus status;

    switch (randomStatus) {
        case 0:
            status = AbilityStatus::DoubleDamage;
            break;
        case 1:
            status = AbilityStatus::Scanner;
            break;
        case 2:
            status = AbilityStatus::Shelling;
            break;    
        default:
            break;
        }
    avaliable_abilities.push(status);
}

Ability* AbilityManager::buildAbility(AbilitySettings* settings) {
    settings->acceptVisitor(visitor);
    return factory.getAbility();
}

void AbilityManager::useAbility(AbilitySettings& settings) {
    if (avaliable_abilities.size() == 0) {
        throw NoAbilityError();
    }
    Ability* ability = this->buildAbility(&settings);
    ability->cast();
    avaliable_abilities.pop();
}

AbilityStatus AbilityManager::getAvaliableAbility() const {
    if (avaliable_abilities.size() == 0)
        throw NoAbilityError();

    return avaliable_abilities.front();
}

AbilityManager::AbilityManager(const AbilityManager& other)
    : avaliable_abilities(other.avaliable_abilities), factory(other.factory), visitor(factory) {}

AbilityManager& AbilityManager::operator=(const AbilityManager& other)
{
    if (this != &other)
    {
        avaliable_abilities = other.avaliable_abilities;
        factory = other.factory;
    }

    return *this;
}