#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>//random number
#include <unistd.h>
#include <conio.h>
#include <ctype.h> // Include this header for isalpha function

void sign_up();
void Residential_property_information_for_sale();
void mainmenu();
void Office_property_for_sale();
void Land_sales();
void Residential_property_for_rent();
void Office_property_for_rent();
void Land_rent();
void Rent_registration();
void Register_new_information();
void Sales_registration();
void account_setting();
void mainmenu();
void reports();
void report_residental_property_sale();
void report_residental_property_rent();
void report_residental_property();
void report_office_property_sale();
void report_office_property_rent();
void report_office_property();
void report_for_user();
void report_residentalsale_price();
void report_residentalsale_age();
void report_residentalsale_area();
void list_residentalsale();
void delet_residentalsale();
char username[40];

#define MAX_NUMBERS 9000 // 9000 possible 4-digit numbers

int generatedNumbers[MAX_NUMBERS];
int generatedCount = 0;

// Function to generate a random 4-digit number without repetition
int getRandomNumber() {
    if (generatedCount == MAX_NUMBERS) {
        printf("All 4-digit numbers have been generated.\n");
        exit(EXIT_SUCCESS); // or handle this case as needed
    }

    int randomNumber;
    srand(time(NULL));

    do {
        randomNumber = rand() % (9999 - 1000 + 1) + 1000;
    } while (isNumberGenerated(randomNumber));

    generatedNumbers[generatedCount++] = randomNumber;
    return randomNumber;
}

// Function to check if a 4-digit number has already been generated
int isNumberGenerated(int number) {
    for (int i = 0; i < generatedCount; i++) {
        if (generatedNumbers[i] == number) {
            return 1; // Number has already been generated
        }
    }
    return 0; // Number is not in the generatedNumbers array
}

int isAlphabetic(const char *str)
{
    while (*str) {
        if (!isalpha(*str)) {
            return 0;  // Not alphabetic
        }
        str++;
    }
    return 1;  // All characters are alphabetic
}

struct sign_upinfo
{
    char name[40];
    char lastname[40];
    char username[40];
    char national_code[11];
    char phonenumber[12];
    char Email[40];
    char password[40];
    struct sign_upinfo *next;
};
void sign_up()
{
    system("cls");
    struct sign_upinfo *next = malloc(sizeof(struct sign_upinfo));

    do {
        printf("Enter your name: ");
        scanf("%s", next->name);
        getchar();

        if (!isAlphabetic(next->name)) {
            printf("\e[31m Name should contain only alphabetic characters. Please try again.\e[m\n");
        }
    } while (!isAlphabetic(next->name));

    do {
        printf("Enter your lastname: ");
        scanf("%s", next->lastname);
        getchar();

        if (!isAlphabetic(next->lastname)) {
            printf("\e[31m Last name should contain only alphabetic characters. Please try again.\e[m\n");
        }
    } while (!isAlphabetic(next->lastname));


    printf("enter your username : ");
    scanf("%s", next->username);
    getchar();


    do {
        printf("Enter your 10-digit national code: ");
        scanf("%10s", next->national_code);
        getchar();

        if (strlen(next->national_code) != 10) {
            printf("\e[31m National code must be exactly 10 digits. Please try again.\e[m\n");
        }
    } while (strlen(next->national_code) != 10);


   do {
        printf("Enter your 11-digit phone number: ");
        scanf("%11s", next->phonenumber);
        getchar();

        if (strlen(next->phonenumber) != 11) {
            printf("\e[31m Phone number must be exactly 11 digits. Please try again.\e[m\n");
        }
    } while (strlen(next->phonenumber) != 11);


    printf("enter your Email : ");
    scanf("%s", next->Email);
    getchar();

      do {
        printf("Enter your password (at least 8 characters): ");
        scanf("%s", next->password);
        getchar();

        if (strlen(next->password) < 8) {
            printf("\e[31m Password must be at least 8 characters. Please try again.\e[m\n");
        }
    } while (strlen(next->password) < 8);

     char confirm_password[20];
    do {
        printf("Confirm your password: ");
        scanf("%s", confirm_password);
        getchar();

        if (strcmp(next->password, confirm_password) != 0) {
            printf("\e[31m Passwords do not match. Please try again.\e[m\n");
        }
    } while (strcmp(next->password, confirm_password) != 0);


    FILE *file;
    file = fopen("admin_information.txt", "a");
    if (file == NULL)
    {
        printf("eror oppening file");
    }
    fprintf(file , "%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
            next->name,
            next->lastname,
            next->username,
            next->national_code,
            next->phonenumber,
            next->Email,
            next->password);

    printf("\e[32m signup successfully...\e[m");
    sleep(3);
    main();
    fclose(file);
}
int sign_in()
{
    system("cls");
    char inputusername[40];
    char inputpassword[40];

    printf("username :\n");
    scanf("%39s", inputusername);
    getchar();

    printf("password :\n");
    scanf("%39s", inputpassword);
    getchar();

    FILE *file;
    file = fopen("admin_information.txt", "r");
    if (file == NULL)
    {
        perror("error opening file");
        return 0;
    }

    struct sign_upinfo *first = NULL, *last = NULL, *temp;

    while ((temp = malloc(sizeof(struct sign_upinfo))) != NULL &&
           fscanf(file, "%39s\n%39s\n%39s\n%39s\n%39s\n%39s\n%39s\n",
                  temp->name,
                  temp->lastname,
                  temp->username,
                  temp->national_code,
                  temp->phonenumber,
                  temp->Email,
                  temp->password) == 7)
    {
        temp->next = NULL;
        if (first == NULL)
        {
            first = temp;
            last = first;
        }
        else
        {
            last->next = temp;
            last = temp;
        }
    }

    fclose(file);

    temp = first;
    while (temp != NULL)
    {
        if (strcmp(inputusername, temp->username) == 0 && strcmp(inputpassword, temp->password) == 0)
        {
            strcpy(username, temp->username);
            printf("\e[32m sign in successfully\e[m");
            sleep(1);
            free_list(first);
            return 1; // Return 1 to indicate successful login
        }
        temp = temp->next;
    }

    free_list(first);

    printf("password or username is wrong!\n");
    return 0; // This is often used to indicate that the login was unsuccessful
}
void free_list(struct sign_upinfo *first)
{
    struct sign_upinfo *temp;
    while (first != NULL)
    {
        temp = first->next;
        free(first);
        first = temp;
    }
}
struct Residential_property_information_for_sale  //اطلاعات ملک مسکونی فروشی
{
    char Municipal_area[20];//ناحیه شهرداری
    char Exact_address[1000];
    char Property_Type[20];
    char Age_of_the_property[20];
    char Size_of_the_infrastructure[20];//زیر بنا
    char Floor[20];
    char Size_of_the_main_land[20];
    char number_of_the_owner[20];
    char Number_of_bedrooms[20];
    char Price[20];
    int  ID;
    int  active;
    struct Residential_property_information_for_sale* next;

};
void Residential_property_information_for_sale()
 {
    system("cls");
    struct Residential_property_information_for_sale *next = malloc(sizeof(struct Residential_property_information_for_sale));

    if (next == NULL) {
        printf("[MEMORY ALLOCATION FAILED]");
        exit(1);
    }

    FILE *file;
    file = fopen("residentalpropertysale.txt", "a+");
    if (file == NULL) {
        printf("Error opening the file");
        exit(1);
    }
    printf("Enter the Municipal area:");
    scanf(" %[^\n]",next->Municipal_area);
    getchar();

    printf("\nEnter the Exact address:(use '-' or '_' instead of space)");
    scanf(" %[^\n]", next->Exact_address);//The %[^\n] format specifier in scanf is used to read a string until a newline character (\n) is encountered
    getchar();

    printf("\nthe Property Type if its Apprtment enter 1 if its villa enter 2:");
    scanf(" %[^\n]",next->Property_Type);
    getchar();

    printf("\nEnter the Age of the property:");
    scanf(" %[^\n]",next->Age_of_the_property);
    getchar();

    printf("\nEnter the Size of the infrastructure:");
    scanf(" %[^\n]",next->Size_of_the_infrastructure);
    getchar();

    printf("\nEnter the Floor:");
    scanf(" %[^\n]",next->Floor);
    getchar();

    printf("\nEnter the Size of the main land:");
    scanf(" %[^\n]",next->Size_of_the_main_land);
    getchar();

    printf("\nEnter Phone number of the owner:");
    scanf(" %[^\n]",next->number_of_the_owner);
    getchar();

    printf("\nEnter the Number of bedrooms:");
    scanf(" %[^\n]",next->Number_of_bedrooms);
    getchar();


    printf("\nEnter the Price:\n");
    scanf(" %[^\n]",next->Price);
    getchar();

    next->active = 1;

    next->ID = getRandomNumber();
    printf("\033[0;34mYour residential ID is: %d\n \e[m", next->ID);

    fprintf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
            next->Municipal_area,
            next->Exact_address,
            next->Property_Type,
            next->Age_of_the_property,
            next->Size_of_the_infrastructure,
            next->Floor,
            next->Size_of_the_main_land,
            next->number_of_the_owner,
            next->Number_of_bedrooms,
            next->Price,
            next->ID,
            next->active);
    printf("\n\e[32mYour information has been successfully registered...\e[m\n");

    fclose(file);
    free(next);
     while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            Sales_registration();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
//اطلاعات ملک اداری فروشی
struct Office_property_information_for_sale
{
    char Municipal_area[20];
    char Exact_address[300];
    char Property_Type[20];
    char Age_of_the_property[20];
    char Size_of_the_infrastructure[20];//زیر بنا
    char Floor[20];
    char Size_of_the_main_land[20];
    char number_of_the_owner[20];
    char Number_of_office_rooms[20];
    char Price[20];
    int ID;
    int active;
    struct Office_property_information_for_sale *next;
};
void Office_property_for_sale()
{
    system("cls");
    struct Office_property_information_for_sale *next = malloc(sizeof(struct Office_property_information_for_sale));
if (next == NULL)
{
    printf("[MEMORY ALLOCATION FAILED]\n");
    exit(1);
}
FILE *file;
file = fopen("officepropartysale.txt", "a+");
if (file == NULL)
{
    printf("\n[ERROR OPENING FILE]");
    exit(1);
}
printf("Enter the Municipal area:\n");
scanf("%s",next->Municipal_area);
getchar();


printf("Enter the Exact address:\n");
scanf("%s",next->Exact_address);
getchar();

printf("Enter the Property Type\n(\033[0;33mEnter 1 if it has an official administrative document and\nenter 2 if it only has an administrative position\e[m\n):");
//سند رسمیِ اداری، یا فقط موقعیت اداری
scanf("%s",next->Property_Type);
getchar();


printf("Enter the Age of the property:\n");
scanf("%s",next->Age_of_the_property);
getchar();


printf("Enter the Size of the infrastructure:\n");
scanf("%s",next->Size_of_the_infrastructure);
getchar();


printf("Enter the Floor:\n");
scanf("%s",next->Floor);
getchar();


printf("Enter the Size of the main land:\n");
scanf("%s",next->Size_of_the_main_land);
getchar();


printf("Enter Phone number of the owner:\n");
scanf("%s",next->number_of_the_owner);
getchar();


printf("Enter the Number of bedrooms:\n");
scanf("%s",next->Number_of_office_rooms);
getchar();


printf("Enter the Price:\n");
scanf("%s",next->Price);
getchar();

next->active = 1;
next->ID = getRandomNumber();
printf("\033[0;34mYour OFFICE ID is: %d\n\e[m", next->ID);

fprintf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
              next->Municipal_area,
              next->Exact_address,
              next->Property_Type,
              next->Age_of_the_property,
              next->Size_of_the_infrastructure,
              next->Floor,
              next->Size_of_the_main_land,
              next->number_of_the_owner,
              next->Number_of_office_rooms,
              next->Price,
              next->ID,
              next->active);

