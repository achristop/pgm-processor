#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"
#include "coreConnector.h"


void help()
{
	int sel;
	while(1)
	{
		cleanScreen();
		printGameTitle();
		printf("\n");
		printf("%s\n","---------------------------------" );
		printf("%s%s\n","Instructions for the ",TITLE );
		printf("%s\n","---------------------------------" );
		printf("\n%s\n","Description:" );
		printf("%s\n","----------------------------------------------------------------------------------" );
		printf("%s\n","This is a simple image processor for the images .pgm and specially for P5 format. " );
		printf("\n%s\n","Commands:" );
		printf("%s\n","----------------------------------------------------------------------------------" );
		printf("%s\n%s\n","1.Create pgm    2.Load pgm     3.Save pgm             4.Create Zigzag line","5.Create Square 6.Create Cycle 7.Create Rectangle     8.Exit help");
		printf("%s\n","----------------------------------------------------------------------------------" );
		printf("%s","Enter the number of the command you want to learn about(Enter 8 to exit):" );
	
		scanf("%d",&sel);
		getchar();
		printf("\n\n");
		switch(sel)
		{
			case 1:
					printf("%s\n","In order to create a new .pgm you have to enter \"-n [name] [columns] [rows] [shades] \" .\nExample:\"-n example 200 300 16 \"" );			
				    pause();
			break;	

			case 2:
					printf("%s\n","In order to load a .pgm you have to enter \"-l [name] \" .\nExample:\"-l test \"" );			
				    pause();
			break;

			case 3:
					printf("%s\n","In order to save a .pgm you have to enter \"-s [name] \" .\nExample:\"-s test \"" );			
				    pause();
			break;

			case 4:
					printf("%s\n","In order to draw a Zigzag line you have to enter \"-zl [NumOfPoints] [x1] [y1] ... [xn] [yn] \" .\nExample:\"-zl 5 10 20 90 120 50 200 150 140 30 30 \"" );			
			    	pause();
			break;

			case 5:
					printf("%s\n","In order to draw a square you have to enter \"-sq [xi] [yi] [side] \" .\nExample:\"-sq 100 100 200 \"" );			
			    	pause();
			break;

			case 6:
					printf("%s\n","In order to draw a cycle you have to enter \"-c [xi] [yi] [radius] \" .\nExample:\"-c 100 100 70 \"" );			
			    	pause();
			break;

			case 7:
					printf("%s\n","In order to draw a rectangle you have to enter \"-r [xi] [yi] [b side] [s side] \" .\nExample:\"-p 100 100 70 120 \"" );			
			    	pause();
			break;

			case 8:
					return;
			break;

			default:
					printf("%s\n","There is no info about this command or wrong input!Try again!");			
			    	pause();
			break;
		}
	}
}



void showCreators()
{
	cleanScreen();
	printGameTitle();
	printf("%s%d\n\n","Version:",VERSION);
	printf("%s\n\n","Name: Adreas Christopoulos	Email: zrn6770@gmail.com" );
	pause();
}

void getParameterAndExecute()
{
	if(strcmp(cmd,"-h")==0)
		help();
	else if(strncmp(cmd,"-n",2)==0)
		createPgm(0,NULL);
	else if(strncmp(cmd,"-l",2)==0)
		loadPgm(0,NULL);
	else if(strncmp(cmd,"-sq",3)==0)
		createSquare();
	else if(strncmp(cmd,"-s",2)==0)
		savePgm();
	else if(strncmp(cmd,"-zl",3)==0)
		createZigZagLine();
	else if(strncmp(cmd,"-c",2)==0)
		createCycle();
	else if(strncmp(cmd,"-r",2)==0)
		createRectangle();
	else if(strncmp(cmd,"-info",5)==0)
		showCreators();
	else if(strcmp(cmd,"-e")==0)
	{
		allocateMemoryForTheImageOrReleaseIt(3);
		died = 1;
	}
	else
	{
		printf("%s%s\n",cmd,": command not found." );
		pause();
	}
}