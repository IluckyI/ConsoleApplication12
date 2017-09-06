#pragma once
#include<cstdlib>
#include<cstdio>
#include<cstring>

typedef struct _ClientData
{
	int i;
	int j;
}ClientData,*ClientDataptr;
typedef struct _Data
{
	ClientDataptr p;
	int count;
}Data,*Dataptr;
int main()
{
	ClientDataptr client = (ClientDataptr)calloc(1, sizeof(ClientData) * 2);
	Data *data;
	data->p = client;
	client[0].i = 1;
	client[1].i = 2;


	return 0;
}