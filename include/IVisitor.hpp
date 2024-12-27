#ifndef VISITOR_HPP
#define VISITOR_HPP


class Visitor {
public:
    virtual void visit(class DoubleDamageSettings* settings) = 0;
    virtual void visit(class ScannerSettings* settings) = 0;
    virtual void visit(class ShellingSettings* settings) = 0;
};

#endif //VISITOR_HPP