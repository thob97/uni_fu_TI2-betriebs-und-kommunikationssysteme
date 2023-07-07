#define _POSIX_C_SOURCE 200809L
#include <sys/mman.h>
#include <sys/stat.h>       
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main ()
{
   int fd;
   off_t length = 200;
   char senden[200];
   char *p;

   if( (fd = shm_open("server",O_RDWR,S_IRWXU))==-1 ){perror("server"); return (1);}
   p = mmap(NULL, length, (PROT_WRITE | PROT_READ), MAP_SHARED,fd, 0);
   if (p == MAP_FAILED) {perror("mmap");return (1);} 
   
   scanf("%s",senden);
   sprintf(&p[1], senden);
   p[0] = 1;
}