#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main_exit;

void menu();
void close_program();
void fordelay(int j);

// Structure for storing date
struct date {
    int month, day, year;
};

// Structure for customer information
struct customer {
    char name[60];
    int acc_no, age;
    char address[60];
    char citizenship[15];
    double phone;
    char acc_type[10];
    float amt;
    struct date dob;
    struct date deposit;
    struct date withdraw;
} add, upd, check, rem, transaction;

// Function to calculate interest
float interest(float t, float amount, int rate) {
    return (rate * t * amount) / 100.0;
}

// Function to create artificial delay
void fordelay(int j) {
    int i;
    for (i = 0; i < j; i++);
}

// Function to create a new account
void new_acc() {
    FILE *ptr = fopen("record.dat", "a+");

    if (!ptr) {
        printf("Error opening file!\n");
        return;
    }

    system("cls");
    printf("\t\t\t\xB2\xB2\xB2 ADD RECORD \xB2\xB2\xB2\xB2\n");

    // Get account details
    printf("Enter today's date (mm/dd/yyyy): ");
    scanf("%d/%d/%d", &add.deposit.month, &add.deposit.day, &add.deposit.year);

    // Ensure unique account number
    printf("Enter the account number: ");
    scanf("%d", &check.acc_no);

    while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                  &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year,
                  &add.age, add.address, add.citizenship, &add.phone, add.acc_type,
                  &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF) {
        if (check.acc_no == add.acc_no) {
            printf("Account no. already in use!\n");
            fclose(ptr);
            return;
        }
    }

    // Collect user data
    add.acc_no = check.acc_no;
    printf("Enter the name: ");
    scanf("%s", add.name);
    printf("Enter the date of birth (mm/dd/yyyy): ");
    scanf("%d/%d/%d", &add.dob.month, &add.dob.day, &add.dob.year);
    printf("Enter the age: ");
    scanf("%d", &add.age);
    printf("Enter the address: ");
    scanf("%s", add.address);
    printf("Enter the citizenship number: ");
    scanf("%s", add.citizenship);
    printf("Enter the phone number: ");
    scanf("%lf", &add.phone);
    printf("Enter the amount to deposit: $");
    scanf("%f", &add.amt);

    // Account type selection
    printf("Type of account:\n\t#Saving\n\t#Current\n\t#Fixed1(for 1 year)\n\t#Fixed2(for 2 years)\n\t#Fixed3(for 3 years)\n");
    printf("\nEnter your choice: ");
    scanf("%s", add.acc_type);

    // Write to file
    fprintf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n", add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.address, add.citizenship, add.phone, add.acc_type, add.amt, add.deposit.month, add.deposit.day, add.deposit.year);

    fclose(ptr);

    printf("\nAccount created successfully!\n");

    printf("\nEnter 1 to go to the main menu or 0 to exit: ");
    scanf("%d", &main_exit);
    if (main_exit == 1) {
        menu();
    } else {
        close_program();
    }
}

