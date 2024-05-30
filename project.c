#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int id;
    char name[50];
    float price;
    char category[20];
} MenuItem;

void signup();
void login();
void menu();
void takeOrder(MenuItem menu[], int size, const char *category);
void displayMenu(MenuItem menu[], int size, const char *category);
void selectCategoryAndOrder(MenuItem menu[], int size);
void reserveTable();
void collectFeedback();

int found1;
char username[100];

int main()
{
    system("color f1");
    int choice1,choice2;
    system("cls");
    printf("\t\t_______________\n");
    printf("\t\t|             |\n");
    printf("\t\t|_A_S_K_Grand_|\n");
    printf("\t\t|-------------|\n");
    printf("\t\t|*************|\n");
    printf("\t\t|/////////////|\n");
    printf("\t\t|    _____    |\n");
    printf("\t\t|    |   |    |\n");
    printf("\t\t|    |   |    |\n");
    printf("\t\t|-------------|\n");

    printf("\n\n\t****** WELCOME TO ASK Grand ******\n\n");
   printf("1. Signup\n2. Login\n3. Exit\nEnter your choice: ");
    scanf("%d",&choice1);

    switch (choice1)
    {
        case 1:
            signup();
            break;
        case 2:
            login();
            break;
        case 3:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice! Please try again.\n");
    }

        if (found1)
        {
        printf("\nHello %s...Welcome to ASK Grand.\n\n",username);
        printf("1. Display menu and Order Items\n2. Reserve Table\n3. Give Feedback\n4. Exit\nEnter your choice: ");

        scanf("%d",&choice2);
        switch(choice2)
         {

        case 1:
            menu();
            break;
        case 2:
            reserveTable();
            break;
        case 3:
            collectFeedback();
            break;
        case 4:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice Please try again.\n");

         }
    }
    else
        {
        printf("Invalid username or password.\n");
    }


}


void signup()
{
    char password[100];
    printf("Enter user name:");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    FILE *file = fopen("users.csv", "a");
    if (file == NULL) {
        printf("Could not open file %s for writing.\n", "users.csv");
        exit(1);
    }

    fprintf(file, "%s,%s\n", username, password);
    fclose(file);

    printf("Signup successful\n");
    exit(0);
}


void login()
{
    char password[100], file_username[100], file_password[100];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    FILE *file = fopen("users.csv", "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        exit(1);
    }

     found1 = 0;
    while (fscanf(file, "%[^,],%s\n", file_username, file_password) != EOF)
        {
        if (strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0)
            {
            found1 = 1;
            break;
        }
    }
    fclose(file);


}


void menu()
{
    printf("\n\t---Menu---\n");
    MenuItem menu[] =
    {
        {1, "Samosa", 11.50, "Starters"},
        {2, "Paneer Tikka", 18.00, "Starters"},
        {3, "Veg Cutlet", 20.00,"Starters"},
        {4, "Pav Bhaji",65.00,"Starters"},
        {5, "Mushroom 65",165.00,"Starters"},
        {6, "Gobi Manchuria",95.00,"Starters"},
        {7, "Egg Manchuria",65.00,"Starters"},
        {8, "Chicken Tandoori",265.00,"Starters"},
        {9, "Sheer Kebab",265.00,"Starters"},
        {10,"VEG starters combo",465.00,"Starters"},
        {11,"Non Veg starters combo",565.00,"Starters"},
        {12,"A.S.K special starters platter",865.00,"Starters"},

        {13, "Paneer Butter Masala", 200.00, "Main Course"},
        {14, "Kaju Butter Masala", 220.00, "Main Course"},
        {15, "Mushroom Masala", 260.00, "Main Course"},
        {16, "Dal makhani ", 200.00, "Main Course"},
        {17, "Butter Chicken", 200.00, "Main Course"},
        {18, "Biryani(veg)", 180.00, "Main Course"},
        {19, " Hyderbad dum Biryani ", 200.00, "Main course"},
        {20, "A.S.K special Biryani", 400.00, "Main course"},
        {21, "Nalli ka Gosh Biryani ", 500.00, "Main course"},
        {22, "Mutton Briyani ", 300.00, "Main course"},

        {23, "Gulab Jamun", 30.00, "Desserts"},
        {24, "Rasgulla", 25.50, "Desserts"},
        {25, "Ras Malai", 35.50, "Desserts"},
        {26, "Double ka Meeta", 65.50, "Desserts"},
        {27, "Matka Kulfi ", 45.50, "Desserts"},
        {28, "A.S.K SP Kheer", 75.50, "Desserts"},

        {29, "Badam Kheer", 75.50, "Drinks"},
        {30, "Rose milk", 65.50, "Drinks"},
        {31, "Sweet lassi", 55.50, "Drinks"},
        {32, "Lemonade", 45.50, "Drinks"},
        {33, "Body cooler", 55.50, "Drinks"},
        {34, "Tender coconut water ", 55.50, "Drinks"},
        {35, "Fresh Sugarcane Juice", 55.50, "Drinks"},
    };
    int menuSize = sizeof(menu) / sizeof(menu[0]);

    selectCategoryAndOrder(menu, menuSize);
}


