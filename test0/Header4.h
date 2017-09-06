#pragma once
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
	struct _Node* prev;

} Node, *NodePtr;

NodePtr new_node(NodePtr *node)
{
	NodePtr ptr = (NodePtr)malloc(sizeof(Node));
	memset(ptr, 0, sizeof(Node));

	if (node != 0)
	{
		*node = ptr;
	}
	return ptr;//*node	
}

void free_node(NodePtr *node)
{
	free(*node);

	*node = 0;
}


void processList(NodePtr list)
{
	//�����������������
	Node* pNode = list;
	int row = 1;
	while (pNode != 0)
	{
		printf("%d:%s\t%d\t%s\n", row,pNode->name,pNode->salary,(pNode->sex==0)?"MALE":"FAMALE");
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
		new_node(ppNode);//*ppNode = new_node(0);

		pCurNode = *ppNode;
	}
	else
	{
		//1. ������Node
		Node* pNewNode = new_node(0);
		//2. ���²���λ�ýڵ��ԭ�¸��ڵ����½ڵ�Ĺ�ϵ
		pCurNode->next->prev = pNewNode;
		pNewNode->next = pCurNode->next;
		//3. ���²���λ�ýڵ����½ڵ�Ĺ�ϵ
		pCurNode->next = pNewNode;
		pNewNode->prev = pCurNode;

		pCurNode = pNewNode;//���µ�ǰ���
	}
	//�������ݣ����ڵ����ݸ�ֵ��
	strcpy(pCurNode->name, data1);
	pCurNode->salary = *data2;
	pCurNode->sex = *data3;
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
int appendData(NodePtr *ppNode, const char* data1, const int *data2, const Sex *data3)
{
	if (*ppNode == 0)
	{
		return insertData(ppNode, data1,data2,data3);
	}

	NodePtr pOrgTailNode = *ppNode;

	while (pOrgTailNode->next != 0)
	{
		pOrgTailNode = pOrgTailNode->next;
	}


	Node* pNewTailNode = new_node(0);

	pOrgTailNode->next = pNewTailNode;

	pNewTailNode->prev = pOrgTailNode;

	strcpy(pNewTailNode->name, data1);
	pNewTailNode->salary = *data2;
	pNewTailNode->sex = *data3;
	return 0;

}

// Node ��ͷ���
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
			if (pNode->next != 0)
			{
				pNode->next->prev = pNode->prev;
			}

			if (pNode->prev != 0)
			{
				pNode->prev->next = pNode->next;
			}

			if (preNode == 0)//�����ͷ��㣬�͸����б�ͷָ��,��Ϊ����ppNode�Ǳ�ͷ
			{
				*ppNode = (*ppNode)->next;
			}

			//2. �ͷ�Ҫɾ���ڵ�ռ�õ��ڴ�
			free_node(&pNode);
			break;
		}
		preNode = pNode;
		pNode = pNode->next;
	}
}


NodePtr findData(NodePtr list, const char* name)
{
	return 0;
}

void printNodeInfo(const NodePtr pNode)
{

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
			scanf("%d", &sex);
			appendData(&header, name, &salary, &sex);
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
			fputs("input the name to find:\n", stdout);
			memset(name, 0, 256);
			scanf("%s", name);
			NodePtr pNode = findData(header, name);
			if (pNode != 0)
			{
				printNodeInfo(pNode);
			}
			else
			{
				printf(" not find!\n");
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


