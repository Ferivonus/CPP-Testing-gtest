#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <ctime>
#include "BankAccount.h"
#include "Person.h"
#include "Man.h"
#include "Woman.h"
#include "Bank.h"
#include "SecurityUtils.h"

// BankAccount Testleri

TEST(BankAccountTest, TestInitialBalance) {
    BankAccount account("password123");
    EXPECT_DOUBLE_EQ(account.getBalance("password123"), 0.0);
}

TEST(BankAccountTest, TestDeposit) {
    BankAccount account("password123");
    account.deposit(1000.0, "password123");
    EXPECT_DOUBLE_EQ(account.getBalance("password123"), 1000.0);
}

TEST(BankAccountTest, TestWithdraw) {
    BankAccount account("password123");
    account.deposit(1000.0, "password123");
    account.withdraw(500.0, "password123");
    EXPECT_DOUBLE_EQ(account.getBalance("password123"), 500.0);
}

TEST(BankAccountTest, TestInsufficientFunds) {
    BankAccount account("password123");
    account.deposit(1000.0, "password123");
    EXPECT_THROW(account.withdraw(1500.0, "password123"), BankAccount::TransactionException);
}

TEST(BankAccountTest, TestAuthenticationFailed) {
    BankAccount account("password123");
    EXPECT_THROW(account.deposit(1000.0, "wrongpassword"), BankAccount::TransactionException);
}

// Person Testleri

TEST(PersonTest, TestPersonCreation) {
    Person person("Alice", 30, "password123");
    EXPECT_EQ(person.getGender(), "");  // Expect an empty string, as `Person` is abstract
}

TEST(PersonTest, TestDepositAndBalance) {
    Person person("Alice", 30, "password123");
    person.performDeposit(500.0, "password123");
    EXPECT_DOUBLE_EQ(person.getBalance("password123"), 500.0);
}

TEST(PersonTest, TestWithdrawal) {
    Person person("Alice", 30, "password123");
    person.performDeposit(1000.0, "password123");
    person.performWithdrawal(400.0, "password123");
    EXPECT_DOUBLE_EQ(person.getBalance("password123"), 600.0);
}

TEST(PersonTest, TestWithdrawalExceedsBalance) {
    Person person("Alice", 30, "password123");
    person.performDeposit(1000.0, "password123");
    EXPECT_THROW(person.performWithdrawal(1500.0, "password123"), BankAccount::TransactionException);
}

TEST(PersonTest, TestFinancialReport) {
    Person person("Alice", 30, "password123");
    person.performDeposit(1000.0, "password123");
    person.performWithdrawal(400.0, "password123");
    std::string report = person.getFinancialReport("password123");
    EXPECT_TRUE(report.find("Deposit of $1000") != std::string::npos);
    EXPECT_TRUE(report.find("Withdrawal of $400") != std::string::npos);
}

// Man ve Woman Testleri

TEST(ManTest, TestGender) {
    Man man("Bob", 35, "password123");
    EXPECT_EQ(man.getGender(), "Male");  // `Man` should return "Male"
}

TEST(WomanTest, TestGender) {
    Woman woman("Alice", 30, "password123");
    EXPECT_EQ(woman.getGender(), "Female");  // `Woman` should return "Female"
}

// Bank Testleri

TEST(BankTest, TestAccountCreation) {
    Bank bank;
    auto manAccount = bank.createAccount("Bob", 40, "Male", "password123");
    auto womanAccount = bank.createAccount("Alice", 30, "Female", "password123");
    EXPECT_EQ(manAccount->getGender(), "Male");
    EXPECT_EQ(womanAccount->getGender(), "Female");
}

TEST(BankTest, TestTotalAssets) {
    Bank bank;
    auto manAccount = bank.createAccount("Bob", 40, "Male", "password123");
    auto womanAccount = bank.createAccount("Alice", 30, "Female", "password123");
    manAccount->performDeposit(1000.0, "password123");
    womanAccount->performDeposit(1500.0, "password123");

    EXPECT_DOUBLE_EQ(bank.getTotalBankAssets(), 2500.0);
}

// SecurityUtils Testleri

TEST(SecurityUtilsTest, TestGenerateSalt) {
    std::string salt1 = CryptoUtils::generateSalt();
    std::string salt2 = CryptoUtils::generateSalt();
    EXPECT_NE(salt1, salt2);
}

TEST(SecurityUtilsTest, TestHashPassword) {
    std::string salt = CryptoUtils::generateSalt();
    std::string password = "password123";
    std::string hash1 = CryptoUtils::hashPassword(password, salt);
    std::string hash2 = CryptoUtils::hashPassword(password, salt);
    EXPECT_EQ(hash1, hash2);
}

// Test Main
static int TEST_main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
