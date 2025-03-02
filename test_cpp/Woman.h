#ifndef WOMAN_H
#define WOMAN_H

#include "Person.h"

class Woman : public Person {
public:
    using Person::Person;
    std::string getGender() const noexcept override { return "Female"; }
};

#endif // WOMAN_H
