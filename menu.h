// ARROW KEYS
#include "utils.h"
// #include<stdlib.h>

#define up 72
#define down 80
#define left 75
#define right 77

// Global variables
char loggedIn[25]; // user who is currently logged in
char loggedInTime[50]; // the time the user log in

void mainMenu();
void loginMenu();
void regis();
void login();
void logout();
void addFriend();
void removeFriend();
void viewInbox();
void viewSent();

void dashboard();
void publicNotes();
void yourPost();

void printLine(){
    puts("----------------------------");
}

void header(){ // print heading
    puts("=============================================");
    puts("                STUDY NETWORK                ");
    puts("=============================================");
    puts("");
}

void welcome(const char *name){
    puts("=============================================");
    printf("Welcome, %s\n",name);
    puts("=============================================");
    printf("Logged in: %s",loggedInTime);
    printLine();
}

void title(const char *text){
    puts("=============================================");
    printf("         %s\n",text);
    puts("=============================================");
}

void mainMenu(){

    int menu = -1;
    
    do{
        system("@cls||clear");
        header();
        PrintUser();

        puts("");
        printLine();

        puts("[1] Register");
        puts("[2] Login");
        puts("[3] Exit");
        printLine();
        puts("Press 0 and enter to abort an operation");
        printLine();
        printf(">> ");
        scanf("%d",&menu);
    }while(menu < 0 || menu > 3);

    switch(menu){
        case 1: regis(); break;
        case 2: login(); break;
        case 3: return; break;
        default: break;
    }

    return;
}

void loginMenu(){

    int menu = -1;
    
    do{
        system("@cls||clear");
        welcome(loggedIn); //tampilkan login header
        puts("");
        PrintFriends(loggedIn);
        puts("");

        printLine();
        puts("         >> Menu <<         ");
        printLine();
        puts("");

        puts("[1] Add Friend");
        puts("[2] Remove Friend");
        puts("[3] View Inbox");
        puts("[4] View Sent Request");
        puts("[5] Add, Edit, Announce, Delete Note");
        puts("[6] Logout");
        printLine();
        puts("Press 0 and enter to abort an operation");
        printLine();
        printf(">> ");
        scanf("%d",&menu); getchar();
    }while(menu < 0 || menu > 6);
        printLine();

    switch(menu){
        case 1: addFriend(); break;
        case 2: removeFriend(); break;
        case 3: viewInbox(); break;
        case 4: viewSent(); break;
        case 5: dashboard(); break;
        case 6: logout(); break;
        case 0: loginMenu(); break;
        default: break;
    }
}

void regis(){
    char username[40], password[40];

    do{
        printf("Please type in your username [lowercase || 1..24]: ");
        scanf("%s",username); getchar();
        printf("Please type in your password [lowercase || 1..24]: ");
        scanf("%s",password); getchar();

        if(CheckUsername(username)){ // if username exists
            int temp = 0;
            puts("Username already used");
            printf("Try again [ 1 = yes / 0 = no] ? ");
            scanf("%d",&temp); getchar();
            if(temp != 1){
                mainMenu();
            }
        }
    }while(CheckUsername(username));

    pushAcc(username,password);

    puts("");
    puts("--- Registration Successful ---");
    printf("Press enter to continue");
    getchar();
    mainMenu();
    return;
}

void login(){
    char username[40], password[40];

    do{
        printf("Please type in your username [lowercase || 1..24]: ");
        scanf("%s",username); getchar();
        printf("Please type in your password [lowercase || 1..24]: ");
        scanf("%s",password); getchar();

        //VALIDATE USERNAME PASSWORD

        if(!CheckLogin(username,password)){
            int temp;
            puts("Invalid username or password");
            printf("Try again [ 1 = yes / 0 = no] ? ");
            scanf("%d",&temp); getchar();
            if(temp != 1){
                mainMenu();
            }
        }
    }while(!CheckLogin(username,password));

    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    strcpy(loggedInTime,asctime (timeinfo));
    strcpy(loggedIn, username);

    loginMenu();
    return;
}

