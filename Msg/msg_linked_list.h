//
// Created by s-gheldd on 4/27/16.
//

#ifndef SERVER_MSG_LINKED_LIST_H
#define SERVER_MSG_LINKED_LIST_H

#include <signal.h>

struct list_node {
    pid_t pid;
    struct list_node *next;
};

int msg_linked_list_add(struct list_node **root, pid_t pid);

int msg_linked_list_remove(struct list_node **root, pid_t pid);

int msg_linked_list_size(struct list_node *list);

int msg_linked_list_free(struct list_node **root);


#endif //CIENT_MSG_LINKED_LIST_H
