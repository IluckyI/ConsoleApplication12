#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdbool>
#include <cstring>
#include<cstdlib>


//static const int MAX_ACCOUNT_NUM = 100;
static const char* FILE_PATH = "accounts.txt";


enum
{
	INVALID_ACCOUNT_NO = 0,
};



typedef struct _ClientData
{
	int acctNum;
	char lastName[15];
	char firstName[10];
	double balance;
}ClientData, *ClientDataptr;
typedef struct _Node
{
	ClientDataptr data;
	_Node* next;
}Node, *Nodeptr;

//static ClientDataptr s_clients = { 0 };

enum OperatorType
{
	INSERT,
	DELETE,
	UPDATE,
};



//int	 updateData(OperatorType type, ClientData* data);
int  enterChoice(void);
void textFile(Nodeptr);
void updateRecord(Nodeptr *);
void newRecord(Nodeptr *header, int num, char*first, char*last, double bal);
void deleteRecord(Nodeptr *);
void initialize(FILE *);
void display(FILE *file);
Nodeptr  recordIndex(Nodeptr ,int);
//void Write_Buff(Buffptr );
Nodeptr new_node(Nodeptr *node);
bool fileExist(const char* file)
{
	FILE *pf = fopen(file, "r");
	if (pf == 0)
		return false;
	fclose(pf);
	return true;
}

static FILE *cfPtr = 0;

int main()
{
	int acctNum = 0;
	char firstName[15];
	char lastName[10];
	double balance;
	//对文件是否存在分情况处理
	if (!fileExist(FILE_PATH))
	{
		cfPtr = fopen(FILE_PATH, "w+");
	}
	else
	{
		cfPtr = fopen(FILE_PATH, "r+");
	}

	if (cfPtr == 0)
	{
		perror("create file:");
		return -1;
	}
	fclose(cfPtr);
	Nodeptr header =  0 ;
	//Nodeptr info = (Nodeptr)malloc(sizeof(Node));
	Nodeptr pNode = header;
	//initialize(cfPtr);

	int choice;
	while ((choice = enterChoice()) != 5)
	{

		switch (choice)
		{
		case 2:
			updateRecord(&header);
			break;
		case 1:
			
			printf("input name:\n");
			scanf("%d", &acctNum);
			printf("input firstName:\n");
			scanf("%s",firstName );
			printf("input lastName:\n");
			scanf("%s",lastName );
			printf("input balance:\n");
			scanf("%lf",&balance);
			newRecord(&header,acctNum,firstName,lastName,balance);
			break;
		case 3:
			deleteRecord(&header);
			break;
		case 4:
			display(cfPtr);
			break;

		}
	}
		if (choice == 5)
		{
			textFile(header);
		}
	

	fclose(cfPtr);


	return 0;
}

//void initialize(FILE *file)
//{
//	//memset(s_clients, 0, MAX_ACCOUNT_NUM * sizeof(ClientData));
//	int count = 0;
//	while (!feof(file) && count < 100)
//	{
//		size_t ret = fread(&s_clients[count], sizeof(ClientData), 1, file);
//		if (ret != 1)
//		{
//			break;
//		}
//		count++;
//	}
//}

Nodeptr recordIndex(Nodeptr header,int account)
{
	Nodeptr pNode = header;
	while(pNode)
	{

		if (pNode->data->acctNum == account)
		{
			return pNode;
		}
		pNode = pNode->next;
	}
	return  NULL;
}

void textFile(Nodeptr header)
{
	FILE *writePtr = 0;
	//ClientData client = { 0, "", "", 0.0 };

	/*if ((writePtr = fopen("accounts.txt", "w")) == NULL)
	{
		printf("File could not be opened.\n");
	}*/
	Nodeptr pCurNode = header;
	writePtr=fopen(FILE_PATH, "w+");
	fprintf(writePtr, "%-6s%-16s%-11s%10s\n",
			"Acct", "Last Name", "First Name", "Balance");

	while (pCurNode!=NULL)
	{
	
		if (pCurNode->data->acctNum!= INVALID_ACCOUNT_NO)
			fprintf(writePtr, "%-6d%-16s%-11s%10.2f\n",
			pCurNode->data->acctNum, pCurNode->data->lastName,
				pCurNode->data->firstName, pCurNode->data->balance);
		pCurNode = pCurNode->next;
	}

		fclose(writePtr);
	

}

void updateRecord(Nodeptr *header)
{
	if (*header == NULL)
	{
		printf("no info !\n");
		return;
	}
	Nodeptr pCurNode = *header;
	int account;

	printf("Enter account to update ( 1 - 100 ): ");
	scanf("%d", &account);

	Nodeptr index = recordIndex(pCurNode,account);
	if (NULL == index)
	{
		printf("Acount #%d has no information.\n", account);
		return;
	}
	pCurNode = index;
	//ClientData data = s_clients[index];

	printf( "---------------------------------------------\n"
		"%-6s%-16s%-11s%10s\n",
		"Acct", "Last Name", "First Name", "Balance");

	printf("%-6d%-16s%-11s%10.2f\n\n",
		pCurNode->data->acctNum, pCurNode->data->lastName,
		pCurNode->data->firstName, pCurNode->data->balance);
	printf("Enter charge ( + ) or payment ( - ): ");
	double transaction;
	scanf("%lf", &transaction);
	pCurNode->data->balance += transaction;
	printf("%-6d%-16s%-11s%10.2f\n",
		pCurNode->data->acctNum, pCurNode->data->lastName,
		pCurNode->data->firstName, pCurNode->data->balance);
	printf("---------------------------------------------\n");
	//updateData(UPDATE, &data);
}

