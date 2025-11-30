#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>


int main(){
    char m[] = "Hello world";
    printf("%p\n", &m);
    return 0;
}
