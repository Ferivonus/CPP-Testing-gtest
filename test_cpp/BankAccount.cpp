#include "BankAccount.h"

std::atomic<unsigned long> BankAccount::lastAccountNumber = 1000000000;

BankAccount::BankAccount(const std::string& password)
    : accountNumber_(generateAccountNumber()), balance_(0.0) {
    salt_ = CryptoUtils::generateSalt();
    passwordHash_ = CryptoUtils::hashPassword(password, salt_);
}

void BankAccount::deposit(double amount, const std::string& password) {
    authenticate(password);
    if (amount <= 0) throw TransactionException("Invalid deposit amount");
    balance_ += amount;
}

void BankAccount::withdraw(double amount, const std::string& password) {
    authenticate(password);
    if (amount <= 0) throw TransactionException("Invalid withdrawal amount");
    if (amount > balance_) throw TransactionException("Insufficient funds");
    balance_ -= amount;
}

double BankAccount::getBalance(const std::string& password) const {
    authenticate(password);
    return balance_;
}

unsigned long BankAccount::getAccountNumber() const noexcept {
    return accountNumber_;
}

unsigned long BankAccount::generateAccountNumber() noexcept {
    return ++lastAccountNumber;
}

void BankAccount::authenticate(const std::string& password) const {
    const std::string attemptHash = CryptoUtils::hashPassword(password, salt_);
    if (attemptHash != passwordHash_) {
        throw TransactionException("Authentication failed");
    }
}