void deleteRecord(Nodeptr *header)
{
	if (*header == NULL)//如果链表为空
	{
		printf("don't have info!\n");
		return;
	}	
	Nodeptr pCurNode = *header;
	int accountNum;
	printf("Enter account number to "
		"delete ( 1 - 100 ): ");
	scanf("%d", &accountNum);
	Nodeptr pNode=pCurNode;//pNode为上一个节点指针

		while (pCurNode->data->acctNum != accountNum)
		{
			 pNode = pCurNode;
			pCurNode = pCurNode->next;
			if (pCurNode == NULL)
			{
				printf("no find this info!\n");
				return;
			}

		}
		if (pNode == pCurNode)
		{
			pCurNode = pCurNode->next;
			free(pNode);
			 *header=pCurNode ;
		//	*header=NULL;
		}
		else
		{
			pNode->next = pCurNode->next;
			free(pCurNode);
		}
	
	//pNode->data = pCurNode->data;
	
	//pCurNode = NULL;
	//pCurNode->data = NUL;
	printf("delete data successful!\n");
     
}

void newRecord(Nodeptr *header,int num,char*first,char*last,double bal)
{
	Nodeptr pCurNode = *header;
	if (*header == NULL)
    {
		new_node(header);
		pCurNode = *header;
	}
	else
	{
		if (pCurNode->data->acctNum == num)
		{
			printf("#%d have information\n", num);
			return;
		}
		while (pCurNode->next != NULL)
		{
			if (pCurNode->data->acctNum == num)
			{
				printf("#%d have information\n", num);
				return;
			}
			pCurNode = pCurNode->next;
			
		}
		
		//1. 生成新Node
		Node* pNewNode = (Nodeptr)malloc(sizeof(Node));
		memset(pNewNode, 0, sizeof(Node));
		pNewNode->data = (ClientDataptr)malloc(sizeof(ClientData));
		memset(pNewNode->data, 0, sizeof(ClientData));
		//2. 更新插入位置节点的原下个节点与新节点的关系
		//pNewNode->next = pCurNode->next;
		//3. 更新插入位置节点与新节点的关系
		pCurNode->next = pNewNode;

		pCurNode = pNewNode;//更新当前结点
	}
	strcpy(pCurNode->data->lastName, last);
	strcpy(pCurNode->data->firstName,first);
	pCurNode->data->acctNum = num;
	pCurNode->data->balance = bal;



	//ClientData client = { 0, "", "", 0.0 };
	//int accountNum;
	//printf("Enter new account number ( 1 - 100 ): ");
	//scanf("%d", &accountNum);
	////找到该记录在列表中的索引
	//int index = recordIndex(accountNum);
	//if (1 != index)//如果该记录已经存在
	//{
	//	printf("Account #%d already contains information.\n",
	//		client.acctNum);
	//	return;
	//}
	//printf("Enter lastname, firstname, balance\n? ");
	//scanf("%s%s%lf", &client.lastName, &client.firstName,
	//	&client.balance);
	//client.acctNum = accountNum;

	//updateData(INSERT, &client);
}

//int updateData(OperatorType type, ClientData * data)
//{
//	int index = recordIndex(data->acctNum);
//
//	if (-1 == index)
//	{
//		printf("Account %d does not exist.\n", data->acctNum);
//		return -1;
//	}
//
//	switch (type)
//	{
//	case DELETE:
//	{
//		//更新文件
//		fseek(cfPtr, index * sizeof(ClientData), SEEK_SET);
//		data->acctNum = INVALID_ACCOUNT_NO;
//		fwrite(data,
//			sizeof(ClientData), 1, cfPtr);
//		//更新内存数据
//		s_clients[index].acctNum = INVALID_ACCOUNT_NO;
//	}
//	break;
//	case UPDATE:
//	{
//		//更新数据
//		s_clients[index].balance = data->balance;//更新数据缓冲
//		fseek(cfPtr,
//			index * sizeof(ClientData),
//			SEEK_SET);
//		fwrite(&s_clients[index], sizeof(ClientData), 1,
//			cfPtr);//更新文件
//
//	}
//	break;
//	case INSERT:
//	{
//		//找到第一条可用record位置
//		index = recordIndex(INVALID_ACCOUNT_NO);
//		//更新数据记录文件
//		fseek(cfPtr, index * sizeof(ClientData), SEEK_SET);
//		fwrite(data, sizeof(ClientData), 1, cfPtr);
//		//更新缓冲区数据	
//		s_clients[index] = *data;
//	}
//	break;
//	default:
//		break;
//	}
//
//	return 0;
//}

int enterChoice(void)
{
	int menuChoice;

	printf("\nEnter your choice\n"

		"1 - add a new account\n"	
		"2 - update an account\n"
		"3 - delete an account\n"
		"4- display \n"
		"5 - end program\n "
		"store a formatted text file of acounts called\n"
		"    \"accounts.txt\" for printing\n");
	scanf("%d", &menuChoice);
	return menuChoice;
}
void display(FILE *file)
{
	file = fopen("accounts.txt", "r+");
	char w[256] = { 0 };
	printf("Information line:\n");
	while (fgets(w, 256, file) != 0)
	{
		fputs(w, stdout);

	}
	fclose(file);

}
Nodeptr new_node(Nodeptr *node)
{
	Nodeptr ptr = (Nodeptr)malloc(sizeof(Node));
	memset(ptr, 0, sizeof(Node));
    ptr->data = (ClientDataptr)malloc(sizeof(ClientData));
    memset(ptr->data, 0, sizeof(ClientData));
	if (node != 0)
	{
		*node = ptr;
		
		
	}
	return ptr;//*node	
}
