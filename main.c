#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>


int main(){
    int key = ftok("main.c", 999);
    int shmid = shmget(key, 200, 0644 | IPC_CREAT);

    char * data = shmat(shmid, (void *) 0, 0);
    if (!strlen(data)) {
      printf("Created new shared memory segment\n");
    } else {
      printf("The current value of the shared memory segment is: %s", data);
    }    
    while (1) {
      printf("Change the value of the shared memory segment? (y/n/exit): ");
      char * input_buffer = malloc(100);
      fgets(input_buffer, 100, stdin);

      if(*input_buffer  == 'y'){
          printf("Enter new value for the shared memory segment: ");
          fgets(data, 100, stdin);
      } else if (*input_buffer  == 'n'){
        printf("Would you like to delete the shared memory segment? (y/n/exit): ");
        input_buffer  = malloc(100);
        fgets(input_buffer, 100, stdin);

        if(*input_buffer  == 'y'){
            printf("Deleting shared memory segment\n");
            shmctl(shmid, IPC_RMID, NULL);
        } else if (strcmp(input_buffer, "exit")) {
          break;
        } else {
          printf("Invalid input\n");
        }
      } else if (strcmp(input_buffer, "exit")) {
        break;
      } else {
        printf("Invalid input\n");
      }
    }
    return 0;
}