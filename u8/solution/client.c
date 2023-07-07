#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include <arpa/inet.h> 
#include <sys/types.h>                 
#include <sys/socket.h>
#include <string.h>

int main (int argc, char *argv[]){
    int socked_fd;
    struct sockaddr_in addr;
    char buffer[1024];
    size_t readed;
    
    
    int opt = getopt(argc, argv, "U: u: t:");
    switch(opt) 
        {
            case 'U':
                puts("U");
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
                struct sockaddr* ip = (struct sockaddr *)&addr;
                
                //connect
                if (connect (socked_fd, ip, sizeof(addr)) == -1 ){
                    perror ("connect");
                    return -1;
                }
                
                //send pfad
                send(socked_fd, argv[3], strlen(argv[3])+1, 0);
                
                //read and fwrite
                while ( (readed = read(socked_fd, buffer, sizeof(buffer)) ) >0 ){
                    fwrite(buffer, readed, 1, stdout);
                }
                
                break;
        }
        
        puts("");
        return 1;
}