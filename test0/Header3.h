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

typedef bool(*CMP_FUNC)(const void*, const void*);
typedef enum _Sex
{
	MALE,
	FEMALE
}Sex;

typedef struct _PersonInfo
{
	char name[256];
	int  salary;
	Sex  sex;
} PersonInfo, *PersonInfoPtr;


typedef struct _Node
{
	void * data;
	struct _Node* next;
	struct _Node* prev;

} Node, *NodePtr;

NodePtr list_new_node(NodePtr *node)
{
	NodePtr ptr = (NodePtr)malloc(sizeof(Node));
	memset(ptr, 0, sizeof(Node));

	if (node != 0)
	{
		*node = ptr;
	}
	return ptr;//*node	
}

void list_free_node(NodePtr *node)
{
	free(*node);

	*node = 0;
}

bool list_empty(NodePtr list)
{
	return list == 0;
}

int list_insert_data(NodePtr *ppNode, void* data)
{
	NodePtr pCurNode = *ppNode;

	if (pCurNode == 0) //��Ϊ�յ����������ڵ�λ��Ϊ�գ�
	{
		list_new_node(ppNode);//*ppNode = new_node(0);

		pCurNode = *ppNode;
	}
	else
	{
		//1. ������Node
		Node* pNewNode = list_new_node(0);
		//2. ���²���λ�ýڵ��ԭ�¸��ڵ����½ڵ�Ĺ�ϵ
		pCurNode->next->prev = pNewNode;
		pNewNode->next = pCurNode->next;
		//3. ���²���λ�ýڵ����½ڵ�Ĺ�ϵ
		pCurNode->next = pNewNode;
		pNewNode->prev = pCurNode;

		pCurNode = pNewNode;//���µ�ǰ���
	}
	//�������ݣ����ڵ����ݸ�ֵ��
	pCurNode->data = data;

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
int list_append_data(NodePtr *ppNode, void* data)
{
	if (*ppNode == 0)
	{
		return list_insert_data(ppNode, data);
	}

	NodePtr pOrgTailNode = *ppNode;

	while (pOrgTailNode->next != 0)
	{
		pOrgTailNode = pOrgTailNode->next;
	}


	Node* pNewTailNode = list_new_node(0);
	pNewTailNode->data = data;

	pOrgTailNode->next = pNewTailNode;

	pNewTailNode->prev = pOrgTailNode;

	return 0;

}


//ppNode ��ͷ���
int list_delete_data(NodePtr *ppNode, void* data, CMP_FUNC pf)
{
	if (ppNode == 0 || *ppNode == 0)
	{
		return -1;
	}
	NodePtr pNode = *ppNode;
	NodePtr preNode = 0;
	while (pNode != 0)
	{
		bool equal = false;

		if (pf != 0)
		{
			equal = pf(pNode->data, data);
		}
		else
		{
			equal = (pNode->data == data);
		}
		if (equal)
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
			list_free_node(&pNode);
			break;
		}
		preNode = pNode;
		pNode = pNode->next;
	}

	return 0;
}
bool PersonInfoEqual(const void* left, const void* right)
{
	return strcmp(((const PersonInfoPtr)left)->name,
		((const PersonInfoPtr)right)->name) == 0;
}

NodePtr list_find_data(NodePtr list, const void* data)
{
	if (list == NULL)
		return NULL;
	NodePtr pNode = list;
	while (pNode)
	{
		int temp = PersonInfoEqual(pNode->data,data);
		if (temp )
		{
		     return pNode;
		}
	pNode = pNode->next;
	}

	return 0;
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


//typedef enum _Sex
//{
//	MALE,
//	FEMALE
//}Sex;
//
//typedef struct _PersonInfo
//{
//	char name[256];
//	int  salary;
//	Sex  sex;
//} PersonInfo, *PersonInfoPtr;


//bool PersonInfoEqual(const void* left, const void* right)
//{
//	return strcmp(((const PersonInfoPtr)left)->name,
//		((const PersonInfoPtr)right)->name) == 0;
//}

void printNodeInfo(const NodePtr pNode)
{
	PersonInfoPtr pInfo = (PersonInfoPtr)pNode->data;

	printf("name:%s\t salary:%d\t sex:%s\n", pInfo->name, pInfo->salary,
		pInfo->sex == MALE ? "man" : "woman");
}
void processDataList(NodePtr list)
{
	//�����������������
	Node* pNode = list;
	int row = 0;
	while (pNode != 0)
	{
		printNodeInfo(pNode);
		pNode = pNode->next;
		row++;
	}
	printf("account total:%d\n", row);
	fputs("\n", stdout);
}


int main()
{
	NodePtr header = 0;
	Node* pCurNode = header;

	while (1)
	{
		int choice = enterChoice();
		switch (choice)
		{
		case 1:
		{
			fputs("input format:\n"
				"[name] [salary] [0:male, 1:famale]\n", stdout);
			PersonInfoPtr pInfo = (PersonInfoPtr)malloc(sizeof(PersonInfo));
			scanf("%s%d%d", pInfo->name, &pInfo->salary, &pInfo->sex);
			list_append_data(&header, pInfo);
		}
		break;
		case 2:
		{
			PersonInfo pi;
			fputs("input the name(delete):\n", stdout);
			scanf("%s", pi.name);

			list_delete_data(&header, &pi, PersonInfoEqual);

		}
		break;
		case 3:
		{
			PersonInfo pi;
			fputs("input the name to find:\n", stdout);
			scanf("%s", pi.name);
			NodePtr pNode = list_find_data(header, &pi);
			if (pNode != NULL)
			{
				printNodeInfo(pNode);
			}
			else
			{
				printf("[%s] not find!\n", pi.name);
			}
		}
		break;
		case 4:
		{
			fputs("list contents:\n", stdout);
			processDataList(header);
		}
		break;
		default:
			return 0;
		}

	}

	return 0;
}