printf("\e[32mYour information has been successfully registered...\e[m");
fclose(file);
free(next);
 while(1)
    {
        printf("\nPlease enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            Sales_registration();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
//اطلاعات زمین فروشی
struct Land_sales_information
{
    char Municipal_area[20];
    char Exact_address[300];
    char land_Type[20];
    char Size_of_the_land[20];
    char number_of_the_owner[20];
    char Price[20];
    int ID;
    int active;
    struct Land_sales_information *next;
};
void Land_sales()
{
system("cls");
struct Land_sales_information *next;
next = malloc(sizeof(struct Land_sales_information));
if(next ==  NULL)
{
    printf("[MEMORY ALLOCATION FAILED]\n");
    exit(0);
}
FILE *file;
file = fopen("landsale.txt", "a+");
if (file == NULL)
{
    printf("[EROR OPENING FILE]");
    exit(0);
}
printf("Enter the Municipal area:\n ");
scanf("%s",next->Municipal_area);
getchar();

printf("Enter the Exact address:\n ");
fgets(next->Exact_address, sizeof(next->Exact_address), stdin);
next->Exact_address[strcspn(next->Exact_address, "\n")] = '\0';

printf("Enter the land Type \n(if its Agricultural enter 1 if its urban enter 2): ");
fgets(next->land_Type, sizeof(next->land_Type), stdin);
next->land_Type[strcspn(next->land_Type, "\n")] = '\0';

printf("Enter the Size of the land:\n ");
fgets(next->Size_of_the_land, sizeof(next->Size_of_the_land), stdin);
next->Size_of_the_land[strcspn(next->Size_of_the_land, "\n")] = '\0';

printf("Enter Phone number of the owner:\n ");
fgets(next->number_of_the_owner, sizeof(next->number_of_the_owner), stdin);
next->number_of_the_owner[strcspn(next->number_of_the_owner, "\n")] = '\0';

printf("Enter the Price:\n ");
fgets(next->Price, sizeof(next->Price), stdin);
next->Price[strcspn(next->Price, "\n")] = '\0';


next->active = 1;
next->ID = getRandomNumber();
printf("Your LAND ID is: %d\n", next->ID);
// Writing to the file
fprintf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
        next->Municipal_area,
        next->Exact_address,
        next->land_Type,
        next->Size_of_the_land,
        next->number_of_the_owner,
        next->Price,
        next->ID,
        next->active);

fclose(file);
free(next);

printf("\n\e[32mYour information has been successfully registered...\e[m\n");

while(1)
    {
        printf("\nPlease enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            Sales_registration();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
//اطلاعات ملک مسکونی اجاره ای
struct Residential_property_information_for_rent
{
    char Municipal_area[20];
    char Exact_address[300];
    char Property_Type[10];
    char Age_of_the_property[20];
    char Size_of_the_infrastructure[20];//زیر بنا
    char Floor[20];
    char Size_of_the_main_land[20];
    char number_of_the_owner[20];
    char Number_of_bedrooms[20];
    char mortgage[20];//رهن
    char Rent[20];//اجاره
    int ID;
    int active;
    struct Residential_property_information_for_rent *next;

};
void Residential_property_for_rent()
{
    system("cls");

    struct Residential_property_information_for_rent *next;
    next = malloc(sizeof(struct Residential_property_information_for_rent));

    if (next == NULL)
    {
        printf("[MEMORY ALLOCATION FAILED]\n");
        exit(0);
    }

    FILE *file;
    file = fopen("residentalpropertyrent.txt", "a+");

    if (file == NULL)
    {
        perror("ERROR OPENING FILE");
        exit(0);
    }

printf("Enter the Municipal area:\n ");
scanf("%s", next->Municipal_area);
getchar();

printf("\nEnter the Exact address:\n ");
scanf(" %[^\n]", next->Exact_address);
getchar();

printf("\nEnter the Property Type\033[0;33m(if it's apartment enter 1 if it's villa enter 2):\e[m\n");
scanf(" %[^\n]", next->Property_Type);
getchar();

printf("\nEnter the Age of the property:\n ");
scanf(" %[^\n]", next->Age_of_the_property);
getchar();

printf("\nEnter the Size of the infrastructure:\n ");
scanf(" %[^\n]", next->Size_of_the_infrastructure);
getchar();

printf("\nEnter the Floor:\n ");
scanf(" %[^\n]", next->Floor);
getchar();

printf("\nEnter the Size of the main land:\n ");
scanf(" %[^\n]", next->Size_of_the_main_land);
getchar();

printf("\nEnter Phone number of the owner:\n ");
scanf(" %[^\n]", next->number_of_the_owner);
getchar();

printf("\nEnter the Number of bedrooms:\n ");
scanf(" %[^\n]", next->Number_of_bedrooms);
getchar();

printf("\nEnter the mortgage:\n ");
scanf(" %[^\n]", next->mortgage);
getchar();

printf("\nEnter the amount of rent:\n ");
scanf(" %[^\n]", next->Rent);
getchar();

    next->active = 1;
    next->ID = getRandomNumber();
    printf("Your residential ID is: %d\n", next->ID);

    // Write information to the file
     fprintf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
            next->Municipal_area,
            next->Exact_address,
            next->Property_Type,
            next->Age_of_the_property,
            next->Size_of_the_infrastructure,
            next->Floor,
            next->Size_of_the_main_land,
            next->number_of_the_owner,
            next->Number_of_bedrooms,
            next->mortgage,
            next->Rent,
            next->ID,
            next->active);

    fclose(file);
    free(next);

    printf("\n\e[32mYour information has been successfully registered...\e[m\n");
    sleep(2);

    while (1)
    {
        system("cls");
        printf("Please enter your choice:\n");
        printf("1 - Back to the Previous menu\n");
        printf("2 - Clear screen\n");
        printf("3 - Exit\n");

        int choice;
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            Rent_registration();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}


//اطلاعات ملک اداری اجاره ای
struct Office_property_information_for_rent
{
    char Municipal_area[20];
    char Exact_address[300];
    char Property_Type[20];
    char Age_of_the_property[20];
    char Size_of_the_infrastructure[20];//زیر بنا
    char Floor[20];
    char Size_of_the_main_land[20];
    char number_of_the_owner[20];
    char Number_of_office_rooms[20];
    char mortgage[20];//رهن
    char Rent[20];//اجاره
    int ID;
    int active;
    struct Office_property_information_for_rent *next;
};
void Office_property_for_rent()
{
    system("cls");
    struct Office_property_information_for_rent *next;
    next = malloc(sizeof(struct Office_property_information_for_rent));
    if(next ==  NULL)
    {
        printf("[MEMORY ALLOCATION FAILED]\n");
        exit(0);
    }
    FILE *file;
    file = fopen("officepropertyrent.txt", "a+");
    if (file == NULL)
    {
        perror("EROR OPENING FILE");
        exit(0);
    }
printf("Enter the Municipal area:\n");
scanf("%s", next->Municipal_area);
getchar();

printf("Enter the Exact address:\n");
scanf("%s", next->Exact_address);
getchar();

printf("Enter the Property Type\n\033[0;33m(Enter 1 if it has an official administrative document and enter 2 if it only has an administrative position):\e[m");
scanf("%s", next->Property_Type);
getchar();

printf("\nEnter the Age of the property:\n");
scanf("%s", next->Age_of_the_property);
getchar();

printf("Enter the Size of the infrastructure:\n");
scanf("%s", next->Size_of_the_infrastructure);
getchar();

printf("Enter the Floor:\n");
scanf("%s", next->Floor);
getchar();

printf("Enter the Size of the main land:\n");
scanf("%s", next->Size_of_the_main_land);
getchar();

printf("Enter Phone number of the owner:\n");
scanf("%s", next->number_of_the_owner);
getchar();

printf("Enter the Number of rooms:\n");
scanf("%s", next->Number_of_office_rooms);
getchar();

printf("Enter the mortgage:\n");
scanf("%s", next->mortgage);
getchar();

printf("Enter the Rent:\n");
scanf("%s", next->Rent);
getchar();

    next->active = 1;
    next->ID = getRandomNumber();
    printf("Your OFFICE ID is: %d\n", next->ID);

    fprintf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
            next->Municipal_area,
            next->Exact_address,
            next->Property_Type,
            next->Age_of_the_property,
            next->Size_of_the_infrastructure,
            next->Floor,
            next->Size_of_the_main_land,
            next->number_of_the_owner,
            next->Number_of_office_rooms,
            next->mortgage,
            next->Rent,
            next->ID,
            next->active);

    fclose(file);
    free(next);
    printf("\n\e[32mYour information has been successfully registered...\e[m\n");
    while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            Rent_registration();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }

}

//اطلاعات زمین اجاره ای
struct Land_rent_information
{
    char Municipal_area[20];
    char Exact_address[300];
    char land_Type[20];
    char Size_of_the_land[20];
    char number_of_the_owner[20];
    char mortgage[20];//رهن
    char Rent[20];//اجاره
    int ID;
    int active;
    struct Land_rent_information *next;
};
void Land_rent()
{
system("cls");
struct Land_rent_information *next;
next = malloc(sizeof(struct Land_rent_information));
if(next == NULL)
{
    printf("[MEMORY ALLOCATION FAILED]\n");
    exit(0);
}

FILE *file;
file = fopen("landrent.txt", "a+");
if (file == NULL)
{
    printf("MEMORY ALLOCATION FAILED");
    exit(0);
}

printf("Enter the Municipal area:\n");
fgets(next->Municipal_area, sizeof(next->Municipal_area), stdin);
next->Municipal_area[strcspn(next->Municipal_area, "\n")] = '\0';

printf("Enter the Exact address:\n");
fgets(next->Exact_address, sizeof(next->Exact_address), stdin);
next->Exact_address[strcspn(next->Exact_address, "\n")] = '\0';

printf("Enter the Property Type(if its Agricultural enter 1 or if its urban enter 2):\n");
fgets(next->land_Type, sizeof(next->land_Type), stdin);
next->land_Type[strcspn(next->land_Type, "\n")] = '\0';

printf("Enter the Size of the land:\n");
fgets(next->Size_of_the_land, sizeof(next->Size_of_the_land), stdin);
next->Size_of_the_land[strcspn(next->Size_of_the_land, "\n")] = '\0';

printf("Enter Phone number of the owner:\n");
fgets(next->number_of_the_owner, sizeof(next->number_of_the_owner), stdin);
next->number_of_the_owner[strcspn(next->number_of_the_owner, "\n")] = '\0';

printf("Enter the mortgage:\n");
fgets(next->mortgage, sizeof(next->mortgage), stdin);
next->mortgage[strcspn(next->mortgage, "\n")] = '\0';

printf("Enter the Rent:\n");
fgets(next->Rent, sizeof(next->Rent), stdin);
next->Rent[strcspn(next->Rent, "\n")] = '\0';

next->active = 1;
next->ID = getRandomNumber();
printf("Your OFFICE ID is: %d\n", next->ID);

fprintf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
        next->Municipal_area,
        next->Exact_address,
        next->land_Type,
        next->Size_of_the_land,
        next->number_of_the_owner,
        next->mortgage,
        next->Rent,
        next->ID,
        next->active);

printf("\n");
printf("\e[32mYour information has been successfully registered...\e[m");
fclose(file);
free(next);

 while(1)
    {
        printf("\nPlease enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            Rent_registration();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }


}
void Rent_registration()
{
    system("cls");
    int choice4;
    printf("Enter your choice:\n1-Registration of rental residential property");
    printf("\n2-Registration of rental office property\n3-Registration of rental land property\n4-Back to the previous menu\n");
    scanf("%d", &choice4);
    getchar();
    switch (choice4)
    {
    case 1:
        Residential_property_for_rent();
        break;
    case 2:
        Office_property_for_rent();
        break;
    case 3:
        Land_rent();
        break;
    case 4:
        Register_new_information();
        break;

    }
}

void Register_new_information()
{
    system("cls");
    int choice_sales_or_rent;
    printf("Please Enter Your Choice:\n");
    printf("1. Sales registration\n");//فروش
    printf("2. Rent registration\n");//احاره
    printf("3. Back to the previous menu\n\n");

    scanf("%d", &choice_sales_or_rent);
    getchar();

    switch (choice_sales_or_rent)
    {
    case 1:
        Sales_registration();
        break;
    case 2:
        Rent_registration();
        break;
    case 3:
        mainmenu();
        break;
    }
}
void Sales_registration()
{
    system("cls");
    int choice3;
    printf("enter your choice :\n");
    printf("1. Registration for the sale of residential property\n");//ملک مسکونی فروشی
    printf("2. Registration for the sale of office property\n");//اداری فروشی
    printf("3. Registration for the sale of land\n");//زمین فروشی
    printf("4. Back to the previous menu\n");
    scanf("%d", &choice3);
    switch(choice3)
    {
    case 1:
        Residential_property_information_for_sale();
        break;
    case 2:
        Office_property_for_sale();
        break;
    case 3:
        Land_sales();
        break;
    case 4:
        Register_new_information();
        break;
    }
}
void account_setting()
{
system("cls");
    FILE *file;
    file = fopen("admin_information.txt", "r");

}

void report_residentalsale_bedrooms()
 {
    system("cls");
    int b_room;
    int property_count = 1;
    FILE* file;
    file = fopen("residentalpropertysale.txt", "r");
    struct Residential_property_information_for_sale* first = NULL, *last = NULL, *temp2;

    if (file == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    printf("Enter the number of bedrooms in the residential property in question\n");
    scanf("%d", &b_room);
    getchar();

    struct Residential_property_information_for_sale* temp = malloc(sizeof(struct Residential_property_information_for_sale));

    while (1) {
       struct Residential_property_information_for_sale* temp = malloc(sizeof(struct Residential_property_information_for_sale));

        if (fscanf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                   temp->Municipal_area,
                   temp->Exact_address,
                   temp->Property_Type,
                   temp->Age_of_the_property,
                   temp->Size_of_the_infrastructure,
                   temp->Floor,
                   temp->Size_of_the_main_land,
                   temp->number_of_the_owner,
                   temp->Number_of_bedrooms,
                   temp->Price,
                   &temp->ID,
                   &temp->active) != 12)
        {
            break;
        }

        if (first == NULL) {
            first = temp;
            last = first;
            last->next = NULL;
        } else {
            last->next = temp;
            last = temp;
            last->next = NULL;
        }
    }

    temp2 = first;
    while (temp2 != NULL) {
        if (atoi(temp2->Number_of_bedrooms) == b_room && temp2->active == 1) {
            printf("%d. RESIDENTIAL PROPERTY:\n", property_count);
            printf("Municipal area:             %s\n", temp2->Municipal_area);
            printf("Address:                    %s\n", temp2->Exact_address);
            printf("Age of the property:        %s\n", temp2->Age_of_the_property);
            printf("Floor:                      %s\n", temp2->Floor);
            printf("Size of the infrastructure: %s\n", temp2->Size_of_the_infrastructure);
            printf("Size of the main land:      %s\n", temp2->Size_of_the_main_land);
            printf("Phone Number:               %s\n", temp2->number_of_the_owner);
            printf("Bedroom:                    %s\n", temp2->Number_of_bedrooms);
            printf("Price:                      %s\n", temp2->Price);
            if(strcmp(temp2->Property_Type , "1") == 0)
           {
             printf("Property Type:              apartment\n");
           }
            else if(strcmp(temp2->Property_Type , "2") == 0)
            {
             printf("property Type:              Villa\n");
            }
            property_count++;
            printf("\033[0;35m********************************************************************\e[m\n");
        }
        temp2 = temp2->next;
    }

    fclose(file);

    // Free allocated memory
    temp = first;
    while (temp != NULL)
    {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }

    if (property_count == 1)
    {
       printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
       sleep(1);
       printf("1-Try another amount of bedrooms :\n2-Exit:\n");
       int choice;
       scanf("%d",&choice);
       switch (choice)
       {
       case 1:
        report_residentalsale_bedrooms();
        break;
       case 2:
        exit(1);
        break;
       }
    }

    while (1) {
        printf("Please enter your choice:\n");
        printf("1 - Back to Previous menu\n");
        printf("2 - Clear screen\n");
        printf("3 - Exit\n");
        int choice;
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                report_residental_property_sale();
                break;
            case 2:
                system("cls");
                break;
            case 3:
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
void report_residentalsale_price()
{
    system("cls");
    int price1[40];
    int price2[40];
    int property_count = 1;
    FILE *file;
    file = fopen("residentalpropertysale.txt", "r");
    struct Residential_property_information_for_sale *first=NULL, *last=NULL;
    struct Residential_property_information_for_sale *temp2;

    if (file == NULL)
    {
        printf("eror opening file");
        exit(1);
    }
    printf("\nEnter the lowest price you will pay to buy a house:\n");
    scanf("%s",price1);
    getchar();
    printf("Enter the highest cost of buying a house:\n");
    scanf("%s",price2);
    getchar();



            struct Residential_property_information_for_sale *temp = malloc(sizeof(struct Residential_property_information_for_sale));
    while(1)
    {
        struct Residential_property_information_for_sale *temp = malloc(sizeof(struct Residential_property_information_for_sale));
       if (fscanf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                   temp->Municipal_area,
                   temp->Exact_address,
                   temp->Property_Type,
                   temp->Age_of_the_property,
                   temp->Size_of_the_infrastructure,
                   temp->Floor,
                   temp->Size_of_the_main_land,
                   temp->number_of_the_owner,
                   temp->Number_of_bedrooms,
                   temp->Price,
                   &temp->ID,
                   &temp->active) != 12)
        {
            break;
        }

        if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next=temp;
            last = temp;
            last->next=NULL;
        }
    }
    temp2 = first;
    while (temp2 != NULL)
    {
        if (atoi(temp2->Price) >= atoi(price1) && atoi(temp2->Price) <= atoi(price2) && temp2->active == 1)
        {
            printf("%d. RESIDENTIAL PROPERTY:\n", property_count);
            printf("Municipal area:             %s\n", temp2->Municipal_area);
            printf("Address:                    %s\n", temp2->Exact_address);
            printf("Age of the property:        %s\n", temp2->Age_of_the_property);
            printf("Floor:                      %s\n", temp2->Floor);
            printf("Size of the infrastructure: %s\n", temp2->Size_of_the_infrastructure);
            printf("Size of the main land:      %s\n", temp2->Size_of_the_main_land);
            printf("Phone Number:               %s\n", temp2->number_of_the_owner);
            printf("Bedroom:                    %s\n", temp2->Number_of_bedrooms);
            printf("Price:                      %s\n", temp2->Price);
            if(strcmp(temp2->Property_Type , "1") == 0)
           {
             printf("Property Type:              apartment\n");
           }
            else if(strcmp(temp2->Property_Type , "2") == 0)
            {
             printf("property Type:              Villa\n");
            }
            property_count++;
            printf("\033[0;35m********************************************************************\e[m\n");
        }
        temp2=temp2->next;
    }
    fclose(file);
    temp = first;
    while (temp != NULL)
    {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
    if ( property_count == 1)
    {
       printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
       sleep(1);
       printf("1-Try another price :\n2-Exit:\n");
       int choice;
       scanf("%d",&choice);
       switch (choice)
       {
       case 1:
        report_residentalsale_price();
        break;
       case 2:
        exit(1);
        break;
       }

    }
    while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_residental_property_sale();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }


}
void report_residentalsale_age()
{
   system("cls");
   int age1;
   int age2;
   int property_count=1;
   FILE *file;
   file = fopen("residentalpropertysale.txt" , "r");
   struct Residential_property_information_for_sale *first=NULL ,*last=NULL;
   if (file == NULL)
   {
       printf("EROR OPRNING FILE");
       exit(1);
   }
   printf("How many years do you want the residential property to be built at least?:\n");
   scanf("%d",&age1);
   getchar();

   printf("How many years do you want the residential property to be built for maximum?:\n");
   scanf("%d",&age2);
   getchar();

     struct Residential_property_information_for_sale *temp = malloc(sizeof(struct Residential_property_information_for_sale));
    while(1)
    {
        struct Residential_property_information_for_sale *temp = malloc(sizeof(struct Residential_property_information_for_sale));
        if (fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                   temp->Municipal_area,
                   temp->Exact_address,
                   temp->Property_Type,
                   temp->Age_of_the_property,
                   temp->Size_of_the_infrastructure,
                   temp->Floor,
                   temp->Size_of_the_main_land,
                   temp->number_of_the_owner,
                   temp->Number_of_bedrooms,
                   temp->Price,
                   &temp->ID,
                   &temp->active)!=12)
        {
            break;
        }
        if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next=temp;
            last = temp;
            last->next=NULL;
        }
    }
    struct Residential_property_information_for_sale *temp2 = first;
    while (temp2 != NULL)
    {
        if (atoi(temp2->Age_of_the_property) >= age1 && atoi(temp2->Age_of_the_property) <= age2 && temp2->active == 1)

           {
            printf("%d. RESIDENTIAL PROPERTY:\n", property_count);
            printf("Municipal area:             %s\n", temp2->Municipal_area);
            printf("Address:                    %s\n", temp2->Exact_address);
            printf("Age of the property:        %s\n", temp2->Age_of_the_property);
            printf("Floor:                      %s\n", temp2->Floor);
            printf("Size of the infrastructure: %s\n", temp2->Size_of_the_infrastructure);
            printf("Size of the main land:      %s\n", temp2->Size_of_the_main_land);
            printf("Phone Number:               %s\n", temp2->number_of_the_owner);
            printf("Bedroom:                    %s\n", temp2->Number_of_bedrooms);
            printf("Price:                      %s\n", temp2->Price);
            if(strcmp(temp2->Property_Type , "1") == 0)
           {
             printf("Property Type:              apartment\n");
           }
            else if(strcmp(temp2->Property_Type , "2") == 0)
            {
             printf("property Type:              Villa\n");
            }
            property_count++;
            printf("\033[0;35m********************************************************************\e[m\n");
           }
            temp2=temp2->next;
       }
       fclose(file);
       temp=first;
       while(temp != NULL)
       {
           temp2=temp->next;
           free(temp);
           temp=temp2;
       }
       if (property_count==1)
       {
        printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
       sleep(1);
       printf("1-Try another age :\n2-Exit:\n");
       int choice;
       scanf("%d",&choice);
       switch (choice)
       {
       case 1:
        report_residentalsale_age();
        break;
       case 2:
        exit(1);
        break;
       }
       }
       while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_residental_property_sale();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }


}
void report_residentalsale_infrastructure()
{
  system("cls");
  int infrastructure1;
  int infrastructure2;
  int property_count=1;
  FILE *file;
  file = fopen("residentalpropertysale.txt" , "r");
  struct Residential_property_information_for_sale *first=NULL ,*last=NULL;
   if (file == NULL)
   {
       printf("EROR OPRNING FILE");
       exit(1);
   }
   struct Residential_property_information_for_sale *temp= malloc(sizeof(struct Residential_property_information_for_sale));
   while(1)
    {
        struct Residential_property_information_for_sale *temp = malloc(sizeof(struct Residential_property_information_for_sale));
       if (fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                   temp->Municipal_area,
                   temp->Exact_address,
                   temp->Property_Type,
                   temp->Age_of_the_property,
                   temp->Size_of_the_infrastructure,
                   temp->Floor,
                   temp->Size_of_the_main_land,
                   temp->number_of_the_owner,
                   temp->Number_of_bedrooms,
                   temp->Price,
                   &temp->ID,
                   &temp->active)!=12)
        {
            break;
        }
        if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next=temp;
            last = temp;
            last->next=NULL;
        }
    }
    printf("please enter the minimum infrastructure of the desired residential property :\n");
    scanf("%d" ,&infrastructure1);
    getchar();

    printf("please enter the maximum infrastructure of the desired residential property :\n");
    scanf("%d",&infrastructure2);
    getchar();

    struct Residential_property_information_for_sale*temp2 = first;

    while (temp2 != NULL)
    {
        if(atoi(temp2->Size_of_the_infrastructure)>=infrastructure1
           && atoi(temp2->Size_of_the_infrastructure)<=infrastructure2
           && temp2->active == 1)
        {
            printf("%d. RESIDENTIAL PROPERTY:\n", property_count);
            printf("Municipal area:             %s\n", temp2->Municipal_area);
            printf("Address:                    %s\n", temp2->Exact_address);
            printf("Age of the property:        %s\n", temp2->Age_of_the_property);
            printf("Floor:                      %s\n", temp2->Floor);
            printf("Size of the infrastructure: %s\n", temp2->Size_of_the_infrastructure);
            printf("Size of the main land:      %s\n", temp2->Size_of_the_main_land);
            printf("Phone Number:               %s\n", temp2->number_of_the_owner);
            printf("Bedroom:                    %s\n", temp2->Number_of_bedrooms);
            printf("Price:                      %s\n", temp2->Price);
            if(strcmp(temp2->Property_Type , "1") == 0)
           {
             printf("Property Type:              apartment\n");
           }
            else if(strcmp(temp2->Property_Type , "2") == 0)
            {
             printf("property Type:              Villa\n");
            }
            property_count++;
            printf("\033[0;35m********************************************************************\e[m\n");
           }
         temp2=temp2->next;
}
       fclose(file);
       temp=first;
       while(temp != NULL)
       {
           temp2=temp->next;
           free(temp);
           temp=temp2;
       }
       if (property_count == 1)
       {
        printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
       sleep(1);
       printf("1-Try another infrastructure:\n2-Exit:\n");
       int choice;
       scanf("%d",&choice);
       switch (choice)
       {
       case 1:
        report_residentalsale_infrastructure();
        break;
       case 2:
        exit(1);
        break;
       }
       }
       while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_residental_property_sale();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_residentalsale_Municipality()
{
  system("cls");
  int municipality;
  int property_count=1;
  FILE *file;
  file = fopen("residentalpropertysale.txt" , "r");
  struct Residential_property_information_for_sale *first=NULL ,*last=NULL;
   if (file == NULL)
   {
       printf("EROR OPRNING FILE");
       exit(1);
   }
   struct Residential_property_information_for_sale *temp= malloc(sizeof(struct Residential_property_information_for_sale));
   while(1)
    {
        struct Residential_property_information_for_sale *temp = malloc(sizeof(struct Residential_property_information_for_sale));
         if (fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                   temp->Municipal_area,
                   temp->Exact_address,
                   temp->Property_Type,
                   temp->Age_of_the_property,
                   temp->Size_of_the_infrastructure,
                   temp->Floor,
                   temp->Size_of_the_main_land,
                   temp->number_of_the_owner,
                   temp->Number_of_bedrooms,
                   temp->Price,
                   &temp->ID,
                   &temp->active)!=12)
        {
            break;
        }
        if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next=temp;
            last = temp;
            last->next=NULL;
        }
    }
    printf("Enter the desired municipality to buy a residential property:\n");
    scanf("%d" ,&municipality);
    getchar();
    struct Residential_property_information_for_sale *temp2 = first;

    while (temp2 != NULL)
    {
        if(municipality == atoi(temp2->Municipal_area) && temp2->active == 1)
        {
            printf("%d. RESIDENTIAL PROPERTY:\n", property_count);
            printf("Municipal area:             %s\n", temp2->Municipal_area);
            printf("Address:                    %s\n", temp2->Exact_address);
            printf("Age of the property:        %s\n", temp2->Age_of_the_property);
            printf("Floor:                      %s\n", temp2->Floor);
            printf("Size of the infrastructure: %s\n", temp2->Size_of_the_infrastructure);
            printf("Size of the main land:      %s\n", temp2->Size_of_the_main_land);
            printf("Phone Number:               %s\n", temp2->number_of_the_owner);
            printf("Bedroom:                    %s\n", temp2->Number_of_bedrooms);
            printf("Price:                      %s\n", temp2->Price);
            if(strcmp(temp2->Property_Type , "1") == 0)
           {
             printf("Property Type:              apartment\n");
           }
            else if(strcmp(temp2->Property_Type , "2") == 0)
            {
             printf("property Type:              Villa\n");
            }
            property_count++;
            printf("\033[0;35m********************************************************************\e[m\n");
           }
         temp2=temp2->next;
}
       fclose(file);
       //free allocated memory
       temp=first;
       while(temp != NULL)
       {
           temp2=temp->next;
           free(temp);
           temp=temp2;
       }
       if (property_count==1)
       {
       printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
       sleep(1);
       printf("1-Try another municipality:\n2-Exit:\n");
       int choice;
       scanf("%d",&choice);
       switch (choice)
       {
       case 1:
        report_residentalsale_Municipality();
        break;
       case 2:
        exit(1);
        break;
       }
       }
       while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_residental_property_sale();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_residentalsale_floor()
{
   system("cls");
  int floor;
  int property_count=1;
  FILE *file;
  file = fopen("residentalpropertysale.txt" , "r");
  struct Residential_property_information_for_sale *first=NULL ,*last=NULL;
   if (file == NULL)
   {
       printf("EROR OPRNING FILE");
       exit(1);
   }
   struct Residential_property_information_for_sale *temp= malloc(sizeof(struct Residential_property_information_for_sale));
   while(1)
    {
        struct Residential_property_information_for_sale *temp = malloc(sizeof(struct Residential_property_information_for_sale));
       if (fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                   temp->Municipal_area,
                   temp->Exact_address,
                   temp->Property_Type,
                   temp->Age_of_the_property,
                   temp->Size_of_the_infrastructure,
                   temp->Floor,
                   temp->Size_of_the_main_land,
                   temp->number_of_the_owner,
                   temp->Number_of_bedrooms,
                   temp->Price,
                   &temp->ID,
                   &temp->active)!=12)
        {
            break;
        }
        if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next=temp;
            last = temp;
            last->next=NULL;
        }
    }
    printf("Enter the desired floor to buy a residential property:\n");
    scanf("%d" ,&floor);
    getchar();

    struct Residential_property_information_for_sale *temp2 = first;

    while (temp2 != NULL)
    {
        if(floor == atoi(temp2->Floor) && temp2->active)
        {
            printf("%d. RESIDENTIAL PROPERTY:\n", property_count);
            printf("Municipal area:             %s\n", temp2->Municipal_area);
            printf("Address:                    %s\n", temp2->Exact_address);
            printf("Age of the property:        %s\n", temp2->Age_of_the_property);
            printf("Floor:                      %s\n", temp2->Floor);
            printf("Size of the infrastructure: %s\n", temp2->Size_of_the_infrastructure);
            printf("Size of the main land:      %s\n", temp2->Size_of_the_main_land);
            printf("Phone Number:               %s\n", temp2->number_of_the_owner);
            printf("Bedroom:                    %s\n", temp2->Number_of_bedrooms);
            printf("Price:                      %s\n", temp2->Price);
            if(strcmp(temp2->Property_Type , "1") == 0)
           {
             printf("Property Type:              apartment\n");
           }
            else if(strcmp(temp2->Property_Type , "2") == 0)
            {
             printf("property Type:              Villa\n");
            }
            property_count++;
            printf("\033[0;35m********************************************************************\e[m\n");
           }
         temp2=temp2->next;
}
       fclose(file);
       //free allocated memory
       temp=first;
       while(temp != NULL)
       {
           temp2=temp->next;
           free(temp);
           temp=temp2;
       }
       if (property_count==1)
       {
       printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
       sleep(1);
       printf("1-Try another floor:\n2-Exit:\n");
       int choice;
       scanf("%d",&choice);
       switch (choice)
       {
       case 1:
        report_residentalsale_floor();
        break;
       case 2:
        exit(1);
        break;
       }
       }
       while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_residental_property_sale();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_residental_property_sale()
{
    system("cls");
    printf("According to which invoice do you want to get a report?\n");
    printf("1-according to price\n2-according to the Age of construction\n3-according to The size of the infrastructure\n");
    printf("4-according to the Regional Municipality\n");//منطقه شهرداری
    printf("5-according to number of bedrooms\n6-according to floor\n7-list all of them\n8-back to previous menu\n9-clear screen\n10-exit\n");
    int choice6;
    scanf("%d",&choice6);
    getchar();
    switch (choice6)
    {
    case 1:
        report_residentalsale_price();
        break;
    case 2:
        report_residentalsale_age();
        break;
    case 3:
        report_residentalsale_infrastructure();
        break;
    case 4:
        report_residentalsale_Municipality();
        break;
    case 5:
        report_residentalsale_bedrooms();
        break;
    case 6:
        report_residentalsale_floor();
        break;
    case 7:
        list_residentalsale();
        break;
    case 8:
        report_residental_property();
        break;
    case 9:
        system("cls");
        break;
    case 10:
        exit(0);
        break;
    }
}

