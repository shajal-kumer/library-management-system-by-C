#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<string.h>
#include <stdlib.h>

//Global variable
char choice;
int password;

/// Set cursor position
void gotoxy(int x,int y){
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

/// Book Structure
struct book{
    int bookId;
    char bookName[30];
    char authorName[30];
} Book;

/// Student structure
struct student{
    int id;
    char name[20];
    char batch[8];
    char dept[10];
    char semester[10];
    char phoneNo[15];
} stu;

/// welcome function prototype
void welcome();

/// passsword function prototype
void passwordFunc();

/// admin function prototype
void admin();

    /// 1. bookInfo function prototype
    void bookInfo();

        ///1. addBooks function prototype
        void addBooks();

        /// 2. searchBook function prototype
        void searchBook();

        /// 3. editBook function prototype
        void editBook();

        /// 4. deleteBook function prototype
        void deleteBook();

        /// 5. viewBookList function prototype
        void viewBookList();

    /// 2. userInfo function prototype
    void userInfo();

         /// 1. addUser() function prototype
        void addUser();

         /// 2. searchUser() function prototype
        void searchUser();

         /// 3. editUser() function prototype
        void editUser();

         /// 4. deleteUser() function prototype
        void deleteUser();

         /// 5. viewUserList() function prototype
        void viewUserList();

/// user function prototype
void user();

/// Main function
int main() {

    system("color 3F");
    welcome();
    gotoxy(30,7);
    printf("\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2 MENU \xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2");
    gotoxy(40,9);
    printf("1. Admin");
    gotoxy(40,10);
    printf("2. User");
    gotoxy(40,11);printf("Please Enter Your Choice: ");
    choice=getch();
    system("cls");
    welcome();
    switch(choice){
    case '1':
        passwordFunc();
        break;
    case '2':
        user();
        break;
    default :
        gotoxy(40,14);
        printf("wrong input! Enter Again");
        main();
    };

return 0;
}

/// Welcome function
void welcome(){
    printf("_______________________________________________________________________________________________");
    gotoxy(25, 2);printf("  WELCOME TO LIBRARY MANAGEMENT SYSTEM  ");
    gotoxy(20, 3);printf("  Varendra University, Rajshahi, Bangladesh  ");
    gotoxy(35, 4);printf("  Estd: 2012\n");
    printf("_______________________________________________________________________________________________");
}

/// 1. Admin function
void admin(){
    system("cls");
    welcome();
    gotoxy(30,7);printf("\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2 Admin Area \xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2");
    gotoxy(40,9);printf("1.Book Info");
    gotoxy(40,10);printf("2.User Info");
    gotoxy(40,11);printf("3.Back");
    gotoxy(40,12);printf("Please Enter Your Choice: ");
    choice=getch();
    system("cls");
    switch(choice){
    case'1':
        bookInfo();
        break;
    case'2':
        userInfo();
        break;
    case '3':
        main();
    default:
        admin();
    };
}

    /// 1. bookInfo function
    void bookInfo(){
        system("cls");
        welcome();
        gotoxy(30,7);
        printf("\xb2\xb2\xb2\xb2\xb2 Admin Book Info Area \xb2\xb2\xb2\xb2\xb2");
        gotoxy(40,8);
        printf("1. Add Book");
        gotoxy(40,9);
        printf("2. Search Book");
        gotoxy(40,10);
        printf("3. Edit Book");
        gotoxy(40,11);
        printf("4. Delete Book");
        gotoxy(40,12);
        printf("5. View Book List");
        gotoxy(40,13);
        printf("6. Back");
        gotoxy(40,14);
        printf("7. Exit");
        gotoxy(40,16);
        printf("Please Enter Your Choice: ");
        choice=getch();
        system("cls");
        switch(choice)
        {
        case'1':
            addBooks();
            break;
        case'2':
            searchBook();
            choice = getch();
            if(choice == 'y' || choice == 'Y'){
                searchBook();
            }else{
                bookInfo();
            }
            break;
        case'3':
            editBook();
            break;
        case'4':
            deleteBook();
            break;
        case'5':
            viewBookList();
            if(getch())
                bookInfo();
            break;
        case'6':
            admin();
            break;
        case'7':
            exit(0);
            break;
        default:
            bookInfo();
            break;
        };
    }

        /// 1. addBooks function
        void addBooks(){
            system("cls");
            welcome();
            FILE *fp;
            int bookId,flag = 0;
            fp = fopen("add-book.txt","ab");
            if(fp==NULL){
                MessageBox(0,"Error in Opening file!","Warning",0);
                printf("Error File");
            }else{
                gotoxy(30,7);printf("\xb2\xb2\xb2\xb2\xb2 Add Book Section \xb2\xb2\xb2\xb2\xb2");
                gotoxy(40,9);printf("Enter Book ID:");
                scanf("%d",&bookId);
                fp=fopen("add-book.txt","rb+");
                while(fread(&Book,sizeof(Book),1,fp) == 1){
                    if(bookId == Book.bookId){
                        flag = 1;
                    }
                }
                if(flag == 1){
                    gotoxy(40,10);
                    printf("Id is already Exits");
                    getch();
                    addBooks();
                }else{
                    Book.bookId = bookId;
                    fflush(stdin);
                    gotoxy(40,10);printf("Enter Book Name: ");
                    gets(Book.bookName);
                    gotoxy(40,11);printf("Enter Author Name: ");
                    gets(Book.authorName);
                    fwrite(&Book,sizeof(Book),1,fp);
                    fclose(fp); // file close

                    gotoxy(40,12);printf("The record is successfully saved.\n");
                    gotoxy(40,13);printf("Save any more?(Y / N): ");
                    choice = getch();
                    if(choice == 'y' || choice == 'Y'){
                        addBooks();
                    }else{
                        bookInfo();
                    }

                }
            }
        }

        /// 2. searchBook function
        void searchBook(){
            welcome();
            FILE *fp;
            fp=fopen("add-book.txt","rb");
            int bookId, flag = 0;
            gotoxy(30,7);printf("Enter Book ID for Search: ");
            scanf("%d",&bookId);
            rewind(fp);
            while(fread(&Book,sizeof(Book),1,fp) == 1){
                if(Book.bookId == bookId){
                    gotoxy(30,9);printf("\xb2\xb2\xb2\xb2\xb2 Book Information \xb2\xb2\xb2\xb2\xb2");
                    gotoxy(35,10);printf("ID             BOOK NAME               AUTHOR NAME  ");
                    gotoxy(35,11);printf("---            -----------             -------------");
                    gotoxy(35,13);printf("%d",Book.bookId);
                    gotoxy(50,13);printf("%s",Book.bookName);
                    gotoxy(75,13);printf("%s",Book.authorName);
                    gotoxy(35,15);printf("Want to Search another Record?(Y/N)");
                    flag++;
                }
            }
            if(flag == 0){
                gotoxy(30,8);printf("No Record Found to Database.");
                gotoxy(30,9);printf("Want to Search another Record?(Y/N)");
            }
            fclose(fp);
        }

        /// 3. editBook function
        void editBook(){
            system("cls");
            welcome();
            gotoxy(25,7);printf("\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2 Edit Information \xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2");
            int bookId, isFound = 0;
            gotoxy(32,9);printf("Enter ID to Modify: ");
            scanf("%d", &bookId);

            FILE *fp;
            fp = fopen("add-book.txt","rb+");
            while(fread(&Book, sizeof(Book),1,fp) == 1){
                if(bookId == Book.bookId){
                    gotoxy(32,10);printf("Book Id: ");scanf("%d", &Book.bookId);
                    gotoxy(32,11);printf("Book Name: ");scanf("%s", &Book.bookName);
                    gotoxy(32,12);printf("Author Name: ");scanf("%s", &Book.authorName);
                    fseek(fp, sizeof(Book), SEEK_CUR);
                    fwrite(&Book,sizeof(Book), 1, fp);

                    gotoxy(32,14);printf("Record is modified.");
                    gotoxy(32,15);printf("Want to Modify another Record?(Y/N): ");
                    isFound = 1;
                    break;
                }
            }
            if(!isFound){
                gotoxy(32, 11);printf("Sorry, No record found in the database.");
                gotoxy(32, 12);printf("Want to Modify another Record?(Y/N): ");
            }
            fclose(fp);
            choice = getch();
            if(choice == 'y' || choice == 'Y'){
                editBook();
            }else{
                bookInfo();
            }
        }

        /// 4. deleteBook function
        void deleteBook(){
            system("cls");
            welcome();
            gotoxy(20,7);printf("Enter ID to Delete: ");
            int bookId;
            scanf("%d", &bookId);
            int flag = 0;

            FILE *fp, *temp;
            fp = fopen("add-book.txt","rb");
            temp = fopen("book-temp.txt", "wb");

            rewind(fp);
            while(fread(&Book,sizeof(Book),1,fp) == 1) {
               if(bookId == Book.bookId){
                    flag = 1;
                    break;
                }else {
                    gotoxy(20,8);printf("Can not find the Book ID in database!");
                    break;
                }
            }
            if(flag == 1) {
                rewind(fp);
                while(fread(&Book, sizeof(Book),1,fp) == 1){
                    if(bookId != Book.bookId){
                        fwrite(&Book,sizeof(Book),1,temp);
                    }
                }
                gotoxy(20,8);printf("The record is successfully deleted.\n");
            }
            fclose(fp);
            fclose(temp);
            remove("add-book.txt");
            rename("book-temp.txt","add-book.txt");

            gotoxy(20,10); printf("For go back press any key: ");
            if(getch())
                bookInfo();
            }

        /// 5. viewBookList function
        void viewBookList(){
            system("cls");
            int axisY = 12;
            welcome();
            FILE *fp;
            gotoxy(35,8);printf("\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2 Book List \xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2");
            gotoxy(25,10);printf("Book ID            BOOK NAME                AUTHOR NAME  ");
            gotoxy(25,11);printf("------------------------------------------------------------------");
            fp=fopen("add-book.txt","rb");
            while(fread(&Book,sizeof(Book),1,fp)==1){
                gotoxy(25,axisY);printf("%d",Book.bookId);
                gotoxy(45,axisY);printf("%s",Book.bookName);
                gotoxy(70,axisY);printf("%s",Book.authorName);
                printf("\n\n");
                axisY++;
            }
            fclose(fp);
            gotoxy(25,axisY+2);printf("For go back press any key: ");
        }

    /// 2. userInfo function
    void userInfo(){
        system("cls");
        welcome();
        gotoxy(30,7);
        printf("\xb2\xb2\xb2\xb2\xb2 Admin User Info Area \xb2\xb2\xb2\xb2\xb2");gotoxy(40,8);
        printf("1. Add User");gotoxy(40,9);
        printf("2. Search User");gotoxy(40,10);
        printf("3. Edit User");gotoxy(40,11);
        printf("4. Delete User");gotoxy(40,12);
        printf("5. View user");gotoxy(40,13);
        printf("6. Back");gotoxy(40,14);
        printf("7. Exit");gotoxy(40,15);
        printf("Please Enter Your Choice: ");
        choice=getch();
        system("cls");
        switch(choice)
        {
        case'1':
            addUser();
            break;
        case'2':
            searchUser();
            choice = getch();
            if(choice == 'y' || choice == 'Y'){
                searchUser();
            }else{
                userInfo();
            }
            break;
        case'3':
            editUser();
            break;
        case'4':
           deleteUser();
            break;
        case'5':
            viewUserList();
            if(getch())
                userInfo();
            break;
        case'6':
            admin();
            break;
        case'7':
            exit(0);
            break;
        default:
            userInfo();
            break;
        }
    }

        /// 1. addUser function
        void addUser(){
            system("cls");
            welcome();
            FILE *fp;
            int userId, flag = 0;
            fp=fopen("add-student.txt","ab");
            if(fp==NULL) {
                MessageBox(0,"Error in Opening file!","Warning",0);
                    printf("Error File");
            }else{
                gotoxy(20,7);printf("\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2 Add Student Information \xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2");
                gotoxy(20,8);printf("-------------------------------------------------");
                gotoxy(30,10);printf("Enter Student ID: ");
                scanf("%d",&userId);
                fp=fopen("add-student.txt","rb+");
                while(fread(&stu,sizeof(stu),1,fp) == 1){
                    if(userId == stu.id){
                        flag=1;
                    }
                }
                if(flag == 1){
                    gotoxy(30,11);
                    printf("Id is already Exits.");
                    getch();
                    addUser();
                }else{
                    stu.id = userId;
                    fflush(stdin);
                    gotoxy(30,11);printf("Enter User Name: ");
                    gets(stu.name);
                    gotoxy(30,12);printf("Enter Department: ");
                    gets(stu.dept);
                    gotoxy(30,13);printf("Enter Batch: ");
                    gets(stu.batch);
                    gotoxy(30,14);printf("Enter Semester: ");
                    gets(stu.semester);
                    gotoxy(30,15);printf("Enter Phone Number: ");
                    gets(stu.phoneNo);
                    fwrite(&stu,sizeof(stu),1,fp);
                    fclose(fp); // File close

                    gotoxy(30,17);printf("The record is successfully saved.");
                    gotoxy(30,18);printf("Save any more?(Y / N): ");
                    choice = getch();
                    if(choice =='y' || choice == 'Y'){
                        addUser();
                    }else{
                        userInfo();
                    }
                }
            }

        }

        /// 2. searchUser function
        void searchUser() {
            system("cls");
            welcome();
            FILE *fp;
            fp=fopen("add-student.txt","rb");
            int userId, flag = 0;
            gotoxy(30,7);printf("Enter User ID for Search: ");
            scanf("%d",&userId);
            rewind(fp);
            while(fread(&stu,sizeof(stu),1,fp) == 1){
                if(stu.id == userId){
                    gotoxy(20,8);printf("\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2 User Information \xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2");
                    gotoxy(20,9);printf("User ID        User Name       Department      Batch       Semester        Phone Number  ");
                    gotoxy(20,10);printf("--------      -----------     ----------       -------    ---------       ------------");
                    gotoxy(20,12);printf("%d",stu.id);
                    gotoxy(35,12);printf("%s",stu.name);
                    gotoxy(50,12);printf("%s",stu.batch);
                    gotoxy(70,12);printf("%s",stu.dept);
                    gotoxy(80,12);printf("%s",stu.semester);
                    gotoxy(95,12);printf("%s",stu.phoneNo);
                    gotoxy(30,14);printf("Want to Search another Record?(Y/N)");
                    flag++;
                }
            }
            if(flag == 0){
                gotoxy(30,8);printf("No Record Found to Database.");
                gotoxy(30,8);printf("Want to Search another Record?(Y/N).");
            }
            fclose(fp);
        }

        /// 3. editUser function
        void editUser() {
            system("cls");
            welcome();
            gotoxy(25,7);printf("\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2 Edit Information \xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2");
            int userId, isFound = 0;
            gotoxy(32,9);printf("Enter ID to Modify: ");
            scanf("%d", &userId);

            FILE *fp;
            fp = fopen("add-student.txt","rb+");
            while(fread(&stu, sizeof(stu),1,fp) == 1){
                if(userId == stu.id){
                    gotoxy(32,10);printf("Id: ");scanf("%d", &stu.id);
                    fflush(stdin);
                    gotoxy(32,11);printf("Name: ");gets(stu.name);
                    gotoxy(32,12);printf("Batch: ");gets(stu.batch);
                    gotoxy(32,13);printf("Dept: ");gets(stu.dept);
                    gotoxy(32,14);printf("Semester: ");gets(stu.semester);
                    gotoxy(32,15);printf("Phone Number: ");gets(stu.phoneNo);

                    fseek(fp, sizeof(stu), SEEK_CUR);
                    fwrite(&stu, sizeof(stu), 1, fp);
                    gotoxy(32,17);printf("Record is modified.");
                    gotoxy(32,18);printf("Want to Modify another Record?(Y/N): ");
                    isFound = 1;
                    break;
                }
            }
            if(!isFound){
                gotoxy(32, 11);printf("Sorry, No record found in the database.");
                gotoxy(32, 12);printf("Want to Modify another Record?(Y/N): ");
            }
            fclose(fp);
            choice = getch();
            if(choice == 'y' || choice == 'Y'){
                editUser();
            }else{
                userInfo();
            }
        }

        /// 4. deleteUser function
        void deleteUser() {
            system("cls");
            welcome();
            gotoxy(20,7);printf("Enter ID to Delete: ");
            int userId;
            scanf("%d", &userId);
            int flag = 0;

            FILE *fp, *temp;
            fp = fopen("add-student.txt","rb");
            temp = fopen("student-temp.txt", "wb");

            rewind(fp);
            while(fread(&stu,sizeof(stu),1,fp) == 1) {
               if(userId == stu.id){
                    flag = 1;
                    break;
                }else {
                    gotoxy(20,8);printf("Can not find the student ID in database!");
                    break;
                }
            }
            if(flag == 1) {
                rewind(fp);
                while(fread(&stu, sizeof(stu),1,fp) == 1){
                    if(userId != stu.id){
                        fwrite(&stu,sizeof(stu),1,temp);
                    }
                }
                gotoxy(20,8);printf("The record is successfully deleted.\n");
            }
            fclose(fp);
            fclose(temp);
            remove("add-student.txt");
            rename("student-temp.txt","add-student.txt");

            gotoxy(20,10); printf("For go back press any key: ");
            if(getch())
                userInfo();
        }

        /// 5. viewUserList function
        void viewUserList(){
            int axisY = 11;
            system("cls");
            welcome();
            FILE *fp;
            gotoxy(20,7);printf("\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2 User List \xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2");
            gotoxy(20,8);printf("User ID          User Name            Department         Batch          Semester        Phone Number  ");
            gotoxy(20,9);printf("-------------------------------------------------------------------------------------------------------");
            fp=fopen("add-student.txt","rb");
            while(fread(&stu,sizeof(stu),1,fp)==1){
                gotoxy(20,axisY);printf("%d",stu.id);
                gotoxy(38,axisY);printf("%s",stu.name);
                gotoxy(55,axisY);printf("%s",stu.dept);
                gotoxy(75,axisY);printf("%s",stu.batch);
                gotoxy(90,axisY);printf("%s",stu.semester);
                gotoxy(100,axisY);printf("%s",stu.phoneNo);
                axisY++;
            }
            fclose(fp);
            gotoxy(20,axisY+2); printf("For go back press any key: ");
    }

/// 2. user function
void user(){
    system("cls");
    welcome();
    gotoxy(30,7);printf("\xb2\xb2\xb2\xb2\xb2 User Information Area \xb2\xb2\xb2\xb2\xb2");
    gotoxy(40,8);printf("1. View Book List");
    gotoxy(40,9);printf("2. Search Book");
    gotoxy(40,10);printf("3. View User Information");
    gotoxy(40,11);printf("4. Search User Information");
    gotoxy(40,12);printf("5. Back");
    gotoxy(40,13);printf("6. Exit");
    gotoxy(40,15);printf("Please Enter Your Choice:");
    choice=getch();
    system("cls");
    switch(choice){
        case'1':
            viewBookList();
            if(getch())
                user();
            break;
        case'2':
            searchBook();
            choice = getch();
            if(choice == 'y' || choice == 'Y'){
                searchBook();
            }else{
                user();
            }
            break;
        case'3':
            viewUserList();
            if(getch())
                user();
            break;
        case'4':
            searchUser();
            choice = getch();
            if(choice == 'y' || choice == 'Y'){
                searchUser();
            }else{
                userInfo();
            }
            break;
        case'5':
            admin();
            break;
        case'6':
            exit(0);
            break;
        default:
            user();
            break;
    };
}

/// passwordFunc function
void passwordFunc() {
        gotoxy(30,7);
        printf("please Log in : ");
        scanf("%d",&password);
        if(password==456){
           admin();
        }
        else{
            gotoxy(40,8);
            printf("Wrong password! Input Again.");
            passwordFunc();
        }
}








