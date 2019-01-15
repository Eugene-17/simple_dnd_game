#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"

int main(void){
    print_login_info(read_login_info("login_info.txt"));
    return 0;
}