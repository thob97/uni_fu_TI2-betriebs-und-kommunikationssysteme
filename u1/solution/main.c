#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main (){

FILE *datei  = fopen("text.dat", "r");
int zeile1, temp, temp2, summe=0;
    
if (datei==NULL) {
    perror("text.dat");
    return (1);
    }  

fscanf(datei, "%d", &zeile1); //Liest die erste Zeile und speichert die Zahl in "zeile1"


while (!feof(datei)) { //Schleife bis EOF
    fscanf(datei, "%d*%d", &temp, &temp2); 
    summe = summe + temp*temp2; 
    }
    
if (zeile1==summe) {puts("0");}
else {puts("1");}
fclose(datei);
}