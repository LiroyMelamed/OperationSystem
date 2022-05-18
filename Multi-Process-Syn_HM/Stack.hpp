
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <fstream>

int const BUFFSIZE = 1024;
struct node
{
    char data[BUFFSIZE];
    struct node *next;
} * head;

struct nodeMap
{
    struct node *first_in;
    struct node *temp;
};
int fd;
struct flock lock;

struct nodeMap *map;

int has_init = 0;
void *memory_start;
void *last_addr;

void malloc_init()
{
    last_addr = sbrk(0);
    memory_start = last_addr;
    has_init = 1;
}
struct mem_block
{
    int is_available;
    int size;
};

void _free(void *firstbyte)
{
    struct mem_block *mcb;
    mcb = (struct mem_block *)firstbyte - sizeof(struct mem_block);
    mcb->is_available = 1;
    return;
}

void *_malloc(long num_of_bytes)
{
    void *curr_location;
    struct mem_block *curr_location_mcb;
    void *mem_location;
    if (!has_init)
    {
        malloc_init();
    }
    num_of_bytes = num_of_bytes + sizeof(struct mem_block);
    mem_location = 0;
    curr_location = memory_start;
    while (curr_location != last_addr)
    {
        curr_location_mcb = (struct mem_block *)curr_location;
        if (curr_location_mcb->is_available)
        {
            if (curr_location_mcb->size >= num_of_bytes)
            {
                curr_location_mcb->is_available = 0;
                mem_location = curr_location;
                break;
            }
        }
        curr_location = curr_location + curr_location_mcb->size;
    }
    if (!mem_location)
    {
        sbrk(num_of_bytes);
        mem_location = last_addr;
        last_addr = last_addr + num_of_bytes;
        curr_location_mcb = (struct mem_block *)mem_location;
        curr_location_mcb->is_available = 0;
        curr_location_mcb->size = num_of_bytes;
    }
    mem_location = mem_location + sizeof(struct mem_block);
    return mem_location;
}

void initialize()
{
    head = NULL;
}

int isEmpty()
{
    if (map->temp == NULL)
        return 1;
    else
        return 0;
}

char *top()
{
    lock.l_type = F_WRLCK;
    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        printf("Problem");
        exit(1);
    }
    char *curr = map->temp->data;
    //    printf("Peeked %s\n",head->data);
    //    char* curr = head->data;
    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        printf("Problem");
        exit(1);
    }
    return curr;
}

void push(char *text)
{
    lock.l_type = F_WRLCK;
    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        printf("Problem");
        exit(1);
    }
    if (map->temp == NULL)
    {
        map->temp = map->first_in;
        strcpy(map->temp->data, text);
        map->temp->next = NULL;
        printf("Pushed %s to stack\n", map->temp->data);
    }
    else
    {
        struct node *temp = map->temp + 1;
        strcpy(temp->data, text);
        temp->next = map->temp;
        map->temp = temp;
        printf("Pushed %s to stack\n", temp->data);
    }
    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        printf("Problem");
        exit(1);
    }
}

char *pop()
{
    lock.l_type = F_WRLCK;
    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        printf("Problem");
        exit(1);
    }
    struct node *temp;
    if (isEmpty())
    {
        printf("\nEmpty stack\n");
    }
    else
    {
        temp = map->temp;
        map->temp = map->temp->next;
        printf("Poped %s\n", temp->data);
    }
    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        printf("Problem");
        exit(1);
    }
    return temp->data;
}
