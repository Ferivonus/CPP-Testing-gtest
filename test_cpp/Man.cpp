#include "Man.h"
#include <iostream>

Man::Man(const std::string& name, int age) : name(name), age(age) {
    if (name.empty()) {
        throw InvalidPersonException("Name cannot be empty.");
    }
    if (age < 0) {
        throw InvalidPersonException("Age cannot be negative.");
    }
}

std::string Man::getName() const {
    return name;
}

int Man::getAge() const {
    return age;
}

std::string Man::getGender() const {
    return "Male";
}

void Man::printDetails() const {
    std::cout << "Name: " << name << "\nAge: " << age << "\nGender: " << getGender() << std::endl;
}
