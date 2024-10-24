#include "main.h"
#include "login.h"



int mainLogin()
{
	UserNode* head = NULL;
	readDataInUserFile(&head);
	int ret=-1;
	while (ret!=0 && ret!=1)
	{
		ret=loginKeyDown(&head);
		system("pause");
		system("cls");
	}
	list_free(&head);
	if(ret==1)
	{
		return 1;
	}
	return 0;
}


//关于登录的人机交互
int loginKeyDown(UserNode** head)
{
	int key = 0;
	showLoginMenu();
	fflush(stdin);		//清空缓冲区
	scanf("%d", &key);
	printf("\n");
	switch (key)
	{
	case 1:
		if(loginUser(*head))
		{
			printf("欢迎你，登陆成功\n");
			return 1;
		}
	
		break;

	case 2:

		if (addUser(head))
		{
			printf("账号注册成功\n");
			writeDataInUserFile(*head);
		}
		break;

	case 3:
		if(changePasswd(*head))
		{
			printf("密码修改成功,请重新登录账号\n");
			writeDataInUserFile(*head);
		}
		break;

	case 4:
		return 0;
		break;

	case 5:
		show(*head);
		break;
	default:
		printf("输入指令错误，请重新输入\n");
		
	}
	return -1;

}


//创建新节点
UserNode* createNewNode(char* account, char* passwd)
{
	UserNode* newNode = (UserNode*)malloc(sizeof(UserNode));
	User* data = (User*)malloc(sizeof(User));
	if (newNode == NULL)
	{
		printf("内存分配失败\n");
		return NULL;
	}
	newNode->next = NULL;
	strcpy(data->account, account);
	strcpy(data->passwd, passwd);
	newNode->data = data;
	return newNode;
}

//增加节点
void addNode(UserNode** head, UserNode* newNode)
{
	if (*head == NULL)
	{
		*head = newNode;
		return;
	}
	newNode->next = (*head)->next;
	(*head)->next = newNode;
}

//验证账号是否合法
int isTrueAccount(char* account)
{
	int len = 0;
	if (account[0] >= '0' && account[0] <= '9')
	{
		printf("输入账号非法,请重新输入\n\n");
		return 0;
	}
	for (int i = 0; account[i] != '\0'; i++)
	{
		if (account[i] >= '0' && account[i] <= '9' || account[i] >= 'a' && account[i] <= 'z' || account[i] >= 'A' && account[i] <= 'Z')
		{
			len++;
		}
		else
		{
			printf("输入账号非法,请重新输入\n\n");
			return 0;
		}


	}
	if (len < 8 || len>20)
	{
		printf("输入账号非法,请重新输入\n");
		printf("\n");
		return 0;
	}
	return 1;
}

//验证账号密码是否合法
int isTruePasswd(char* passwd)
{
	int len = 0;
	for (int i = 0; passwd[i] != '\0'; i++)
	{
		if (passwd[i] >= '0' && passwd[i] <= '9' || passwd[i] >= 'a' && passwd[i] <= 'z' || passwd[i] >= 'A' && passwd[i] <= 'Z')
		{
			len++;
		}
		else
		{
			printf("输入密码非法,请重新输入\n\n");
			return 0;
		}


	}
	if (len < 8 || len>20)
	{
		printf("输入密码非法,请重新输入\n");
		printf("\n");
		return 0;
	}
	return 1;
}

//验证用户账号信息
int checkUser(UserNode* head, char* account, char* passwd)
{
	return 1;
}

//查找用户账号信息
UserNode* findUser(UserNode* head, char* account)
{
	if (head == NULL)
	{
		return NULL;
	}
	while (head)
	{
		if (memcmp(head->data->account, account, strlen(account)) == 0)
		{
			return head;
		}
		head = head->next;
	}
	return NULL;
}


//密码加密：“*”表示字符
void getPwd(char* pwd)
{
	int n = 0;
    int i = 0;
    while(1){
        char an = getch();//从控制台读取一个字符，但不显示在屏幕上
        if(an == 13)//回车键
		{
			pwd[n]='\0';
			break;
		}
            
        if(an == 8) //退格键
        {   n--;
            system("cls");
            printf("请输入密码：");
            for(i = 0; i < n; i++){
                printf("*");
            }
            continue;
        }
        printf("*");
        pwd[n++] = an;
    }
	printf("\n");
}


