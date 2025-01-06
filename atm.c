# include "ATM.H" // custom header with function definitions & variables
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/*
  Description : Entry point of the program, functionality is nested within
  @main : Entry Point of the program
  @return : 0 (success)
*/
int main() {
  User user;

  // int to create transactions
  int transactionsLength = 30;

  // variable to track the amount of transactions committed, decrease after every transaction
  int trackTransactions = 0;

  // create an array of transactions & dynamically allocate memory for it
  struct Transaction * transactions = malloc(transactionsLength * sizeof(struct Transaction));

  // check that the transactions array has been created
  if (transactions == NULL) {
    puts("Failed to create memory for transactions");

    exit(1);
  }

  // simulate creating an account for the user
  puts("Enter your first name");
  scanf("%19s", &user.first_name[0]);
  puts("");

  puts("Enter your last name");
  scanf("%19s", &user.last_name[0]);
  puts("");

  puts("Enter an account pin");
  scanf("%d", &user.pin);

  puts("Enter your phone number");
  scanf("%14s", &user.phone_number[0]);

  // integer to store a starting balance
  int starting;

  // Prompt the user to create a deposit for the starting balance
  puts("Enter a starting balance between 10 and 5000");
  scanf("%d", &starting);
  puts("");

  // make a first deposit for the user
  user.balance += starting;

  // create a user sign up transaction
  Transaction created = {
    .type = "creation",
    .balance = user.balance
  };

  // add the created transaction to the transactions array
  transactions[0] = created;

  // add the amount of transactions comitted;
  trackTransactions += 1;

  printf("Account successfully created for %s %s, balance : %d \n", user.first_name, user.last_name, user.balance);
  puts("");

  // use a while loop to keep the shell active until the user exits
  while(1) {
    // prompt the user to make a transaction on the account
    puts("Enter an action to continue : deposit, withdraw, history, balance, mobile_transfer, change_pin, exit");

    // record the action the user enters
    char action[40];
    scanf("%s", &action[0]);

    // check the users entered action & commit it, otherwise exit
    if (strcmp(action, "history") == 0) {
      history(transactions, transactionsLength);

      puts("");

    } else if (strcmp(action, "deposit") == 0) {
      puts("Enter amount to deposit");

      int amount;
      scanf("%d", &amount);

      deposit(&user, amount, transactions, trackTransactions);
      trackTransactions++;

      puts("");

    } else if (strcmp(action, "withdraw") == 0) {
      puts("Enter amount to withdraw");

      int amount;
      scanf("%d", &amount);

      int returned;

      returned = withdraw(&user, amount, transactions, trackTransactions);

      if (returned == 0) {
        trackTransactions++;
      }

      puts("");

    } else if (strcmp(action, "balance") == 0) {

      balance(&user);

    } else if (strcmp(action, "change_pin") == 0) {
      int new_pin;

      puts("Enter a new pin");
      scanf("%d", &new_pin);

      update_pin(&user, new_pin);

    } else if (strcmp(action, "mobile_transfer") == 0 ) {
      int amount;

      puts("Enter the amount you want to transfer to your phone");
      scanf("%d", amount);

      send_to_sim(&user, amount);

    } else if (strcmp(action, "exit") == 0) {

      break;

    } else {

      puts("Invalid action");
    }
  }

  // free the memory set aside for transactions
  free(transactions);

  return (0);
}

/*
  @deposit Description : Function to deposit cash in the User's account
  @param : User struct u,
  @param : Transactions t - array of transactions
  @param : int trackTransactions - Integer tracking transactions (will also tell you where the deposit transaction will be placed in t)
  *@returns : (void)
*/
void deposit(User * u, int amount, Transaction * transactions, int trackTransactions) {
  if (amount > 30000) {
    puts("Maximum amount depositable via ATM is 30000, please visit bank teller.");
  } else {
    u -> balance += amount;
    // create a deposit transaction & add it to the transactions array
    Transaction deposit = {
      .type = "deposit",
      .balance = u -> balance
    };

    // add the transaction to the array
    transactions[trackTransactions] = deposit;

    // print a success message to the user
    printf("Deposit successful, new balance : %d \n", u -> balance);
  }
};

/*
  Description : Function to withdraw cash in the User's account
  @returns : (0) : transaction successful, (1) : Amount can't be withdrawn
*/

int withdraw(User * u, int amount, Transaction * transactions, int trackTransactions) {
  if (amount > u -> balance) {
    printf("Can't withdraw %d, your balance is %d \n", amount, u -> balance);

    return 1;
  } else {
    // decrement the account balance & create a withdrawal transaction
    u -> balance -= amount;

    Transaction withdraw =  {
      .type = "withdrawal",
      .balance = u -> balance
    };

    // add the withdrawal to the transactions
    transactions[trackTransactions] = withdraw;

    // print a success message to the user
    printf("Withdrawal successful, new balance : %d \n", u -> balance);

    return 0;
  }
};

/*
  Description : function that checks the account history of a user
  @return : (void)
*/
void history(Transaction * transactions, int transactionsLength) {
  // loop through the transactions & print them
  for (int i = 0; i < transactionsLength; i++) {
    if (transactions[i].balance >= 1) {
      printf("Transaction : %s, Balance : %d \n", transactions[i].type, transactions[i].balance);
    }
  }
};

/*
  Description : Function that checks the user's account balance
  @return : (void)
*/
void balance(User * u) {
  printf("Your balance is %d \n", u -> balance);
};


/*
  Description : Function to send an amount to the user's phone
*/
void send_to_sim(User * user, int amount) {
  if (user -> balance >= amount) {
    user -> balance -= amount;

    printf("%d, sent to %s, new account balance is %d", amount, user -> phone_number, user -> balance);
  } else {
    printf("Amount can't be sent from your account, balance is : %d", user -> balance);
  }
}

void update_pin(User * user, int new_pin) {
  user -> pin = new_pin;

  puts("Your pin has updated successfully");
}

int authenticate_user(User * user, int pin) {
  if (pin == user -> pin) {
    return 0;
  } else {

    puts("Wrong pin entered; Exit system");
    return 1;
  }
}
