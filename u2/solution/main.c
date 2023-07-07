#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

int copy (char *sourcename, char *targetname){
    //Überprüft ob Zieldatei bereits existiert
    if ( (access(targetname, F_OK)) == 0) 
        {
        fprintf(stderr,"Zieldatei exetiert bereits!"); 
        return -1;
        }
        
    else 
        {
        //Öffnen und Fehlerbehandlung vom öffnen der target und source Datei
        int target = open(targetname, O_WRONLY | O_CREAT, S_IRWXU);
        if(target==-1){fprintf(stderr,"Fehler beim öffnen von %s\n",targetname); return -1;}
        int source = open(sourcename, O_RDONLY); 
        if(source==-1){fprintf(stderr,"Fehler beim öffnen von %s\n",sourcename); return -1;}
        
        char buf[1000000];  //1mb
        //Lesen und Fehlerbehandlung vom lesen der source Datei
        int readwhile;
        while( (readwhile = read(source, buf, 1000000)) !=0)
            {
            if (readwhile == -1) {fprintf(stderr,"Fehler beim lesen von %s\n",sourcename); return -1;}
            int written = 0;
            //Fehlerbehandlung bzw.fängt Abbrüche von write() ab
            while (written != readwhile)   
                {
                written = write(target, &buf[written], readwhile);
                }
            }
        //Fallabfrage beim Schließen der Datein    
        if ( (close(target) ==-1) | (close(source) ==-1) ) {fprintf(stderr,"Fehler beim Schließen der Datein"); return -1;}   
        return 1;
        }
}


int main (int argc, char *argv[])
{
     argc +=0;
    //Erstellt trashcan falls nicht vorhanden
    if ( (access(".ti3_trashcan", F_OK)) == -1)
        {
        mkdir(".ti3_trashcan",S_IRWXU);   
        } 


    switch(argv[1][1]) 
        {
            case 'd': 
                {
                //Erstellt Verzeichniss String
                char destination[16] = ".ti3_trashcan/\0";
                strcat(destination, argv[2]);
                //Fallabfrage für Falls Datei schon existiert 
                if ( (copy(argv[2],destination)) ==-1) {break;}
                //else
                if ( (unlink(argv[2])) ==-1) {fprintf(stderr,"Fehler beim löschen der Datei");}
                break;
                    
                }
                
            case 'l':
                {
                DIR *trashcanzeiger = opendir(".ti3_trashcan/");
                if (trashcanzeiger==NULL) 
                    {
                        fprintf(stderr,"Fehler beim öffnen von trashcan");
                        break;
                    }
                
                struct dirent *filezeiger;
                while ( (filezeiger=readdir(trashcanzeiger)) !=NULL ) 
                    {
                        fprintf(stderr,">> %s\n",filezeiger->d_name);
                    }
                
                if ( closedir(trashcanzeiger) ==-1) {fprintf(stderr,"Fehler beim schließen des trashcans");}
                break;   
                }
                
            case 'r':
                {
                //Erstellt Verzeichniss String
                char destination[16] = ".ti3_trashcan/\0";
                strcat(destination, argv[2]);
                //Fallabfrage für Falls Datei schon existiert 
                if ( (copy(destination,argv[2])) ==-1) {break;}
                //else
                if ( (unlink(destination)) ==-1) {fprintf(stderr,"Fehler beim löschen der Datei");}
                break;

                }
                
            case 'f':
                {
                char destination[16] = ".ti3_trashcan/\0";
                strcat(destination, argv[2]);    
                //Fallabfrage unlink()
                if ( (unlink(destination)) ==-1) {fprintf(stderr,"Fehler beim löschen der Datei");}
                break;   
                }
        }
        
}