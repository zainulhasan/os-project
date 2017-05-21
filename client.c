#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main()
{
    key_t shm_key = 6166529;
    const int shm_size = 1024;

    int shm_id;
    char *shmaddr, *ptr;
    char *shared_memory[3];
    int *p;

    /* Allocate a shared memory segment. */
    shm_id = shmget(shm_key, shm_size, IPC_CREAT | S_IRUSR | S_IWUSR);

    /* Attach the shared memory segment. */
    shmaddr = (char *)shmat(shm_id, 0, 0);

    
    /* Start to read data. */
    p = (int *)shmaddr;
    ptr = shmaddr + sizeof(int) * 2;
    shared_memory[0] = ptr;

    printf("%s\n", shared_memory[0]);


    /* Detach the shared memory segment. */
    shmdt(shmaddr);
    return 0;
}