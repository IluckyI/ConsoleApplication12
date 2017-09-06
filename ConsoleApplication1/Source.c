#include <stdio.h>
#define CRT_SECURE_NO_WARNINGS
#define MAX_NUM_ 100;
// credit.dat
 struct clientData {
	int acctNum;
	char lastName[15];
	char firstName[10];
	double balance;
};

//static struct clientData s_client[MAX_NUM_] = { 0 };
int enterChoice(void);
void textFile(FILE *);
void updateRecord(FILE *);
int newRecord(FILE *);
void deleteRecord(FILE *);
void display(FILE*);
int recordIndex(int account_s);
int main()
{
   
    FILE *cfPtr;
	int choice;

	if ( ( cfPtr = fopen( "credit.dat", "r+" ) ) == NULL )
	printf( "File could not be opened.\n" );
	else {

	while ( ( choice = enterChoice() ) != 6 ) {

	switch ( choice ) {
	case 1:
	textFile( cfPtr );
	break;
	case 2:
	updateRecord( cfPtr );
	break;
	case 3:
	newRecord( cfPtr );
	break;
	case 4:
	deleteRecord( cfPtr );
	break;
	case 5:
	display(cfPtr);
	break;
	}
	}

	fclose( cfPtr );
	}
	
	return 0;
}

void textFile(FILE *readPtr)
{
	FILE *writePtr;
	struct clientData client = { 0, "", "", 0.0 };

	if ((writePtr = fopen("accounts.txt", "w+")) == NULL)
		printf("File could not be opened.\n");
	else {
		rewind(readPtr);
		fprintf(writePtr, "%-6s%-16s%-11s%10s\n",
			"Acct", "Last Name", "First Name", "Balance");

		while (!feof(readPtr)) {
			int ret = fread(&client, sizeof(struct clientData), 1,readPtr);
			if (ret != 1)
				break;


			if (client.acctNum != 0)
				fprintf(writePtr, "%-6d%-16s%-11s%10.2f\n",
					client.acctNum, client.lastName,
					client.firstName, client.balance);
		}

		fclose(writePtr);
	}

}

void updateRecord(FILE *fPtr)
{
	int account;
	double transaction;
	struct clientData client = { 0, "", "", 0.0 };
	struct clientData num = { 0, "", "", 0.0 };
	printf("Enter account to update ( 1 - 100 ): ");
	scanf("%d", &account);
	int i;
	for ( i = 0; i < 100; i++)
	{
		fseek(fPtr, i * sizeof(struct clientData), SEEK_SET);
		fread(&num, sizeof(struct clientData), 1, fPtr);
		if (num.acctNum == account)
		{
			fseek(fPtr, -sizeof(struct clientData), SEEK_CUR);
			printf("%-6d%-16s%-11s%10.2f\n\n",
				num.acctNum, num.lastName,
				num.firstName, num.balance);
			printf("Enter charge ( + ) or payment ( - ): ");
			scanf("%lf", &transaction);
			num.balance += transaction;
			printf("%-6d%-16s%-11s%10.2f\n",
				num.acctNum, num.lastName,
				num.firstName, num.balance);
			fseek(fPtr, i * sizeof(struct clientData), SEEK_SET);
			fwrite(&num, sizeof(struct clientData), 1,fPtr);
			break;
		}
	}
	if(i==100)
	    printf("Account %d is not exist!\n");


//	fseek(fPtr,(account - 1) * sizeof(struct clientData),SEEK_SET);
//	fread(&client, sizeof(struct clientData), 1, fPtr);

	/*if (client.acctNum == 0)
		printf("Acount #%d has no information.\n", account);
	else {
		printf("%-6d%-16s%-11s%10.2f\n\n",
			client.acctNum, client.lastName,
			client.firstName, client.balance);
		printf("Enter charge ( + ) or payment ( - ): ");
		scanf("%lf", &transaction);
		client.balance += transaction;
		printf("%-6d%-16s%-11s%10.2f\n",
			client.acctNum, client.lastName,
			client.firstName, client.balance);
		fseek(fPtr,(account - 1) * sizeof(struct clientData),SEEK_SET);
		fwrite(&client, sizeof(struct clientData), 1,
			fPtr);
	}*/
}

void deleteRecord(FILE *fPtr)
{
	
	struct clientData client,
		blankClient = { 0, "", "", 0 };
	int accountNum = 0;

	struct clientData num = { 0, "", "", 0.0 };

	printf("Enter account number to " "delete ( 1 - 100 ): ");
	scanf("%d", &accountNum);

	for (int i = 0; i <= 100; i++)
	{
		fseek(fPtr, i * sizeof(struct clientData), SEEK_SET);
		fread(&num, sizeof(struct clientData), 1, fPtr);

		/*if (num.acctNum == 0)
		{
		break;
		}*/

		if (num.acctNum == accountNum)
		{
			fseek(fPtr, -sizeof(struct clientData), SEEK_CUR);
			fwrite(&blankClient, sizeof(struct clientData), 1, fPtr);
			printf("Account %d Delete the success!\n", accountNum);
			break;
		}
	}

	if (num.acctNum != accountNum)
	{
		printf("Account %d is not exist!\n", accountNum);
	}
}

int newRecord(FILE *fPtr)
{

	struct clientData client = { 0, "", "", 0.0 };
	int accountNum = 0;
	printf("Enter new account number ( 1 - 100 ): ");
	scanf("%d", &accountNum);

	for (int i = 0; i <= 100; i++)
	{
		/*if (i == 0)
		{
		fseek(fPtr, 0, SEEK_SET);
		}
		else
		{
		fseek(fPtr, sizeof(struct clientData), SEEK_CUR);
		}*/
		fseek(fPtr, i * sizeof(struct clientData), SEEK_SET);
		fread(&client, sizeof(struct clientData), 1, fPtr);
		if (client.acctNum == accountNum)
		{
			printf("Account #%d already contains information.\n", client.acctNum);
			return 0;
		}
	}
	if (client.acctNum != accountNum)
	{
		fseek(fPtr, 0, SEEK_END);
		printf("Enter lastname, firstname, balance\n? ");
		scanf("%s%s%lf", &client.lastName, &client.firstName,
			&client.balance);
		client.acctNum = accountNum;   //( client.acctNum - 1 ) * sizeof(struct clientData)

		fwrite(&client, sizeof(struct clientData), 1, fPtr);
	}
	return 0;
	
}

int enterChoice(void)
{
	int menuChoice;

	printf("\nEnter your choice\n"
		"1 - store a formatted text file of acounts called\n"
		"    \"accounts.txt\" for printing\n"
		"2 - update an account\n"
		"3 - add a new account\n"
		"4 - delete an account\n"
		"5 - display information\n"
		"6 - end program\n? ");
	scanf("%d", &menuChoice);
	return menuChoice;
}

void display(FILE *file)
{
	file = fopen("accounts.txt", "r+");
	char w[256] = {0};
	printf("Information line:\n");
	while (fgets(w,256,file)!=0 )
	{
				fputs(w,stdout);
		
	}
	fclose(file);
	
}
//int main()
//{
//	return 0;
//}
//int recordIndex(int account_s)
//{
//	for (int i = 0; i < MAX_NUM; i++)
//	{
//		if (s_client[i] == account_s)
//			return i;
//	}
//	return -1;
//}