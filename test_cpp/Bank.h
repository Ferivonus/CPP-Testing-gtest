#ifndef BANK_H
#define BANK_H

#include <memory>
#include <unordered_map>
#include <stdexcept>
#include "Person.h"
#include "Man.h"
#include "Woman.h"

class Bank {
public:
    std::shared_ptr<Person> createAccount(const std::string& name,
        int age,
        const std::string& gender,
        const std::string& password);
    double getTotalBankAssets() const noexcept;

private:
    std::unordered_map<unsigned long, std::shared_ptr<Person>> accounts_;
};

#endif // BANK_H
