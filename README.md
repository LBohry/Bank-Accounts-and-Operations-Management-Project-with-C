# Bank Management System by Bahaeddine Ben Abdallah

## To run the project : 
	1. clone the repository 
 	2. open the .c file in CODE::BLOCKS
	3. build the file & run the program :) 
## Main data structure : Account 
### Each account is represented by an account number, a username, the balance, a pointer to its transactions file, and its filename, which are initiated at the creation of the account : 
struct Account {
  int accNo;
  char name[50];
  float balance;
  FILE* transFile;
  char filename[50];
};


## Features of the project : 
 #### 1. Account creation : 
 this features allows you to creates a new account, with checks if the account number already exists
  	
 #### 2. Account info update :
 this feature allows you to change the username, or account number of a given account 
  	(with checks if it doesn't exist), and it provides a way to keep the initial values if  you changed your mind about the updates.

 #### 3. Account deletion :
 this feature allows you to delete a given account, (with checks if the account doesn't exist)

 #### 4. Printing Transaction Details : 
 this feature allows you to print all the transaction details of a given account's transfile 

 #### 5. Printing Account Details : 
 this feature allows you to print all information of a given account, the number, username, and the balance (with checks if the account doesn't exist)

 #### 6. Printing all Accounts Details : 
 this feature allows you to print all the information of all the accounts details.

 #### 7. Transfer Money : 
 this feature allows you to choose your account, and the account you want to transfer money to. 
 with checks for both account numbers if they exist or not, and a balance check to see if you have the money to be transfered. (and logs the money transfered in the transaction files for each account)

 #### 8. Deposit Money : 
 this feature allows you to deposit money into a given account, with checks if the account doesn't exist. (logs the transaction in the account's transaction file).

 #### 9. Withdraw Money : 
 this feature allows you to withdraw money from a given account, with checks if the account doesn't exist, also checks if you have enough balance to withdraw that amount. (logs the transaction in the account's transaction file).

 #### 10. Menu : 
 this feature allows you to have a recurring menu to choose your options for your next operation to do. (with checks if you give an invalid choice) 


 #### 11. Demo : 

 https://github.com/LBohry/C-Project/assets/83679014/c207f00d-1aca-4f47-81f0-5fde68466338


