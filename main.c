#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>


void get_heap_addr(int fd){
    struct stat fileInfo; 
    if (fstat(fd, &fileInfo) == -1){
        perror("Ошибка fstat");
        exit(1);
    }

    char* addr;
    printf("Адрес памяти из стэка: %p \n", addr);
    addr = (char*) mmap(0, fileInfo.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED){
        perror("Ошибка mmap");
        close(fd);
        exit(1);
    }

    printf("%s", addr);
    printf("Адрес памяти из кучи: %p \n", addr);

    if (munmap(addr, fileInfo.st_size) == -1){
        perror("Ошибка un-mapping the file");
        exit(1);
    }
}

int main(){
    int fd = open("test.txt", O_RDWR);
    if (fd == -1){
        perror("Ошибка при открытии файла");
        exit(1);
    }

    get_heap_addr(fd);
    close(fd);

    return 0;
}
