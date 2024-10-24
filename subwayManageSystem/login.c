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


//���ڵ�¼���˻�����
int loginKeyDown(UserNode** head)
{
	int key = 0;
	showLoginMenu();
	fflush(stdin);		//��ջ�����
	scanf("%d", &key);
	printf("\n");
	switch (key)
	{
	case 1:
		if(loginUser(*head))
		{
			printf("��ӭ�㣬��½�ɹ�\n");
			return 1;
		}
	
		break;

	case 2:

		if (addUser(head))
		{
			printf("�˺�ע��ɹ�\n");
			writeDataInUserFile(*head);
		}
		break;

	case 3:
		if(changePasswd(*head))
		{
			printf("�����޸ĳɹ�,�����µ�¼�˺�\n");
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
		printf("����ָ���������������\n");
		
	}
	return -1;

}


//�����½ڵ�
UserNode* createNewNode(char* account, char* passwd)
{
	UserNode* newNode = (UserNode*)malloc(sizeof(UserNode));
	User* data = (User*)malloc(sizeof(User));
	if (newNode == NULL)
	{
		printf("�ڴ����ʧ��\n");
		return NULL;
	}
	newNode->next = NULL;
	strcpy(data->account, account);
	strcpy(data->passwd, passwd);
	newNode->data = data;
	return newNode;
}

//���ӽڵ�
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

//��֤�˺��Ƿ�Ϸ�
int isTrueAccount(char* account)
{
	int len = 0;
	if (account[0] >= '0' && account[0] <= '9')
	{
		printf("�����˺ŷǷ�,����������\n\n");
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
			printf("�����˺ŷǷ�,����������\n\n");
			return 0;
		}


	}
	if (len < 8 || len>20)
	{
		printf("�����˺ŷǷ�,����������\n");
		printf("\n");
		return 0;
	}
	return 1;
}

//��֤�˺������Ƿ�Ϸ�
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
			printf("��������Ƿ�,����������\n\n");
			return 0;
		}


	}
	if (len < 8 || len>20)
	{
		printf("��������Ƿ�,����������\n");
		printf("\n");
		return 0;
	}
	return 1;
}

//��֤�û��˺���Ϣ
int checkUser(UserNode* head, char* account, char* passwd)
{
	return 1;
}

//�����û��˺���Ϣ
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


//������ܣ���*����ʾ�ַ�
void getPwd(char* pwd)
{
	int n = 0;
    int i = 0;
    while(1){
        char an = getch();//�ӿ���̨��ȡһ���ַ���������ʾ����Ļ��
        if(an == 13)//�س���
		{
			pwd[n]='\0';
			break;
		}
            
        if(an == 8) //�˸��
        {   n--;
            system("cls");
            printf("���������룺");
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


//����û�
int addUser(UserNode** head)
{
	char newAccount[MAX_ARR_LENGTH];
	char newPasswd[MAX_ARR_LENGTH];
	printf("�������˺���Ϣ��\n");
	printf("��ܰ��ʾ��\n\t�˺�������λ����Ϊ8~20λ���˺���λֻ��Ϊ��ĸ��\n\t���˺ź�����ֻ֧�ִ�Сд��ĸ������\n\n");
	do {
		printf("�������˺ţ�");
		scanf("%s", newAccount);
	} while (!isTrueAccount(newAccount));

	do {
		printf("���������룺");
		getPwd(newPasswd);
	} while (!isTruePasswd(newPasswd));
	if (findUser(*head, newAccount))
	{
		printf("���˺��ѱ�ע��\n");
		return 0;
	}
	UserNode* newNode = createNewNode(newAccount, newPasswd);
	addNode(head, newNode);
	return 1;
}

//��ʾ�û���¼�˵�
void showLoginMenu()
{
    
	printf("\n\t\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
	printf("\n\t\t\t�U ******��ӭʹ�ó��е�����·����ϵͳ******�U\n");
	printf("\t\t\t�U\t\t\t\t\t  �U\n");
	printf("\t\t\t�U ******  \t�� ��¼�˺�          ******�U\n");
	printf("\t\t\t�U ******  \t�� ע���˺�          ******�U\n");
	printf("\t\t\t�U ******  \t�� �޸�����          ******�U\n");
	printf("\t\t\t�U ******  \t�� �˳�ϵͳ          ******�U\n");
	printf("\t\t\t�U ****************************************�U\n");
	printf("\t\t\t�U *******\t  ���ȵ�¼\t   *******�U\n");
	printf("\t\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");

	printf("\n\t\t������ѡ�");

}

//�ļ�������
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

//�ļ�д����
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
		printf("����Ϊ��\n");
		return;
	}
	while (head)
	{
		printf("�˺ţ�%s\n", head->data->account);
		printf("���룺%s\n", head->data->passwd);
		head = head->next;
	}
}

//�û���¼
UserNode* loginUser(UserNode *head)
{
	char account[MAX_ARR_LENGTH];
	char passwd[MAX_ARR_LENGTH];
	printf("�������˺���Ϣ��\n");
	do {
		printf("�������˺ţ�");
		scanf("%s", account);
	} while (!isTrueAccount(account));

	do {
		printf("���������룺");
		getPwd(passwd);
	} while (!isTruePasswd(passwd));
	UserNode* user=findUser(head, account);
	if (!user)
	{
		printf("δ�ҵ����˺ţ�����ȥע���˺�\n");
		return NULL;
	}
	if (memcmp(user->data->passwd,passwd,strlen(passwd)))
	{
		printf("�����������\n");
		return NULL;
	}
	return user;
}

//�޸�����
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
		printf("������ԭ���룺");
		getPwd(oldPasswd);
		if(!memcmp(user->data->passwd,oldPasswd,strlen(oldPasswd)))
		{
			break;
		}
		printf("�����������,����������\n");
	}while (1);
	do
	{
		do {
			printf("�������µ����룺");
			getPwd(newPasswd);
		} while (!isTruePasswd(newPasswd));
		do {
			printf("���ٴ������µ����룺");
			getPwd(newPasswd2);
		} while (!isTruePasswd(newPasswd2));
		if(!memcmp(newPasswd,newPasswd2,strlen(oldPasswd)))
		{
			break;
		}
		printf("�����������벻һ��,����������\n");
		
	}while(1);
	strcpy(user->data->passwd,newPasswd);
	return 1;
}

//�ͷ�����ռ�
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


