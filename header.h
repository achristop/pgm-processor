#define TITLE "PGM Process"
#define VERSION 1
#define MAX_WIDTH 800
#define MAX_HEIGHT 800

//START - Structs
typedef struct  portable_greymap_format
{
	char *name;
	char *code;
	char *creator;
	char * width;
	char * height;
	char * palette;
	unsigned char **image;	
}pgm_format;
//END - Structs

//START - Functions 
void pause();
void getParameterAndExecute();
void cleanScreen();
void printGameTitle();
void createPgm(int argc, char *argv[]);
void loadPgm(int argc, char *argv[]);
void setTitle();
void showMainMenu();
//END - Functions

//START - Global var
int died;
char cmd[100];
pgm_format *pgm;
//END - Global var