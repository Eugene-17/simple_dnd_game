#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"

int main(void){
    login_node* head; 
    head = read_login_info("login_info.txt");

    printf("\n%d\n",check_login(head,"BINH","123"));
    return 0;
}