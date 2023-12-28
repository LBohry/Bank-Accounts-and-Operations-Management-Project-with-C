#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>

struct Account {
  int accNo;
  char name[50];
  float balance;
  FILE* transFile;
  char filename[50];
};



struct Account accounts[100];
int num_accounts = 0;

// Function prototypes
void createAccount();
void update_account_info();
void delete_account();
void print_account_details();
void print_all_accounts();
void transfer_money();
void deposit_money();
void withdraw_money();
void transaction_details();
int AccountExists(int accid);

int AccountExists(int accid){ //function to check if an account exists or not 
    for(int i=0; i<num_accounts; i++) {
        if(accounts[i].accNo == accid) {
            return 1;
        }
    }
    return 0;  // Add this line
}

void create_account(){
  system("cls");
  int accNumAux;
  struct Account acc;


  printf("Enter name: ");
  scanf("%s", acc.name);

  printf("Enter account number: ");
  scanf("%d", &accNumAux);

    if(AccountExists(accNumAux) == 1){
        printf("Account number already exists!");
        return;
    }
  acc.accNo = accNumAux;

  acc.balance = 20;


  sprintf(acc.filename, "%d_trans.txt", acc.accNo); //this gives the filename as accountnumber_trans.txt
  acc.transFile = fopen(acc.filename, "w");

  if(!acc.transFile) {
    printf("Error opening file");
    return;
  }

  fprintf(acc.transFile, "Account created\n"); //adding to the transactions file "Account created" since it's the same as depositing 20TND at the tunisian banks
  fclose(acc.transFile);
  accounts[num_accounts++] = acc;

  printf("Account created successfully!");
  printf("Press any key to go back to menu..");
  getch();
  system("cls");
  return;
}
void update_account_info() { //function  to update the username or the number of an account

  int accNo;
  int accNoAux;
  char name[50];

  printf("Enter account number: ");
  scanf("%d", &accNo);

  if (AccountExists(accNo)==0){
    printf("account doesnt exist");
    return;
  }
  for(int i=0; i<num_accounts; i++) {
    if(accounts[i].accNo == accNo) {

      printf("Enter new name (or enter x to keep the initial): ");
      scanf("%s", name);

      if(strcmp(name, "x") != 0) {
        strcpy(accounts[i].name, name);
      }

      printf("Enter new account number (or enter -1 to keep the initial): ");
      scanf("%d", &accNoAux);
      if (accNoAux == -1){
        return;
      }
      while(AccountExists(accNoAux) == 1 ) {
        printf("Acc no. already exists! Re-enter: ");
        scanf("%d", &accounts[i].accNo);
      }

        accounts[i].accNo = accNoAux;




    printf("Information updated");
    printf("Press any key to go back to menu..");
    getch();
    system("cls");
      return;
    }
  }


}

void delete_account() { 
    system("cls");
    int account_number;

    printf("Enter the account number: ");
    scanf("%d", &account_number);
    if (AccountExists(account_number)==0){
        printf("account doesnt exist");
        return;
    }
    for (int i = 0; i < num_accounts; i++) {
        if (accounts[i].accNo == account_number) {
            fclose(accounts[i].transFile);
            for (int j = i; j < num_accounts - 1; j++) {
                accounts[j] = accounts[j + 1];
            }
            num_accounts--;
            printf("Account deleted successfully.\n");
            printf("Press any key to go back to menu..");
            getch();
            system("cls");
            return;
        }
    }
}

void transaction_details() { //function to print all the transaction details (in case of deposits, withdrawl, transfers, etc)
    system("cls");
    int account_number;

    printf("Enter the account number: ");
    scanf("%d", &account_number);

    if (AccountExists(account_number)==0){
        printf("account doesnt exist");
        return;
    }

    for (int i = 0; i < num_accounts; i++) {
        if (accounts[i].accNo == account_number) {
            accounts[i].transFile = fopen(accounts[i].filename, "r");
                if (!accounts[i].transFile) {
                    printf("Error opening file\n");
                return;
                }
            printf("TRANSACTION DETAILS\n"); //this is just printed as the beginning of the file to be clearer
            for (int j = 0; j < 50; j++) {
                printf("-");
            }
            printf("\n");

            rewind(accounts[i].transFile);  // Go back to the start of the file

            char c = fgetc(accounts[i].transFile);
            if (c == EOF) {
                printf("*******NO RECENT TRANSACTION*******\n");
            } else {
                while (c != EOF) {
                    printf("%c", c);
                    c = fgetc(accounts[i].transFile);
                }
            }
             printf("Press any key to go back to menu..");
            getch();
            system("cls");
            fclose(accounts[i].transFile);
            return;
            
        }
    }

}

void print_account_details() { //function to print the name, account number, and balance of an account
    system("cls");
    int account_number;

    printf("Enter the account number: ");
    scanf("%d", &account_number);

    if (AccountExists(account_number)==0){
        printf("account doesnt exist");
        return;
    }

    for (int i = 0; i < num_accounts; i++) {
        if (accounts[i].accNo == account_number) {
            printf("Account number: %d\n", accounts[i].accNo);
            printf("Account username: %s\n", accounts[i].name);
            printf("Account balance: %.2f TND \n", accounts[i].balance);
            printf("Press any key to go back to menu..");
            getch();
            system("cls");
            return;
        }
    }

    printf("Account not found.\n");

}

