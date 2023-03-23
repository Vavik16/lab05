#include <Account.h>
#include <Transaction.h>
#include <gtest/gtest.h>

TEST(Banking, Account) {
Account acc(0, 0); 

ASSERT_EQ(acc.GetBalance(), 0); 
ASSERT_THROW(acc.ChangeBalance(120), std::runtime_error); 
acc.Lock(); 
ASSERT_NO_THROW(acc.ChangeBalance(120)); 
ASSERT_THROW(acc.Lock(), std::runtime_error);
ASSERT_EQ(acc.GetBalance(), 120);
acc.ChangeBalance(-124); 
ASSERT_EQ(acc.GetBalance(), -4);
acc.Unlock(); 
ASSERT_THROW(acc.ChangeBalance(120), std::runtime_error);
}

TEST(Banking, Transaction) {
Account accA(1, 1500);
Account accB(2, 1500);
Transaction transaction;

ASSERT_EQ(transaction.fee(), 1);
transaction.set_fee(20); 
ASSERT_EQ(transaction.fee(), 20);

ASSERT_THROW(transaction.Make(accA, accB, -345), std::invalid_argument); 
ASSERT_THROW(transaction.Make(accB, accB, 1000), std::logic_error); 
ASSERT_THROW(transaction.Make (accA, accB, 40), std::logic_error); 
transaction.set_fee(100); 
ASSERT_EQ(transaction.Make(accA, accB, 150), false); 
ASSERT_EQ(transaction.Make(accA, accB, 200000), false); 

ASSERT_EQ(transaction.Make(accA, accB, 1200), true); 
ASSERT_EQ(accB.GetBalance(), 2700);
ASSERT_EQ(accA.GetBalance(), 300); 
}
