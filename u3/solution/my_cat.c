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
    char buf[1000000];
    
    if (argc<2) 
    {
        puts("Zum beenden strg+d");
        while (fread(buf, sizeof(char), sizeof(buf), stdin)!=0){}
        if (ferror(stdin) !=0) {fprintf(stdout,"Fehler beim lesen von stdin"); return -1;}
        puts("");
        printf("%s \n",buf);
        return 1;
    }

    while (argc>ai)
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
            FILE *datei = fopen(argv[ai], "r");
            if (datei==NULL){fprintf(stdout,"Fehler beim öffnen der Zieldatei");return -1;}
            
            printf("Inhalt der %d.Datei: \n",filecount);
        	while (fgets(buf, sizeof(buf), datei)!=NULL) 
        	{
                printf("%s",buf);
        	}
        	
        	if (fclose(datei) == -1){fprintf(stdout,"Fehler beim schließen der Datein");return -1;}
        	puts("");
        	return 1;
        }
    
    } 
}