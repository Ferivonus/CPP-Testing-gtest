#ifndef MAN_H
#define MAN_H

#include "Person.h"

class Man : public Person {
public:
    using Person::Person;
    std::string getGender() const noexcept override { return "Male"; }
};

#endif // MAN_H