// Function to view the list of customers
void view_list() {
    FILE *view = fopen("record.dat", "r");
    if (!view) {
        printf("Error opening file!\n");
        return;
    }

    system("cls");
    printf("\nACC. NO.\tNAME\t\tADDRESS\t\tPHONE\n");

    int test = 0;
    while (fscanf(view, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                  &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year,
                  &add.age, add.address, add.citizenship, &add.phone, add.acc_type,
                  &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF) {
        printf("\n%6d\t%10s\t%10s\t%.0lf", add.acc_no, add.name, add.address, add.phone);
        test++;
    }

    fclose(view);

    if (test == 0) {
        printf("\nNO RECORDS!!\n");
    }

    printf("\nEnter 1 to go to the main menu or 0 to exit: ");
    scanf("%d", &main_exit);
    if (main_exit == 1) {
        menu();
    } else {
        close_program();
    }
}

// Function to edit account details
void edit() {
    FILE *old = fopen("record.dat", "r");
    FILE *newrec = fopen("new.dat", "w");

    if (!old || !newrec) {
        printf("Error opening file!\n");
        return;
    }

    int test = 0;
    printf("Enter the account no. of the customer whose info you want to change: ");
    scanf("%d", &upd.acc_no);

    while (fscanf(old, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                  &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year,
                  &add.age, add.address, add.citizenship, &add.phone, add.acc_type,
                  &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF) {

        if (add.acc_no == upd.acc_no) {
            test = 1;
            printf("\nWhich information do you want to change?\n1. Address\n2. Phone\nEnter your choice: ");
            int choice;
            scanf("%d", &choice);
            system("cls");

            if (choice == 1) {
                printf("Enter the new address: ");
                scanf("%s", upd.address);
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",
                        add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,
                        add.age, upd.address, add.citizenship, add.phone, add.acc_type,
                        add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
            } else if (choice == 2) {
                printf("Enter the new phone number: ");
                scanf("%lf", &upd.phone);
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",
                        add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,
                        add.age, add.address, add.citizenship, upd.phone, add.acc_type,
                        add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
            }
            printf("Changes saved!\n");
        } else {
            fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",
                    add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,
                    add.age, add.address, add.citizenship, add.phone, add.acc_type,
                    add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
        }
    }

    fclose(old);
    fclose(newrec);

    remove("record.dat");
    rename("new.dat", "record.dat");

    if (test != 1) {
        printf("Record not found!\n");
    }

    printf("\nEnter 1 to go to the main menu or 0 to exit: ");
    scanf("%d", &main_exit);
    if (main_exit == 1) {
        menu();
    } else {
        close_program();
    }
}

// Function to handle deposits and withdrawals
void transact() {
    FILE *old = fopen("record.dat", "r");
    FILE *newrec = fopen("new.dat", "w");

    if (!old || !newrec) {
        printf("Error opening file!\n");
        return;
    }

    int test = 0;
    printf("Enter the account no. of the customer: ");
    scanf("%d", &transaction.acc_no);

    while (fscanf(old, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                  &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year,
                  &add.age, add.address, add.citizenship, &add.phone, add.acc_type,
                  &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF) {

        if (add.acc_no == transaction.acc_no) {
            test = 1;
            printf("\nDo you want to\n1. Deposit\n2. Withdraw?\nEnter your choice: ");
            int choice;
            scanf("%d", &choice);

            if (choice == 1) {
                printf("Enter the amount you want to deposit: $");
                scanf("%f", &transaction.amt);
                add.amt += transaction.amt;
                fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",
                        add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,
                        add.age, add.address, add.citizenship, add.phone, add.acc_type,
                        add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                printf("\nDeposited successfully!\n");
            } else if (choice == 2) {
                printf("Enter the amount you want to withdraw: $");
                scanf("%f", &transaction.amt);
                if (add.amt < transaction.amt) {
                    printf("Insufficient balance!\n");
                } else {
                    add.amt -= transaction.amt;
                    fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",
                            add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,
                            add.age, add.address, add.citizenship, add.phone, add.acc_type,
                            add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
                    printf("\nWithdrawn successfully!\n");
                }
            }
        } else {
            fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",
                    add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,
                    add.age, add.address, add.citizenship, add.phone, add.acc_type,
                    add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
        }
    }

    fclose(old);
    fclose(newrec);

    remove("record.dat");
    rename("new.dat", "record.dat");

    if (test != 1) {
        printf("Record not found!\n");
    }

    printf("\nEnter 1 to go to the main menu or 0 to exit: ");
    scanf("%d", &main_exit);
    if (main_exit == 1) {
        menu();
    } else {
        close_program();
    }
}

// Function to delete an account
void erase() {
    FILE *old = fopen("record.dat", "r");
    FILE *newrec = fopen("new.dat", "w");

    if (!old || !newrec) {
        printf("Error opening file!\n");
        return;
    }

    int test = 0;
    printf("Enter the account no. of the customer you want to delete: ");
    scanf("%d", &rem.acc_no);

    while (fscanf(old, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                  &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year,
                  &add.age, add.address, add.citizenship, &add.phone, add.acc_type,
                  &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF) {

        if (add.acc_no == rem.acc_no) {
            test = 1;
            printf("\nAccount deleted successfully!\n");
        } else {
            fprintf(newrec, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d\n",
                    add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year,
                    add.age, add.address, add.citizenship, add.phone, add.acc_type,
                    add.amt, add.deposit.month, add.deposit.day, add.deposit.year);
        }
    }

    fclose(old);
    fclose(newrec);

    remove("record.dat");
    rename("new.dat", "record.dat");

    if (test != 1) {
        printf("Record not found!\n");
    }

    printf("\nEnter 1 to go to the main menu or 0 to exit: ");
    scanf("%d", &main_exit);
    if (main_exit == 1) {
        menu();
    } else {
        close_program();
    }
}

// Function to see account details
void see() {
    FILE *ptr = fopen("record.dat", "r");

    if (!ptr) {
        printf("Error opening file!\n");
        return;
    }

    int test = 0;
    int choice;
    printf("Do you want to check by\n1. Account no\n2. Name\nEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter the account number: ");
        scanf("%d", &check.acc_no);

        while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                      &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year,
                      &add.age, add.address, add.citizenship, &add.phone, add.acc_type,
                      &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF) {

            if (add.acc_no == check.acc_no) {
                test = 1;
                printf("\nAccount NO.: %d\nName: %s\nDOB: %d/%d/%d\nAge: %d\nAddress: %s\nCitizenship No: %s\nPhone number: %.0lf\nType Of Account: %s\nAmount deposited: $%.2f\nDate Of Deposit: %d/%d/%d\n", 
                    add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, 
                    add.age, add.address, add.citizenship, add.phone, add.acc_type, 
                    add.amt, add.deposit.month, add.deposit.day, add.deposit.year);

                if (strcmp(add.acc_type, "fixed1") == 0) {
                    printf("You will get $%.2f as interest on %d/%d/%d\n", 
                           interest(1.0, add.amt, 9), add.deposit.month, add.deposit.day, add.deposit.year + 1);
                } else if (strcmp(add.acc_type, "fixed2") == 0) {
                    printf("You will get $%.2f as interest on %d/%d/%d\n", 
                           interest(2.0, add.amt, 11), add.deposit.month, add.deposit.day, add.deposit.year + 2);
                } else if (strcmp(add.acc_type, "fixed3") == 0) {
                    printf("You will get $%.2f as interest on %d/%d/%d\n", 
                           interest(3.0, add.amt, 13), add.deposit.month, add.deposit.day, add.deposit.year + 3);
                } else if (strcmp(add.acc_type, "saving") == 0) {
                    printf("You will get $%.2f as interest on %d of every month\n", 
                           interest(1.0 / 12.0, add.amt, 8), add.deposit.day);
                }
            }
        }
    } else if (choice == 2) {
        printf("Enter the name: ");
        scanf("%s", check.name);

        while (fscanf(ptr, "%d %s %d/%d/%d %d %s %s %lf %s %f %d/%d/%d",
                      &add.acc_no, add.name, &add.dob.month, &add.dob.day, &add.dob.year,
                      &add.age, add.address, add.citizenship, &add.phone, add.acc_type,
                      &add.amt, &add.deposit.month, &add.deposit.day, &add.deposit.year) != EOF) {

            if (strcmp(add.name, check.name) == 0) {
                test = 1;
                printf("\nAccount NO.: %d\nName: %s\nDOB: %d/%d/%d\nAge: %d\nAddress: %s\nCitizenship No: %s\nPhone number: %.0lf\nType Of Account: %s\nAmount deposited: $%.2f\nDate Of Deposit: %d/%d/%d\n", 
                    add.acc_no, add.name, add.dob.month, add.dob.day, add.dob.year, 
                    add.age, add.address, add.citizenship, add.phone, add.acc_type, 
                    add.amt, add.deposit.month, add.deposit.day, add.deposit.year);

                if (strcmp(add.acc_type, "fixed1") == 0) {
                    printf("You will get $%.2f as interest on %d/%d/%d\n", 
                           interest(1.0, add.amt, 9), add.deposit.month, add.deposit.day, add.deposit.year + 1);
                } else if (strcmp(add.acc_type, "fixed2") == 0) {
                    printf("You will get $%.2f as interest on %d/%d/%d\n", 
                           interest(2.0, add.amt, 11), add.deposit.month, add.deposit.day, add.deposit.year + 2);
                } else if (strcmp(add.acc_type, "fixed3") == 0) {
                    printf("You will get $%.2f as interest on %d/%d/%d\n", 
                           interest(3.0, add.amt, 13), add.deposit.month, add.deposit.day, add.deposit.year + 3);
                } else if (strcmp(add.acc_type, "saving") == 0) {
                    printf("You will get $%.2f as interest on %d of every month\n", 
                           interest(1.0 / 12.0, add.amt, 8), add.deposit.day);
                }
            }
        }
    }

    fclose(ptr);

    if (test != 1) {
        printf("\nRecord not found!\n");
    }

    printf("\nEnter 1 to go to the main menu or 0 to exit: ");
    scanf("%d", &main_exit);
    if (main_exit == 1) {
        menu();
    } else {
        close_program();
    }
}

// Menu function
void menu() {
    system("cls");
    printf("\n\n\t\t\tCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM");
    printf("\n\n\t\t\t\t WELCOME TO THE MAIN MENU ");
    printf("\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\n\n\t\t\t\t 1.Create new account\n\t\t\t\t 2.Update information of existing account\n\t\t\t\t 3.For transactions\n\t\t\t\t 4.Check the details of existing account\n\t\t\t\t 5.Removing existing account\n\t\t\t\t 6.View customer's list\n\t\t\t\t 7.Exit\n\n\n\t\t\t\t Enter your choice: ");
    
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            new_acc();
            break;
        case 2:
            edit();
            break;
        case 3:
            transact();
            break;
        case 4:
            see();
            break;
        case 5:
            erase();
            break;
        case 6:
            view_list();
            break;
        case 7:
            close_program();
            break;
        default:
            printf("Invalid choice!\n");
            menu();
            break;
    }
}

// Function to close the program
void close_program() {
    printf("\n\n\t\t\tThank you for using the banking system!\n");
    exit(0);
}

int main() {
    system("cls");
    menu();
    return 0;
}