void logout(){
    strcpy(loggedIn,"");
    strcpy(loggedInTime,"");

    mainMenu();
}

void addFriend(){
    char username[25];
    puts("");
    PrintUser();
    puts("");

    printf("Which user do you want to add? [0 to cancel]\n");
    do{
        printf(">> ");
        scanf("%s",username); getchar();

        if(!CheckUsername(username)) puts("Invalid Username");
    }while(!CheckUsername(username) && strcmp(username,"0")!=0);

    if(CheckUsername(username)){
        pushRequest(loggedIn,username);
        puts("");
        printf("-- Sent request to %s --\n",username);
        printf("Press enter to continue");
        getchar();
    }

    loginMenu();
}

void removeFriend(){
    char username[25];
    puts("");
    PrintFriends(loggedIn);
    puts("");

    printf("Which user do you want to remove? [0 to cancel]\n");
    do{
        printf(">> ");
        scanf("%s",username); getchar();

        if(!CheckUsername(username)) puts("Invalid Username");
    }while(!CheckUsername(username) && strcmp(username,"0")!=0);

    if(CheckUsername(username)){
        deleteFriend(loggedIn, username);
        puts("");
        printf("-- Removed %s as friend --\n",username);
        printf("Press enter to continue");
        getchar();
    }

    loginMenu();    
}

void viewInbox(){
    char username[25];
    puts("");
    PrintRequest(loggedIn);
    puts("");

    do{
        puts("Which user do you want to accept? [0 to go back]");
        printf(">> ");
        scanf("%s",username);

        if(!CheckRequest(username, loggedIn)){
            puts("Invalid username!");
        }
    }while(!CheckRequest(username, loggedIn) && strcmp(username,"0")!=0 && strcmp(username,loggedIn)!=0);

    if(CheckRequest(username,loggedIn)){

        pushFriends(username, loggedIn);

        puts("");
        printf("-- You and %s are now friends! --\n",username); 
        printf("Press enter to continue");
        getchar();
    }

    loginMenu();
}

void viewSent(){

    puts("");
    PrintSent(loggedIn);
    puts("");
        
    printf("Press enter to go back");
    getchar();

    loginMenu();
}

// ####################################### DASHBOARD ####################################### //

void dashboard(){

    int menu = -1;
    do{
        system("@cls||clear");
        title("DASHBOARD");
        puts("");
        puts("[1] Public Posts");
        puts("[2] Your Posts");
        puts("[3] Create Post");
        puts("[4] Back");
        printf(">> ");

        scanf("%d",&menu);

    }while(menu < 0 && menu > 4);

    switch(menu){
        case 1: publicNotes(); break;
        case 2: yourPost(); break;
        case 3: break;
        case 4: loginMenu(); break;
    }
}

void publicNotes(){
    char key;
    
    while(1){

        system("@cls||clear");
        title("PUBLIC POSTS");
        puts("");
        puts("[Notes]");

        // PrintNotes(page);

        puts("[C] Add Comment");
        puts("[V] View Comment");
        puts("[X] Back to Dashboard");

        while(kbhit()){
            key = getch();

            if(key==left){
                //puts("LEFT KEY PRESSED");
                if(page > 1) page--;
            }else if(key==right){
                // puts("RIGHT KEY PRESSED");
                page++;
            }
        }
    }
}

void yourPost(){
    int page = 1;
    char key;
    
    while(1){

        system("cls");
        title("PUBLIC POSTS");
        puts("");
        puts("[Notes]");

        // PrintPostBy(loggedIn);

        puts("[C] Add Comment");
        puts("[V] View Comment");
        puts("[E] Edit Post");
        puts("[D] Delete Post");
        puts("[X] Back to Dashboard");

        while(kbhit()){
            key = getch();

            if(key==left){
                //puts("LEFT KEY PRESSED");
                if(page > 1) page--;
            }else if(key==right){
                // puts("RIGHT KEY PRESSED");
                page++;
            }
        }
    }
}