//添加用户
int addUser(UserNode** head)
{
	char newAccount[MAX_ARR_LENGTH];
	char newPasswd[MAX_ARR_LENGTH];
	printf("请输入账号信息：\n");
	printf("温馨提示：\n\t账号与密码位数均为8~20位，账号首位只能为字母，\n\t且账号和密码只支持大小写字母与数字\n\n");
	do {
		printf("请输入账号：");
		scanf("%s", newAccount);
	} while (!isTrueAccount(newAccount));

	do {
		printf("请输入密码：");
		getPwd(newPasswd);
	} while (!isTruePasswd(newPasswd));
	if (findUser(*head, newAccount))
	{
		printf("该账号已被注册\n");
		return 0;
	}
	UserNode* newNode = createNewNode(newAccount, newPasswd);
	addNode(head, newNode);
	return 1;
}

//显示用户登录菜单
void showLoginMenu()
{
    
	printf("\n\t\t\t╔═════════════════════════════════════════╗");
	printf("\n\t\t\t║ ******欢迎使用城市地铁线路管理系统******║\n");
	printf("\t\t\t║\t\t\t\t\t  ║\n");
	printf("\t\t\t║ ******  \t① 登录账号          ******║\n");
	printf("\t\t\t║ ******  \t② 注册账号          ******║\n");
	printf("\t\t\t║ ******  \t③ 修改密码          ******║\n");
	printf("\t\t\t║ ******  \t④ 退出系统          ******║\n");
	printf("\t\t\t║ ****************************************║\n");
	printf("\t\t\t║ *******\t  请先登录\t   *******║\n");
	printf("\t\t\t╚═════════════════════════════════════════╝\n");

	printf("\n\t\t请输入选项：");

}

//文件读操作
void readDataInUserFile(UserNode **head)
{
	FILE* fp = fopen(UserFileName, "r");
	UserNode* newNode;
	
	char account[MAX_ARR_LENGTH];
	char passwd[MAX_ARR_LENGTH];
	if(fp==NULL)
	{
		fp = fopen(UserFileName, "w+");
	}
	while(fscanf(fp,"%s %s\n",account,passwd)!=EOF)
	{
		newNode=createNewNode(account,passwd);
		addNode(head, newNode);
	}
	fclose(fp);

}

//文件写操作
void writeDataInUserFile(UserNode *head)
{
    FILE* fp=fopen(UserFileName,"w");
    if(fp==NULL)
    {
		perror("fopen");
		return;
    }
    while(head)
    {
     fprintf(fp,"%s %s\n",head->data->account,head->data->passwd);
	 head=head->next;
    }
    fclose(fp);
}

void show(UserNode* head)
{
	if (head == NULL)
	{
		printf("链表为空\n");
		return;
	}
	while (head)
	{
		printf("账号：%s\n", head->data->account);
		printf("密码：%s\n", head->data->passwd);
		head = head->next;
	}
}

//用户登录
UserNode* loginUser(UserNode *head)
{
	char account[MAX_ARR_LENGTH];
	char passwd[MAX_ARR_LENGTH];
	printf("请输入账号信息：\n");
	do {
		printf("请输入账号：");
		scanf("%s", account);
	} while (!isTrueAccount(account));

	do {
		printf("请输入密码：");
		getPwd(passwd);
	} while (!isTruePasswd(passwd));
	UserNode* user=findUser(head, account);
	if (!user)
	{
		printf("未找到该账号，请先去注册账号\n");
		return NULL;
	}
	if (memcmp(user->data->passwd,passwd,strlen(passwd)))
	{
		printf("输入密码错误\n");
		return NULL;
	}
	return user;
}

//修改密码
int changePasswd(UserNode* head)
{
	char newPasswd[MAX_ARR_LENGTH];
	char newPasswd2[MAX_ARR_LENGTH];
	char oldPasswd[MAX_ARR_LENGTH];
	UserNode* user=loginUser(head);
	if(!user)
	{
		return 0;
	}
	do{
		printf("请输入原密码：");
		getPwd(oldPasswd);
		if(!memcmp(user->data->passwd,oldPasswd,strlen(oldPasswd)))
		{
			break;
		}
		printf("输入密码错误,请重新输入\n");
	}while (1);
	do
	{
		do {
			printf("请输入新的密码：");
			getPwd(newPasswd);
		} while (!isTruePasswd(newPasswd));
		do {
			printf("请再次输入新的密码：");
			getPwd(newPasswd2);
		} while (!isTruePasswd(newPasswd2));
		if(!memcmp(newPasswd,newPasswd2,strlen(oldPasswd)))
		{
			break;
		}
		printf("两次输入密码不一致,请重新输入\n");
		
	}while(1);
	strcpy(user->data->passwd,newPasswd);
	return 1;
}

//释放链表空间
void list_free(UserNode** head)
{
	UserNode* p=*head;
	UserNode* q=NULL;
	while(p!=NULL)
	{
		q=p;
		p=p->next;
		free(q->data);
		free(q);
		q=NULL;
	}
}


