#ifndef __LOGIN_H__
#define __LOGIN_H__

#define MAX_ARR_LENGTH 20
#define UserFileName "D:/tmpFile/user.txt"

typedef struct user
{
	char account[MAX_ARR_LENGTH];
	char passwd[MAX_ARR_LENGTH];
}User;

typedef struct UserNodeInfo  //链表存储用户信息
{
	User* data;
	struct UserNodeInfo* next;

}UserNode;


int mainLogin();
UserNode* createNewNode(char* account, char* passwd);
void addNode(UserNode** head, UserNode* newNode);
int isTrueAccount(char* account);
int isTruePasswd(char* passwd);
int checkUser(UserNode* head, char* account, char* passwd);
UserNode* findUser(UserNode* head, char* account);
void getPwd(char* pwd);
int addUser(UserNode** head);
void showLoginMenu();
void readDataInUserFile(UserNode **head);
void writeDataInUserFile(UserNode *head);
void show(UserNode* head);
UserNode* loginUser(UserNode *head);
int changePasswd(UserNode* head);
void list_free(UserNode** head);
int loginKeyDown(UserNode** head);

#endif