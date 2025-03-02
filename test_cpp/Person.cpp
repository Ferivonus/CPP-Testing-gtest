#include "Person.h"
#include <sstream>
#include <ctime>
#include <chrono>
#include <iomanip>

Person::Person(const std::string& name, int age, const std::string& password)
    : name_(validateName(name)), age_(validateAge(age)),
    account_(std::make_unique<BankAccount>(password)) {
}

void Person::performDeposit(double amount, const std::string& password) {
    account_->deposit(amount, password);
    financialHistory_.emplace_back(FinancialOperation::Type::DEPOSIT, amount, std::time(nullptr));
}

void Person::performWithdrawal(double amount, const std::string& password) {
    account_->withdraw(amount, password);
    financialHistory_.emplace_back(FinancialOperation::Type::WITHDRAWAL, amount, std::time(nullptr));
}

std::string Person::getGender() const noexcept {
    return std::string();
}

std::string Person::getFinancialReport(const std::string& password) const {
    std::stringstream report;
    report << "Financial Report for " << name_ << "\n";
    report << "Account Number: " << account_->getAccountNumber() << "\n";
    report << "Current Balance: $" << account_->getBalance(password) << "\n";
    report << "Transaction History:\n";

    for (const auto& op : financialHistory_) {
        std::time_t timestamp = op.getTimestamp();
        std::tm tm_buf;

        // Use localtime_s for Windows, or localtime_r for POSIX systems
#ifdef _WIN32
        localtime_s(&tm_buf, &timestamp);
#else
        localtime_r(&timestamp, &tm_buf);
#endif

        report << "- " << op.getDescription() << " at "
            << std::put_time(&tm_buf, "%Y-%m-%d %H:%M:%S") << "\n";
    }

    return report.str();
}

std::string Person::validateName(const std::string& name) {
    if (name.empty()) throw std::invalid_argument("Name cannot be empty");
    return name;
}

int Person::validateAge(int age) {
    if (age < 0) throw std::invalid_argument("Age cannot be negative");
    return age;
}

double Person::getBalance(const std::string& passwordInput) const {
    return account_->getBalance(passwordInput);
}
