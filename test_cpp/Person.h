#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <memory>
#include <vector>
#include <ctime>
#include "BankAccount.h"

class Person {
public:
    class FinancialOperation {
    public:
        enum class Type { DEPOSIT, WITHDRAWAL };

        FinancialOperation(Type type, double amount, std::time_t timestamp)
            : type_(type), amount_(amount), timestamp_(timestamp) {
        }

        std::time_t getTimestamp() const { return timestamp_; }
        std::string getDescription() const {
            std::string typeStr = (type_ == Type::DEPOSIT) ? "Deposit" : "Withdrawal";
            return typeStr + " of $" + std::to_string(amount_);
        }

    private:
        Type type_;
        double amount_;
        std::time_t timestamp_;
    };

    Person(const std::string& name, int age, const std::string& password);
    virtual ~Person() = default;
    void performDeposit(double amount, const std::string& password);
    void performWithdrawal(double amount, const std::string& password);

    std::shared_ptr<BankAccount> getAccount() const {
        return std::make_shared<BankAccount>(*account_);
    }

    std::string getFinancialReport(const std::string& password) const;
    virtual std::string getGender() const noexcept;
    double getBalance(const std::string& passwordInput) const;

protected:
    

    std::string name_;
    int age_;
    std::unique_ptr<BankAccount> account_;
    std::vector<FinancialOperation> financialHistory_;

    static std::string validateName(const std::string& name);
    static int validateAge(int age);
    
};

#endif // PERSON_H