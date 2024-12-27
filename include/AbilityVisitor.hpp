#ifndef ABILITY_VISITOR_HPP
#define ABILITY_VISITOR_HPP

#include "IVisitor.hpp"
#include "AbilityFactory.hpp"


class AbilityVisitor: public Visitor {
public:
    AbilityVisitor(AbilityFactory& factory);

    ~AbilityVisitor() = default;
    
    void visit(class DoubleDamageSettings* settings) override;
    void visit(class ScannerSettings* settings) override;
    void visit(class ShellingSettings* settings) override;

private:
    AbilityFactory& factory;
};

#endif //ABILITY_VISITOR_HPP