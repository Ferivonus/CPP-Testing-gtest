#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <string>
#include <atomic>
#include <stdexcept>
#include "SecurityUtils.h"

class BankAccount {
public:
    class TransactionException : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    BankAccount(const std::string& password);
    void deposit(double amount, const std::string& password);
    void withdraw(double amount, const std::string& password);
    double getBalance(const std::string& password) const;
    unsigned long getAccountNumber() const noexcept;

private:
    unsigned long accountNumber_;
    double balance_;
    std::string salt_;
    std::string passwordHash_;

    static std::atomic<unsigned long> lastAccountNumber;

    static unsigned long generateAccountNumber() noexcept;
    void authenticate(const std::string& password) const;
};

#endif // BANK_ACCOUNT_H