void print_all_accounts() { //prints the details of all accounts
    system("cls");
    for (int i = 0; i < num_accounts; i++) {
        printf("Account number: %d\n", accounts[i].accNo);
        printf("Account username: %s\n", accounts[i].name);
        printf("Account balance: %.2f TND \n", accounts[i].balance);
        printf("------------------------------------\n");
    }

    printf("Press any key to go back to menu..");
    getch();
    system("cls");
}

void transfer_money() { //this transfers money from one account to another
    system("cls");
    time_t tm;
    time(&tm);
    int account_number_from, account_number_to;
    float transfer_amount;

    printf("Enter the account number from which you want to transfer money: ");
    scanf("%d", &account_number_from);

    printf("Enter the account number to which you want to transfer money: ");
    scanf("%d", &account_number_to);

    printf("Enter the amount you want to transfer: ");
    scanf("%f", &transfer_amount);

    struct Account *account_from = NULL;
    struct Account *account_to = NULL;

    // Find the accounts using the account numbers
    for (int i = 0; i < num_accounts; i++) {
        if (accounts[i].accNo == account_number_from) {
            account_from = &accounts[i];
        }
        if (accounts[i].accNo == account_number_to) {
            account_to = &accounts[i];
        }
    }

    if (account_from == NULL || account_to == NULL) {
        printf("One or both account numbers are invalid.\n");
        return;
    }

    if (account_from->balance < transfer_amount) {
        printf("Insufficient balance.\n");
        return;
    }
    account_from->transFile = fopen(account_from->filename,"a");
    account_to->transFile = fopen(account_to->filename,"a");
    account_from->balance -= transfer_amount;
    account_to->balance += transfer_amount;

    // Record the transaction in both accounts' transaction files
    fprintf(account_from->transFile, "Date/Time of transaction :  %s\n", ctime(&tm));
    fprintf(account_from->transFile, "Transferred %.2f TND to account %d\n", transfer_amount, account_number_to);
    fprintf(account_to->transFile, "Date/Time of transaction :  %s\n", ctime(&tm));
    fprintf(account_to->transFile, "Received %.2f TND from account %d\n", transfer_amount, account_number_from);
    fclose(account_from->transFile);

    fclose(account_to->transFile);
    printf("Money transferred successfully.\n");
    printf("Press any key to go back to menu..");
    getch();
    system("cls");
    return;
}

void deposit_money() { //this deposits a certain ammount into a given account
    struct Account *account = NULL;
    system("cls");
    int account_number;
    float deposit_amount;
    time_t tm;
    time(&tm);


    printf("Enter the account number: ");
    scanf("%d", &account_number);

    for (int i = 0; i < num_accounts; i++) {
        if (accounts[i].accNo == account_number) {
            account = &accounts[i];
            break;
        }
    }

    if (account == NULL){
        printf("Account doesn't exist.\n");
        return;
    }

    account->transFile = fopen(account->filename,"a");


    printf("Enter the amount you want to deposit: ");
    scanf("%f", &deposit_amount);

    account->balance += deposit_amount;
    fprintf(account->transFile, "Date/Time of transaction :  %s\n", ctime(&tm));
    fprintf(account->transFile, "Deposited %.2f TND\n", deposit_amount);


    fclose(account->transFile);


    printf("Money deposited successfully.\n");
    printf("Press any key to go back to menu..");
    getch();
    system("cls");
    return;

}
void withdraw_money() { //this withdrawls a certain ammount from an account 
    struct Account *account;
    system("cls");
    int account_number;
    float withdraw_amount;
    time_t tm;
    time(&tm);

    printf("Enter the account number: ");
    scanf("%d", &account_number);

    if (AccountExists(account_number)==0){
        printf("account doesnt exist");
        return;
    }

    for (int i = 0; i < num_accounts; i++) {
       if (accounts[i].accNo == account_number) {
            account = &accounts[i];
            break;
    }
    }


    account->transFile = fopen(account->filename,"a");



    printf("Enter the amount you want to withdraw: ");
    scanf("%f", &withdraw_amount);

    if (account->balance < withdraw_amount) {
        printf("Insufficient balance.\n");
        return;
    }

    account->balance -= withdraw_amount;

    fprintf(account->transFile, "Date/Time of transaction :  %s\n", ctime(&tm));
    fprintf(account->transFile, "Withdrew %.2f TND\n", withdraw_amount);

    fclose(account->transFile);


    printf("Money withdrawn successfully.\n");
    printf("Press any key to go back to menu..");
    getch();
    system("cls");
    return;


}
void menu() {
    printf("\n1.Deposit Money\n");
    printf("2.Withdraw Money\n");
    printf("3.Transfer Money\n");
    printf("4.Account details\n");
    printf("5.Transaction details\n");
    printf("6.Update Account Information\n");
    printf("7.Delete Account\n");
    printf("8.Print All Accounts\n");
    printf("9.Create New Account\n");
    printf("10.Exit\n");
}

int main() {
    int ch;


    // Create a new account
    create_account();

    while (1) {
        menu();
        printf("\nEnter your choice :\n");
        scanf("%d", &ch);
        switch (ch) {
        case 1:
            deposit_money();
            break;
        case 2:
            withdraw_money();
            break;
        case 3:
            transfer_money();
            break;
        case 4:
            print_account_details();
            break;
        case 5:
            transaction_details();
            break;
        case 6:
            update_account_info();
            break;
        case 7:
            delete_account();
            break;
        case 8:
            print_all_accounts();
            break;
        case 9:
            create_account();
            break;
        case 10:
            exit(1);
        break;
        default:
            printf("*****Invalid choice*****");
        }
    }

    return 0;
}
