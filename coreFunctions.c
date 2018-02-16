#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"
#include "coreConnector.h"
#include <math.h>

const char SET[]=" ";

void cleanCommandFromTheString(int x)
{
	int i;

	for(i=0;i<x;i++)
		cmd[i]=' ';
}


int checkIfTheInputIsCorrect(int x)
{
	char *token,*tmp;
	int i,n;

	token=strdup(cmd);
	tmp=token;
	tmp=strtok(tmp,SET);
	if(x==6)
		n = atoi(tmp);
	i=0;
	while(tmp)
	{
		i++;
		tmp=strtok(NULL,SET);
	}
	free(token);
	if( x==0 && i!=4)  // -n
		return 1;
	else if(x==1 && i!=1 ) // -l
		return 1;
	else if(x==2 && i!=1 ) // -s
		return 1;
	else if(x==3 && i!=3 ) // -c
		return 1;
	else if(x==4 && i!=3 ) // -sq
		return 1;
	else if( x==5 && i!=4 ) // -r
		return 1;
	else if(x==6 && i!=2*n+1 ) // -zl
		return 1;
	else
		return 0;
}

void checkExistance(int x)
{
	char answer;
	if(pgm!=NULL)
	{
		printf("%s","An image is already loaded do you want to relese it(y/Y,n/N)?:" );
		while(1)
		{
			answer = getchar();
			getchar();
			if(answer=='Y' || answer=='y')
			{

				allocateMemoryForTheImageOrReleaseIt(3);
				printf("%s\n","Image is deleted!Now you can create a new one!" );
				pause();
				break;
			}
			else if(answer=='N' || answer=='n')
			{
				printf("%s\n","Image is not deleted!" );
				pause();
				return;
			}
		}
	}
}

void allocateMemoryForTheImageOrReleaseIt(int mode)
{
	int i;

	if(mode==1)
	{
		if((pgm = (pgm_format *) malloc(sizeof(pgm_format)))==NULL)
		{
			printf("%s\n","ERROR:Not available memory!" );
			exit(1);
		}
	}
	else if(mode==2)
	{
		if((pgm->image = (unsigned char **) malloc(w*sizeof(unsigned char*)))==NULL)
		{
			printf("%s\n","ERROR:Not available memory!" );
			exit(1);
		}
		for(i=0;i<w;i++)
		{
			if((pgm->image[i] = (unsigned char *) malloc(h*sizeof(unsigned char)))==NULL)
			{
				printf("%s\n","ERROR:Not available memory!" );
				exit(1);
			}
		}
	}
	else if(mode==3)
	{
		if(pgm==NULL)
			return;
		free(pgm->name);
		free(pgm->code);
		free(pgm->creator);
		free(pgm->width);
		free(pgm->height);
		free(pgm->palette);
		for(i=0;i<w;i++)
			free(pgm->image[i]);
		free(pgm->image);
	}
}

void fillThePgmStructAuto(int argc, char *argv[])
{
	FILE *fp;
	char *token,*tmp;
	int i,j,k;
	int size;

	if(checkIfTheInputIsCorrect(1) && argc==0)
	{
		printf("%s\n","Your input is incorrect!Please advice command \"-h\" .");
		return;
	}
	allocateMemoryForTheImageOrReleaseIt(1);
	if(argc==0)
	{
		token=cmd;
		pgm->name = strdup(strcat(strtok(token,SET),".pgm"));
	}
	else
	{
		pgm->name = strdup(strcat(argv[1],".pgm"));
	}

	if((fp=fopen(pgm->name,"rb"))==NULL)
	{
		printf("%s\n","The file is not found!" );
		free(pgm);
		pgm=NULL;
		return;
	}
	fseek(fp,0,SEEK_END);
	size = ftell(fp);
	rewind(fp);
	tmp = malloc(size+1);
    fread(tmp,size,1,fp);
    for(i=0;i<size;i++)
    {
    	if(tmp[i]=='\n')
    		tmp[i]=' ';
    	else if(tmp[i]=='#' && tmp[i+1]==' ')
    		tmp[i+1]='\b';
    	else if(tmp[i]==':' && tmp[i+1]==' ')
    		tmp[i+1]='\b';

    }
    token = strtok(tmp,SET);
    pgm->code = strdup(token);
    i=0;
    while(token)
    {
    	if(i==1)
    		pgm->creator = strdup(token);
    	else if(i==2)
    		pgm->width = strdup(token);
    	else if(i==3)
    		pgm->height = strdup(token);
    	else if(i==4)
    		pgm->palette = strdup(token);
    	else if(i==5)
    	{
    		w = atoi(pgm->width);
			h = atoi(pgm->height);
			p = atoi(pgm->palette);
			allocateMemoryForTheImageOrReleaseIt(2);
			k=0;
    		for(i=0;i<w;i++)
    		{
    			for(j=0;j<h;j++)
    			{
    				pgm->image[i][j]=token[k];
    				k++;
    			}
    		}
    	}
    	token = strtok(NULL,SET);
  		i++;
    }
    fclose(fp);
	printf("%s\n","Image is loaded!" );
}

