//
// Created by s-gheldd on 4/27/16.
//
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <zconf.h>
#include "mq.h"
#include "msg_linked_set.h"

int main() {
    int msq_id = msgget(MQ_KEY, IPC_PRIVATE | IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    struct msqid_ds msqid_ds;
    int child_count = 0;
    struct list_node *root = NULL;
    struct list_node **root_ptr = &root;
    pid_t pid_server, pid_client;
    pid_server = getpid();

    if (msq_id == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    while (1) {
        struct msg_message rec_message, send_message;
        rec_message.mtyp = 1;
        msgrcv(msq_id, &rec_message, MSG_SIZE, 1, 0);
        sscanf(rec_message.text, "%d", &pid_client);

        if (pid_client == -1) {
            child_count--;
        } else if (msg_linked_set_add(root_ptr, pid_client)) {
            child_count++;
            printf("New Client: %d\n", pid_client);
        }
        if (!child_count) {
            break;
        }
        send_message.mtyp = pid_client;
        sprintf(send_message.text, "%d\n", pid_server);
        msgsnd(msq_id, &send_message, MSG_SIZE, 0);
    }

    sleep(1);
    if (msgctl(msq_id, IPC_RMID, &msqid_ds) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }
    msg_linked_set_free(root_ptr);
    printf("Server done, shutting down.\n");
    return EXIT_SUCCESS;
}