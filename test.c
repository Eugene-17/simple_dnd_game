#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"
#include "util.h"

int main(void){
    char message[128];
    char username[]="BINH";
    char password[]="1234";
    login_node * login_database; 
    login_database = read_login_info("login_info.txt"); 
    print_login_info(login_database);

    printf("%d\n", check_login(login_database,"BINH","1234"));
    return 0;
}