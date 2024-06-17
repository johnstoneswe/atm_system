# ifndef ATM_H
# define ATM_H

// Transaction type
typedef struct Transaction {
  int  balance;
  char type[10];
} Transaction;

// User Type
typedef struct User {
  int  balance;
  int  pin;
  char first_name[20];
  char last_name[20];
} User;

// function to deposit cash in the user's account
void deposit(User * u, int amount, Transaction * transactions, int trackTransactions);

// function to withdraw cash in the user's account
int withdraw(User * u, int amount, Transaction * transactions, int trackTransactions);

// function to view transaction history
void history(Transaction * transactions, int transactionsLength);

// function to check the balance of a user's account
void balance(User *u);

# endif