void displayMenu(MenuItem menu[], int size, const char *category)
{
    printf("\n--- %s ---\n", category);
    for (int i = 0; i < size; i++)
    {
        if (strcmp(menu[i].category, category) == 0)
        {
            printf("%d. %s - %.2f Rs\n", menu[i].id, menu[i].name, menu[i].price);
        }
    }
}

void takeOrder(MenuItem menu[], int size, const char *category)
{
    int choice,quantity;
    float total;
    char more;

    printf("\n\t--- Take Order from %s ---\n", category);

    do {
        displayMenu(menu, size, category);

        printf("\nEnter the item number to order: ");
        scanf("%d", &choice);


        int found = 0;
        for (int i = 0; i < size; i++)
        {
            if (menu[i].id == choice && strcmp(menu[i].category, category) == 0)
           {
                found = 1;
                printf("\nEnter the quantity: ");
                scanf("%d", &quantity);
                total += menu[i].price * quantity;
                break;
            }
        }

        if (!found)
        {
            printf("Invalid item number. Please try again.\n");
            continue;
        }


        printf("\nDo you want to order another item from %s? (y/n): ", category);
        scanf(" %c", &more);

    }
    while (more == 'y' || more == 'Y');
    char a[15]={'L','o','a','d','i','n','g','.','.','.','.'};
  for(int i =0;i<5;i++)
    {
        printf("\r------------------\r");
        for(int j=0;j<=8;j++){
           printf("%c ",a[j]);
            usleep(300000);
        }

    }
    FILE *ptr = fopen("orders.csv", "a");
    if (ptr == NULL)
    {
        printf("\nCould not open file %s .\n", "orders.csv");
    }
    else
    {

    fprintf(ptr,"The Orders are Category:%s,Quantity:%d,Total amount:%.2f\n", category,quantity,total);
    fclose(ptr);
    printf("\n\nYour total bill for %s is: %.2f Rs\n", category, total);
    exit(0);
    }
}


void selectCategoryAndOrder(MenuItem menu[], int size)
{
    int choice;
    while (1)
    {
        printf("\n--- Select a Category ---\n");
        printf("1. Starters\n");
        printf("2. Main Course\n");
        printf("3. Desserts\n");
        printf("4. Drinks\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                takeOrder(menu, size, "Starters");
                break;
            case 2:
                takeOrder(menu, size, "Main Course");
                break;
            case 3:
                takeOrder(menu, size, "Desserts");
                break;
            case 4:
                takeOrder(menu, size, "Drinks");
                break;
            case 5:
                printf("Exiting...\n");
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void reserveTable()
{
    char name[20];
    int tab_no;
    int day;
    char month[10];
    int time;
    char am_pm[20];

    FILE *file = fopen("reserved.csv", "r");
    if (file == NULL)
    {
        printf("Could not open file %s for reading.\n", "reserved.csv");
    }
    else
    {
        printf("Currently booked tables:\n");
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            printf("%s", line);
        }
        fclose(file);
    }

    printf("Enter Your Name: ");
    scanf("%s", name);
    printf("Enter Table number (1 to 10): ");
    scanf("%d", &tab_no);
    printf("Enter Date and month (eg 20 may): ");
    scanf("%d %s", &day, month);
    printf("Enter Time (eg: 4 pm): ");
    scanf("%d %s", &time, am_pm);

    file = fopen("reserved.csv", "a");
    if (file == NULL) {
        printf("Could not open file %s for writing.\n", "reserved.csv");
    }
    else
    {
    fprintf(file, "Table %d was successfully reserved for %d %s on %s %d by %s.\n", tab_no, time, am_pm, month, day, name);
    fclose(file);
    printf("Table %d was successfully reserved for %d %s on %s %d by %s.\n", tab_no, time, am_pm, month, day, name);
    }
}

void collectFeedback()
{
    char feedback[500];
    printf("Enter your feedback: ");
    scanf(" %[^\n]", feedback);
    FILE *file = fopen("feedback.txt", "a");
    if (file == NULL)
    {
        printf("Could not open file %s for writing.\n", "feedback");

    }

    fprintf(file,"%s\n",feedback);
    fclose(file);

    printf("Thank you for your feedback!\n");
}








