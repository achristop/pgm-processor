#include <stdio.h>
#include <stdlib.h>
#include "header.h"



void cleanScreen()
{
	//A function for eazy transfer from windows to unix and respectively from unix to windows.

	//UNIX
	system("clear");
	
	//WINDOWS
	//system("cls");
}

void printGameTitle()
{
	//Prints game's title
	printf("%s%s%d%s\n",TITLE," [ Version ",VERSION," ]");
}

void pause()
{
	printf("%s\n","Press enter to continue . . ." );
	while(getchar()!='\n');
}

void setTitle()
{
	//Windows title 
	//system("title PGM Process");
	
	//Unix title
	//system(""); UNKNOWN :(
}

void showMainMenu()
{
	while(1)
	{
			cleanScreen();
			printGameTitle();
			printf("\n%s\n","If you need instructions enter \"-h\".And \"-info\" for the creators." );
			printf("$>");
			gets(cmd);
			getParameterAndExecute();
			if(died==1)
			{
				printf("%s%s\n","Thank you for using ",TITLE );
				pause();
				break;
			}
	}
}