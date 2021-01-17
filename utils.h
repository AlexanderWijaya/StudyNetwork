#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
int page = 1;
// #################################### INITIALIZE STRUCT ####################################
struct Friends{
    char username[25];
    Friends *next;
};
struct Requests{
    char username[25];
    Requests *next;
};
struct Sents{
    char username[25];
    Sents *next;
};
struct Comments{
    char username[25];
    char comment[256];
    int likes;
    int num; 
    Comments *next;
}*headcom, *tailcom;
struct Notes{
    char notes[256];
    int id;
    char category[20];
    int announced; // 1 = yes, 0 = no
    int privatecheck; // 1 = public , 0 = private
    Comments *cmntHead;
    Notes *next;
}*headnote;
struct Account{
    char username[25];
    char password[25];
    Friends *friendHead;
    Requests *reqHead;
    Sents *sentHead;
    Notes *noteHead;
    Account *next;
} *head, *tail, *curr;


// #################################### CREATE NODES ####################################

Account *createAcc(char *username, char *password){
    Account *temp = (Account*)malloc(sizeof(Account));
    strcpy(temp->username , username);
    strcpy(temp->password , password);
    temp->reqHead = NULL;
    temp->sentHead = NULL;
    temp->noteHead = NULL;
    temp->friendHead = NULL;
    temp->next = NULL;
    return temp;
}
Friends *createFriend(char *username){
    Friends *temp = (Friends*)malloc(sizeof(Friends));
    strcpy(temp->username , username);
    temp->next = NULL;
    return temp;
}
Requests *createRequest(char *username){
    Requests *temp = (Requests*)malloc(sizeof(Requests));
    strcpy(temp->username , username);
    temp->next = NULL;
    return temp;
}
Sents *createSent(char *username){
    Sents *temp = (Sents*)malloc(sizeof(Sents));
    strcpy(temp->username , username);
    temp->next = NULL;
    return temp;
}
Comments *createComment(char *username, char *comment, int num){
    Comments *temp = (Comments*)malloc(sizeof(Comments));
    strcpy(temp->comment , comment);
    temp->next = NULL;
    temp->num = num;
    return temp;
}
Notes *createNote(char *notes, char *category, int announced, int privatecheck, int id){
    Notes *temp = (Notes*)malloc(sizeof(Notes));
    strcpy(temp->notes, notes);
    strcpy(temp->category, category);
    temp->announced = announced;
    temp->privatecheck = privatecheck;
    temp->id = id;
    temp->cmntHead = NULL;
    temp->next = NULL;
    return temp;
}

// #################################### PRINT ALL'S ####################################

void PrintUser()
{
    Account *curr = head;

    printf("[All User]\n");
    printf("No.     Username\n");
    int i = 1;
    while(curr != NULL)
    {
        printf("%2d      %s\n", i++, curr->username);
        curr = curr->next;
    }
}
void PrintFriends(char *username)
{
    Account *curr = head;

    puts("[Your Friends]");
    puts("No.     Username");

    while(curr){
        if(strcmp(username,curr->username) == 0){
            Friends *curr2 = curr->friendHead;
                int i=1;
                while(curr2){
                    printf("%2d      %s\n", i++, curr2->username);
                    curr2 = curr2->next;
                }
                return;
            }
            curr = curr->next;
        }
    }

void PrintRequest(char *username){
    Account *curr = head;

    puts("[Friend Requests]");
    puts("No.     Username");

    while(curr)
    {
        if(strcmp(username, curr->username) == 0){
        Requests *curr2 = curr->reqHead;
            int i=1;
            while(curr2){
                printf("%2d      %s\n", i++, curr2->username);
                curr2 = curr2->next;
            }
            return;
        }
        curr = curr->next;
    }
}
void PrintSent(char *username){
    Account *curr = head;

    puts("[Friend Requests sent by you]");
    puts("No.     Username");

    while(curr)
    {
        if(strcmp(username, curr->username) == 0){
        Sents *curr2 = curr->sentHead;
            int i=1;
            while(curr2){
                printf("%2d      %s\n", i++, curr2->username);
                curr2 = curr2->next;
            }
            return;
        }
        curr = curr->next;
    }
}

// #################################### REGISTER & LOGIN ####################################

int CheckUsername(char *username)
{
    Account *curr = head;

    while(curr != NULL)
    {
        if(strcmp(username, curr->username) == 0)
        {
            return 1; //barti ada yang sama
        }
        curr = curr->next;
    }
    return 0; // aman boleh dipake
}
int CheckLogin(char *username, char *password)
{
    Account *curr = head;

    while(curr != NULL)
    {
        if(strcmp(username, curr->username) == 0 && strcmp(password, curr->password) == 0)
        {
            return 1; //barti ada yang sama
        }
        curr = curr->next;
    }
    return 0; // aman boleh dipake
}
void pushAcc(char *username, char *password) {
  Account *temp = createAcc(username, password);
  if(!head) 
  { 
    head = tail = temp;
  }
  else 
  {
    tail->next = temp;
    tail = temp; 
  }
}

