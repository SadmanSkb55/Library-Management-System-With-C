#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#define IN 1
#define OUT 0

#define MAX_NAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 25


void Addbook();
void Searchbook();
void Displaybook();
void Author();
void Titlelist();
void Stock();
void Issue();
void bookret();
void Addmembr();
void Exit();
void Deletebook(); // Added function prototype for deleting a book
void Deletemembr(); // Added function prototype for deleting a member
void Modifybook(); // Added function prototype for modifying a book
void Modifymembr(); // Added function prototype for modifying a member

void clearScreen() {
    // Windows
    #ifdef _WIN32
    system("cls");
    // Unix-like (Linux, macOS)
    #else
    system("clear");
    #endif
}

int Login();
void Signup();


char info[500];

struct User {
    int id;
    char name[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct
{
  int bid;
  char bname[25] ;
  char author[25];
  int nooftitles;
  char titles[500];
  int status;
}book;

struct
{
  int mid;
  char mname[25] ;
  char department[25];
  int availibcard;
  int phno;
}membr;

//initializing the files used in the program
FILE *librecord;
FILE *membrrecord;
FILE *fp1;
FILE *fp2;
FILE *temp1;
FILE *temp2;

int main() {
    int loggedIn = 0;
    int choice;

    // Loop until the user chooses to exit
    while (1) {
            clearScreen();
        if (!loggedIn) {
            // Display login/signup options
            printf("\n\t\t---Library Management System---\n");
            printf("1. Login\n2. Signup\n3. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    if (Login())
                        loggedIn = 1;
                    else
                        printf("Login failed. Invalid credentials!\n");
                    break;
                case 2:
                    Signup();
                    break;
                case 3:
                    printf("Exiting...\n");
                    exit(0);
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        } else {
            // Display menu options after login
            printf("\n\t--MENU--\n");
            printf("1. Add A New Book\n");
            printf("2. Search a book\n");
            printf("3. Display Complete Information\n");
            printf("4. Display All Books of An Author\n");
            printf("5. List Titles of a Book\n");
            printf("6. List Count of Books (Issued & On Stock)\n");
            printf("7. To Issue a Book\n");
            printf("8. To Return a Book\n");
            printf("9. Add A New Member\n");
            printf("10. Delete A Book\n");
            printf("11. Delete A Member\n");
            printf("12. Modify A Book\n");
            printf("13. Modify A Member\n");
            printf("14. Exit the program\n\n");
            printf("Enter your choice <1-14>: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    Addbook();
                    break;
                case 2:
                    Searchbook();
                    break;
                case 3:
                    Displaybook();
                    break;
                case 4:
                    Author();
                    break;
                case 5:
                    Titlelist();
                    break;
                case 6:
                    Stock();
                    break;
                case 7:
                    Issue();
                    break;
                case 8:
                    bookret();
                    break;
                case 9:
                    Addmembr();
                    break;
                case 10:
                    Deletebook();
                    break;
                case 11:
                    Deletemembr();
                    break;
                case 12:
                    Modifybook();
                    break;
                case 13:
                    Modifymembr();
                    break;
                case 14:
                    Exit();
                    break;
                default:
                    printf("Invalid Input...\n");
            }
        }
    }
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Function to sign up a new user
void Signup() {
    struct User user;
    FILE *userFile = fopen("userrecord.txt", "a+");
    printf("Enter your name: ");
    scanf("%s", user.name);
    printf("Enter your ID: ");
    scanf("%d", &user.id);

    printf("Enter your password: ");
    int i = 0;
    char ch;
    while (1) {
        ch = _getch(); // Read a character without echoing it to the console
        if (ch == '\r') { // Check if Enter key is pressed
            user.password[i] = '\0'; // Null-terminate the string
            break;
        } else if (ch != '\b') { // Ignore Backspace character itself
            user.password[i++] = ch;
            printf("*"); // Print '*' to mask the character
        }
    }
    fprintf(userFile, "%d %s %s\n", user.id, user.name, user.password);
    fclose(userFile);
    printf("\nSignup successful!\n");
}

// Function to log in an existing user
int Login() {
    int id;
    char password[25];
    printf("Enter your ID: ");
    scanf("%d", &id);

    printf("Enter your password: ");
    int i = 0;
    char ch;
    while (1) {
        ch = _getch(); // Read a character without echoing it to the console
        if (ch == '\r') { // Check if Enter key is pressed
            password[i] = '\0'; // Null-terminate the string
            break;
        } else if (ch != '\b') { // Ignore Backspace character itself
            password[i++] = ch;
            printf("*"); // Print '*' to mask the character
        }
    }
    printf("\n");

    FILE *userFile = fopen("userrecord.txt", "r");
    if (userFile == NULL) {
        printf("User database not found!\n");
        return 0;
    }
    struct User user;
    while (fscanf(userFile, "%d %s %s\n", &user.id, user.name, user.password) != EOF) {
        if (user.id == id && strcmp(user.password, password) == 0) {
            fclose(userFile);
            return 1; // Login successful
        }
    }
    fclose(userFile);
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Addbook()
{
    int i;
    book.status = IN;
    // opening the librecord file
    librecord = fopen("librecord.txt", "a+");
    printf("Enter The number of The Book :(Integer) \n");
    scanf("%d", &book.bid);
    printf("Enter The Name of The Book :\n");
    scanf("%s", book.bname);
    printf("Enter The Name of Author :\n");
    scanf("%s", book.author);
    printf("Enter The Number of Titles Of The Book:(Integer)\n");
    scanf("%d", &book.nooftitles);
    fprintf(librecord, "\n%d\t%s\t%s\t%d\t%d\t", book.bid, book.bname, book.author, book.status, book.nooftitles);
    printf("Enter The Titles Of The Book : \n");
    for(i = 0; i < book.nooftitles; i++)
    {
        scanf("%s", book.titles);
        fprintf(librecord, "%s\t", book.titles);
    }
    fclose(librecord);
    printf(" (' ' ) A New Book has been Added Successfully...\n");
}

void Displaybook()
{
    librecord = fopen("librecord.txt", "a+");
    printf("\nBookid\tName\tAuthor\tStatus\tNo.\tTitles\n", info);
    do
    {
        fgets(info, 500, librecord);
        printf("%s\n", info);
    } while(!feof(librecord));
    fclose(librecord);

    membrrecord = fopen("membrrecord.txt", "a+");
    printf("\nMid\tName\tDept\tPh.no\tAvailablecards\n");
    do
    {
        fgets(info, 500, membrrecord);
        printf("%s\n", info);
    } while(!feof(membrrecord));
    fclose(membrrecord);
}

void Searchbook()
{
    int i;
    char Target[25], stats[3];
    int Found = 0;
    if((librecord = fopen("librecord.txt", "r")) == NULL)
        printf(" ! The File is Empty...\n\n");
    else
    {
        printf("\nEnter The Name Of Book : ");
        scanf("%s", Target);
        while(!feof(librecord) && Found == 0)
        {
            fscanf(librecord, "%d %s %s %d %d", &book.bid, book.bname, book.author, &book.status, &book.nooftitles);
            if(strcmp(Target, book.bname) == 0)
                Found = 1;
            for(i = 0; i < book.nooftitles; i++)
                fscanf(librecord, "%s", book.titles);
        }
        if(Found)
        {
            if(book.status == IN)
                strcpy(stats, "IN");
            else
                strcpy(stats, "OUT");

            printf("\nThe Unique ID of The Book:  %d\nThe Name of Book is:  %s\nThe Author is:  %s\nThe Book Status: %s\n\n", book.bid, book.bname, book.author, stats);
        }
        else if(!Found)
            printf("! There is no such Entry...\n");
        fclose(librecord);
    }
}

void Author()
{
    int i;
    char Target[500];
    int Found = 0;
    if((librecord = fopen("librecord.txt", "r")) == NULL)
        printf(" ! The file is empty... \n\n");
    else
    {
        printf("\nEnter The Name Of Author : ");
        scanf("%s", Target);
        printf("\nBooks:");
        while(!feof(librecord))
        {
            fscanf(librecord, "%d %s %s %d %d", &book.bid, book.bname, book.author, &book.status, &book.nooftitles);
            if(strcmp(Target, book.author) == 0)
            {
                Found = 1;
                printf("\n\t%s", book.bname);
            }
            for(i = 0; i < book.nooftitles; i++)
                fscanf(librecord, "%s", book.titles);
        }
        if(!Found)
            printf(" ! There is no such Entry...\n");
        fclose(librecord);
    }
}

void Titlelist()
{
    int i;
    char Target[500];
    int Found = 0;
    if((librecord = fopen("librecord.txt", "r")) == NULL)
        printf(" ! The file is empty...\n\n");
    else
    {
        printf("\nEnter The Book Name :");
        scanf("%s", Target);
        while(!feof(librecord) && Found == 0)
        {
            fscanf(librecord, "%d %s %s %d %d", &book.bid, book.bname, book.author, &book.status, &book.nooftitles);
            if(strcmp(Target, book.bname) == 0)
            {
                Found = 1;
                break;
            }
            for(i = 0; i < book.nooftitles; i++)
                fscanf(librecord, "%s", book.titles);
        }
        if(Found)
        {
            printf("\nThe Titles:\n");
            for(i = 0; i < book.nooftitles; i++)
            {
                fscanf(librecord, "%s", book.titles);
                printf("%d.%s......\n", i + 1, book.titles);
            }
        }
        else if(!Found)
            printf(" ! There is no such Entry...\n");
        fclose(librecord);
    }
}

void Stock()
{
    int i, issuecount = 0, stockcount = 0;
    char Issued[100][20];
    int Found = 0;
    if((librecord = fopen("librecord.txt", "r")) == NULL)
        printf(" ! The file is empty...\n\n");
    else
    {
        while(!feof(librecord))
        {
            fscanf(librecord, "%d %s %s %d %d", &book.bid, book.bname, book.author, &book.status, &book.nooftitles);
            if(book.status == IN)
            {
                stockcount++;
            }
            else
            {
                issuecount++;
            }
            for(i = 0; i < book.nooftitles; i++)
                fscanf(librecord, "%s", book.titles);
        }
                fclose(librecord);
        printf("\nCount of issued Books:%d\nCount of Books in Stock:%d\n", issuecount, stockcount - 1);
    }
}

void Addmembr()
{
    int i;

    membrrecord = fopen("membrrecord.txt", "a+");
    printf("Enter The userid of the Member(Integer) :\n");
    scanf("%d", &membr.mid);
    printf("Enter The Name of the Member :\n");
    scanf("%s", membr.mname);
    printf("Enter The Department\n");
    scanf("%s", membr.department);

    printf("Enter The phone number of the member:\n");
    scanf("%d", &membr.phno);
    membr.availibcard = 5;
    fprintf(membrrecord, "\n%d\t%s\t%s\t%d\t%d\t", membr.mid, membr.mname, membr.department, membr.phno, membr.availibcard);
    fclose(membrrecord);
    printf("\n (' ') Added  A New member Successfully...\n");
}

void Issue()
{
    int mid, i, Found1 = 0, Found2 = 0;
    char issubookname[20];
    printf("\nEnter The userid of the Member : \n");
    scanf("%d", &mid);
    if((membrrecord = fopen("membrrecord.txt", "r")) == NULL)
        printf(" ! The file is empty...\n\n");
    else
    {
        while(!feof(membrrecord) && Found1 == 0)
        {
            fscanf(membrrecord, "%d %s %s %d %d ", &membr.mid, membr.mname, membr.department, &membr.phno, &membr.availibcard);
            if(mid == membr.mid)
            {
                Found1 = 1;
            }
        }
        if(Found1)
        {
            if(membr.availibcard < 1)
            {
                printf(" ! Library card not available...\n");
            }
            else
            {
                printf("\nEnter The Name of book :");
                scanf("%s", issubookname);
                if((librecord = fopen("librecord.txt", "r")) == NULL)
                    printf(" ! The file is empty...\n\n");
                else
                {
                    while(!feof(librecord) && Found2 == 0)
                    {
                        fscanf(librecord, "%d %s %s %d %d", &book.bid, book.bname, book.author, &book.status, &book.nooftitles);
                        if(strcmp(issubookname, book.bname) == 0)
                            Found2 = 1;
                        for(i = 0; i < book.nooftitles; i++)
                            fscanf(librecord, "%s", book.titles);
                    }
                    if(Found2)
                    {
                        if(book.status == 0)
                        {
                            printf(" ! Book already issued...\n");
                        }
                        else
                        {
                            fp2 = fopen("fp2.txt", "w");
                            if((temp2 = fopen("membrrecord.txt", "r")) == NULL)
                                printf(" ! The file is empty...\n\n");
                            else
                            {
                                while(!feof(temp2))
                                {
                                    fscanf(temp2, "%d %s %s %d %d ", &membr.mid, membr.mname, membr.department, &membr.phno, &membr.availibcard);

                                    if(mid == membr.mid)
                                    {
                                        membr.availibcard--;
                                        fprintf(fp2, "\n %d\t%s\t%s\t%d\t%d\t", membr.mid, membr.mname, membr.department, membr.phno, membr.availibcard);
                                    }
                                    else
                                    {
                                        fprintf(fp2, "\n %d\t%s\t%s\t%d\t%d\t", membr.mid, membr.mname, membr.department, membr.phno, membr.availibcard);
                                    }
                                    if(feof(temp2))
                                        break;
                                }
                            }
                            fclose(temp2);
                            fclose(fp2);

                            fp1 = fopen("fp1.txt", "w");
                            if((temp1 = fopen("librecord.txt", "r")) == NULL)
                                printf(" ! The file is empty...\n\n");
                            else
                            {
                                while(!feof(temp1))
                                {
                                    fscanf(temp1, "%d %s %s %d %d", &book.bid, book.bname, book.author, &book.status, &book.nooftitles);
                                    if(feof(temp1))
                                        break;
                                    if(strcmp(issubookname, book.bname) != 0)
                                    {
                                        fprintf(fp1, "\n%d\t%s\t%s\t%d\t%d    \t", book.bid, book.bname, book.author, book.status, book.nooftitles);
                                    }
                                    else
                                    {
                                        fprintf(fp1, "\n%d\t%s\t%s\t%d\t%d\t", book.bid, book.bname, book.author, 0, book.nooftitles);
                                    }
                                    for(i = 0; i < book.nooftitles; i++)
                                    {
                                        fscanf(temp1, "%s", book.titles);
                                        fprintf(fp1, "%s\t", book.titles);
                                    }
                                }
                            }
                            fclose(temp1);
                            fclose(fp1);
                            fclose(librecord);
                            fclose(membrrecord);
                            remove("librecord.txt");
                            rename("fp1.txt", "librecord.txt");
                            remove("membrrecord.txt");
                            rename("fp2.txt", "membrrecord.txt");
                            printf(" (' ') Book Successfully issued...\n");
                        }
                    }
                    else if(!Found2)
                        printf(" ! There is no such Book...\n");
                }
            }
        }
        else if(!Found1)
            printf(" ! Invalid User id...\n");
    }
}

void bookret()
{
    int mid, i, Found1 = 0, Found2 = 0, flag = 0;
    char retbookname[20];
    temp1 = librecord;
    temp2 = membrrecord;
    printf("\nEnter The userid of the Member :\n");
    scanf("%d", &mid);
    if((membrrecord = fopen("membrrecord.txt", "r")) == NULL)
        printf(" ! The file is empty...\n\n");
    else
    {
        while(!feof(membrrecord) && Found1 == 0)
        {
            fscanf(membrrecord, "%d %s %s %d %d ", &membr.mid, membr.mname, membr.department, &membr.phno, &membr.availibcard);
            if(mid == membr.mid)
            {
                Found1 = 1;
            }
        }
        if(Found1)
        {
            if(membr.availibcard >= 5)
            {
                printf(" ! Error...\n");
            }
            else
            {
                printf("\nEnter The Name of book :");
                scanf("%s", retbookname);
                if((librecord = fopen("librecord.txt", "r")) == NULL)
                    printf(" ! The file is empty\n\n");
                else
                {
                    while(!feof(librecord) && Found2 == 0)
                    {
                        fscanf(librecord, "%d %s %s %d %d", &book.bid, book.bname, book.author, &book.status, &book.nooftitles);
                        if(strcmp(retbookname, book.bname) == 0)
                            Found2 = 1;
                        for(i = 0; i < book.nooftitles; i++)
                            fscanf(librecord, "%s", book.titles);
                    }
                    if(Found2)
                    {
                        if(book.status == 1)
                        {
                            printf(" ! Book not issued...\n");
                        }
                        else
                        {
                            fp2 = fopen("fp2.txt", "w");
                            if((temp2 = fopen("membrrecord.txt", "r")) == NULL)
                                printf(" ! The file is empty...\n\n");
                            else
                            {
                                while(!feof(temp2))
                                {
                                    fscanf(temp2, "%d %s %s %d %d ", &membr.mid, membr.mname, membr.department, &membr.phno, &membr.availibcard);
                                    if(mid == membr.mid)
                                    {
                                        membr.availibcard++;
                                        fprintf(fp2, "\n %d\t%s\t%s\t%d\t%d\t", membr.mid, membr.mname, membr.department, membr.phno, membr.availibcard);
                                    }
                                    else
                                    {
                                        fprintf(fp2, "\n %d\t%s\t%s\t%d\t%d\t", membr.mid, membr.mname, membr.department, membr.phno, membr.availibcard);
                                    }
                                    if(feof(temp2))
                                        break;
                                }
                            }
                            fclose(temp2);
                            fclose(fp2);

                            fp1 = fopen("fp1.txt", "w");
                            if((temp1 = fopen("librecord.txt", "r")) == NULL)
                                printf(" ! The file is empty...\n\n");
                            else
                            {
                                while(!feof(temp1))
                                {
                                    fscanf(temp1, "%d %s %s %d %d", &book.bid, book.bname, book.author, &book.status, &book.nooftitles);
                                    if(feof(temp1))
                                        break;
                                    if(strcmp(retbookname, book.bname) != 0)
                                    {
                                        fprintf(fp1, "\n%d\t%s\t%s\t%d\t%d\t", book.bid, book.bname, book.author, book.status, book.nooftitles);
                                    }
                                    else
                                    {
                                        fprintf(fp1, "\n%d\t%s\t%s\t%d\t%d\t", book.bid, book.bname, book.author, 1, book.nooftitles);
                                    }
                                    for(i = 0; i < book.nooftitles; i++)
                                    {
                                        fscanf(temp1, "%s", book.titles);
                                        fprintf(fp1, "%s\t", book.titles);
                                    }
                                }
                            }
                            fclose(temp1);
                            fclose(fp1);
                            fclose(librecord);
                            fclose(membrrecord);
                            remove("librecord.txt");
                            rename("fp1.txt", "librecord.txt");
                            remove("membrrecord.txt");
                            rename("fp2.txt", "membrrecord.txt");
                            printf(" (' ') Book Successfully Returned...\n");
                        }
                    }
                    else if(!Found2)
                        printf(" ! There is no such Book...\n");
                }
            }
        }
        else if(!Found1)
            printf(" ! Invalid User id...\n");
    }
}

void Exit()
{
    printf("\n\t\t--Thanks for using the program--\n");
    exit(0);
}

void Deletebook() // Function to delete a book
{
    char target[25];
    int found = 0;

    printf("\nEnter the name of the book to be deleted: ");
    scanf("%s", target);

    // Opening the file in read mode
    librecord = fopen("librecord.txt", "r");
    // Opening temporary file in write mode
    fp1 = fopen("temp.txt", "w");

    // Reading the file
    while (fscanf(librecord, "%d %s %s %d %d", &book.bid, book.bname, book.author, &book.status, &book.nooftitles) != EOF)
    {
        if (strcmp(target, book.bname) == 0)
        {
            printf("\nThe record has been found and deleted.\n");
            found = 1;
            // Skip writing this book to the temporary file
            for (int i = 0; i < book.nooftitles; i++)
            {
                fscanf(librecord, "%s", book.titles);
            }
        }
        else
        {
            // Write other books to the temporary file
            fprintf(fp1, "\n%d\t%s\t%s\t%d\t%d\t", book.bid, book.bname, book.author, book.status, book.nooftitles);
            for (int i = 0; i < book.nooftitles; i++)
            {
                fscanf(librecord, "%s", book.titles);
                fprintf(fp1, "%s\t", book.titles);
            }
        }
    }
    fclose(librecord);
    fclose(fp1);
    remove("librecord.txt");
    rename("temp.txt", "librecord.txt");

    if (found == 0)
    {
        printf("\nRecord not found!\n");
    }
}



void Deletemembr() // Function to delete a member
{
    int target;
    int found = 0;

    printf("\nEnter the ID of the member to be deleted: ");
    scanf("%d", &target);

    // Opening the file in read mode
    membrrecord = fopen("membrrecord.txt", "r");
    // Opening temporary file in write mode
    fp1 = fopen("temp.txt", "w");

    // Reading the file
    while (!feof(membrrecord))
    {
        fscanf(membrrecord, "%d %s %s %d %d", &membr.mid, membr.mname, membr.department, &membr.phno, &membr.availibcard);

        if (target == membr.mid)
        {
            printf("\nThe record has been found and deleted.\n");
            found = 1;
        }
        else
        {
            fprintf(fp1, "\n%d\t%s\t%s\t%d\t%d\t", membr.mid, membr.mname, membr.department, membr.phno, membr.availibcard);
        }
    }
    fclose(membrrecord);
    fclose(fp1);
    remove("membrrecord.txt");
    rename("temp.txt", "membrrecord.txt");

    if (found == 0)
    {
        printf("\nRecord not found!\n");
    }
}

void Modifybook() // Function to modify book details
{
    char target[25];
    int found = 0;

    printf("\nEnter the name of the book to be modified: ");
    scanf("%s", target);

    // Opening the file in read mode
    librecord = fopen("librecord.txt", "r");
    // Opening temporary file in write mode
    fp1 = fopen("temp.txt", "w");

    // Reading the file
    while (!feof(librecord))
    {
        fscanf(librecord, "%d %s %s %d %d", &book.bid, book.bname, book.author, &book.status, &book.nooftitles);

        if (strcmp(target, book.bname) == 0)
        {
                        printf("\nThe record has been found and is being modified.\n");
            found = 1;

            // Modify book details
            printf("Enter new Book ID: ");
            scanf("%d", &book.bid);
            printf("Enter new Book Name: ");
            scanf("%s", book.bname);
            printf("Enter new Author Name: ");
            scanf("%s", book.author);
            printf("Enter new status (IN or OUT): ");
            scanf("%d", &book.status);
            printf("Enter new number of titles: ");
            scanf("%d", &book.nooftitles);

            // Write modified details to temporary file
            fprintf(fp1, "\n%d\t%s\t%s\t%d\t%d\t", book.bid, book.bname, book.author, book.status, book.nooftitles);
            for (int i = 0; i < book.nooftitles; i++)
            {
                printf("Enter Title %d: ", i + 1);
                scanf("%s", book.titles);
                fprintf(fp1, "%s\t", book.titles);
            }
        }
        else
        {
            fprintf(fp1, "\n%d\t%s\t%s\t%d\t%d\t", book.bid, book.bname, book.author, book.status, book.nooftitles);
            for (int i = 0; i < book.nooftitles; i++)
            {
                fscanf(librecord, "%s", book.titles);
                fprintf(fp1, "%s\t", book.titles);
            }
        }
    }
    fclose(librecord);
    fclose(fp1);
    remove("librecord.txt");
    rename("temp.txt", "librecord.txt");

    if (found == 0)
    {
        printf("\nRecord not found!\n");
    }
}

void Modifymembr() // Function to modify member details
{
    int target;
    int found = 0;

    printf("\nEnter the ID of the member to be modified: ");
    scanf("%d", &target);

    // Opening the file in read mode
    membrrecord = fopen("membrrecord.txt", "r");
    // Opening temporary file in write mode
    fp1 = fopen("temp.txt", "w");

    // Reading the file
    while (!feof(membrrecord))
    {
        fscanf(membrrecord, "%d %s %s %d %d", &membr.mid, membr.mname, membr.department, &membr.phno, &membr.availibcard);

        if (target == membr.mid)
        {
            printf("\nThe record has been found and is being modified.\n");
            found = 1;

            // Modify member details
            printf("Enter new User ID: ");
            scanf("%d", &membr.mid);
            printf("Enter new Name: ");
            scanf("%s", membr.mname);
            printf("Enter new Department: ");
            scanf("%s", membr.department);
            printf("Enter new Phone number: ");
            scanf("%d", &membr.phno);
            printf("Enter new Available Library Cards: ");
            scanf("%d", &membr.availibcard);

            // Write modified details to temporary file
            fprintf(fp1, "\n%d\t%s\t%s\t%d\t%d\t", membr.mid, membr.mname, membr.department, membr.phno, membr.availibcard);
        }
        else
        {
            fprintf(fp1, "\n%d\t%s\t%s\t%d\t%d\t", membr.mid, membr.mname, membr.department, membr.phno, membr.availibcard);
        }
    }
    fclose(membrrecord);
    fclose(fp1);
    remove("membrrecord.txt");
    rename("temp.txt", "membrrecord.txt");

    if (found == 0)
    {
        printf("\nRecord not found!\n");
    }
}




