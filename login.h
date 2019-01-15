#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LOGIN_NODE {
    char *username;
    char *password;
    struct LOGIN_NODE * next;
} login_node;

login_node * read_login_info(char *filename);

void print_login_info(login_node *head);

#endif /* LOGIN_H */