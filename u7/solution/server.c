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
   char *p;

   if (fd = shm_open("server",O_CREAT | O_RDWR,S_IRWXU), fd ==-1 ){perror("server"); return (1); }
   if( ftruncate(fd, length)==-1 ) {perror("ftruncate"); return (1);}
   p = mmap(NULL, length, (PROT_WRITE | PROT_READ), MAP_SHARED,fd, 0);
   if (p == MAP_FAILED) {perror("mmap");return (1);} 

   while(p[0]==0){;}
   {printf("%s \n",&p[1]);}
   
   if( shm_unlink("server")==-1 ) {perror("unlink");return 1;}
}