void fillThePgmStructManually(int argc, char *argv[])
{
	char *token;
	int i,j,color;

	if(checkIfTheInputIsCorrect(0) && argc==0)
	{
		printf("%s\n","Your input is incorrect!Please advice command \"-h\" .");
		return;
	}
	allocateMemoryForTheImageOrReleaseIt(1);
	pgm->code = strdup("P5");
	pgm->creator = strdup("#CREATOR:Christopoulos");
	if(argc==0)
	{
		token=cmd;
		pgm->name = strdup(strtok(token,SET));
		i=0;
		while(token!=NULL)
		{
			if(i==1)	
				pgm->width = strdup(token);
			else if(i==2)
				pgm->height = strdup(token);
			else if(i==3)
				pgm->palette = strdup(token);
			i++;
			token = strtok(NULL,SET);
		}
	}
	else
	{
		pgm->name = strdup(argv[1]);
		pgm->width =strdup(argv[2]);
		pgm->height = strdup(argv[3]);
		pgm->palette = strdup(argv[4]);
	}
	w = atoi(pgm->width);
	h = atoi(pgm->height);
	p = atoi(pgm->palette);
	if((w >MAX_WIDTH || w <= 0) || (h>MAX_HEIGHT || h <= 0 ) || (p>255 || p<0))
	{
		printf("%s\n","Your input is wrong.Width must be between 1-800 ,height must be between 1-800 and palette must be between 1-255!Pleaze try again!" );
		free(pgm);
		pgm=NULL;
		pause();
		return;
	}	
	allocateMemoryForTheImageOrReleaseIt(2);
	printf("%s%d%s%d%s","Enter a number from the palette in order to be your background(Val=0 -> black,Val=",p," ->white and any number between (0-",p,") are shades of grey):");
	scanf("%d",&color);
	getchar();
	for (i = 0; i < w; i++)
	{
		for (j = 0; j < h; j++)
		{
			pgm->image[i][j] = color;
		}
	}
	printf("%s\n","Image background is set!" );
}

void createPgm(int argc, char *argv[])
{	
	checkExistance(1);
	cleanCommandFromTheString(2);
	if(argc!=5)
		fillThePgmStructManually(0,NULL);
	else
		fillThePgmStructManually(argc,argv);
	pause();
}
void loadPgm(int argc, char *argv[])
{
	checkExistance(0);
	cleanCommandFromTheString(2);
	if(argc!=2)
		fillThePgmStructAuto(0,NULL);
	else
		fillThePgmStructAuto(argc,argv);
	pause();
}
void savePgm()
{
	FILE *fp;
	char *name,*token;
	char ch[2];
	char answer,ans;
	int i,j;

	if(pgm==NULL)
	{
		printf("%s\n","There is no image!" );
		pause();
		return;
	}
	cleanCommandFromTheString(2);
	if(checkIfTheInputIsCorrect(2))
	{
		printf("%s\n","Your input is incorrect!Please advice command \"-h\" .");
		pause();
		return;
	}
	token = strtok(cmd,SET);
	name = strcat(token,".pgm");
	printf("%s%s%s","Do you want to save ",name,"(y/Y,n/N)?:" );	
	
	while(1)
	{
		answer = getchar();
		if(answer=='y' || answer=='Y')
		{
			if((fp = fopen(name,"wb"))==NULL)
			{
				printf("%s\n","ERROR:File didnt open!" );
				exit(1);
			}
			strcpy(ch,"\n");
			fwrite(pgm->code,sizeof(char),strlen(pgm->code),fp );
			fwrite(ch,sizeof(char),strlen(ch),fp);
			fwrite(pgm->creator,sizeof(char),strlen(pgm->creator),fp );
			fwrite(ch,sizeof(char),strlen(ch),fp);
			fwrite(pgm->width,sizeof(char),strlen(pgm->width),fp );
			strcpy(ch," ");
			fwrite(ch,sizeof(char),strlen(ch),fp);
			fwrite(pgm->height,sizeof(char),strlen(pgm->height),fp );
			strcpy(ch,"\n");
			fwrite(ch,sizeof(char),strlen(ch),fp);
			fwrite(pgm->palette,sizeof(char),strlen(pgm->palette),fp );
			fwrite(ch,sizeof(char),strlen(ch),fp);
			for(i=0;i<w;i++)
			{
				for(j=0;j<h;j++)
				{
					fwrite(&pgm->image[i][j],sizeof(unsigned char),1,fp);
				}
			}
			fclose(fp);
			printf("%s\n","Image is saved!" );
			printf("%s","Do you want to release the memory now?:(y/Y,n/N):" );
			while(1)
			{
				getchar();
				ans = getchar();
				if(ans=='Y' || ans=='y')
				{
					allocateMemoryForTheImageOrReleaseIt(3);
					printf("%s\n","Memory released!" );
					pgm=NULL;
					break;
				}
				else if(ans=='n' || ans=='N')
				{
					printf("%s\n","Memory is not released!" );
					break;
				}
			}
			break;
		}
		else if(answer=='n' || answer=='N')
		{
			printf("%s\n","Image is not saved!" );
			break;
		}
	}
	getchar();
	pause();
}

