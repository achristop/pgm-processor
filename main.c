/* 
Subject:Project 3 -Portable Greymap Process (.pgm)
Name: Andreas Christopoulos    
Email: zrn6770@gmail.com
*/

#include <stdio.h>
#include "header.h"

int main(int argc,char *argv[])
{
	pgm = NULL;
	if(argc==6)
	{
		createPgm(argc-1,argv+1);
	}
	else if(argc==3)
	{
		loadPgm(argc-1,argv+1);
	}
	setTitle();
	cleanScreen();
	printGameTitle();
	showMainMenu();
	return 0;
}