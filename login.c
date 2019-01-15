#include "login.h"

login_node * read_login_info(char *filename){
    FILE *login_info_file;
    
    char temp[80];
    char *ch;
    char *username;
    char *password;

    login_node *head, *current;

    head = current = NULL;
    login_info_file = fopen("login_info.txt", "r");

    while ( fgets(temp, 80, login_info_file) != NULL ) {
        /* read from file */
        ch = strtok(temp, "-");
        username = ch;
        ch = strtok(NULL, "-");
        password = ch;

        login_node *node = malloc(sizeof(login_node));
        node->username = strdup(username);
        node->password = strdup(password);

        if(head == NULL){
            current = head = node;
        } else {
            current = current->next = node;
        }
    }
    fclose(login_info_file);

    return head;
};

void print_login_info(login_node * head){
    login_node *current;
    current = NULL;

    for(current = head; current ; current=current->next){
        printf("\n%s\n%s", current->username,current->password);
    }
};