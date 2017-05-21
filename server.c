#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/stat.h>

//Function deceleration
void clear();
void mainMenu();
int createClient(choice);

int main(int argc, char **argv)
{
    //variables
    pid_t id = fork();
    int pin;
    int choice;

    if (id > 0)
    {

        int status;
        waitpid(id, &status, 0);
        if (status == 0)
        {
            mainMenu();
            scanf("%d", &choice);
            if (choice == 5)
            {
                exit(0);
            }
            if (createClient(choice) != 1)
            {
                printf("Error Create Process");
                exit(0);
            }
        }
        if (status == 1)
        {
            printf("child process us terminated with error\n");
            exit(0);
        }
    }
    else if (id == 0)
    {

        while (pin != 4444)
        {
            printf("What is the Password :");
            scanf("%d", &pin);
            if (pin != 4444)
            {
                printf("Please enter a valid password\n");
            }
        }
    }

    return 0;
};

//Function Implementation
void clear()
{
    system("clear");
}
void mainMenu()
{
    clear();
    printf("\t \t \t \t \t \t\tWellcome to Pharmacy Management System\n");
    printf("1- Create Medicine\n");
    printf("2- Search Medicine\n");
    printf("3- Delete Medicine\n");
    printf("4- Edit Medicine\n");
    printf("5- Exit\n");
    printf("Enter your choice: ");
}

int createClient(choice)
{

    key_t shm_key = 6166529;
    const int shm_size = 1024;

    int shm_id;
    char *shmaddr, *ptr;
    int next[2];

 

    /* Allocate a shared memory segment. */
    shm_id = shmget(shm_key, shm_size, IPC_CREAT | S_IRUSR | S_IWUSR);

    /* Attach the shared memory segment. */
    shmaddr = (char *)shmat(shm_id, 0, 0);

    printf("shared memory attached at address %p\n", shmaddr);

    char cid = '1';

    /* Start to write data. */
    ptr = shmaddr + sizeof(next);

    if (choice == 1)
    {
        next[0] = sprintf(ptr, "1");
    }
    if (choice == 2)
    {
        next[0] = sprintf(ptr, "2");
    }
    if (choice == 3)
    {
        next[0] = sprintf(ptr, "3");
    }
    if (choice == 4)
    {
        next[0] = sprintf(ptr, "4");
    }

    memcpy(shmaddr, &next, sizeof(next));

    /*calling the other process*/
    system("./client");

    /* Detach the shared memory segment. */
    shmdt(shmaddr);
    /* Deallocate the shared memory segment.*/
    shmctl(shm_id, IPC_RMID, 0);

    return 1;
}