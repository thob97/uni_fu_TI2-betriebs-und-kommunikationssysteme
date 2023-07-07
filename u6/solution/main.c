#define _GNU_SOURCE
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <fcntl.h>         
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>


int filter (const struct dirent *current)
{
    if(current->d_name[0]!='.'){return(1);}
    else {return 0;}
}

int main (int argc, char *argv[])
{
    struct dirent **namelist;
    int n = 0;
    int stop = -1;
    int (*filterB)() = filter; 
    int (*sortB)() = NULL;
    struct stat time;
    char timedict [1000] = "";

   
    int opt;
    while( (opt = getopt(argc, argv, "a:: l::")) != -1 )
    { 
        switch(opt) 
            {
                case 'l': 
                    {   
                    sortB=alphasort;
                    break;
                    }
                    
                case 'a':
                    {
                    filterB=NULL;
                    break;   
                    }
                    
                    case '/':
                    {
                    puts("/");    
                    printf("%s \n", optarg);
                    
                    break;   
                    }
                    
            }
    }
    
    
  
    
    //my_ls 
    if (argc==1) {n = scandir(".", &namelist,filter,NULL);}
    
    //Führe die Opt aus
    if (optind<argc) {n = scandir(argv[optind], &namelist,filterB,sortB);strcpy(timedict,argv[optind]);strcat (timedict, "/");}
    else {n = scandir(".", &namelist,filterB,sortB);}
          
        
    //Fehler Abfrage
    if ( n==-1 ){fprintf(stdout,"Fehler \n"); return 1;}    
    
    else 
        {
                 
                while (++stop != n)
                {
                    //Falls -l
                    if (sortB==alphasort)
                    {
                        //Fürs richtige Verzeichniss
                        char td[2000];
                        strcpy (td,timedict);
                        strcat (td, namelist[stop]->d_name);
                        
                        
                        stat(td, &time);
                        char *timestr = ctime(&time.st_ctime);
                        printf("%s", timestr);
                    }
                    
                    printf(">> %s \n", namelist[stop]->d_name);
                    free(namelist[stop]);
                }  
        }                
}