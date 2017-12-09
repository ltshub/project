
//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define ACCOUNT "ACCOUNT"
#define LOG "LOG"
#define DEPOSIT 1
#define DRAW 2
#define ASK 3

void WriteHistory(unsigned int menu, unsigned int amount, unsigned int money)
{
	FILE* log = fopen(LOG, "a");
	char action[10] = { 0, };
	char buf[100] = { 0, };
	time_t current;
	time(&current);

	fwrite("--------------------------------\n", 1, 33, log);
	switch (menu)
	{
	case DEPOSIT:
		sprintf(buf, "MONEY :: %d (DEPOSIT :: %d) \n TIME :: %s\n\n", money, amount, ctime(&current));
		break;
	case DRAW:
		sprintf(buf, "MONEY :: %d (DRAW :: %d) \n TIME :: %s\n\n", money, amount, ctime(&current));
		break;
	case ASK:
		sprintf(buf, "ACCOUNT ASK \n TIME :: %s\n", ctime(&current));
		break;
	}
	fwrite(buf, 1, strlen(buf), log);
	fclose(log); 
}

void clear()
{
	system("cls");
}

void printmenu()
{
	clear();
	printf("+--------------------------------+\n");
	printf("|    SEJONG RACE CONDITION ATM   |\n");
	printf("+--------------------------------+\n");
	printf("|      HERE IS YOUR MENU         |\n");
	printf("+--------------------------------+\n");
	printf("|1. Deposit                      |\n");
	printf("|2. Draw                         |\n");
	printf("|3. Ask my account               |\n");
	printf("+--------------------------------+\n");
	printf(">>> ");

}

FILE* openaccount(char* mode)
{
	FILE* ret;
	while (1)
	{
		ret = fopen(ACCOUNT, mode);
		if (ret>0) return ret;
		else {
			ret = fopen(ACCOUNT, "w");

			fputs("0", ret);

			fclose(ret);
		}
	}
}

void deposit()
{
	//OPEN MY ACCOUNT
	FILE* Raccount = openaccount("r");
	unsigned int money;
	char buf[10] = { 0, };
	unsigned int input;
	fscanf(Raccount, "%d", &money);
	fclose(Raccount);   

	clear();
	printf("How much depoist in your account?\n>> ");
	scanf("%d", &input);

	money += input;

	sprintf(buf, "%d", money);

	FILE* account = openaccount("w+t");
	fwrite(buf, 1, sizeof(buf), account);
	fclose(account);

	//logging
	WriteHistory(DEPOSIT, input, money);
}

void draw()
{
	//OPEN MY ACCOUNT
	FILE* Raccount = openaccount("r");
	unsigned int money;
	char buf[10] = { 0, };
	unsigned int output;
	fscanf(Raccount, "%d", &money);
	fclose(Raccount);   

						
	while (1)
	{
		clear();
		printf("Your account has %d won!\n", money);
		printf("How much draw in your account?\n>> ");
		scanf("%d", &output);
		if (money < output)
			continue;
		else
		{
			money -= output;
			break;
		}
	}

	sprintf(buf, "%d", money);   //for fwrite!

								 //OPEN MY ACCOUNT to write my money
	FILE* account = openaccount("w");
	fwrite(buf, 1, strlen(buf), account);
	fclose(account);

	//logging
	WriteHistory(DRAW, output, money);
}


void ask()
{
	WriteHistory(ASK, 0, 0);
	clear();
	system("type LOG");
	printf("For security reason, we will show this log 5 second.\n");
	Sleep(5000);
}

int main()
{
	int sel;
	while (1)
	{
			printmenu();
			scanf("%d", &sel);
			switch (sel)
			{
			case DEPOSIT:
				deposit();
				break;
			case DRAW:
				draw();
				break;
			case ASK:
				ask();
				break;
			}
		}
	}
	
	
