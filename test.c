#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"
#include "util.h"
#include "gameplay.h"

int main(void){
    char message[128];
    char username[]="BINH";
    char password[]="1234";

    user_node* head;
    user_node* temp;

    head = create_new_user("BINH", 1, 1);
    temp = create_new_user("NAM", 1, 1);

    add_user(head,temp);

    print_user_list(head);

    temp = find_user(head, "cat");

    if(temp==NULL) printf("found no cat\n");
    else printf("Found user: %s\n", temp->username);

    return 0;
}