#pragma once
#define _CRT_SECURE_NO_WARNINGS

//#include "pointer.h"

//#include "string_test.h"
//#include "shuffle.h"

//#include "file_test.h"

#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdbool>

typedef enum _Sex
{
	MALE,
	FEMALE

}Sex;

typedef struct _Node
{
	char name[256];
	int  salary;
	Sex  sex;
	struct _Node* next;
} Node, *NodePtr;


void processList(NodePtr list)
{
	//�����������������
	Node* pNode = list;
	int row = 1;
	while (pNode != 0)
	{
		printf(":%d\t%s\t%d\t", row, pNode->name,pNode->salary);
		if (pNode->sex == MALE)
			printf("MALE\n");
		else
			printf("FEMALE\n");
		pNode = pNode->next;
		row++;
	}

	fputs("\n", stdout);
}

bool isEmpty(NodePtr list)
{
	return list == 0;
}

int insertData(NodePtr *ppNode, const char* data1, const int *data2, const Sex *data3)
{
	NodePtr pCurNode = *ppNode;

	if (pCurNode == 0) //��Ϊ�յ����������ڵ�λ��Ϊ�գ�
	{
		*ppNode = (NodePtr)malloc(sizeof(Node));
		memset(*ppNode, 0, sizeof(Node));
		pCurNode = *ppNode;
		strcpy(pCurNode->name, data1);
		pCurNode->salary = *data2;
		pCurNode->sex = *data3;

	}
	else
	{
		//1. ������Node
		Node* pNewNode = (Node*)malloc(sizeof(Node));
		memset(pNewNode, 0, sizeof(Node));
		//2. ����ڵ��next��ֵ����Node
		pNewNode->next = pCurNode->next;
		//3. 
		pCurNode->next = pNewNode;

		pCurNode = pNewNode;//���µ�ǰ���
		strcpy(pCurNode->name, data1);
		pNewNode->salary = *data2;
    	pNewNode->sex = *data3;
	}
	//�������ݣ����ڵ����ݸ�ֵ��
	//strcpy(pCurNode->name, data1);
	
	return 0;
}

/**
* ��ָ���ڵ��׷�ӽڵ㣬�������ݸ�ֵ������ڵ㡣
* 1. ����б�Ϊ�գ������½ڵ㣬 ��ֵ
* 2. ֱ�������б�ĩ�ˣ������½ڵ�
*
* @author zf (09/01/2017)
*
* @param NodePtr   �б�ͷ�ڵ�ָ��
*
* @param const char*   ����
*
* @return int  ʧ�ܷ���-1�� �ɹ�����0
*/
int appendData(NodePtr *ppNode, const char* data1,const int *data2,const Sex *data3)
{
	if (*ppNode == 0)
	{
		return insertData(ppNode, data1,data2,data3);
	}

	NodePtr pNode = *ppNode;

	while (pNode->next != 0)
	{
		pNode = pNode->next;
	}


	Node* pNewNode = (Node*)malloc(sizeof(Node));
	if (pNewNode == 0)
	{
		return -1;
	}
	memset(pNewNode, 0, sizeof(Node));

	pNode->next = pNewNode;

	strcpy(pNewNode->name, data1);
	pNewNode->salary = *data2;
	pNewNode->sex = *data3;
	return 0;

}


int deleteData(NodePtr *ppNode, const char* data)
{
	if (ppNode == 0 || *ppNode == 0)
	{
		return -1;
	}
	NodePtr pNode = *ppNode;
	NodePtr preNode = 0;
	while (pNode != 0)
	{
		if (strcmp(pNode->name, data) == 0)
		{
			//1.��Ҫɾ���ڵ��next��ֵ����ǰһ���ڵ��next
			if (preNode == 0)//�����ͷ��㣬�͸����б�ͷָ��
			{
				*ppNode = (*ppNode)->next;
			}
			else
			{
				preNode->next = pNode->next;
			}
			//2. �ͷ�Ҫɾ���ڵ�ռ�õ��ڴ�
			free(pNode);
			break;
		}
		preNode = pNode;
		pNode = pNode->next;
	}
	return 0;
}
void printNodeInfo(const NodePtr pNode)
{
	printf("%s\t%d\t%s",pNode->name,pNode->salary,(pNode->sex==0)?"MALE":"FEMALE");
}

NodePtr findData(NodePtr list, const char* name)
{
	if (list == 0)
		return NULL;
	NodePtr pNode = list;
	while (pNode)
	{
		if (strcmp(pNode->name,name)==0)
			return pNode;
		pNode = pNode->next;
	}
	return NULL;
}


int enterChoice(void)
{
	int menuChoice;

	printf("\nEnter your choice\n"
		"1 - add a new account\n"
		"2 - delete an account\n"
		"3 - print account info\n"
		"4 - print list contents\n"
		"5 - end program\n? ");
	scanf("%d", &menuChoice);
	return menuChoice;
}

int main()
{
	NodePtr header = 0;
	NodePtr temp = 0;
	Node* pCurNode = header;

	char name[256];
	int salary = 0;
	Sex sex = MALE;
	while (1)
	{
		int choice = enterChoice();
		switch (choice)
		{
		case 1:
		{
			fputs("input name:\n", stdout);
			memset(name, 0, 256);
			scanf("%s", name);
			printf("input salary:\n");
			scanf("%d", &salary);
			printf("input sex:(MALE:0 or FEMALE:1)\n");
			scanf("%d",&sex);
			appendData(&header,name,&salary,&sex);
		}
		break;
		case 2:
		{
			fputs("input the name(delete):\n", stdout);
			memset(name, 0, 256);
			scanf("%s", name);
			deleteData(&header, name);

		}
		break;
		case 3:
		{
			fputs("input find info:\n", stdout);
			memset(name, 0, 256);
			scanf("%s", name);
				
				if (temp=findData(header, name))
				{
					printNodeInfo(temp);
				}
				else
				{
					fputs("not found it!\n",stdout);
				}
		}
		break;
		case 4:
		{
			fputs("list contents:\n", stdout);
			processList(header);
		}
		break;
		default:
			return 0;
		}

	}

	return 0;
}