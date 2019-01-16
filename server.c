#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<fcntl.h> // for open
#include<unistd.h> // for close
#include<pthread.h>

#include "util.h"
#include "login.h"

#define MAX_THREAD 64
#define MESSAGE_SIZE 128


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

login_node* login_database; // store login database taken from txt file

void * socketThread(void *arg){
    int newSocket = *((int *)arg);
    int break_flip = 1; // change to 0 if thread should be dead

    char client_message[MESSAGE_SIZE];
    char server_message[MESSAGE_SIZE];

    int check_login_flip;
    char* username;
    char* password;
    char* client_message_type;

    while(break_flip){
        memset(server_message, 0, sizeof(server_message));
        memset(client_message, 0, sizeof(client_message));
        if(recv(newSocket, client_message, MESSAGE_SIZE, 0) < 0){
            printf("Receive failed\n");
        }
        strcat(client_message,"");
        printf("Thead %d: \"%s\"\n", newSocket ,client_message);

        client_message_type = strtok(client_message, " "); //first call strok

        if(strcmp(client_message_type,"LOGIN")==0){
            username = strtok(NULL, " "); //second call strok
            password = strtok(NULL, " "); //third call strok
            check_login_flip = check_login(login_database,username,password);

            if(check_login_flip == 1) strcpy(server_message,"OK");
            if(check_login_flip == 0) strcpy(server_message,"NOUSER");
            if(check_login_flip == -1) strcpy(server_message,"WRONGPASS");

            send(newSocket,server_message,strlen(server_message),0);
            continue;
        }


        // Send message to the client socket 
        strcpy(server_message,client_message);
        send(newSocket,server_message,strlen(server_message),0);
        if(strcmp("exit",client_message)==0) break_flip=0;
        //clean the message variable
    
    }

    printf("user exited. \n");
    close(newSocket);
    pthread_exit(NULL);
}

int main(){
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    //Create the socket. 
    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    // Configure settings of the server address struct
    // Address family = Internet 
    serverAddr.sin_family = AF_INET;
    //Set port number, using htons function to use proper byte order 
    serverAddr.sin_port = htons(7799);
    //Set IP address to localhost 
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //Set all bits of the padding field to 0 
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    //Bind the address struct to the socket 
    bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    //Listen on the socket, with 64 max connection requests queued 
    if(listen(serverSocket,MAX_THREAD)==0)
        printf("Listening\n");
    else printf("Error\n");
    
    login_database = read_login_info("login_info.txt"); // get login info from txt file

    pthread_t tid[MAX_THREAD];
    
    int i = 0;
    while(1){
        //Accept call creates a new socket for the incoming connection
        addr_size = sizeof serverStorage;
        newSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);
        //for each client request creates a thread and assign the client request to it to process
        //so the main thread can entertain next request
        if( pthread_create(&tid[i], NULL, socketThread, &newSocket) != 0 )
            printf("Failed to create thread\n");
        if( i >= MAX_THREAD){
            i = 0;
            while(i < MAX_THREAD){
                pthread_join(tid[i++],NULL);
            }
            i = 0;
        }
    }
  return 0;
}