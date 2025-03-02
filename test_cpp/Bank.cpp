#include "Bank.h"

std::shared_ptr<Person> Bank::createAccount(const std::string& name,
    int age,
    const std::string& gender,
    const std::string& password) {
    std::shared_ptr<Person> account;

    if (gender == "Male") {
        account = std::make_shared<Man>(name, age, password);
    }
    else if (gender == "Female") {
        account = std::make_shared<Woman>(name, age, password);
    }
    else {
        throw std::invalid_argument("Unsupported gender specification");
    }

    accounts_[account->getAccount()->getAccountNumber()] = account;
    return account;
}

double Bank::getTotalBankAssets() const noexcept {
    double total = 0.0;
    for (const auto& [_, account] : accounts_) {
        total += account->getAccount()->getBalance("bank_system_access"); // Correct access
    }
    return total;
}
