#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include <arpa/inet.h> 
#include <sys/types.h>                 
#include <sys/socket.h>
#include <string.h>
#include <dirent.h>

int main (int argc, char *argv[]){
    int socked_fd, new_socket;
    struct sockaddr_in addr, cliaddr;
    struct sockaddr* ip;
    char pfad[1024];
    char buffer[1024];
    FILE *datei;
    size_t written;
    size_t sizeofaddr = sizeof(addr);
    
    
    
    int opt = getopt(argc, argv, "U: u: t:");
    switch(opt) 
        {
            case 'U':               
                break;
            case 'u':       
                break;
                
                
                
                
                
                
                
                
                
                
                
                
            case 't':
                
                //Socket erstellen
                if ((socked_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
                    perror ("socket");
                    return -1;
                }                             
                
                //Sockaddr_in
                addr.sin_family = AF_INET;
                addr.sin_port = htons(8080);
                if(inet_pton(AF_INET, argv[2], &addr.sin_addr) == -1){
                    perror ("inet_pton");
                    return -1;
                }
                
                //sockaddr_in -> sockaddr
                ip = (struct sockaddr *)&addr;
                
                //Bind
                if (bind(socked_fd, ip, sizeofaddr) ==-1){
                    perror ("bind");
                    return -1;
                }
                
                //Listen
                if (listen( socked_fd, 2) == -1){
                    perror ("bind");
                    return -1;
                }
                
                //Accept
                if ((new_socket = accept(socked_fd, ip, (socklen_t*) &sizeofaddr )) == -1) {
                    perror("accept");
                    return -1;
                }
                
                //read (Pfad einlesen)
                if ( read(new_socket , pfad, sizeof(pfad)) ==-1){
                    perror("read");
                    return -1;
                }
                printf("reading: %s\n",pfad);
                
                //Pfad öffnen
                if( (datei = fopen(pfad, "r")) == NULL){
                    perror("fopen");
                    return -1;
                }
                
                //Send and Read
                while ((written = fread(buffer, 1, sizeof(buffer), datei)) > 0) {
                    printf(".");
                    send(new_socket, buffer, written, 0);
                }
                
                fclose(datei);         
                break;
        }
        puts("done");
        return 1;
}