// #################################### ADD FRIEND REQUESTS ####################################

int CheckRequest(char *sender, char *receiver){
    Account *curr = head;

    while(curr){
        if(strcmp(receiver, curr->username) == 0){
            Requests *curr2 = curr->reqHead;
            while(curr2){
                if(strcmp(sender, curr2->username) == 0){
                    return 1;
                }
                curr2 = curr2->next;
            }
        }
        curr = curr->next;
    }

    return 0;
}

void pushRequest(char *sender, char *receiver){
    Account *curr = head;

    while(curr){
        if(strcmp(receiver, curr->username) == 0){
            Requests *temp = createRequest(sender);

            if(!curr->reqHead) {  // ini push head
                curr->reqHead = temp;
            } else { 
                temp->next = curr->reqHead;
                curr->reqHead = temp;
            }
        }

        if(strcmp(sender, curr->username) == 0){
            Sents *temp2 = createSent(receiver);

            if(!curr->sentHead) {  // ini push head
                curr->sentHead = temp2;
            } else { 
                temp2->next = curr->sentHead;
                curr->sentHead = temp2;
            }
        }
        curr = curr->next;
    }
}


// #################################### FRIENDS ####################################

void pushFriends(char *sender, char *receiver)
{
    Account *curr = head;

    while(curr){
        if(strcmp(receiver, curr->username) == 0){
            Friends *temp = createFriend(sender);

            if(!curr->friendHead) {
                curr->friendHead = temp;
            } else { 
                temp->next = curr->friendHead;
                curr->friendHead = temp;
            }

            // Requests *curr2 = curr->reqHead;
            // Requests *temp2;

            // if(strcmp(curr2->username,sender)==0){
            //     temp2 = curr->reqHead->next;
            //     curr->reqHead = NULL;
            //     free(curr->reqHead);
            //     curr->reqHead = temp2;
            // }else{
            //     while(curr2){
            //         if(strcmp(curr2->next->username, receiver)==0){
            //             temp2 = curr2->next->next;
            //             free(curr2->next);
            //             curr2->next = NULL;
            //             curr2->next = temp2;
            //         }
            //     }
            // }
        }

        if(strcmp(sender, curr->username) == 0){
            Friends *temp = createFriend(receiver);

            if(!curr->friendHead) { 
                curr->friendHead = temp;
            } else { 
                temp->next = curr->friendHead;
                curr->friendHead = temp;
            }

            // Sents *curr2 = curr->sentHead;
            // Sents *temp2;

            // if(strcmp(curr2->username,sender)==0){
            //     temp2 = curr->sentHead->next;
            //     curr->sentHead = NULL;
            //     free(curr->sentHead);
            //     curr->sentHead = temp2;
            // }else{
            //     while(curr2){
            //         if(strcmp(curr2->next->username, receiver)==0){
            //             temp2 = curr2->next->next;
            //             free(curr2->next);
            //             curr2->next = NULL;
            //             curr2->next = temp2;
            //         }
            //     }
            // }
        }
        curr = curr->next;
    }
}

void deleteFriend(char *sender, char *receiver)
{
    Account *curr = head;

    while(curr){
        if(strcmp(receiver, curr->username) == 0){
            //pop friend
        }

        if(strcmp(sender, curr->username) == 0){
            // pop friend
        }
    }
}

// #################################### PUBLIC DASHBOARD ####################################

// ######## POST ###########

void pushNotes(char *username, char *notes, char *category, int announced, int privatecheck, int id){
    Account *curr = head;

    while(curr){
        if(strcmp(username, curr->username) == 0){
            Notes *temp = createNote(notes, category, announced, privatecheck, id);

            if(!curr->noteHead){
                curr->noteHead = temp;
            } else { 
                temp->next = curr->noteHead;
                curr->noteHead = temp;
            }
        }
    }
}
void pushComment(char *username, char *comment, char *tempnote, int num)
{
    Account *curr = head;
    Notes *current = headnote;
    while(curr)
    {
        if(strcmp(username, curr->username) == 0)
        {
            while(current)
            {
                if(strcmp(current->notes,  tempnote) == 0)
                {
                    Comments *temp = createComment(username, comment, num);
                    Comments *cur = headcom;
                    if(!cur)
                    {
                        headcom = temp;
                    } else 
                    {
                        tailcom->next = temp;
                        tailcom = temp;
                    }
                }
            }

        }
    }
}