void uniteThePoints(int x0, int y0, int x1, int y1) 
{ 
	//Bresenham's line algorithm
  	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  	int err = (dx>dy ? dx : -dy)/2, e2;
 
	for(;;)
  	{
  		pgm->image[x0][y0]=0;
    	if (x0==x1 && y0==y1) break;
    	e2 = err;
    	if (e2 >-dx) { err -= dy; x0 += sx; }
    	if (e2 < dy) { err += dx; y0 += sy; }
  	}
}

void createZigZagLine()
{
	char *token;
	int numOfPoints,i,j,x0,y0,x1,y1;
	int *coords;

	if(pgm==NULL)
	{
		printf("%s\n","There is no image!" );
		pause();
		return;
	}
	cleanCommandFromTheString(3);
	if(checkIfTheInputIsCorrect(6))
	{
		printf("%s\n","Your input is incorrect!Please advice command \"-h\" .");
		pause();
		return;
	}
	token = cmd;
	numOfPoints = atoi(strtok(token,SET));
	if((coords = (int *) malloc(2*numOfPoints*sizeof(int))) == NULL)
	{
		printf("Error:Not available memory!\n");
		exit(1);
	}
	i=0;
	j=0;
	while(token)
	{
		if(j!=0)
		{
			coords[i]=atoi(token);
			if((coords[i]%2==0 && (coords[i]<0 ||coords[i]>w)) || ( coords[i]%2==1 && (coords[i]<0 ||coords[i]>h)))
			{
				printf("%s\n","Error:Your input is incorrect!Please advice command \"-h\" ." );
			}
			i++;
		}
		token = strtok(NULL,SET);
		j=1;
	}
	for(i=0;i<numOfPoints;i+=2)
		uniteThePoints(coords[i],coords[i+1],coords[i+2],coords[i+3]);
	free(coords);
	pause();
}

void createSquare()
{
	char *token;
	int i,j,s,x,y,x1,y1,x2,y2,x3,y3,x4,y4;
	if(pgm==NULL)
	{
		printf("%s\n","There is no image!" );
		pause();
		return;
	}
	cleanCommandFromTheString(3);
	if(checkIfTheInputIsCorrect(4))
	{
		printf("%s\n","Your input is incorrect!Please advice command \"-h\" .");
		pause();
		return;
	}
	token = cmd;
	x = atoi(strtok(token,SET));
	i=0;
	while(token)
	{
		if(i==1)
			y = atoi(token);
		else if(i==2)
			s = atoi(token);
		i++;
		token = strtok(NULL,SET);
	}
	if( (x<0 || x>w) || (y<0 || y>h) || (s<0 || s> w || s > h ) )
	{
		printf("%s\n","Your input is incorrect![  x>=0 x<width , y>=0 y>height , s>=0 s<width s<height  ]" );
		pause();
		return;
	}
	x1 = x - s/2;
	y1 = y - s/2;
	x2 = x - s/2;
	y2 = y + s/2;
	x3 = x + s/2;
	y3 = y - s/2;
	x4 = x + s/2;
	y4 = y + s/2;
	for(i=x1;i<x1+s;i++)
		for(j=y1;j<y1+s;j++)
			pgm->image[i][j] =(int) p/2;
	for(i=x1;i<x1+s;i++)
		pgm->image[i][y1]=0;
	for(j=y1;j<y1+s;j++)
		pgm->image[x1][j]=0;
	for(i=x2;i<x2+s;i++)
		pgm->image[i][y2]=0;
	for(j=y3;j<y3+s;j++)
		pgm->image[x3][j]=0;
	uniteThePoints(x1,y1,x4,y4);
	uniteThePoints(x2,y2,x3,y3);
	pause();
}

