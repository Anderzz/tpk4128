#include <sys/types.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int gVar = 0;

/*
fork() creates a new process with a copy of the parents' address space (memory), while vfork() creates
a copy where the child process shares the same memory as the parent process. Therefore gVar only lives in one
memory address, so both processes increment it, thus it goes to 20. lVar is local, so it only lives in the function scope. 
*/

int main(){
    int lVar = 0;
    //pid_t pid = fork(); // fork a child process
    pid_t pid = vfork(); // fork a child process
    if (pid == 0){ // child process
        for (int i = 0; i < 10; i++){
            printf("Child is incrementing: gVar = %d, lVar = %d\n", gVar, lVar);
            gVar++;
            lVar++;
        }
        printf("Child done: gVar = %d, lVar = %d\n\n", gVar, lVar);
    
    } else if (pid > 0){ // parent process
        for (int i = 0; i < 10; i++){
            printf("Parent is incrementing: gVar = %d, lVar = %d\n", gVar, lVar);
            gVar++;
            lVar++;
        }
        printf("Parent done: gVar = %d, lVar = %d\n\n", gVar, lVar);
        //wait(NULL); // wait for child process to finish
    } else {
        perror("Error forking");
        return 1;
        
    }
    return 0;
}