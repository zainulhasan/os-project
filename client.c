#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <semaphore.h>

void *createRecord(void *data);
void *searchRecord(void *data);
void *deleteRecord(void *data);
void *editRecord(void *data);

sem_t mutex;

int main()
{
    key_t shm_key = 6166529;
    const int shm_size = 1024;

    int shm_id;
    char *shmaddr, *ptr;
    char *shared_memory[3];
    int *p;

    sem_init(&mutex, 0, 1);
    pthread_t thread;

    /* Allocate a shared memory segment. */
    shm_id = shmget(shm_key, shm_size, IPC_CREAT | S_IRUSR | S_IWUSR);

    /* Attach the shared memory segment. */
    shmaddr = (char *)shmat(shm_id, 0, 0);

    /* Start to read data. */
    p = (int *)shmaddr;
    ptr = shmaddr + sizeof(int) * 2;
    shared_memory[0] = ptr;

    int id = atoi(shared_memory[0]);

    switch (id)
    {

    case 1:
        if (pthread_create(&thread, NULL, createRecord) != 0)
        {
            printf("Error creating thread\n");
        }
        break;
    case 2:
        if (pthread_create(&thread, NULL, searchRecord) != 0)
        {
            printf("Error creating thread\n");
        }
        break;
    case 3:
        if (pthread_create(&thread, NULL, deleteRecord) != 0)
        {
            printf("Error creating thread\n");
        }
        break;
    case 4:
        if (pthread_create(&thread, NULL, editRecord) != 0)
        {
            printf("Error creating thread\n");
        }
        break;
    default:
        printf("defult");
        break;
    }

    pthread_join(thread, NULL);
    /* Detach the shared memory segment. */
    shmdt(shmaddr);
    sem_destroy(&mutex);
    return 0;
}

void *createRecord(void *data)
{

    sem_wait(&mutex);
    printf("Create");
    sem_post(&mutex);
    pthread_exit(0);
}
void *searchRecord(void *data)
{
    sem_wait(&mutex);
    printf("search");
    sem_post(&mutex);
    pthread_exit(0);
}
void *deleteRecord(void *data)
{
    sem_wait(&mutex);
    printf("delete");
    sem_post(&mutex);
    pthread_exit(0);
}
void *editRecord(void *data)
{
    sem_wait(&mutex);
    printf("edit");
    sem_post(&mutex);
    pthread_exit(0);
}