void createCycle()
{
	char *token;
	int i,j,x,y,r;
	if(pgm==NULL)
	{
		printf("%s\n","There is no image!" );
		pause();
		return;
	}
	cleanCommandFromTheString(2);
	if(checkIfTheInputIsCorrect(3))
	{
		printf("%s\n","Your input is incorrect!Please advice command \"-h\" .");
		pause();
		return;
	}
	token = cmd;
	x = atoi(strtok(token,SET));
	i=0;
	while(token)
	{
		if(i==1)
			y = atoi(token);
		else if(i==2)
			r = atoi(token);
		i++;
		token = strtok(NULL,SET);
	}
	if( (x<0 || x>w) || (y<0 || y>h) || (r<0) )
	{
		printf("%s\n","Your input is incorrect![  x>=0 x<width , y>=0 y>height , r>=0  ]" );
		pause();
		return;
	}
	
	for(i=0;i<w;i++)
	{
		for(j=0;j<h;j++)
		{
			 if( ((i-x)*(i-x) + (j-y)*(j-y) == r * r) || ((i-x)*(i-x) + (j-y)*(j-y) < r * r))
				pgm->image[i][j] = 0;
		}
	}
	r-=1;
	for(i=0;i<w;i++)
	{
		for(j=0;j<h;j++)
		{
		    if ( (i-x)*(i-x) + (j-y)*(j-y) < r * r  )
				pgm->image[i][j] = (int) p/2;
		}
	}
	pgm->image[x][y]=0;
	pause();
}

void createRectangle()
{
	char *token;
	int i,j,sH,sW,x,y,x1,y1,x2,y2,x3,y3,x4,y4,mode;
	float aspectRatio;
	if(pgm==NULL)
	{
		printf("%s\n","There is no image!" );
		pause();
		return;
	}
	cleanCommandFromTheString(2);
	if(checkIfTheInputIsCorrect(5))
	{
		printf("%s\n","Your input is incorrect!Please advice command \"-h\" .");
		pause();
		return;
	}
	token = cmd;
	x = atoi(strtok(token,SET));
	i=0;
	while(token)
	{
		if(i==1)
			y = atoi(token);
		else if(i==2)
			sH = atoi(token);
		else if(i==3)
			sW = atoi(token);

		i++;
		token = strtok(NULL,SET);
	}
	if( (x<0 || x>w) || (y<0 || y>h) || (sH<0 || sH> w || sH > h ) || (sW<0 || sW> w || sW > h ) )
	{
		printf("%s\n","Your input is incorrect![  x>=0 x<width , y>=0 y>height , s1>=0 s<width s1<height  , s2>=0 s<width s2<height ]" );
		pause();
		return;
	}
	x1 = x - sH/2;
	y1 = y - sW/2;
	x2 = x - sH/2;
	y2 = y + sW/2;
	x3 = x + sH/2;
	y3 = y1;
	x4 = x + sH/2;
	y4 = y2;
	for(i=x1;i<x1+sH;i++)
		for(j=y1;j<y1+sW;j++)
			pgm->image[i][j] =(int) p/2;
	for(i=x1;i<x1+sH;i++)
		pgm->image[i][y1]=0;
	for(j=y1;j<y1+sW;j++)
		pgm->image[x1][j]=0;
	for(i=x2;i<x2+sH;i++)
		pgm->image[i][y2]=0;
	for(j=y3;j<y3+sW;j++)
		pgm->image[x3][j]=0;
	uniteThePoints(x1,y1,x4,y4);
	uniteThePoints(x2,y2,x3,y3);
	pause();
}