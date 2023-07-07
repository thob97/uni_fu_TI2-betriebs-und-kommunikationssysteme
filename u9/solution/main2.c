//Von Thore Brehmer und Jonny Lam
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <unistd.h>
#define POLY   98309 

unsigned int message[1024];
int pt = 0;
int len = 0;
char c;
uint16_t crc16 = 0; 
char argv2[124];  
int error;        

int main (int argc, char *argv[])
{    
    //Überprüft ob eine txt oder crc Datei in argv ist
    char *p = strrchr(argv[1],'.');
    if (strcmp (p, ".txt")==0){
        
        //Öffnen der txt datei
        FILE *datei  = fopen(argv[1], "r+");
        if (datei == NULL) {perror("datei öffnen"); return 0;}
        
        //Erstellt den crc namen
        strcpy (argv2, argv[1]);
        argc = strlen(argv2);
        argv2[argc-4] = '\0';
        strcat(argv2,".crc");
    
        //Renaming der Datei
        error = rename (argv[1], argv2);
        if (error==-1) {perror("datei öffnen"); return 0;}
            
        //Aus txt die Nachricht erhalten
        while ( (c = fgetc (datei) ) != EOF){
            len +=8;  
            for (int i = 0; i<8; i++){
                if ((c&128)==128){
                    message[pt] = 1;
                }
                pt ++;
                c <<=1;
            }
        }    
        
        //Rechnung für crc
        for (int i = 0; i < len; i++)
        {
            if ( ((crc16 >> 15) & 1) != message[i])
                crc16 = (crc16 << 1) ^ POLY;
            else
                crc16 = (crc16 << 1);
        }
        
        //Fügt crc in die datei ein.
        error = fputc(crc16>>8,datei);
        error = fputc(crc16&255,datei);
        if (error == EOF){fprintf(stdout,"fputc \n"); return 0; }
        
        fclose(datei);
         
        printf ("Checksumme = 0x%08X\n", crc16);
        printf ("Message = ");
        for (int i = 0; i<len; i++){
            printf("%d",message[i]);
        }
        puts("");

              
    }
    
    // Falls crc datei übergeben wurde
    else {
        
        //die crc datei öffnen
        FILE *dateicrc = fopen (argv[1], "r+");
        if (dateicrc == NULL) {perror("dateicrc öffnen"); return 0;}
        
        //Aus crc die Nachricht erhalten
        while ( (c = fgetc (dateicrc) ) != EOF){
            len +=8;  
            for (int i = 0; i<8; i++){
                if ((c&128)==128){
                    message[pt] = 1;
                }
                pt ++;
                c <<=1;
            }
        }
        
        printf("Message = ");
        for (int i = 0; i<len; i++){
            printf("%d",message[i]);
        }
        puts("");
        
        //überprüft crc
        for (int i = 0; i < len; i++)
        {
            if ( ((crc16 >> 15) & 1) != message[i])
                crc16 = (crc16 << 1) ^ POLY;
            else
                crc16 = (crc16 << 1);
        }
        
        //Falls ein Fehler vorliegt
        if (crc16 != 0){fprintf(stdout,"Die Nachricht und crc stimmen nicht überein \n"); return 0; }
    
        //sonst
        //Erstellt den txt namen
        strcpy (argv2, argv[1]);
        argc = strlen(argv2);
        argv2[argc-4] = '\0';
        strcat(argv2,".txt");
        
        //erstellt die txt datei
        if (access (argv2, F_OK) != -1) {fprintf(stdout,"%s existiert bereits \n", argv2); return 0; }
        FILE *datei = fopen (argv2, "a");
        if (datei == NULL) {perror("dateicrc öffnen"); return 0;}
        
        //Crc zu txt kopieren
        rewind(dateicrc);
        while ( len > 16 ) {
            c = fgetc (dateicrc);
            len -=8;  
            fputc (c, datei);
        }
        
        //crc datei löschen und schließen der datein
        fclose(datei);
        error = remove (argv[1]);
        if (error==-1) {perror("remove"); return 0;}
        fclose(dateicrc);
        
        printf("Checksumme = ");
        printf ("0x%08X\n", crc16);
    }
    return EXIT_SUCCESS;    
}