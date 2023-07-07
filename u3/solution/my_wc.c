#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

int main (int argc, char *argv[]){
    
    int ai = 1;
    int filecount = 1;
    int bytes = 0;
	int words = 0;
	int lines = 1;
	int doubl = 1;
	int cchar;
		
	
	do
    {
        pid_t pid = fork();
        if (pid<0) {fprintf(stdout,"Fehler fork"); return -1;}
        
        //Parent
        else if (pid>0) 
        {
            wait(NULL);
            ai++;
            filecount++;
        } 
    
        //child
        else if (pid==0) 
        {
            FILE *datei;
            if(argc>1) {datei = fopen(argv[ai], "r");}
            else {puts("Zum beenden strg+d");datei = stdin;}
            if (datei==NULL){fprintf(stdout,"Fehler beim öffnen der Zieldatei");return -1;}
            
        	while ( (cchar = fgetc(datei))!= EOF )  
        	{
                if ( (cchar == ' ' || cchar == '\t' || cchar == '\n') ) 
                {
                    doubl=1;
                    if (cchar == '\n') {lines++;}
                }
                else if (doubl==1){words++;doubl=0;}
                bytes += sizeof(char);
            }
    if (argc<=1){puts("");}
    printf("%d.Datei : bytes = %d, words = %d, lines = %d \n",filecount,bytes, words, lines);
    return 1;
        }
    }    while (argc>ai);	    
}