void report_residentalrent_rent()
{
 system("cls");
 int c = 1;
 int rent1;
 int rent2;
 int mortgage1;
 int mortgage2;
    printf("enter the minimum mortgage you can pay :\n");
    scanf("%d",&mortgage1);
    getchar();

    printf("enter the maximum mortgage you can pay :\n");
    scanf("%d",&mortgage2);
    getchar();

    printf("enter the minimum rent you can pay:\n");
    scanf("%d",&rent1);
    getchar();

    printf("enter the maximum rent you can pay:\n");
    scanf("%d",&rent2);
    getchar();

 FILE *file;
 file = fopen("residentalpropertyrent.txt" , "r");
 struct Residential_property_information_for_rent *first=NULL , *last=NULL;

 if (file == NULL)
 {
     printf("EROR OPENING FILE");
     exit(1);
 }
 struct Residential_property_information_for_rent *temp = malloc(sizeof(struct Residential_property_information_for_rent));
 while(1)
 {
      struct Residential_property_information_for_rent *temp = malloc(sizeof(struct Residential_property_information_for_rent));
      if (fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d",
                 temp->Municipal_area,
                 temp->Exact_address,
                 temp->Property_Type,
                 temp->Age_of_the_property,
                 temp->Size_of_the_infrastructure,
                 temp->Floor,
                 temp->Size_of_the_main_land,
                 temp->number_of_the_owner,
                 temp->Number_of_bedrooms,
                 temp->mortgage,
                 temp->Rent,
                 &temp->ID,
                 &temp->active)!=13)
      {
          break;
      }
      if (first == NULL)
      {
          first=temp;
          last=first;
          last->next=NULL;
      }
      else
      {
          last->next=temp;
          last=temp;
          last->next=NULL;
      }
    }

    struct Residential_property_information_for_rent *temp2 = first;

    while(temp2 != NULL)
    {
        if (atoi(temp2->mortgage)>=mortgage1 && atoi(temp2->mortgage)<=mortgage2
             && atoi(temp2->Rent)>=rent1 && atoi(temp2->Rent)<=rent2
            && temp2->active == 1)
        {
            printf("%d.RESIDENTAL PROPERTY:\n",c);
            printf("municipialarea:            %s\n",temp2->Municipal_area);
            printf("exact address:             %s\n",temp2->Exact_address);
               if(strcmp(temp2->Property_Type , "1") == 0)
           {
             printf("Property Type:              apartment\n");
           }
            else if(strcmp(temp2->Property_Type , "2") == 0)
            {
             printf("property Type:              Villa\n");
            }
            printf("age of the property:       %s\n",temp2->Age_of_the_property);
            printf("infrastructure:            %s\n",temp2->Size_of_the_infrastructure);
            printf("floor:                     %s\n",temp2->Floor);
            printf("Size of mainland:          %s\n",temp2->Size_of_the_main_land);
            printf("number of owner:           %s\n",temp2->number_of_the_owner);
            printf("bedrooms:                  %s\n",temp2->Number_of_bedrooms);
            printf("mortgage:                  %s\n",temp2->mortgage);
            printf("Rent:                      %s\n",temp2->Rent);
            c++;
            printf("\033[0;35m********************************************************************\e[m\n");
        }
        temp2=temp2->next;
    }
    fclose(file);
    //free allocated memory
    temp=first;
    while(temp!=NULL)
    {
        temp2=temp->next;
        free(temp);
        temp=temp2;
    }
    if(c==1)
    {
        printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
        exit(1);
    }

 while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_residentalrent_rent();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_residentalrent_age()
{
 system("cls");
 int c=1;
 int age1;
 int age2;

 printf("enter the minimum age:\n");
 scanf("%d",&age1);
 getchar();

 printf("enter the maximum age:\n");
 scanf("%d",&age2);
 getchar();

 FILE *file;
 file = fopen("residentalpropertyrent.txt" , "r");
 struct Residential_property_information_for_rent *first=NULL , *last=NULL;

 if (file == NULL)
 {
     printf("EROR OPENING FILE");
     exit(1);
 }
 struct Residential_property_information_for_rent *temp = malloc(sizeof(struct Residential_property_information_for_rent));
 while(1)
 {
      struct Residential_property_information_for_rent *temp = malloc(sizeof(struct Residential_property_information_for_rent));
       if (fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d",
                 temp->Municipal_area,
                 temp->Exact_address,
                 temp->Property_Type,
                 temp->Age_of_the_property,
                 temp->Size_of_the_infrastructure,
                 temp->Floor,
                 temp->Size_of_the_main_land,
                 temp->number_of_the_owner,
                 temp->Number_of_bedrooms,
                 temp->mortgage,
                 temp->Rent,
                 &temp->ID,
                 &temp->active)!=13)
      {
          break;
      }
      if (first == NULL)
      {
          first=temp;
          last=first;
          last->next=NULL;
      }
      else
      {
          last->next=temp;
          last=temp;
          last->next=NULL;
      }
    }

    struct Residential_property_information_for_rent *temp2 = first;

    while(temp2 != NULL)
    {
        if (atoi(temp2->Age_of_the_property)>=age1 &&
             atoi(temp2->Age_of_the_property)<=age2
            && temp2->active == 1)
        {
            printf("%d.RESIDENTAL PROPERTY:\n",c);
            printf("municipialarea:            %s\n",temp2->Municipal_area);
            printf("exact address:             %s\n",temp2->Exact_address);
               if(strcmp(temp2->Property_Type , "1") == 0)
           {
             printf("Property Type:              apartment\n");
           }
            else if(strcmp(temp2->Property_Type , "2") == 0)
            {
             printf("property Type:              Villa\n");
            }
            printf("age of the property:       %s\n",temp2->Age_of_the_property);
            printf("infrastructure:            %s\n",temp2->Size_of_the_infrastructure);
            printf("floor:                     %s\n",temp2->Floor);
            printf("Size of mainland:          %s\n",temp2->Size_of_the_main_land);
            printf("number of owner:           %s\n",temp2->number_of_the_owner);
            printf("bedrooms:                  %s\n",temp2->Number_of_bedrooms);
            printf("mortgage:                  %s\n",temp2->mortgage);
            printf("Rent:                      %s\n",temp2->Rent);
            c++;
            printf("\033[0;35m********************************************************************\e[m\n");

        }
        temp2=temp2->next;
    }
    fclose(file);
    //free allocated memory
    temp=first;
    while(temp!=NULL)
    {
        temp2=temp->next;
        free(temp);
        temp=temp2;
    }
    if(c==1)
    {
        printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
        exit(1);
    }

 while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_residentalrent_rent();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_residentalrent_infrastructure()
{
  system("cls");
 int c=1;
 int infrastructure1;
 int infrastructure2;

 printf("minimum infrastructure of desired residental:\n");
 scanf("%d",&infrastructure1);
 getchar();

 printf("maximum infrastructure of desired residental:\n");
 scanf("%d",&infrastructure2);
 getchar();

 FILE *file;
 file = fopen("residentalpropertyrent.txt" , "r");
 struct Residential_property_information_for_rent *first=NULL , *last=NULL;

 if (file == NULL)
 {
     printf("EROR OPENING FILE");
     exit(1);
 }
 struct Residential_property_information_for_rent *temp = malloc(sizeof(struct Residential_property_information_for_rent));
 while(1)
 {
      struct Residential_property_information_for_rent *temp = malloc(sizeof(struct Residential_property_information_for_rent));
       if (fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d",
                 temp->Municipal_area,
                 temp->Exact_address,
                 temp->Property_Type,
                 temp->Age_of_the_property,
                 temp->Size_of_the_infrastructure,
                 temp->Floor,
                 temp->Size_of_the_main_land,
                 temp->number_of_the_owner,
                 temp->Number_of_bedrooms,
                 temp->mortgage,
                 temp->Rent,
                 &temp->ID,
                 &temp->active)!=13)
      {
          break;
      }
      if (first == NULL)
      {
          first=temp;
          last=first;
          last->next=NULL;
      }
      else
      {
          last->next=temp;
          last=temp;
          last->next=NULL;
      }
    }

    struct Residential_property_information_for_rent *temp2 = first;

    while(temp2 != NULL)
    {
        if (atoi(temp2->Size_of_the_infrastructure)>=infrastructure1 &&
             atoi(temp2->Size_of_the_infrastructure)<=infrastructure2 &&
            temp2->active == 1)
        {
            printf("%d.RESIDENTAL PROPERTY:\n",c);
            printf("municipialarea:            %s\n",temp2->Municipal_area);
            printf("exact address:             %s\n",temp2->Exact_address);
               if(strcmp(temp2->Property_Type , "1") == 0)
           {
             printf("Property Type:              apartment\n");
           }
            else if(strcmp(temp2->Property_Type , "2") == 0)
            {
             printf("property Type:              Villa\n");
            }
            printf("age of the property:       %s\n",temp2->Age_of_the_property);
            printf("infrastructure:            %s\n",temp2->Size_of_the_infrastructure);
            printf("floor:                     %s\n",temp2->Floor);
            printf("Size of mainland:          %s\n",temp2->Size_of_the_main_land);
            printf("number of owner:           %s\n",temp2->number_of_the_owner);
            printf("bedrooms:                  %s\n",temp2->Number_of_bedrooms);
            printf("mortgage:                  %s\n",temp2->mortgage);
            printf("Rent:                      %s\n",temp2->Rent);
            c++;
            printf("\033[0;35m********************************************************************\e[m\n");
        }
        temp2=temp2->next;
    }
    fclose(file);
    //free allocated memory
    temp=first;
    while(temp!=NULL)
    {
        temp2=temp->next;
        free(temp);
        temp=temp2;
    }
    if(c==1)
    {
        printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
        exit(1);
    }

 while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_residentalrent_rent();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_residentalrent_Municipality()
{
 system("cls");
 int c=1;
 int Municipality;


 printf("in wich Municipality you wanna rent a residental:\n");
 scanf("%d",&Municipality);
 getchar();

 FILE *file;
 file = fopen("residentalpropertyrent.txt" , "r");
 struct Residential_property_information_for_rent *first=NULL , *last=NULL;

 if (file == NULL)
 {
     printf("EROR OPENING FILE");
     exit(1);
 }
 struct Residential_property_information_for_rent *temp = malloc(sizeof(struct Residential_property_information_for_rent));
 while(1)
 {
      struct Residential_property_information_for_rent *temp = malloc(sizeof(struct Residential_property_information_for_rent));
       if (fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d",
                 temp->Municipal_area,
                 temp->Exact_address,
                 temp->Property_Type,
                 temp->Age_of_the_property,
                 temp->Size_of_the_infrastructure,
                 temp->Floor,
                 temp->Size_of_the_main_land,
                 temp->number_of_the_owner,
                 temp->Number_of_bedrooms,
                 temp->mortgage,
                 temp->Rent,
                 &temp->ID,
                 &temp->active)!=13)
      {
          break;
      }
      if (first == NULL)
      {
          first=temp;
          last=first;
          last->next=NULL;
      }
      else
      {
          last->next=temp;
          last=temp;
          last->next=NULL;
      }
    }

    struct Residential_property_information_for_rent *temp2 = first;

    while(temp2 != NULL)
    {
        if (atoi(temp2->Municipal_area) == Municipality
            && temp2->active == 1)
        {
            printf("%d.RESIDENTAL PROPERTY:\n",c);
            printf("municipialarea:            %s\n",temp2->Municipal_area);
            printf("exact address:             %s\n",temp2->Exact_address);
               if(strcmp(temp2->Property_Type , "1") == 0)
           {
             printf("Property Type:              apartment\n");
           }
            else if(strcmp(temp2->Property_Type , "2") == 0)
            {
             printf("property Type:              Villa\n");
            }
            printf("age of the property:       %s\n",temp2->Age_of_the_property);
            printf("infrastructure:            %s\n",temp2->Size_of_the_infrastructure);
            printf("floor:                     %s\n",temp2->Floor);
            printf("Size of mainland:          %s\n",temp2->Size_of_the_main_land);
            printf("number of owner:           %s\n",temp2->number_of_the_owner);
            printf("bedrooms:                  %s\n",temp2->Number_of_bedrooms);
            printf("mortgage:                  %s\n",temp2->mortgage);
            printf("Rent:                      %s\n",temp2->Rent);
            c++;
            printf("\033[0;35m********************************************************************\e[m\n");
        }
        temp2=temp2->next;
    }
    fclose(file);
    //free allocated memory
    temp=first;
    while(temp!=NULL)
    {
        temp2=temp->next;
        free(temp);
        temp=temp2;
    }
    if(c==1)
    {
        printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
        exit(1);
    }

 while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_residentalrent_rent();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_residentalrent_bedrooms()
{
  system("cls");
 int c=1;
 int bedroom;


 printf("how many bedroom you want a desired house to have:\n");
 scanf("%d",&bedroom);
 getchar();

 FILE *file;
 file = fopen("residentalpropertyrent.txt" , "r");
 struct Residential_property_information_for_rent *first=NULL , *last=NULL;

 if (file == NULL)
 {
     printf("EROR OPENING FILE");
     exit(1);
 }
 struct Residential_property_information_for_rent *temp = malloc(sizeof(struct Residential_property_information_for_rent));
 while(1)
 {
      struct Residential_property_information_for_rent *temp = malloc(sizeof(struct Residential_property_information_for_rent));
     if (fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d",
                 temp->Municipal_area,
                 temp->Exact_address,
                 temp->Property_Type,
                 temp->Age_of_the_property,
                 temp->Size_of_the_infrastructure,
                 temp->Floor,
                 temp->Size_of_the_main_land,
                 temp->number_of_the_owner,
                 temp->Number_of_bedrooms,
                 temp->mortgage,
                 temp->Rent,
                 &temp->ID,
                 &temp->active)!=13)
      {
          break;
      }
      if (first == NULL)
      {
          first=temp;
          last=first;
          last->next=NULL;
      }
      else
      {
          last->next=temp;
          last=temp;
          last->next=NULL;
      }
    }

    struct Residential_property_information_for_rent *temp2 = first;

    while(temp2 != NULL)
    {
        if (atoi(temp2->Number_of_bedrooms) == bedroom &&
            temp2->active == 1)
        {
            printf("%d.RESIDENTAL PROPERTY:\n",c);
            printf("municipialarea:            %s\n",temp2->Municipal_area);
            printf("exact address:             %s\n",temp2->Exact_address);
               if(strcmp(temp2->Property_Type , "1") == 0)
           {
             printf("Property Type:              apartment\n");
           }
            else if(strcmp(temp2->Property_Type , "2") == 0)
            {
             printf("property Type:              Villa\n");
            }
            printf("age of the property:       %s\n",temp2->Age_of_the_property);
            printf("infrastructure:            %s\n",temp2->Size_of_the_infrastructure);
            printf("floor:                     %s\n",temp2->Floor);
            printf("Size of mainland:          %s\n",temp2->Size_of_the_main_land);
            printf("number of owner:           %s\n",temp2->number_of_the_owner);
            printf("bedrooms:                  %s\n",temp2->Number_of_bedrooms);
            printf("mortgage:                  %s\n",temp2->mortgage);
            printf("Rent:                      %s\n",temp2->Rent);
            c++;
            printf("\033[0;35m********************************************************************\e[m\n");
        }
        temp2=temp2->next;
    }
    fclose(file);
    //free allocated memory
    temp=first;
    while(temp!=NULL)
    {
        temp2=temp->next;
        free(temp);
        temp=temp2;
    }
    if(c==1)
    {
        printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
        exit(1);
    }

 while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_residentalrent_rent();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_residentalrent_floor()
{
   system("cls");
 int c=1;
 int floor;


 printf("in wich floor you wanna rent a house:\n");
 scanf("%d",&floor);
 getchar();

 FILE *file;
 file = fopen("residentalpropertyrent.txt" , "r");
 struct Residential_property_information_for_rent *first=NULL , *last=NULL;

 if (file == NULL)
 {
     printf("EROR OPENING FILE");
     exit(1);
 }
 struct Residential_property_information_for_rent *temp = malloc(sizeof(struct Residential_property_information_for_rent));
 while(1)
 {
      struct Residential_property_information_for_rent *temp = malloc(sizeof(struct Residential_property_information_for_rent));
      if (fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d",
                 temp->Municipal_area,
                 temp->Exact_address,
                 temp->Property_Type,
                 temp->Age_of_the_property,
                 temp->Size_of_the_infrastructure,
                 temp->Floor,
                 temp->Size_of_the_main_land,
                 temp->number_of_the_owner,
                 temp->Number_of_bedrooms,
                 temp->mortgage,
                 temp->Rent,
                 &temp->ID,
                 &temp->active)!=13)
      {
          break;
      }
      if (first == NULL)
      {
          first=temp;
          last=first;
          last->next=NULL;
      }
      else
      {
          last->next=temp;
          last=temp;
          last->next=NULL;
      }
    }

    struct Residential_property_information_for_rent *temp2 = first;

    while(temp2 != NULL)
    {
        if (atoi(temp2->Floor) == floor && temp2->active == 1)
        {
            printf("%d.RESIDENTAL PROPERTY:\n",c);
            printf("municipialarea:            %s\n",temp2->Municipal_area);
            printf("exact address:             %s\n",temp2->Exact_address);
               if(strcmp(temp2->Property_Type , "1") == 0)
           {
             printf("Property Type:              apartment\n");
           }
            else if(strcmp(temp2->Property_Type , "2") == 0)
            {
             printf("property Type:              Villa\n");
            }
            printf("age of the property:       %s\n",temp2->Age_of_the_property);
            printf("infrastructure:            %s\n",temp2->Size_of_the_infrastructure);
            printf("floor:                     %s\n",temp2->Floor);
            printf("Size of mainland:          %s\n",temp2->Size_of_the_main_land);
            printf("number of owner:           %s\n",temp2->number_of_the_owner);
            printf("bedrooms:                  %s\n",temp2->Number_of_bedrooms);
            printf("mortgage:                  %s\n",temp2->mortgage);
            printf("Rent:                      %s\n",temp2->Rent);
            c++;
            printf("\033[0;35m********************************************************************\e[m\n");
        }
        temp2=temp2->next;
    }
    fclose(file);
    //free allocated memory
    temp=first;
    while(temp!=NULL)
    {
        temp2=temp->next;
        free(temp);
        temp=temp2;
    }
    if(c==1)
    {
        printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
        exit(1);
    }

 while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_residentalrent_rent();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_residental_property_rent()
{
    system("cls");
    printf("According to which invoice do you want to get a report?\n");
    printf("1-according to rent&mortgage\n2-according to the Age of construction\n3-according to The infrastructure\n");
    printf("4-according to the Regional Municipality\n");//منطقه شهرداری
    printf("5-according to number of bedrooms\n6-according to floor\n7-list all of them\n8-back to previous menu\n9-clear screen\n10-exit\n");
    int choice6;
    scanf("%d",&choice6);
    getchar();
    switch (choice6)
    {
    case 1:
        report_residentalrent_rent();
        break;
    case 2:
        report_residentalrent_age();
        break;
    case 3:
        report_residentalrent_infrastructure();
        break;
    case 4:
        report_residentalrent_Municipality();
        break;
    case 5:
        report_residentalrent_bedrooms();
        break;
    case 6:
        report_residentalrent_floor();
        break;
    case 7:
        list_residentalrent();
        break;
    case 8:
        report_residental_property();
        break;
    case 9:
        system("cls");
        break;
    case 10:
        exit(0);
        break;
    }
}

