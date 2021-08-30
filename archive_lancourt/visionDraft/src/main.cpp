#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <errno.h>

#include <iostream>
#include <thread>
#include <string>

// VISION
int main(void)
{
    char *sharedMem = nullptr;
    key_t key = 36;
    size_t size = 50;
    int shmid; // return of shmget

    // creation memoire partagee avec droits d acces rxw
    if ((shmid = shmget(key, size, 0666)) < 0)
    {
        std::cout << "[vision] shmget: shmget returned " << shmid << std::endl;
        return 1;
    }

    sharedMem = (char *)shmat(shmid, NULL, 0);

    std::cout << "New shared Mem : " << sharedMem << std::endl;

    shmdt(sharedMem);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}