void report_residental_property()
{
    system("cls");
    printf("What kind of residential property are you looking for?");
    printf("\n1-residental sale\n2-residental rent\n3-back to previous menu\n4-clear the screen\n5-exit\n");
    int choice6;
    scanf("%d",&choice6);
    switch (choice6)
    {
    case 1:
        report_residental_property_sale();
        break;
    case 2:
        report_residental_property_rent();
        break;
    case 3:
        report_for_user();
        break;
    case 4:
        system("cls");
        break;
    case 5:
        exit(1);
        break;

    }
}
void report_office_sale_price()
{
    system("cls");
    int price1;
    int price2;
    int c=1;
    FILE *file;
    file = fopen("officepropartysale.txt" ,"r");
    struct Office_property_information_for_sale *first=NULL ,*last=NULL ,*temp2;
    if (file == NULL)
    {
        printf("EROR OPPENING FILE");
        exit(1);
    }
    printf("enter The least amount you want to spend to buy office");
    scanf("%d",&price1);
    getchar();

    printf("enter The maximum amount you want to spend to buy office");
    scanf("%d",&price2);
    getchar();

    struct Office_property_information_for_sale *temp = malloc(sizeof(struct Office_property_information_for_sale));

    while(1)
    {
      struct Office_property_information_for_sale *temp = malloc(sizeof(struct Office_property_information_for_sale));
      if(fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
              temp->Municipal_area,
              temp->Exact_address,
              temp->Property_Type,
              temp->Age_of_the_property,
              temp->Size_of_the_infrastructure,
              temp->Floor,
              temp->Size_of_the_main_land,
              temp->number_of_the_owner,
              temp->Number_of_office_rooms,
              temp->Price,
              &temp->ID,
              &temp->active)!=12)
      {
          break;
      }
        if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next=temp;
            last = temp;
            last->next=NULL;
        }
    }
    temp2=first;
    while(temp2 != NULL)
    {
        if(atoi(temp2->Price)>=price1 && atoi(temp2->Price)<=price2 &&
           temp2->active == 1)
        {
            printf("%d.office PROPERTY:\n"       , c);
            printf("Municipalarea:           %s\n",temp2->Municipal_area);
            printf("Exactaddress:            %s\n",temp2->Exact_address);
             if(strcmp(temp2->Property_Type , "1") == 0)
           {
             printf("Property Type:              official administrative document\n");
           }
            else if(strcmp(temp2->Property_Type , "2") == 0)
            {
             printf("property Type:              administrative position\n");
            }
            printf("Age of the property:     %s\n",temp2->Age_of_the_property);
            printf("infrastructure:          %s\n",temp2->Size_of_the_infrastructure);
            printf("floor:                   %s\n",temp2->Floor);
            printf("Size of the main land:   %s\n",temp2->Size_of_the_main_land);
            printf("number of the owner:     %s\n",temp2->number_of_the_owner);
            printf("Number of office rooms:  %s\n",temp2->Number_of_office_rooms);
            printf("Price:                   %s\n",temp2->Price);
            c++;
            printf("\033[0;35m********************************************************************\e[m\n");
        }
     temp2=temp2->next;
    }
    fclose(file);
    temp = first;
    while (temp != NULL)
    {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
    if ( c == 1)
    {
       printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
       exit(0);
    }
    while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_office_property_sale();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_office_sale_age()
{
   system("cls");
    int age1;
    int age2;
    int c=1;
    FILE *file;
    file = fopen("officepropartysale.txt" ,"r");
    struct Office_property_information_for_sale *first=NULL ,*last=NULL ,*temp2;
    if (file == NULL)
    {
        printf("EROR OPPENING FILE");
        exit(1);
    }
    printf("Do you want the desired office to be built for at least how many years?");
    scanf("%d",&age1);
    getchar();

    printf("How many years do you want the desired office to be built at most?");
    scanf("%d",&age2);
    getchar();

    struct Office_property_information_for_sale *temp = malloc(sizeof(struct Office_property_information_for_sale));

    while(1)
    {
      struct Office_property_information_for_sale *temp = malloc(sizeof(struct Office_property_information_for_sale));
            if(fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
              temp->Municipal_area,
              temp->Exact_address,
              temp->Property_Type,
              temp->Age_of_the_property,
              temp->Size_of_the_infrastructure,
              temp->Floor,
              temp->Size_of_the_main_land,
              temp->number_of_the_owner,
              temp->Number_of_office_rooms,
              temp->Price,
              &temp->ID,
              &temp->active)!=12)
      {
          break;
      }
        if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next=temp;
            last = temp;
            last->next=NULL;
        }
    }
    temp2=first;
    while(temp2 != NULL)
    {
        if(atoi(temp2->Age_of_the_property)>=age1 &&
           atoi(temp2->Age_of_the_property)<=age2
           && temp2->active == 1)
        {
            printf("%d.office PROPERTY:\n"       , c);
            printf("Municipalarea:           %s\n",temp2->Municipal_area);
            printf("Exactaddress:            %s\n",temp2->Exact_address);
             if(strcmp(temp2->Property_Type , "1") == 0)
           {
             printf("Property Type:              official administrative\n");
           }
            else if(strcmp(temp2->Property_Type , "2") == 0)
            {
             printf("property Type:              administrative position\n");
            }
            printf("Age of the property:     %s\n",temp2->Age_of_the_property);
            printf("infrastructure:          %s\n",temp2->Size_of_the_infrastructure);
            printf("floor:                   %s\n",temp2->Floor);
            printf("Size of the main land:   %s\n",temp2->Size_of_the_main_land);
            printf("number of the owner:     %s\n",temp2->number_of_the_owner);
            printf("Number of office rooms:  %s\n",temp2->Number_of_office_rooms);
            printf("Price:                   %s\n",temp2->Price);
            c++;
            printf("\033[0;35m********************************************************************\e[m\n");
        }
     temp2=temp2->next;
    }
    fclose(file);
    temp = first;
    while (temp != NULL)
    {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
    if ( c == 1)
    {
       printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
       exit(0);
    }
    while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_office_property_sale();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_office_sale_infrastructure()
{
    system("cls");
    int infrastructure1;
    int infrastructure2;
    int c=1;
    FILE *file;
    file = fopen("officepropartysale.txt" ,"r");
    struct Office_property_information_for_sale *first=NULL ,*last=NULL ,*temp2;
    if (file == NULL)
    {
        printf("EROR OPPENING FILE");
        exit(1);
    }
    printf("What is the minimum infrastructure of the office you want?");
    scanf("%d",&infrastructure1);
    getchar();

    printf("What is the maximum infrastructure of the desired office?");
    scanf("%d",&infrastructure2);
    getchar();

    struct Office_property_information_for_sale *temp = malloc(sizeof(struct Office_property_information_for_sale));

    while(1)
    {
      struct Office_property_information_for_sale *temp = malloc(sizeof(struct Office_property_information_for_sale));
           if(fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
              temp->Municipal_area,
              temp->Exact_address,
              temp->Property_Type,
              temp->Age_of_the_property,
              temp->Size_of_the_infrastructure,
              temp->Floor,
              temp->Size_of_the_main_land,
              temp->number_of_the_owner,
              temp->Number_of_office_rooms,
              temp->Price,
              &temp->ID,
              &temp->active)!=12)
      {
          break;
      }
        if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next=temp;
            last = temp;
            last->next=NULL;
        }
    }
    temp2=first;
    while(temp2 != NULL)
    {
        if(atoi(temp2->Size_of_the_infrastructure)>=infrastructure1 &&
            atoi(temp2->Size_of_the_infrastructure)<=infrastructure2
           && temp2->active == 1)
        {
            printf("%d.office PROPERTY:\n"       , c);
            printf("Municipalarea:           %s\n",temp2->Municipal_area);
            printf("Exactaddress:            %s\n",temp2->Exact_address);
             if(strcmp(temp2->Property_Type , "1") == 0)
           {
             printf("Property Type:              official administrative\n");
           }
            else if(strcmp(temp2->Property_Type , "2") == 0)
            {
             printf("property Type:              administrative position\n");
            }
            printf("Age of the property:     %s\n",temp2->Age_of_the_property);
            printf("infrastructure:          %s\n",temp2->Size_of_the_infrastructure);
            printf("floor:                   %s\n",temp2->Floor);
            printf("Size of the main land:   %s\n",temp2->Size_of_the_main_land);
            printf("number of the owner:     %s\n",temp2->number_of_the_owner);
            printf("Number of office rooms:  %s\n",temp2->Number_of_office_rooms);
            printf("Price:                   %s\n",temp2->Price);
            c++;
            printf("\033[0;35m********************************************************************\e[m\n");
        }
     temp2=temp2->next;
    }
    fclose(file);
    temp = first;
    while (temp != NULL)
    {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
    if ( c == 1)
    {
       printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
       exit(0);
    }
    while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_office_property_sale();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_office_sale_Municipality()
{
     system("cls");
    int Municipality;
    int c=1;
    FILE *file;
    file = fopen("officepropartysale.txt" ,"r");
    struct Office_property_information_for_sale *first=NULL ,*last=NULL ,*temp2;
    if (file == NULL)
    {
        printf("EROR OPPENING FILE");
        exit(1);
    }
    printf("In which municipal do you want the desired office to be?");
    scanf("%d",&Municipality);
    getchar();

    struct Office_property_information_for_sale *temp = malloc(sizeof(struct Office_property_information_for_sale));

    while(1)
    {
      struct Office_property_information_for_sale *temp = malloc(sizeof(struct Office_property_information_for_sale));
            if(fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
              temp->Municipal_area,
              temp->Exact_address,
              temp->Property_Type,
              temp->Age_of_the_property,
              temp->Size_of_the_infrastructure,
              temp->Floor,
              temp->Size_of_the_main_land,
              temp->number_of_the_owner,
              temp->Number_of_office_rooms,
              temp->Price,
              &temp->ID,
              &temp->active)!=12)
      {
          break;
      }
        if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next=temp;
            last = temp;
            last->next=NULL;
        }
    }
    temp2=first;
    while(temp2 != NULL)
    {
        if(atoi(temp2->Municipal_area) == Municipality
           && temp2->active == 1)
        {
            printf("%d.office PROPERTY:\n"       , c);
            printf("Municipalarea:           %s\n",temp2->Municipal_area);
            printf("Exactaddress:            %s\n",temp2->Exact_address);
              if(strcmp(temp2->Property_Type , "1") == 0)
           {
             printf("Property Type:              official administrative\n");
           }
            else if(strcmp(temp2->Property_Type , "2") == 0)
            {
             printf("property Type:              administrative position\n");
            }
            printf("Age of the property:     %s\n",temp2->Age_of_the_property);
            printf("infrastructure:          %s\n",temp2->Size_of_the_infrastructure);
            printf("floor:                   %s\n",temp2->Floor);
            printf("Size of the main land:   %s\n",temp2->Size_of_the_main_land);
            printf("number of the owner:     %s\n",temp2->number_of_the_owner);
            printf("Number of office rooms:  %s\n",temp2->Number_of_office_rooms);
            printf("Price:                   %s\n",temp2->Price);
            c++;
            printf("\033[0;35m********************************************************************\e[m\n");
        }
     temp2=temp2->next;
    }
    fclose(file);
    temp = first;
    while (temp != NULL)
    {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
    if ( c == 1)
    {
       printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
       exit(0);
    }
    while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_office_property_sale();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_office_sale_bedrooms()
{
     system("cls");
    int bedrooms;
    int c=1;
    FILE *file;
    file = fopen("officepropartysale.txt" ,"r");
    struct Office_property_information_for_sale *first=NULL ,*last=NULL ,*temp2;
    if (file == NULL)
    {
        printf("EROR OPPENING FILE");
        exit(1);
    }
    printf("How many rooms do you want the office to have?");
    scanf("%d",&bedrooms);
    getchar();

    struct Office_property_information_for_sale *temp = malloc(sizeof(struct Office_property_information_for_sale));

    while(1)
    {
      struct Office_property_information_for_sale *temp = malloc(sizeof(struct Office_property_information_for_sale));
       if(fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
              temp->Municipal_area,
              temp->Exact_address,
              temp->Property_Type,
              temp->Age_of_the_property,
              temp->Size_of_the_infrastructure,
              temp->Floor,
              temp->Size_of_the_main_land,
              temp->number_of_the_owner,
              temp->Number_of_office_rooms,
              temp->Price,
              &temp->ID,
              &temp->active)!=12)
      {
          break;
      }
        if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next=temp;
            last = temp;
            last->next=NULL;
        }
    }
    temp2=first;
    while(temp2 != NULL)
    {
        if(atoi(temp2->Number_of_office_rooms) == bedrooms && temp2->active == 1)
        {
            printf("%d.office PROPERTY:\n"       , c);
            printf("Municipalarea:           %s\n",temp2->Municipal_area);
            printf("Exactaddress:            %s\n",temp2->Exact_address);
              if(strcmp(temp2->Property_Type , "1") == 0)
           {
             printf("Property Type:              official administrative\n");
           }
            else if(strcmp(temp2->Property_Type , "2") == 0)
            {
             printf("property Type:              administrative position\n");
            }
            printf("Age of the property:     %s\n",temp2->Age_of_the_property);
            printf("infrastructure:          %s\n",temp2->Size_of_the_infrastructure);
            printf("floor:                   %s\n",temp2->Floor);
            printf("Size of the main land:   %s\n",temp2->Size_of_the_main_land);
            printf("number of the owner:     %s\n",temp2->number_of_the_owner);
            printf("Number of office rooms:  %s\n",temp2->Number_of_office_rooms);
            printf("Price:                   %s\n",temp2->Price);
            c++;
            printf("\033[0;35m********************************************************************\e[m\n");
        }
     temp2=temp2->next;
    }
    fclose(file);
    temp = first;
    while (temp != NULL)
    {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
    if ( c == 1)
    {
       printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
       exit(0);
    }
    while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_office_property_sale();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_office_property_sale()
{
    system("cls");
    printf("According to which invoice do you want to get a report?\n");
    printf("1-according to price\n2-according to the Age of construction\n3-according to The infrastructure\n");
    printf("4-according to the Regional Municipality\n");//منطقه شهرداری
    printf("5-according to number of bedrooms\n6list all of them\n7-back to previous menu\n8-clear screen\n9-exit\n");
    int choice9;
    scanf("%d",&choice9);
    getchar();
    switch (choice9)
    {
    case 1:
        report_office_sale_price();
        break;
    case 2:
        report_office_sale_age();
        break;
    case 3:
        report_office_sale_infrastructure();
        break;
    case 4:
        report_office_sale_Municipality();
        break;
    case 5:
        report_office_sale_bedrooms();
        break;
    case 6:
        list_officesale();
        break;
    case 7:
        report_office_property();
        break;
    case 8:
        system("cls");
        break;
    case 9:
        exit(1);
        break;
    }
}
void report_officerent_rent()
{
  system("cls");
    int price1;
    int price2;
    int mortgage1;
    int mortgage2;
    int c=1;
    FILE *file;
    file = fopen("officepropertyrent.txt" ,"r");
    struct  Office_property_information_for_rent *first=NULL ,*last=NULL ,*temp2;
    if (file == NULL)
    {
        printf("EROR OPPENING FILE");
        exit(1);
    }
    printf("enter The least amount you want to spend to rent office:");
    scanf("%d",&price1);
    getchar();

    printf("enter The maximum amount you want to spend to rent office:");
    scanf("%d",&price2);
    getchar();

    printf("enter The least amount you want to spend to mortgage office:");
    scanf("%d",&mortgage1);
    getchar();

    printf("enter The maximum amount you want to spend to mortgage office:");
    scanf("%d",&mortgage2);
    getchar();

    struct Office_property_information_for_rent *temp = malloc(sizeof(struct Office_property_information_for_rent));

    while(1)
    {
      struct Office_property_information_for_rent *temp = malloc(sizeof(struct Office_property_information_for_rent));
      if(fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
              temp->Municipal_area,
              temp->Exact_address,
              temp->Property_Type,
              temp->Age_of_the_property,
              temp->Size_of_the_infrastructure,
              temp->Floor,
              temp->Size_of_the_main_land,
              temp->number_of_the_owner,
              temp->Number_of_office_rooms,
              temp->mortgage,
              temp->Rent,
              &temp->ID,
              &temp->active)!=13)
      {
          break;
      }
        if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next=temp;
            last = temp;
            last->next=NULL;
        }
    }
    temp2=first;
    while(temp2 != NULL)
    {
        if(atoi(temp2->Rent)>=price1 && atoi(temp2->Rent)<=price2 &&
            atoi(temp2->mortgage)>=mortgage1 && atoi(temp2->mortgage)<=mortgage2
           && temp2->active == 1)
        {
            printf("%d.office PROPERTY:\n"       , c);
            printf("Municipal area:              %s\n",temp2->Municipal_area);
            printf("Exact address:               %s\n",temp2->Exact_address);
            if(strcmp(temp2->Property_Type , "1") == 0)
           {
             printf("Property Type:              official administrative document\n");
           }
            else if(strcmp(temp2->Property_Type , "2") == 0)
            {
             printf("property Type:              administrative position\n");
            }
            printf("Age of the property:         %s\n",temp2->Age_of_the_property);
            printf("Size of the infrastructure:  %s\n",temp2->Size_of_the_infrastructure);
            printf("Floor:                       %s\n",temp2->Floor);
            printf("Size of the main land:       %s\n",temp2->Size_of_the_main_land);
            printf("Number of the owner:         %s\n",temp2->number_of_the_owner);
            printf("Number of office rooms:      %s\n",temp2->Number_of_office_rooms);
            printf("Mortgage:                    %s\n",temp2->mortgage);
            printf("Rent:                        %s\n",temp2->Rent);
            c++;
            printf("\033[0;35m********************************************************************\e[m\n");
        }
     temp2=temp2->next;
    }
    fclose(file);
    temp = first;
    while (temp != NULL)
    {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
    if ( c == 1)
    {
       printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
       exit(0);
    }
    while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_office_property_rent();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_officerent_age()
{
    system("cls");
    int age1;
    int age2;
    int c=1;
    FILE *file;
    file = fopen("officepropertyrent.txt" ,"r");
    struct  Office_property_information_for_rent *first=NULL ,*last=NULL ,*temp2;
    if (file == NULL)
    {
        printf("EROR OPPENING FILE");
        exit(1);
    }
    printf("Do you want the desired office to be built for at least how many years?");
    scanf("%d",&age1);
    getchar();

    printf("How many years do you want the desired office to be built at most?");
    scanf("%d",&age2);
    getchar();

    struct Office_property_information_for_rent *temp = malloc(sizeof(struct Office_property_information_for_rent));

    while(1)
    {
      struct Office_property_information_for_rent *temp = malloc(sizeof(struct Office_property_information_for_rent));
      if(fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
              temp->Municipal_area,
              temp->Exact_address,
              temp->Property_Type,
              temp->Age_of_the_property,
              temp->Size_of_the_infrastructure,
              temp->Floor,
              temp->Size_of_the_main_land,
              temp->number_of_the_owner,
              temp->Number_of_office_rooms,
              temp->mortgage,
              temp->Rent,
              &temp->ID,
              &temp->active)!=13)
      {
          break;
      }
        if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next=temp;
            last = temp;
            last->next=NULL;
        }
    }
    temp2=first;
    while(temp2 != NULL)
    {
        if(atoi(temp2->Age_of_the_property)>=age1 && atoi(temp2->Age_of_the_property)<= age2 &&
           temp2->active == 1)
        {
            printf("%d.office PROPERTY:\n"            ,c);
            printf("Municipal area:              %s\n",temp2->Municipal_area);
            printf("Exact address:               %s\n",temp2->Exact_address);
            if(strcmp(temp2->Property_Type , "1") == 0)
           {
             printf("Property Type:              official administrative document\n");
           }
            else if(strcmp(temp2->Property_Type , "2") == 0)
            {
             printf("property Type:              administrative position\n");
            }
            printf("Age of the property:         %s\n",temp2->Age_of_the_property);
            printf("Size of the infrastructure:  %s\n",temp2->Size_of_the_infrastructure);
            printf("Floor:                       %s\n",temp2->Floor);
            printf("Size of the main land:       %s\n",temp2->Size_of_the_main_land);
            printf("Number of the owner:         %s\n",temp2->number_of_the_owner);
            printf("Number of office rooms:      %s\n",temp2->Number_of_office_rooms);
            printf("Mortgage:                    %s\n",temp2->mortgage);
            printf("Rent:                        %s\n",temp2->Rent);
            c++;
            printf("\033[0;35m********************************************************************\e[m\n");
        }
     temp2=temp2->next;
    }
    fclose(file);
    temp = first;
    while (temp != NULL)
    {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
    if ( c == 1)
    {
       printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
       exit(0);
    }
    while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_office_property_rent();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_officerent_infrastructure()
{
    system("cls");
    int infrastructure1;
    int infrastructure2;
    int c=1;
    FILE *file;
    file = fopen("officepropertyrent.txt" ,"r");
    struct  Office_property_information_for_rent *first=NULL ,*last=NULL ,*temp2;
    if (file == NULL)
    {
        printf("EROR OPPENING FILE");
        exit(1);
    }
    printf("What is the minimum infrastructure of the office you want?");
    scanf("%d",&infrastructure1);
    getchar();

    printf("What is the maximum infrastructure of the desired office?");
    scanf("%d",&infrastructure2);
    getchar();

    struct Office_property_information_for_rent *temp = malloc(sizeof(struct Office_property_information_for_rent));

    while(1)
    {
      struct Office_property_information_for_rent *temp = malloc(sizeof(struct Office_property_information_for_rent));
     if(fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
              temp->Municipal_area,
              temp->Exact_address,
              temp->Property_Type,
              temp->Age_of_the_property,
              temp->Size_of_the_infrastructure,
              temp->Floor,
              temp->Size_of_the_main_land,
              temp->number_of_the_owner,
              temp->Number_of_office_rooms,
              temp->mortgage,
              temp->Rent,
              &temp->ID,
              &temp->active)!=13)
      {
          break;
      }
        if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next=temp;
            last = temp;
            last->next=NULL;
        }
    }
    temp2=first;
    while(temp2 != NULL)
    {
        if(atoi(temp2->Size_of_the_infrastructure)>=infrastructure1 &&
            atoi(temp2->Size_of_the_infrastructure)<=infrastructure2 &&
           temp2->active == 1)
        {
            printf("%d.office PROPERTY:\n"            ,c);
            printf("Municipal area:              %s\n",temp2->Municipal_area);
            printf("Exact address:               %s\n",temp2->Exact_address);
            if(strcmp(temp2->Property_Type , "1") == 0)
           {
             printf("Property Type:              official administrative document\n");
           }
            else if(strcmp(temp2->Property_Type , "2") == 0)
            {
             printf("property Type:              administrative position\n");
            }
            printf("Age of the property:         %s\n",temp2->Age_of_the_property);
            printf("Size of the infrastructure:  %s\n",temp2->Size_of_the_infrastructure);
            printf("Floor:                       %s\n",temp2->Floor);
            printf("Size of the main land:       %s\n",temp2->Size_of_the_main_land);
            printf("Number of the owner:         %s\n",temp2->number_of_the_owner);
            printf("Number of office rooms:      %s\n",temp2->Number_of_office_rooms);
            printf("Mortgage:                    %s\n",temp2->mortgage);
            printf("Rent:                        %s\n",temp2->Rent);
            c++;
            printf("\033[0;35m********************************************************************\e[m\n");
        }
     temp2=temp2->next;
    }
    fclose(file);
    temp = first;
    while (temp != NULL)
    {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
    if ( c == 1)
    {
       printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
       exit(0);
    }
    while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_office_property_rent();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_officerent_Municipality()
{
    system("cls");
    int Municipality;
    int c=1;
    FILE *file;
    file = fopen("officepropertyrent.txt" ,"r");
    struct  Office_property_information_for_rent *first=NULL ,*last=NULL ,*temp2;
    if (file == NULL)
    {
        printf("EROR OPPENING FILE");
        exit(1);
    }
    printf("In which municipal do you want the desired office to be?");
    scanf("%d",&Municipality);
    getchar();


    struct Office_property_information_for_rent *temp = malloc(sizeof(struct Office_property_information_for_rent));

    while(1)
    {
      struct Office_property_information_for_rent *temp = malloc(sizeof(struct Office_property_information_for_rent));
     if(fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
              temp->Municipal_area,
              temp->Exact_address,
              temp->Property_Type,
              temp->Age_of_the_property,
              temp->Size_of_the_infrastructure,
              temp->Floor,
              temp->Size_of_the_main_land,
              temp->number_of_the_owner,
              temp->Number_of_office_rooms,
              temp->mortgage,
              temp->Rent,
              &temp->ID,
              &temp->active)!=13)
      {
          break;
      }
        if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next=temp;
            last = temp;
            last->next=NULL;
        }
    }
    temp2=first;
    while(temp2 != NULL)
    {
        if(atoi(temp2->Municipal_area) == Municipality && temp2->active == 1)
        {
            printf("%d.office PROPERTY:\n"            ,c);
            printf("Municipal area:              %s\n",temp2->Municipal_area);
            printf("Exact address:               %s\n",temp2->Exact_address);
            if(strcmp(temp2->Property_Type , "1") == 0)
           {
             printf("Property Type:              official administrative document\n");
           }
            else if(strcmp(temp2->Property_Type , "2") == 0)
            {
             printf("property Type:              administrative position\n");
            }
            printf("Age of the property:         %s\n",temp2->Age_of_the_property);
            printf("Size of the infrastructure:  %s\n",temp2->Size_of_the_infrastructure);
            printf("Floor:                       %s\n",temp2->Floor);
            printf("Size of the main land:       %s\n",temp2->Size_of_the_main_land);
            printf("Number of the owner:         %s\n",temp2->number_of_the_owner);
            printf("Number of office rooms:      %s\n",temp2->Number_of_office_rooms);
            printf("Mortgage:                    %s\n",temp2->mortgage);
            printf("Rent:                        %s\n",temp2->Rent);
            c++;
            printf("\033[0;35m********************************************************************\e[m\n");
        }
     temp2=temp2->next;
    }
    fclose(file);
    temp = first;
    while (temp != NULL)
    {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
    if ( c == 1)
    {
       printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
       exit(0);
    }
    while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_office_property_rent();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_officerent_rooms()
{
     system("cls");
    int room;
    int c=1;
    FILE *file;
    file = fopen("officepropertyrent.txt" ,"r");
    struct  Office_property_information_for_rent *first=NULL ,*last=NULL ,*temp2;
    if (file == NULL)
    {
        printf("EROR OPPENING FILE");
        exit(1);
    }
    printf("In which municipal do you want the desired office to be?");
    scanf("%d",&room);
    getchar();


    struct Office_property_information_for_rent *temp = malloc(sizeof(struct Office_property_information_for_rent));

    while(1)
    {
      struct Office_property_information_for_rent *temp = malloc(sizeof(struct Office_property_information_for_rent));
    if(fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
              temp->Municipal_area,
              temp->Exact_address,
              temp->Property_Type,
              temp->Age_of_the_property,
              temp->Size_of_the_infrastructure,
              temp->Floor,
              temp->Size_of_the_main_land,
              temp->number_of_the_owner,
              temp->Number_of_office_rooms,
              temp->mortgage,
              temp->Rent,
              &temp->ID,
              &temp->active)!=13)
      {
          break;
      }
        if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next=temp;
            last = temp;
            last->next=NULL;
        }
    }
    temp2=first;
    while(temp2 != NULL)
    {
        if(atoi(temp2->Number_of_office_rooms) == room && temp2->active == 1)
        {
            printf("%d.office PROPERTY:\n"            ,c);
            printf("Municipal area:              %s\n",temp2->Municipal_area);
            printf("Exact address:               %s\n",temp2->Exact_address);
            if(strcmp(temp2->Property_Type , "1") == 0)
           {
             printf("Property Type:              official administrative document\n");
           }
            else if(strcmp(temp2->Property_Type , "2") == 0)
            {
             printf("property Type:              administrative position\n");
            }
            printf("Age of the property:         %s\n",temp2->Age_of_the_property);
            printf("Size of the infrastructure:  %s\n",temp2->Size_of_the_infrastructure);
            printf("Floor:                       %s\n",temp2->Floor);
            printf("Size of the main land:       %s\n",temp2->Size_of_the_main_land);
            printf("Number of the owner:         %s\n",temp2->number_of_the_owner);
            printf("Number of office rooms:      %s\n",temp2->Number_of_office_rooms);
            printf("Mortgage:                    %s\n",temp2->mortgage);
            printf("Rent:                        %s\n",temp2->Rent);
            c++;
            printf("\033[0;35m********************************************************************\e[m\n");
        }
     temp2=temp2->next;
    }
    fclose(file);
    temp = first;
    while (temp != NULL)
    {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
    if ( c == 1)
    {
       printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
       exit(0);
    }
    while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_office_property_rent();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_office_property_rent()
{
    system("cls");
    printf("According to which invoice do you want to get a report?\n");
    printf("1-according to rent&mortgage\n2-according to the Age of construction\n3-according to The infrastructure\n");
    printf("4-according to the Regional Municipality\n");//منطقه شهرداری
    printf("5-according to number of rooms\n6list all of them\n7-back to previous menu\n8-clear screen\n9-exit\n");
    int choice10;
    scanf("%d",&choice10);
    getchar();
    switch (choice10)
    {
    case 1:
        report_officerent_rent();
        break;
    case 2:
        report_officerent_age();
        break;
    case 3:
        report_officerent_infrastructure();
        break;
    case 4:
        report_officerent_Municipality();
        break;
    case 5:
        report_officerent_rooms();
        break;
    case 6:
        list_officerent();
        break;
    case 7:
        report_office_property();
        break;
    case 8:
        system("cls");
        break;
    case 9:
        exit(1);
        break;
    }
}
void report_office_property()
{
    system("cls");
    printf("What kind of office property are you looking for?");
    printf("\n1-office for sale\n2-office for rent\n3-back to previous menu\n4-clear the screen\n5-exit\n");
    int choice7;
    scanf("%d",&choice7);
    switch (choice7)
    {
    case 1:
        report_office_property_sale();
        break;
    case 2:
        report_office_property_rent();
        break;
    case 3:
        report_for_user();
        break;
    case 4:
        system("cls");
        break;
    case 5:
        exit(1);
        break;
    }
}
void report_landsale_type()
{
  system("cls");
  int c=1;
  int type;
  FILE *file;
  file = fopen("landsale.txt","r");
  struct Land_sales_information*first = NULL, *last = NULL, *temp2;
  if (file == NULL)
  {
      printf("EROR OPEMIMG FILE!");
      exit(1);
  }
  struct Land_sales_information*temp = malloc(sizeof(struct Land_sales_information));
  while (1)
  {
      struct Land_sales_information*temp = malloc(sizeof(struct Land_sales_information));
      if (fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                 temp->Municipal_area,
                 temp->Exact_address,
                 temp->land_Type,
                 temp->Size_of_the_land,
                 temp->number_of_the_owner,
                 temp->Price,
                 &temp->ID,
                 &temp->active)!=8)
      {
          break;
      }
       if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next=temp;
            last = temp;
            last->next=NULL;
        }
    }
    printf("enter the desired land type if its Agricultural enter 1 if its urban enter 2");
    scanf("%d",&type);
    getchar();
    temp2=first;
    while (temp2 != NULL)
    {
        if(type == atoi(temp2->land_Type) && temp2->active == 1)
        {
         printf("%d. LAND PROPERTY:\n",c);
         printf("Municipal area:             %s\n",temp2->Municipal_area);
         printf("Exact address:              %s\n",temp2->Exact_address);
         if (strcmp(temp2->land_Type, "1") == 0)
         {
             printf("land Type:                  Agricultural\n");
         }
         if (strcmp(temp2->land_Type, "2") == 0)
         {
            printf("land Type:                   urban\n");
         }
         printf("Size of the land:           %s\n",temp2->Size_of_the_land);
         printf("number of the owner:        %s\n",temp2->number_of_the_owner);
         printf("Price:                      %s\n",temp2->Price);
         c++;
         printf("\033[0;35m********************************************************************\e[m\n");
        }
        temp2=temp2->next;
    }
    fclose(file);
    //free allocated memory
    temp=first;
    while(temp!=NULL)
    {
       temp2=temp->next;
       free(temp);
       temp=temp2;
    }
    if (c==1)
    {
      printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
      exit(1);
    }
    while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_land_property_sale();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_landsale_size()
{
  system("cls");
  int c=1;
  int size1;
  int size2;
  FILE *file;
  file = fopen("landsale.txt","r");
  struct Land_sales_information*first = NULL, *last = NULL, *temp2;
  if (file == NULL)
  {
      printf("EROR OPEMIMG FILE!");
      exit(1);
  }
  struct Land_sales_information*temp = malloc(sizeof(struct Land_sales_information));
  while (1)
  {
      struct Land_sales_information*temp = malloc(sizeof(struct Land_sales_information));
        if (fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                 temp->Municipal_area,
                 temp->Exact_address,
                 temp->land_Type,
                 temp->Size_of_the_land,
                 temp->number_of_the_owner,
                 temp->Price,
                 &temp->ID,
                 &temp->active)!=8)
      {
          break;
      }
       if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next=temp;
            last = temp;
            last->next=NULL;
        }
    }
    printf(" enter the minimum size of desired land: \n");
    scanf("%d",&size1);
    getchar();

    printf("enter the maximum size of desired land: \n");
    scanf("%d",&size2);
    getchar();

    temp2=first;
    while (temp2 != NULL)
    {
        if(atoi(temp2->Size_of_the_land)>=size1 &&
           atoi(temp2->Size_of_the_land)<=size2 && temp2->active == 1)
        {
         printf("%d. LAND PROPERTY:\n",c);
         printf("Municipal area:             %s\n",temp2->Municipal_area);
         printf("Exact address:              %s\n",temp2->Exact_address);
         if (strcmp(temp2->land_Type, "1") == 0)
         {
             printf("land Type:                  Agricultural\n");
         }
         if (strcmp(temp2->land_Type, "2") == 0)
         {
            printf("land Type:                   urban\n");
         }
         printf("Size of the land:           %s\n",temp2->Size_of_the_land);
         printf("number of the owner:        %s\n",temp2->number_of_the_owner);
         printf("Price:                      %s\n",temp2->Price);
         c++;
         printf("\033[0;35m********************************************************************\e[m\n");
        }
        temp2=temp2->next;
    }
    fclose(file);
    //free allocated memory
    temp=first;
    while(temp!=NULL)
    {
       temp2=temp->next;
       free(temp);
       temp=temp2;
    }
    if (c==1)
    {
      printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
      exit(1);
    }
    while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_land_property_sale();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_landsale_price()
{
  system("cls");
  int c=1;
  int price1;
  int price2;
  FILE *file;
  file = fopen("landsale.txt","r");
  struct Land_sales_information*first = NULL, *last = NULL, *temp2;
  if (file == NULL)
  {
      printf("EROR OPEMIMG FILE!");
      exit(1);
  }
  struct Land_sales_information*temp = malloc(sizeof(struct Land_sales_information));
  while (1)
  {
      struct Land_sales_information*temp = malloc(sizeof(struct Land_sales_information));
        if (fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                 temp->Municipal_area,
                 temp->Exact_address,
                 temp->land_Type,
                 temp->Size_of_the_land,
                 temp->number_of_the_owner,
                 temp->Price,
                 &temp->ID,
                 &temp->active)!=8)
      {
          break;
      }
       if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next=temp;
            last = temp;
            last->next=NULL;
        }
    }
    printf(" enter the minimum price you can pay for desired land: \n");
    scanf("%d",&price1);
    getchar();

    printf("enter the maximum price you can pay for desired land: \n");
    scanf("%d",&price2);
    getchar();

    temp2=first;
    while (temp2 != NULL)
    {
        if(atoi(temp2->Price)>=price1 && atoi(temp2->Price)<=price2
           && temp2->active == 1)
        {
         printf("%d. LAND PROPERTY:\n",c);
         printf("Municipal area:             %s\n",temp2->Municipal_area);
         printf("Exact address:              %s\n",temp2->Exact_address);
         if (strcmp(temp2->land_Type, "1") == 0)
         {
             printf("land Type:                  Agricultural\n");
         }
         if (strcmp(temp2->land_Type, "2") == 0)
         {
            printf("land Type:                   urban\n");
         }
         printf("Size of the land:           %s\n",temp2->Size_of_the_land);
         printf("number of the owner:        %s\n",temp2->number_of_the_owner);
         printf("Price:                      %s\n",temp2->Price);
         c++;
         printf("\033[0;35m********************************************************************\e[m\n");
        }
        temp2=temp2->next;
    }
    fclose(file);
    //free allocated memory
    temp=first;
    while(temp!=NULL)
    {
       temp2=temp->next;
       free(temp);
       temp=temp2;
    }
    if (c==1)
    {
      printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
      exit(1);
    }
    while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_land_property_sale();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_landsale_municipil()
{
  system("cls");
  int c=1;
  int municipil;
  FILE *file;
  file = fopen("landsale.txt","r");
  struct Land_sales_information*first = NULL, *last = NULL, *temp2;
  if (file == NULL)
  {
      printf("EROR OPEMIMG FILE!");
      exit(1);
  }
  struct Land_sales_information*temp = malloc(sizeof(struct Land_sales_information));
  while (1)
  {
      struct Land_sales_information*temp = malloc(sizeof(struct Land_sales_information));
        if (fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                 temp->Municipal_area,
                 temp->Exact_address,
                 temp->land_Type,
                 temp->Size_of_the_land,
                 temp->number_of_the_owner,
                 temp->Price,
                 &temp->ID,
                 &temp->active)!=8)
      {
          break;
      }
       if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next=temp;
            last = temp;
            last->next=NULL;
        }
    }
    printf("in wich municipil area you wanna buy a land");
    scanf("%d",&municipil);
    getchar();
    temp2=first;
    while (temp2 != NULL)
    {
        if(municipil == atoi(temp2->Municipal_area) && temp2->active==1)
        {
         printf("%d. LAND PROPERTY:\n",c);
         printf("Municipal area:             %s\n",temp2->Municipal_area);
         printf("Exact address:              %s\n",temp2->Exact_address);
         if (strcmp(temp2->land_Type, "1") == 0)
         {
             printf("land Type:                  Agricultural\n");
         }
         if (strcmp(temp2->land_Type, "2") == 0)
         {
            printf("land Type:                   urban\n");
         }
         printf("Size of the land:           %s\n",temp2->Size_of_the_land);
         printf("number of the owner:        %s\n",temp2->number_of_the_owner);
         printf("Price:                      %s\n",temp2->Price);
         c++;
         printf("\033[0;35m********************************************************************\e[m\n");
        }
        temp2=temp2->next;
    }
    fclose(file);
    //free allocated memory
    temp=first;
    while(temp!=NULL)
    {
       temp2=temp->next;
       free(temp);
       temp=temp2;
    }
    if (c==1)
    {
      printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
      exit(1);
    }
    while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_land_property_sale();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_land_property_sale()
{
    system("cls");
    printf("According to which invoice do you want to get a report?\n1-land type\n2-size of land\n3-price\n4-municipil_area\n5-list all of them\n6-clear screen\n");
    printf("7-back to previous menu\n8-exit\nEnter your choice: \n");
    int choice;
    scanf("%d",&choice);
    getchar();
    switch (choice)
    {
    case 1:
        report_landsale_type();
        break;
    case 2:
        report_landsale_size();
        break;
    case 3:
        report_landsale_price();
        break;
    case 4:
        report_landsale_municipil();
        break;
    case 5:
        list_landsales();
        break;
    case 6:
        system("cls");
        break;
    case 7:
        report_land_property();
        break;
    case 8:
        exit(1);
        break;

    }
}
void report_landrent_type()
{
  system("cls");
  int c=1;
  int type;
  FILE *file;
  file = fopen("landrent.txt","r");
  struct Land_rent_information*first = NULL, *last = NULL, *temp2;
  if (file == NULL)
  {
      printf("EROR OPEMIMG FILE!");
      exit(1);
  }
  struct Land_rent_information*temp = malloc(sizeof(struct Land_rent_information));
  while (1)
  {
      struct Land_rent_information *temp = malloc(sizeof(struct Land_rent_information));
      if (fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                 temp->Municipal_area,
                 temp->Exact_address,
                 temp->land_Type,
                 temp->Size_of_the_land,
                 temp->number_of_the_owner,
                 temp->mortgage,
                 temp->Rent,
                 &temp->ID,
                 &temp->active)!=9)
      {
          break;
      }
       if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next=temp;
            last = temp;
            last->next=NULL;
        }
    }
    printf("enter the desired land type if its Agricultural enter 1 if its urban enter 2 : ");
    scanf("%d",&type);
    getchar();
    temp2=first;
    while (temp2 != NULL)
    {
        if(type == atoi(temp2->land_Type) && temp2->active==1)
        {
         printf("%d. LAND PROPERTY:\n",c);
         printf("Municipal area:             %s\n",temp2->Municipal_area);
         printf("Exact address:              %s\n",temp2->Exact_address);
         if (strcmp(temp2->land_Type, "1") == 0)
         {
             printf("land Type:                  Agricultural\n");
         }
         if (strcmp(temp2->land_Type, "2") == 0)
         {
            printf("land Type:                   urban\n");
         }
         printf("Size of the land:           %s\n",temp2->Size_of_the_land);
         printf("Number of the owner:        %s\n",temp2->number_of_the_owner);
         printf("Mortgage:                   %s\n",temp2->mortgage);
         printf("Rent:                       %s\n",temp2->Rent);
         c++;
         printf("\033[0;35m********************************************************************\e[m\n");
        }
        temp2=temp2->next;
    }
    fclose(file);
    //free allocated memory
    temp=first;
    while(temp!=NULL)
    {
       temp2=temp->next;
       free(temp);
       temp=temp2;
    }
    if (c==1)
    {
      printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
      exit(1);
    }
    while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_land_property_rent();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_landrent_size()
{
  system("cls");
  int c=1;
  int size1;
  int size2;
  FILE *file;
  file = fopen("landrent.txt","r");
  struct Land_rent_information*first = NULL, *last = NULL, *temp2;
  if (file == NULL)
  {
      printf("EROR OPEMIMG FILE!");
      exit(1);
  }
  struct Land_rent_information*temp = malloc(sizeof(struct Land_rent_information));
  while (1)
  {
      struct Land_rent_information *temp = malloc(sizeof(struct Land_rent_information));
      if (fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
                 temp->Municipal_area,
                 temp->Exact_address,
                 temp->land_Type,
                 temp->Size_of_the_land,
                 temp->number_of_the_owner,
                 &temp->mortgage,
                 &temp->Rent)!=7)
      {
          break;
      }
       if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next=temp;
            last = temp;
            last->next=NULL;
        }
    }
    printf(" enter the minimum size of desired land: \n");
    scanf("%d",&size1);
    getchar();

    printf("enter the maximum size of desired land: \n");
    scanf("%d",&size2);
    getchar();
    temp2=first;
    while (temp2 != NULL)
    {
        if(atoi(temp2->Size_of_the_land)>= size1 && atoi(temp2->Size_of_the_land)<=size2)
        {
         printf("%d. LAND PROPERTY:\n",c);
         printf("Municipal area:             %s\n",temp2->Municipal_area);
         printf("Exact address:              %s\n",temp2->Exact_address);
         if (strcmp(temp2->land_Type, "1") == 0)
         {
             printf("land Type:                  Agricultural\n");
         }
         if (strcmp(temp2->land_Type, "2") == 0)
         {
            printf("land Type:                   urban\n");
         }
         printf("Size of the land:           %s\n",temp2->Size_of_the_land);
         printf("Number of the owner:        %s\n",temp2->number_of_the_owner);
         printf("Mortgage:                   %s\n",temp2->mortgage);
         printf("Rent:                       %s\n",temp2->Rent);
         c++;
         printf("\033[0;35m********************************************************************\e[m\n");
        }
        temp2=temp2->next;
    }
    fclose(file);
    //free allocated memory
    temp=first;
    while(temp!=NULL)
    {
       temp2=temp->next;
       free(temp);
       temp=temp2;
    }
    if (c==1)
    {
      printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
      exit(1);
    }
    while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_land_property_rent();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_landrent_price()
{
  system("cls");
  int c=1;
  int mortgage1;
  int mortgage2;
  FILE *file;
  file = fopen("landrent.txt","r");
  struct Land_rent_information*first = NULL, *last = NULL, *temp2;
  if (file == NULL)
  {
      printf("EROR OPEMIMG FILE!");
      exit(1);
  }
  struct Land_rent_information*temp = malloc(sizeof(struct Land_rent_information));
  while (1)
  {
      struct Land_rent_information *temp = malloc(sizeof(struct Land_rent_information));
      if (fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
                 temp->Municipal_area,
                 temp->Exact_address,
                 temp->land_Type,
                 temp->Size_of_the_land,
                 temp->number_of_the_owner,
                 &temp->mortgage,
                 &temp->Rent)!=7)
      {
          break;
      }
       if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next=temp;
            last = temp;
            last->next=NULL;
        }
    }
    printf(" enter the minimum mortgage you can pay for rent a land: \n");
    scanf("%d",&mortgage1);
    getchar();

    printf("enter the maximum mortgage you can pay for rent a land: \n");
    scanf("%d",&mortgage2);
    getchar();

    int rent1;
    printf("enter the minimum rent you can pay for rent a land: \n");
    scanf("%d",&rent1);
    getchar();

    int rent2;
    printf("enter the maximum rent you can pay for rent a land: \n");
    scanf("%d",&rent2);
    getchar();


    temp2=first;
    while (temp2 != NULL)
    {
        if(atoi(temp2->mortgage)>= mortgage1 && atoi(temp2->mortgage)<=mortgage2 && atoi(temp2->Rent)>=rent1 && atoi(temp2->Rent)<=rent2)
        {
         printf("%d. LAND PROPERTY:\n",c);
         printf("Municipal area:             %s\n",temp2->Municipal_area);
         printf("Exact address:              %s\n",temp2->Exact_address);
         if (strcmp(temp2->land_Type, "1") == 0)
         {
             printf("land Type:                  Agricultural\n");
         }
         if (strcmp(temp2->land_Type, "2") == 0)
         {
            printf("land Type:                   urban\n");
         }
         printf("Size of the land:           %s\n",temp2->Size_of_the_land);
         printf("Number of the owner:        %s\n",temp2->number_of_the_owner);
         printf("Mortgage:                   %s\n",temp2->mortgage);
         printf("Rent:                       %s\n",temp2->Rent);
         c++;
         printf("\033[0;35m********************************************************************\e[m\n");
        }
        temp2=temp2->next;
    }
    fclose(file);
    //free allocated memory
    temp=first;
    while(temp!=NULL)
    {
       temp2=temp->next;
       free(temp);
       temp=temp2;
    }
    if (c==1)
    {
      printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
      exit(1);
    }
    while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_land_property_rent();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_landrent_municipil()
{
  system("cls");
  int c=1;
  int municipil;
  FILE *file;
  file = fopen("landrent.txt","r");
  struct Land_rent_information*first = NULL, *last = NULL, *temp2;
  if (file == NULL)
  {
      printf("EROR OPEMIMG FILE!");
      exit(1);
  }
  struct Land_rent_information*temp = malloc(sizeof(struct Land_rent_information));
  while (1)
  {
      struct Land_rent_information *temp = malloc(sizeof(struct Land_rent_information));
      if (fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
                 temp->Municipal_area,
                 temp->Exact_address,
                 temp->land_Type,
                 temp->Size_of_the_land,
                 temp->number_of_the_owner,
                 &temp->mortgage,
                 &temp->Rent)!=7)
      {
          break;
      }
       if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next=temp;
            last = temp;
            last->next=NULL;
        }
    }
    printf("in wich municipil area you wanna rent a land:");
    scanf("%d",&municipil);
    getchar();
    temp2=first;
    while (temp2 != NULL)
    {
        if(municipil == atoi(temp2->Municipal_area))
        {
         printf("%d. LAND PROPERTY:\n",c);
         printf("Municipal area:             %s\n",temp2->Municipal_area);
         printf("Exact address:              %s\n",temp2->Exact_address);
         if (strcmp(temp2->land_Type, "1") == 0)
         {
             printf("land Type:                  Agricultural\n");
         }
         if (strcmp(temp2->land_Type, "2") == 0)
         {
            printf("land Type:                   urban\n");
         }
         printf("Size of the land:           %s\n",temp2->Size_of_the_land);
         printf("Number of the owner:        %s\n",temp2->number_of_the_owner);
         printf("Mortgage:                   %s\n",temp2->mortgage);
         printf("Rent:                       %s\n",temp2->Rent);
         c++;
         printf("\033[0;35m********************************************************************\e[m\n");
        }
        temp2=temp2->next;
    }
    fclose(file);
    //free allocated memory
    temp=first;
    while(temp!=NULL)
    {
       temp2=temp->next;
       free(temp);
       temp=temp2;
    }
    if (c==1)
    {
      printf("\x1b[31mSORRY! The specified property does not exist\x1b[0m\n");
      exit(1);
    }
    while(1)
    {
        printf("Please enter your choice:\n");
        printf("1-back Previous menu\n");
        printf("2- Clear screen\n");
        printf("3- Exit\n");

        int choice;
        scanf("%d",&choice);
        getchar();


        switch(choice)
        {
        case 1:
            report_land_property_rent();
            break;
        case 2:
            system("cls");
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
void report_land_property_rent()
{
    system("cls");
    printf("According to which invoice do you want to get a report?\n1-land_type\n2-size of land\n3-mortgage&rent\n4-municipil_area\n5-list all of them\n6-clear screen\n");
    printf("7-back to previous menu\n8-exit\nEnter your choice: \n");
    int choice;
    scanf("%d",&choice);
    getchar();
    switch (choice)
    {
    case 1:
        report_landrent_type();
        break;
    case 2:
        report_landrent_size();
        break;
    case 3:
        report_landrent_price();
        break;
    case 4:
        report_landrent_municipil();
        break;
    case 5:
        list_landrent();
        break;
    case 6:
        system("cls");
        break;
    case 7:
        report_land_property();
        break;
    case 8:
        exit(0);
        break;

    }

}
void report_land_property()
{
    system("cls");
    printf("What kind of land property are you looking for?");
    printf("\n1-land sale\n2-land rent\n3-back to previous menu\n4-clear the screen\n5-exit\n");
    int choice6;
    scanf("%d",&choice6);
    switch (choice6)
    {
    case 1:
        report_land_property_sale();
        break;
    case 2:
        report_land_property_rent();
        break;
    case 3:
        report_for_user();
        break;
    case 4:
        system("cls");
        break;
    case 5:
        exit(0);
        break;

    }
}
void report_for_user()
{
    system("cls");
    int choice5;
    printf("Which of the following do you want a report on?\n");
    printf("1-residental property\n2-office property\n3-land property\n4-previous menu\n5-clear screen\n6-Exit\n");
    scanf("%d", &choice5);
    getchar();
    switch (choice5)
    {
    case 1:
        report_residental_property();
        break;
    case 2:
        report_office_property();
        break;
    case 3:
        report_land_property();
        break;
    case 4:
        reports();
        break;
    case 5:
        system("cls");
        break;
    case 6:
        exit(0);
        break;
    }

}
void reports()
{
    system("cls");
    int i;
    printf("Please enter your choice:\n");
    printf("1-report for user\n");
    printf("2-go back to previous menu\n");
    printf("3-clear the screan\n");
    printf("4-exit\n");
    scanf("%d",&i);
    getchar();
    switch(i)
    {
    case 1:
        report_for_user();
        break;
    case 2:
        mainmenu();
        break;
    case 3:
        system("cls");
        break;
    case 4:
        exit(1);
        break;
    }

}
void list_residentalsale()
{
    FILE *file;
    int residental_count = 1;
    file = fopen("residentalpropertysale.txt", "r");
    if (file == NULL) {
        printf("\033[1;31mERROR OPENING FILE\033[0m\n");
        exit(1);
    }

    struct Residential_property_information_for_sale *first = NULL, *last = NULL, *temp2;
    struct Residential_property_information_for_sale *temp = malloc(sizeof(struct Residential_property_information_for_sale));

    while (fscanf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                  temp->Municipal_area,
                  temp->Exact_address,
                  temp->Property_Type,
                  temp->Age_of_the_property,
                  temp->Size_of_the_infrastructure,
                  temp->Floor,
                  temp->Size_of_the_main_land,
                  temp->number_of_the_owner,
                  temp->Number_of_bedrooms,
                  temp->Price,
                  &temp->ID,
                  &temp->active) == 12) {

        if (first == NULL) {
            first = temp;
            last = first;
            last->next = NULL;
        } else {
            last->next = temp;
            last = temp;
            last->next = NULL;
        }

        temp = malloc(sizeof(struct Residential_property_information_for_sale));
    }

    temp2 = first;
    while (temp2 != NULL) {
        if (temp2->active == 1) {
            printf("%d. RESIDENTIAL PROPERTY ID:%d\n", residental_count, temp2->ID);
            printf("Municipal area:             %s\n", temp2->Municipal_area);
            printf("Address:                    %s\n", temp2->Exact_address);
            printf("Age of the property:        %s\n", temp2->Age_of_the_property);
            printf("Floor:                      %s\n", temp2->Floor);
            printf("Size of the infrastructure: %s\n", temp2->Size_of_the_infrastructure);
            printf("Size of the main land:      %s\n", temp2->Size_of_the_main_land);
            printf("Phone Number:               %s\n", temp2->number_of_the_owner);
            printf("Bedroom:                    %s\n", temp2->Number_of_bedrooms);
            printf("Price:                      %s\n", temp2->Price);

            if (strcmp(temp2->Property_Type, "1") == 0) {
                printf("Property Type: apartment\n");
            } else if (strcmp(temp2->Property_Type, "2") == 0) {
                printf("Property Type: Villa\n");
            }

            residental_count++;
            printf("\033[0;35m********************************************************************\e[m\n");
        }
        temp2 = temp2->next;
    }

    fclose(file);
    temp = first;
    while (temp != NULL) {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
}
void delet_residentalsale()
 {
    system("cls");
    int residental_count = 0;
    struct Residential_property_information_for_sale *first = NULL, *last = NULL, *temp2;
    FILE *file, *file2;
    file = fopen("residentalpropertysale.txt", "r+");
    if (file == NULL) {
        printf("\033[1;31mERROR OPENING FILE\033[0m\n");
        exit(1);
    }

    printf("If you know the residential ID, enter 1. Otherwise, enter 2 to view the list: ");
    int i;
    scanf("%d", &i);
    getchar();

    if (i == 2) {
        list_residentalsale();
    }

    printf("Enter the residential property ID to delete:\n");
    int id;
    scanf("%d", &id);
    getchar();

    residental_count = 0;
    system("cls");

    struct Residential_property_information_for_sale *temp = malloc(sizeof(struct Residential_property_information_for_sale));

    while (fscanf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                  temp->Municipal_area,
                  temp->Exact_address,
                  temp->Property_Type,
                  temp->Age_of_the_property,
                  temp->Size_of_the_infrastructure,
                  temp->Floor,
                  temp->Size_of_the_main_land,
                  temp->number_of_the_owner,
                  temp->Number_of_bedrooms,
                  temp->Price,
                  &temp->ID,
                  &temp->active) == 12) {

        if (first == NULL) {
            first = temp;
            last = first;
            last->next = NULL;
        } else {
            last->next = temp;
            last = temp;
            last->next = NULL;
        }

        temp = malloc(sizeof(struct Residential_property_information_for_sale));
    }

    temp2 = first;
    while (temp2 != NULL) {
        if (temp2->ID == id) {
            temp2->active = 0;
            residental_count++;
        }
        temp2 = temp2->next;
    }

    if (residental_count != 0) {
        temp2 = first;
        file2 = fopen("residentalpropertysale.txt", "w");

        while (temp2 != NULL) {
            fprintf(file2, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                    temp2->Municipal_area,
                    temp2->Exact_address,
                    temp2->Property_Type,
                    temp2->Age_of_the_property,
                    temp2->Size_of_the_infrastructure,
                    temp2->Floor,
                    temp2->Size_of_the_main_land,
                    temp2->number_of_the_owner,
                    temp2->Number_of_bedrooms,
                    temp2->Price,
                    temp2->ID,
                    temp2->active);
            temp2 = temp2->next;
        }
        printf("The residential property has been deleted successfully.\n");
        sleep(1);
    } else {
        printf("The property does not exist.\n");
        sleep(1);
    }

    fclose(file);
    fclose(file2);
    temp = first;
    while (temp != NULL) {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
}
void list_officesale()
{
    FILE* file;
    int office_count = 1;
    struct Office_property_information_for_sale* first = NULL, * last = NULL, * temp2;
    file = fopen("officepropartysale.txt", "r");
    if (file == NULL) {
        printf("\033[1;31mERROR OPENING FILE\033[0m\n");
        exit(1);
    }

    struct Office_property_information_for_sale* temp = malloc(sizeof(struct Office_property_information_for_sale));

    while (fscanf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                  temp->Municipal_area,
                  temp->Exact_address,
                  temp->Property_Type,
                  temp->Age_of_the_property,
                  temp->Size_of_the_infrastructure,
                  temp->Floor,
                  temp->Size_of_the_main_land,
                  temp->number_of_the_owner,
                  temp->Number_of_office_rooms,
                  temp->Price,
                  &temp->ID,
                  &temp->active) == 12) {

        temp->next = NULL;
        if (first == NULL) {
            first = temp;
            last = first;
        } else {
            last->next = temp;
            last = temp;
        }

        temp = malloc(sizeof(struct Office_property_information_for_sale));
    }

    temp2 = first;
    while (temp2 != NULL) {
        if (temp2->active == 1) {
            printf("%d. OFFICE PROPERTY ID:%d\n", office_count, temp2->ID);
            printf("Municipal area:             %s\n", temp2->Municipal_area);
            printf("Address:                    %s\n", temp2->Exact_address);
            printf("Age of the property:        %s\n", temp2->Age_of_the_property);
            printf("Floor:                      %s\n", temp2->Floor);
            printf("Size of the infrastructure: %s\n", temp2->Size_of_the_infrastructure);
            printf("Size of the main land:      %s\n", temp2->Size_of_the_main_land);
            printf("Phone Number:               %s\n", temp2->number_of_the_owner);
            printf("Number of office rooms:     %s\n", temp2->Number_of_office_rooms);
            printf("Price:                      %s\n", temp2->Price);

            if (strcmp(temp2->Property_Type, "1") == 0)
            {
                printf("Property Type:        official administrative document\n");
            }
            else if (strcmp(temp2->Property_Type, "2") == 0)
            {
                printf("Property Type:         administrative position");
            }

            office_count++;
            printf("\033[0;35m********************************************************************\e[m\n");
        }
        temp2 = temp2->next;
    }
    fclose(file);

    // Free allocated memory
    temp = first;
    while (temp != NULL) {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
}
void delete_officesale()
{
    system("cls");
    int office_count = 0;
    struct Office_property_information_for_sale *first = NULL, *last = NULL, *temp2;
    FILE* file, *file2;
    file = fopen("officepropartysale.txt", "r+");
    if (file == NULL) {
        printf("\033[1;31mERROR OPENING FILE\033[0m\n");
        exit(1);
    }

    printf("If you know the office ID, enter 1. Otherwise, enter 2 to view the list: ");
    int i;
    scanf("%d", &i);
    getchar();

    if (i == 2) {
        list_officesale();
    }

    printf("Enter the office property ID to delete:\n");
    int id;
    scanf("%d", &id);
    getchar();

    office_count = 0;
    system("cls");

    struct Office_property_information_for_sale* temp = malloc(sizeof(struct Office_property_information_for_sale));

    while (fscanf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                  temp->Municipal_area,
                  temp->Exact_address,
                  temp->Property_Type,
                  temp->Age_of_the_property,
                  temp->Size_of_the_infrastructure,
                  temp->Floor,
                  temp->Size_of_the_main_land,
                  temp->number_of_the_owner,
                  temp->Number_of_office_rooms,
                  temp->Price,
                  &temp->ID,
                  &temp->active) == 12) {

        temp->next = NULL;
        if (first == NULL) {
            first = temp;
            last = first;
        } else {
            last->next = temp;
            last = temp;
        }

        temp = malloc(sizeof(struct Office_property_information_for_sale));
    }

    temp2 = first;
    while (temp2 != NULL) {
        if (temp2->ID == id) {
            temp2->active = 0;
            office_count++;
        }
        temp2 = temp2->next;
    }

    if (office_count != 0) {
        temp2 = first;
        file2 = fopen("officepropartysale.txt", "w");

        while (temp2 != NULL) {
            fprintf(file2, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                    temp2->Municipal_area,
                    temp2->Exact_address,
                    temp2->Property_Type,
                    temp2->Age_of_the_property,
                    temp2->Size_of_the_infrastructure,
                    temp2->Floor,
                    temp2->Size_of_the_main_land,
                    temp2->number_of_the_owner,
                    temp2->Number_of_office_rooms,
                    temp2->Price,
                    temp2->ID,
                    temp2->active);
            temp2 = temp2->next;
        }
        printf("The office property has been deleted successfully.\n");
        sleep(1);
    } else {
        printf("The property does not exist.\n");
        sleep(1);
    }

    fclose(file);
    fclose(file2);
    temp = first;
    while (temp != NULL) {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }

}
void list_landsales()
{
    FILE *file;
    int land_count = 1;
    struct Land_sales_information *first = NULL, *last = NULL, *temp2;
    file = fopen("landsale.txt", "r");
    if (file == NULL)
    {
        printf("\033[1;31mERROR OPENING FILE\033[0m\n");
        exit(1);
    }

    struct Land_sales_information *temp = malloc(sizeof(struct Land_sales_information));

    while (fscanf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                  temp->Municipal_area,
                  temp->Exact_address,
                  temp->land_Type,
                  temp->Size_of_the_land,
                  temp->number_of_the_owner,
                  temp->Price,
                  &temp->ID,
                  &temp->active) == 8)
    {
        temp->next = NULL;
        if (first == NULL)
        {
            first = temp;
            last = first;
        }
        else
        {
            last->next = temp;
            last = temp;
        }

        temp = malloc(sizeof(struct Land_sales_information));
    }

    temp2 = first;
    while (temp2 != NULL)
    {
        if (temp2->active == 1)
        {
            printf("%d. LAND ID:%d\n", land_count, temp2->ID);
            printf("Municipal area:    %s\n", temp2->Municipal_area);
            printf("Address:           %s\n", temp2->Exact_address);
            if(strcmp(temp2->land_Type , "1") == 0)
            {
                printf("Land type:            Agricultural\n");
            }
            else if(strcmp(temp2->land_Type ,"2") == 0)
            {
                printf("Land type:            urban\n");
            }
            printf("Size of the land:  %s\n", temp2->Size_of_the_land);
            printf("Phone Number:      %s\n", temp2->number_of_the_owner);
            printf("Price:             %s\n", temp2->Price);

            land_count++;
            printf("\033[0;35m********************************************************************\e[m\n");
        }
        temp2 = temp2->next;
    }
    fclose(file);

    // Free allocated memory
    temp = first;
    while (temp != NULL)
    {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
}
void delete_landsales()
{
     system("cls");
    int land_count = 0;
    struct Land_sales_information *first = NULL, *last = NULL, *temp2;
    FILE *file, *file2;
    file = fopen("landsale.txt", "r+");
    if (file == NULL)
    {
        printf("\033[1;31mERROR OPENING FILE\033[0m\n");
        exit(1);
    }

    printf("If you know the land ID, enter 1. Otherwise, enter 2 to view the list: ");
    int i;
    scanf("%d", &i);
    getchar();

    if (i == 2)
    {
        list_landsales();
    }

    printf("Enter the land ID to delete:\n");
    int id;
    scanf("%d", &id);
    getchar();

    land_count = 0;
    system("cls");

    struct Land_sales_information *temp = malloc(sizeof(struct Land_sales_information));

    while (fscanf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                  temp->Municipal_area,
                  temp->Exact_address,
                  temp->land_Type,
                  temp->Size_of_the_land,
                  temp->number_of_the_owner,
                  temp->Price,
                  &temp->ID,
                  &temp->active) == 8)
    {
        temp->next = NULL;
        if (first == NULL)
        {
            first = temp;
            last = first;
        }
        else
        {
            last->next = temp;
            last = temp;
        }

        temp = malloc(sizeof(struct Land_sales_information));
    }

    temp2 = first;
    while (temp2 != NULL)
    {
        if (temp2->ID == id)
        {
            temp2->active = 0;
            land_count++;
        }
        temp2 = temp2->next;
    }

    if (land_count != 0)
    {
        temp2 = first;
        file2 = fopen("landsale.txt", "w");

        while (temp2 != NULL)
        {
            fprintf(file2, "%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                    temp2->Municipal_area,
                    temp2->Exact_address,
                    temp2->land_Type,
                    temp2->Size_of_the_land,
                    temp2->number_of_the_owner,
                    temp2->Price,
                    temp2->ID,
                    temp2->active);
            temp2 = temp2->next;
        }
        printf("The land has been deleted successfully.\n");
        sleep(1);
    }
    else
    {
        printf("The land does not exist.\n");
        sleep(1);
    }

    fclose(file);
    fclose(file2);
    temp = first;
    while (temp != NULL)
    {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
}
void delet_sale()
{
    system("cls");
    printf("in wich case you wanna dellet information?\n");
    printf("1-residental sale\n2-office sale\n3-land sale\n");
    printf("4-back to previous menu\n5-exit\n");
    int choice;
    scanf("%d",&choice);
    getchar();
    switch(choice){
case 1:
    delet_residentalsale();
    break;
case 2:
    delete_officesale();
    break;
case 3:
    delete_landsales();
    break;
case 4:
    delet();
    break;
case 5:
    exit(1);
    break;
default:
    printf("Invalid choice. Please choose a valid option.\n");
    break;
   }
}
void list_residentalrent()
 {
    FILE* file;
    int residental_count = 1;
    struct Residential_property_information_for_rent* first = NULL, * last = NULL, * temp2;
    file = fopen("residentalpropertyrent.txt", "r");
    if (file == NULL) {
        printf("\033[1;31mERROR OPENING FILE\033[0m\n");
        exit(1);
    }

    struct Residential_property_information_for_rent* temp = malloc(sizeof(struct Residential_property_information_for_rent));

    while (fscanf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                  temp->Municipal_area,
                  temp->Exact_address,
                  temp->Property_Type,
                  temp->Age_of_the_property,
                  temp->Size_of_the_infrastructure,
                  temp->Floor,
                  temp->Size_of_the_main_land,
                  temp->number_of_the_owner,
                  temp->Number_of_bedrooms,
                  temp->mortgage,
                  temp->Rent,
                  &temp->ID,
                  &temp->active) == 13) {
        temp->next = NULL;
        if (first == NULL) {
            first = temp;
            last = first;
        } else {
            last->next = temp;
            last = temp;
        }
        temp = malloc(sizeof(struct Residential_property_information_for_rent));
    }
    fclose(file);

    temp2 = first;
    while (temp2 != NULL) {
        if (temp2->active == 1) {
            printf("%d. RESIDENTIAL PROPERTY ID:%d\n", residental_count, temp2->ID);
            printf("Municipal area:             %s\n", temp2->Municipal_area);
            printf("Address:                    %s\n", temp2->Exact_address);
            printf("Age of the property:        %s\n", temp2->Age_of_the_property);
            printf("Floor:                      %s\n", temp2->Floor);
            printf("Size of the infrastructure: %s\n", temp2->Size_of_the_infrastructure);
            printf("Size of the main land:      %s\n", temp2->Size_of_the_main_land);
            printf("Phone Number:               %s\n", temp2->number_of_the_owner);
            printf("Bedroom:                    %s\n", temp2->Number_of_bedrooms);
            printf("mortgage:                   %s\n", temp2->mortgage);
            printf("Rent:                       %s\n", temp2->Rent);

            if (strcmp(temp2->Property_Type, "1") == 0) {
                printf("Property Type: apartment\n");
            } else if (strcmp(temp2->Property_Type, "2") == 0) {
                printf("Property Type: Villa\n");
            }

            residental_count++;
            printf("\033[0;35m********************************************************************\e[m\n");
        }
        temp2 = temp2->next;
    }

    // Free allocated memory
    temp = first;
    while (temp != NULL) {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
}
void delete_residentalrent()
{
    system("cls");
    int residental_count = 0;
    struct Residential_property_information_for_rent* first = NULL, * last = NULL, * temp2;
    FILE* file, * file2;
    file = fopen("residentalpropertyrent.txt", "r+");
    if (file == NULL) {
        printf("\033[1;31mERROR OPENING FILE\033[0m\n");
        exit(1);
    }

    printf("If you know the residential ID, enter 1. Otherwise, enter 2 to view the list: ");
    int i;
    scanf("%d", &i);
    getchar();

    if (i == 2) {
        list_residentalrent();
    }
    printf("Enter the residential property ID to delete:\n");
    int id;
    scanf("%d", &id);
    getchar();

    residental_count = 0;
    system("cls");

    struct Residential_property_information_for_rent* temp = malloc(sizeof(struct Residential_property_information_for_rent));

    while (fscanf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                  temp->Municipal_area,
                  temp->Exact_address,
                  temp->Property_Type,
                  temp->Age_of_the_property,
                  temp->Size_of_the_infrastructure,
                  temp->Floor,
                  temp->Size_of_the_main_land,
                  temp->number_of_the_owner,
                  temp->Number_of_bedrooms,
                  temp->mortgage,
                  temp->Rent,
                  &temp->ID,
                  &temp->active) == 13) {
        if (first == NULL) {
            first = temp;
            last = first;
            last->next = NULL;
        } else {
            last->next = temp;
            last = temp;
            last->next = NULL;
        }
        temp = malloc(sizeof(struct Residential_property_information_for_rent));
    }
    temp2 = first;
    while (temp2 != NULL) {
        if (temp2->ID == id) {
            temp2->active = 0;
            residental_count++;
        }
        temp2 = temp2->next;
    }
    if (residental_count != 0) {
        temp2 = first;
        file2 = fopen("residentalpropertyrent.txt", "w");

        while (temp2 != NULL) {
            fprintf(file2, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                    temp2->Municipal_area,
                    temp2->Exact_address,
                    temp2->Property_Type,
                    temp2->Age_of_the_property,
                    temp2->Size_of_the_infrastructure,
                    temp2->Floor,
                    temp2->Size_of_the_main_land,
                    temp2->number_of_the_owner,
                    temp2->Number_of_bedrooms,
                    temp2->mortgage,
                    temp2->Rent,
                    temp2->ID,
                    temp2->active);
            temp2 = temp2->next;
        }
        printf("The residential property has been deleted successfully.\n");
        sleep(1);
    } else {
        printf("The property does not exist.\n");
        sleep(1);
    }
    fclose(file);
    fclose(file2);
    temp = first;
    while (temp != NULL) {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
}
void list_officerent()
{
     FILE *file;
    int office_count = 1;
    struct Office_property_information_for_rent *first = NULL, *last = NULL, *temp2;
    file = fopen("officepropertyrent.txt", "r");
    if (file == NULL)
    {
        printf("\033[1;31mERROR OPENING FILE\033[0m\n");
        exit(1);
    }

    struct Office_property_information_for_rent *temp = malloc(sizeof(struct Office_property_information_for_rent));

    while (fscanf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                  temp->Municipal_area,
                  temp->Exact_address,
                  temp->Property_Type,
                  temp->Age_of_the_property,
                  temp->Size_of_the_infrastructure,
                  temp->Floor,
                  temp->Size_of_the_main_land,
                  temp->number_of_the_owner,
                  temp->Number_of_office_rooms,
                  temp->mortgage,
                  temp->Rent,
                  &temp->ID,
                  &temp->active) == 13)
    {
        temp->next = NULL;
        if (first == NULL)
        {
            first = temp;
            last = first;
        }
        else
        {
            last->next = temp;
            last = temp;
        }

        temp = malloc(sizeof(struct Office_property_information_for_rent));
    }

    temp2 = first;
    while (temp2 != NULL)
    {
        if (temp2->active == 1)
        {
            printf("%d. OFFICE PROPERTY ID:%d\n", office_count, temp2->ID);
            printf("Municipal area:             %s\n", temp2->Municipal_area);
            printf("Address:                    %s\n", temp2->Exact_address);
            printf("Age of the property:        %s\n", temp2->Age_of_the_property);
            printf("Floor:                      %s\n", temp2->Floor);
            printf("Size of the infrastructure: %s\n", temp2->Size_of_the_infrastructure);
            printf("Size of the main land:      %s\n", temp2->Size_of_the_main_land);
            printf("Phone Number:               %s\n", temp2->number_of_the_owner);
            printf("Number of office rooms:     %s\n", temp2->Number_of_office_rooms);
            printf("Mortgage:                   %s\n", temp2->mortgage);
            printf("Rent:                       %s\n", temp2->Rent);

            if (strcmp(temp2->Property_Type, "1") == 0)
            {
                printf("Property Type:        official administrative document\n");
            }
            else if (strcmp(temp2->Property_Type, "2") == 0)
            {
                printf("Property Type:         administrative position");
            }

            office_count++;
            printf("\033[0;35m********************************************************************\e[m\n");
        }
        temp2 = temp2->next;
    }
    fclose(file);

    // Free allocated memory
    temp = first;
    while (temp != NULL)
    {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
}
void delete_officerent()
{
    system("cls");
    int office_count = 0;
    struct Office_property_information_for_rent *first = NULL, *last = NULL, *temp2;
    FILE *file, *file2;
    file = fopen("officepropertyrent.txt", "r+");
    if (file == NULL)
    {
        printf("\033[1;31mERROR OPENING FILE\033[0m\n");
        exit(1);
    }

    printf("If you know the office ID, enter 1. Otherwise, enter 2 to view the list: ");
    int i;
    scanf("%d", &i);
    getchar();

    if (i == 2)
    {
        list_officerent();
    }

    printf("Enter the office property ID to delete:\n");
    int id;
    scanf("%d", &id);
    getchar();

    office_count = 0;
    system("cls");

    struct Office_property_information_for_rent *temp = malloc(sizeof(struct Office_property_information_for_rent));

    while (fscanf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                  temp->Municipal_area,
                  temp->Exact_address,
                  temp->Property_Type,
                  temp->Age_of_the_property,
                  temp->Size_of_the_infrastructure,
                  temp->Floor,
                  temp->Size_of_the_main_land,
                  temp->number_of_the_owner,
                  temp->Number_of_office_rooms,
                  temp->mortgage,
                  temp->Rent,
                  &temp->ID,
                  &temp->active) == 13)
    {

        temp->next = NULL;
        if (first == NULL)
        {
            first = temp;
            last = first;
        }
        else
        {
            last->next = temp;
            last = temp;
        }

        temp = malloc(sizeof(struct Office_property_information_for_rent));
    }

    temp2 = first;
    while (temp2 != NULL)
    {
        if (temp2->ID == id)
        {
            temp2->active = 0;
            office_count++;
        }
        temp2 = temp2->next;
    }

    if (office_count != 0)
    {
        temp2 = first;
        file2 = fopen("officepropertyrent.txt", "w");

        while (temp2 != NULL)
        {
            fprintf(file2, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                    temp2->Municipal_area,
                    temp2->Exact_address,
                    temp2->Property_Type,
                    temp2->Age_of_the_property,
                    temp2->Size_of_the_infrastructure,
                    temp2->Floor,
                    temp2->Size_of_the_main_land,
                    temp2->number_of_the_owner,
                    temp2->Number_of_office_rooms,
                    temp2->mortgage,
                    temp2->Rent,
                    temp2->ID,
                    temp2->active);
            temp2 = temp2->next;
        }
        printf("The office property has been deleted successfully.\n");
        sleep(1);
    }
    else
    {
        printf("The property does not exist.\n");
        sleep(1);
    }

    fclose(file);
    fclose(file2);
    temp = first;
    while (temp != NULL)
    {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
}
void list_landrent()
{
    FILE *file;
    int land_count = 1;
    struct Land_rent_information *first = NULL, *last = NULL, *temp2;
    file = fopen("landrent.txt", "r");
    if (file == NULL)
    {
        printf("\033[1;31mERROR OPENING FILE\033[0m\n");
        exit(1);
    }

    struct Land_rent_information *temp = malloc(sizeof(struct Land_rent_information));

    while (fscanf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                  temp->Municipal_area,
                  temp->Exact_address,
                  temp->land_Type,
                  temp->Size_of_the_land,
                  temp->number_of_the_owner,
                  temp->mortgage,
                  temp->Rent,
                  &temp->ID,
                  &temp->active) == 9)
    {
        temp->next = NULL;
        if (first == NULL)
        {
            first = temp;
            last = first;
        }
        else
        {
            last->next = temp;
            last = temp;
        }

        temp = malloc(sizeof(struct Land_rent_information));
    }

    temp2 = first;
    while (temp2 != NULL)
    {
        if (temp2->active == 1)
        {
            printf("%d. LAND ID:%d\n", land_count, temp2->ID);
            printf("Municipal area:     %s\n", temp2->Municipal_area);
            printf("Address:            %s\n", temp2->Exact_address);
            if(strcmp(temp2->land_Type , "1") == 0)
            {
                printf("Land type:            Agricultural\n");
            }
            else if(strcmp(temp2->land_Type ,"2") == 0)
            {
                printf("Land type:            urban\n");
            }
            printf("Size of the land:   %s\n", temp2->Size_of_the_land);
            printf("Phone Number:       %s\n", temp2->number_of_the_owner);
            printf("Mortgage:           %s\n", temp2->mortgage);
            printf("Rent:               %s\n", temp2->Rent);

            land_count++;
            printf("\033[0;35m********************************************************************\e[m\n");
        }
        temp2 = temp2->next;
    }
    fclose(file);

    // Free allocated memory
    temp = first;
    while (temp != NULL)
    {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
}
void delete_landrent()
{
     system("cls");
    int land_count = 0;
    struct Land_rent_information *first = NULL, *last = NULL, *temp2;
    FILE *file, *file2;
    file = fopen("landrent.txt", "r+");
    if (file == NULL)
    {
        printf("\033[1;31mERROR OPENING FILE\033[0m\n");
        exit(1);
    }

    printf("If you know the land ID, enter 1. Otherwise, enter 2 to view the list: ");
    int i;
    scanf("%d", &i);
    getchar();

    if (i == 2)
    {
        list_landrent();
    }

    printf("Enter the land ID to delete:\n");
    int id;
    scanf("%d", &id);
    getchar();

    land_count = 0;
    system("cls");

    struct Land_rent_information *temp = malloc(sizeof(struct Land_rent_information));

    while (fscanf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                  temp->Municipal_area,
                  temp->Exact_address,
                  temp->land_Type,
                  temp->Size_of_the_land,
                  temp->number_of_the_owner,
                  temp->mortgage,
                  temp->Rent,
                  &temp->ID,
                  &temp->active) == 9)
    {
        temp->next = NULL;
        if (first == NULL)
        {
            first = temp;
            last = first;
        }
        else
        {
            last->next = temp;
            last = temp;
        }

        temp = malloc(sizeof(struct Land_rent_information));
    }

    temp2 = first;
    while (temp2 != NULL)
    {
        if (temp2->ID == id)
        {
            temp2->active = 0;
            land_count++;
        }
        temp2 = temp2->next;
    }

    if (land_count != 0)
    {
        temp2 = first;
        file2 = fopen("landrent.txt", "w");

        while (temp2 != NULL)
        {
            fprintf(file2, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n",
                    temp2->Municipal_area,
                    temp2->Exact_address,
                    temp2->land_Type,
                    temp2->Size_of_the_land,
                    temp2->number_of_the_owner,
                    temp2->mortgage,
                    temp2->Rent,
                    temp2->ID,
                    temp2->active);
                  temp2 = temp2->next;
        }
        printf("The land has been deleted successfully.\n");
        sleep(1);
    }
    else
    {
        printf("The land does not exist.\n");
        sleep(1);
    }

    fclose(file);
    fclose(file2);
    temp = first;
    while (temp != NULL)
    {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
}
void delet_rent()
{
    system("cls");
    printf("Wich rent informatin you wanna delet?\n");
    printf("1-Residental rent\n2-Office rent\n3-land rent\n4-Clear the screen\n5-Back to previous menu\n6-Exit\n");
    int i;
    scanf("%d",&i);
    switch(i)
    {
    case 1:
        delete_residentalrent();
        break;
    case 2:
        delete_officerent();
        break;
    case 3:
        delete_landrent();
        break;
    case 4:
        system("cls");
        break;
    case 5:
        delet();
        break;
    case 6:
        exit(1);
        break;
    }
}
void delet()
{
    system("cls");
    printf("wich information you wanna delet?\n");
    printf("1-sale information\n2-rent information\n3-back to previous menu\n4-exit\n");
    int choice;
    scanf("%d",&choice);
    getchar();
    switch(choice)
    {
    case 1:
        delet_sale();
        break;
    case 2:
        delet_rent();
        break;
    case 3:
        mainmenu();
        break;
    case 4:
        exit(1);
        break;
     default:
        printf("Invalid choice. Please choose a valid option.\n");
        break;
    }
}
void setting_name()
{
    system("cls");
    char name2[50];
    struct sign_upinfo *first=NULL , *last=NULL , *temp ,*temp2;
    FILE *file,*file2;
    file = fopen("admin_information.txt","r+");
    if (file == NULL)
    {
        printf("\e[31mERROR opening file.\e[m\n");
        exit(1);
    }
    while(1)
    {
        temp = malloc(sizeof(struct sign_upinfo));
        if(fscanf(file,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
                  temp->name,
                  temp->lastname,
                  temp->username,
                  temp->national_code,
                  temp->phonenumber,
                  temp->Email,
                  temp->password) != 7)
        {
            break;
        }
          if(first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next = temp;
            last = temp;
            last->next = NULL;
        }
    }
    temp2 = first;
    printf("please enter the NEW name:");
    char name[50];
    scanf("%s", name);
    getchar();
    while(temp2 != NULL)
    {
        if(strcmp(username,temp2->username) == 0)
        {
            strcpy(temp2->name , name);
        }
        temp2 = temp2->next;
    }
    file2 = fopen("admin_information.txt","w");
    if(file2 == NULL)
    {
        printf("memory allocation failed");
        exit(1);
    }
    temp = first;
    while(temp != NULL)
    {
        fprintf(file2,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
                  temp->name,
                  temp->lastname,
                  temp->username,
                  temp->national_code,
                  temp->phonenumber,
                  temp->Email,
                  temp->password);
                  temp=temp->next;
    }
    fclose(file);
    fclose(file2);
    printf("\e[32mChanges saved successfully\e[m");

}
void setting_lastname()
{

    system("cls");
    char lastname[50];
    struct sign_upinfo *first = NULL, *last = NULL, *temp, *temp2;
    FILE *file, *file2;
    file = fopen("admin_information.txt", "r+");
    if (file == NULL)
    {
        printf("\e[31mERROR opening file.\e[m\n");
        exit(1);
    }
    while (1)
    {
        temp = malloc(sizeof(struct sign_upinfo));
        if (fscanf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
                   temp->name,
                   temp->lastname,
                   temp->username,
                   temp->national_code,
                   temp->phonenumber,
                   temp->Email,
                   temp->password) != 7)
        {
            break;
        }
        if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next = temp;
            last = temp;
            last->next = NULL;
        }
    }
    temp2 = first;
    printf("Please enter the NEW last name:");
    scanf("%s", lastname);
    getchar();
    while (temp2 != NULL)
    {
        if (strcmp(username, temp2->username) == 0)
        {
            strcpy(temp2->lastname, lastname);
        }
        temp2 = temp2->next;
    }
    file2 = fopen("admin_information.txt", "w");
    if (file2 == NULL)
    {
        printf("Memory allocation failed");
        exit(1);
    }
    temp = first;
    while (temp != NULL)
    {
        fprintf(file2, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
                temp->name,
                temp->lastname,
                temp->username,
                temp->national_code,
                temp->phonenumber,
                temp->Email,
                temp->password);
        temp = temp->next;
    }
    fclose(file);
    fclose(file2);
    printf("\e[32mChanges saved successfully\e[m");
}
void setting_nationalcode()
{
    system("cls");
    char national_code[50];
    struct sign_upinfo *first = NULL, *last = NULL, *temp, *temp2;
    FILE *file, *file2;
    file = fopen("admin_information.txt", "r+");
    if (file == NULL)
    {
        printf("\e[31mERROR opening file.\e[m\n");
        exit(1);
    }
    while (1)
    {
        temp = malloc(sizeof(struct sign_upinfo));
        if (fscanf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
                   temp->name,
                   temp->lastname,
                   temp->username,
                   temp->national_code,
                   temp->phonenumber,
                   temp->Email,
                   temp->password) != 7)
        {
            break;
        }
        if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next = temp;
            last = temp;
            last->next = NULL;
        }
    }
    temp2 = first;
    printf("Please enter the NEW national code:");
    scanf("%s", national_code);
    getchar();
    while (temp2 != NULL)
    {
        if (strcmp(username, temp2->username) == 0)
        {
            strcpy(temp2->national_code, national_code);
        }
        temp2 = temp2->next;
    }
    file2 = fopen("admin_information.txt", "w");
    if (file2 == NULL)
    {
        printf("Memory allocation failed");
        exit(1);
    }
    temp = first;
    while (temp != NULL)
    {
        fprintf(file2, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
                temp->name,
                temp->lastname,
                temp->username,
                temp->national_code,
                temp->phonenumber,
                temp->Email,
                temp->password);
        temp = temp->next;
    }
    fclose(file);
    fclose(file2);
    printf("\e[32mChanges saved successfully\e[m");
}
void setting_phonenumber()
{
    system("cls");
    char phonenumber[50];
    struct sign_upinfo *first = NULL, *last = NULL, *temp, *temp2;
    FILE *file, *file2;
    file = fopen("admin_information.txt", "r+");
    if (file == NULL)
    {
        printf("\e[31mERROR opening file.\e[m\n");
        exit(1);
    }
    while (1)
    {
        temp = malloc(sizeof(struct sign_upinfo));
        if (fscanf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
                   temp->name,
                   temp->lastname,
                   temp->username,
                   temp->national_code,
                   temp->phonenumber,
                   temp->Email,
                   temp->password) != 7)
        {
            break;
        }
        if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next = temp;
            last = temp;
            last->next = NULL;
        }
    }
    temp2 = first;
    printf("Please enter the NEW phone number:");
    scanf("%s", phonenumber);
    getchar();
    while (temp2 != NULL)
    {
        if (strcmp(username, temp2->username) == 0)
        {
            strcpy(temp2->phonenumber, phonenumber);
        }
        temp2 = temp2->next;
    }
    file2 = fopen("admin_information.txt", "w");
    if (file2 == NULL)
    {
        printf("Memory allocation failed");
        exit(1);
    }
    temp = first;
    while (temp != NULL)
    {
        fprintf(file2, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
                temp->name,
                temp->lastname,
                temp->username,
                temp->national_code,
                temp->phonenumber,
                temp->Email,
                temp->password);
        temp = temp->next;
    }
    fclose(file);
    fclose(file2);
    printf("\e[32mChanges saved successfully\e[m");
}
void setting_email()
{
    system("cls");
    char email[50];
    struct sign_upinfo *first = NULL, *last = NULL, *temp, *temp2;
    FILE *file, *file2;
    file = fopen("admin_information.txt", "r+");
    if (file == NULL)
    {
        printf("\e[31mERROR opening file.\e[m\n");
        exit(1);
    }
    while (1)
    {
        temp = malloc(sizeof(struct sign_upinfo));
        if (fscanf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
                   temp->name,
                   temp->lastname,
                   temp->username,
                   temp->national_code,
                   temp->phonenumber,
                   temp->Email,
                   temp->password) != 7)
        {
            break;
        }
        if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next = temp;
            last = temp;
            last->next = NULL;
        }
    }
    temp2 = first;
    printf("Please enter the NEW email:");
    scanf("%s", email);
    getchar();
    while (temp2 != NULL)
    {
        if (strcmp(username, temp2->username) == 0)
        {
            strcpy(temp2->Email, email);
        }
        temp2 = temp2->next;
    }
    file2 = fopen("admin_information.txt", "w");
    if (file2 == NULL)
    {
        printf("Memory allocation failed");
        exit(1);
    }
    temp = first;
    while (temp != NULL)
    {
        fprintf(file2, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
                temp->name,
                temp->lastname,
                temp->username,
                temp->national_code,
                temp->phonenumber,
                temp->Email,
                temp->password);
        temp = temp->next;
    }
    fclose(file);
    fclose(file2);
    printf("\e[32mChanges saved successfully\e[m");
}
void setting_password()
{
    system("cls");
    char password[50];
    struct sign_upinfo *first = NULL, *last = NULL, *temp, *temp2;
    FILE *file, *file2;
    file = fopen("admin_information.txt", "r+");
    if (file == NULL)
    {
        printf("\e[31mERROR opening file.\e[m\n");
        exit(1);
    }
    while (1)
    {
        temp = malloc(sizeof(struct sign_upinfo));
        if (fscanf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
                   temp->name,
                   temp->lastname,
                   temp->username,
                   temp->national_code,
                   temp->phonenumber,
                   temp->Email,
                   temp->password) != 7)
        {
            break;
        }
        if (first == NULL)
        {
            first = temp;
            last = first;
            last->next = NULL;
        }
        else
        {
            last->next = temp;
            last = temp;
            last->next = NULL;
        }
    }
    temp2 = first;
    printf("Please enter the NEW password:");
    scanf("%s", password);
    getchar();
    while (temp2 != NULL)
    {
        if (strcmp(username, temp2->username) == 0)
        {
            strcpy(temp2->password, password);
        }
        temp2 = temp2->next;
    }
    file2 = fopen("admin_information.txt", "w");
    if (file2 == NULL)
    {
        printf("Memory allocation failed");
        exit(1);
    }
    temp = first;
    while (temp != NULL)
    {
        fprintf(file2, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
                temp->name,
                temp->lastname,
                temp->username,
                temp->national_code,
                temp->phonenumber,
                temp->Email,
                temp->password);
        temp = temp->next;
    }
    fclose(file);
    fclose(file2);
    printf("\e[32mChanges saved successfully\e[m");
}
void setting()
{
    system("cls");
    printf("wich information you wannna change ?\n");
    printf("1-Name\n2-Lastname\n3-National code\n4-Phone number\n5-Email\n");
    printf("6-Paaword\n7-back to previous menu\n8-exit\n");
    int choice;
    scanf("%d",&choice);
    getchar();
    switch(choice)
    {
    case 1:
        setting_name();
        break;
    case 2:
        setting_lastname();
        break;
    case 3:
        setting_nationalcode();
        break;
    case 4:
        setting_phonenumber();
        break;
    case 5:
        setting_email();
        break;
    case 6:
        setting_password();
        break;
    case 7:
        mainmenu();
        break;
    case 8:
        exit(1);
        break;
    }
}
void mainmenu()
{
    system("cls");
    int choice2;
    printf("please enter your choice:\n");
    printf("1. Register new information\n");
    printf("2. Delet existing information\n");
    printf("3. Reports\n");
    printf("4. User account settings\n");
    printf("5. Sign out of the user account\n");//برگشت به منوی قبلی
    scanf("%d", &choice2);
    getchar();
    printf("\n");
    switch (choice2)
    {
    case 1:
        Register_new_information();
        break;
    case 2:
        delet();
        break;
    case 3:
        reports();
        break;
    case 4:
        setting();
        break;
    case 5:
        main();
        break;

    }
}
int main()
{
    system("cls");
    int choice;
    printf("chose what do you want to do\n*****************\n1-signup\n2-signin\n3-exit\n");
    scanf("%d", &choice);
    getchar();
    switch(choice)
    {
    case 1 :
        sign_up();
        break;
    case 2 :
        if (sign_in())
        {
            mainmenu();
        }
        break;
    case 3 :
        exit(1);
        break;
    }

    return 0;
}




