/* tcpserver.c */
/* Programmed by Adarsh Sethi */
/* September 13, 2017 */

#include <ctype.h>          /* for toupper */
#include <stdio.h>          /* for standard I/O functions */
#include <stdlib.h>         /* for exit */
#include <string.h>         /* for memset */
#include <sys/socket.h>     /* for socket, bind, listen, accept */
#include <netinet/in.h>     /* for sockaddr_in */
#include <unistd.h>         /* for close */
#include <time.h>

#define STRING_SIZE 1024

/* SERV_TCP_PORT is the port number on which the server listens for
 incoming requests from clients. You should change this to a different
 number to prevent conflicts with others in the class. */

#define SERV_TCP_PORT 63773

int main(void){
    
    int sock_server;  /* Socket on which server listens to clients */
    int sock_connection;  /* Socket on which server exchanges data with client */
    
    struct sockaddr_in server_addr;  /* Internet address structure that
                                      stores server address */
    unsigned int server_addr_len;  /* Length of server address structure */
    unsigned short server_port;  /* Port number used by server (local port) */
    
    struct sockaddr_in client_addr;  /* Internet address structure that
                                      stores client address */
    unsigned int client_addr_len;  /* Length of client address structure */
    
    char sentence[STRING_SIZE];  /* receive message */
    char modifiedSentence[STRING_SIZE]; /* send message */
    unsigned int msg_len;  /* length of message */
    int bytes_sent1, bytes_sent2,bytes_sent3, bytes_sent4, bytes_recd1, bytes_recd2; /* number of bytes sent or received */
    unsigned int i;  /* temporary loop variable */
    
    char Letter;
    unsigned short Number;
    int x, size;
    unsigned short int j[Number] ;
    int y = 0;
    char L[Number],S[Number];
    int t =time(NULL);
    
    int bufferNumber1=(Number/100)+1;
    int ToBeSent1 [bufferNumber1][100];
    char ToBeSent2 [bufferNumber1][100];
    int v,k;
    unsigned int r, m;
    unsigned short check_sum1;
    char check_sum2;
    
    
    /* open a socket */
    
    if ((sock_server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("Server: can't open stream socket");
        exit(1);
    }
    
    /* initialize server address information */
    
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl (INADDR_ANY);  /* This allows choice of
                                                        any host interface, if more than one
                                                        are present */
    server_port = SERV_TCP_PORT; /* Server will listen on this port */
    server_addr.sin_port = htons(server_port);
    
    /* bind the socket to the local server port */
    
    if (bind(sock_server, (struct sockaddr *) &server_addr,
             sizeof (server_addr)) < 0) {
        perror("Server: can't bind to local address");
        close(sock_server);
        exit(1);
    }
    
    /* listen for incoming requests from clients */
    
    if (listen(sock_server, 50) < 0) {    /* 50 is the max number of pending */
        perror("Server: error on listen"); /* requests that will be queued */
        close(sock_server);
        exit(1);
    }
    printf("I am here to listen ... on port %hu\n\n", server_port);
    
    client_addr_len = sizeof (client_addr);
    
    /* wait for incoming connection requests in an indefinite loop */
    
    for (;;) {
        sock_connection = accept(sock_server, (struct sockaddr *) &client_addr,
                                 &client_addr_len);
        /* The accept function blocks the server until a
         connection request comes from a client */
        if (sock_connection < 0) {
            perror("Server: accept() error\n");
            close(sock_server);
            exit(1);
        }
        
        /* receive the message */
        
        bytes_recd1 = recv(sock_connection, &Letter, sizeof(Letter), 0);
        bytes_recd2 = recv(sock_connection, &Number, sizeof(Number), 0);
        bytes_sent1 = send(sock_connection, &Letter, sizeof(Letter), 0);
        bytes_sent2 = send(sock_connection, &Number, sizeof(Number), 0);
        
        printf("The input letter is: %c \n",Letter);
        printf("The input number is: %hu\n",Number);
        
       /*Generate Letter od Number*/
        
        if(Letter=='N')        //random sequence of numbers
        {
            srand(time(NULL));
            for(x =0;x<Number;x++)
            {
                j[x] = rand()%100 ;
                //printf("%d",j);
            }
            for (x = 0; x<Number; x++) {
                check_sum1 += j[x];
            }
            for(x=0;x<Number;x++)
            {
                printf("%d,",j[x]);
            }
            //size = sizeof(j);
            
            for (int q=0;q<bufferNumber1;q++)
            {
                printf("1");
                for (k=0;k<100;k++) {
                    if(j[k+100*q]!=0){
                        ToBeSent1[q][k] = j[k+100*q];
                        printf("%d",k+100*q);
                    }else{
                        ToBeSent1[q][k] = 0;
                    }
                }
            }
            
            printf("\n-------------\n");
            int buffer[100];
            int j;
            for (i=0;i<bufferNumber1;i++)
            {
                for(j=0;j<100;j++){
                  buffer[j] = ToBeSent1[i][j];
                }
                bytes_sent3 = send(sock_connection,&buffer,100,0);
                printf("\n buffer number %d\n", i);
                for(int j=0;j<100;j++) {
                    printf("%d, ", ToBeSent1[i][j]);
                    srand(time(NULL));
                    r=(rand()%900+100)*1000;
                    for(m=0;m<r;m++){}
                }
            }
            printf("\ntotal number of letters transmitted: %d.\n", Number);
            printf("number of separate transmissions: %d.\n", bufferNumber1);
            printf("total number of bytes transmitted: %d.\n", size);
            printf("check sum: %hu.\n\n", check_sum1);
            return 0;
        }
        else
        {  //random sequence of letters
            srand(time(0));
            for(y=0; y<Number; y++)
            {
                L[y] = 'a'+rand()%26;
            }
            for (y = 0; y<Number; y++) {
                check_sum2 += L[y];
            }
            
            for(y=0;y<Number;y++)
            {
                printf("%c",L[y]);
            }
            
            size = sizeof(L);
            printf("Size %lu",sizeof(L));
            
            for (int q=0;q<bufferNumber1;q++)
            {
                for (k=0;k<100;k++) {
                    if (k>=Number){ToBeSent2[q][k]=0;}
                    else{ToBeSent2[q][k]=L[k];}
                }
            }
            
            printf("\n-------------\n");
            int buffer[99];
            for (i=0;i<bufferNumber1;i++)
            {
                int j;
                for (i=0;i<bufferNumber1;i++)
                {
                    for(j=0;j<100;j++){
                    buffer[j] = ToBeSent2[i][j];
                        }
                }
                bytes_sent4 = send(sock_connection,&buffer,100,0);
                printf("\nbuffer number %d\n", i);
                for(int j=0;j<100;j++) {
                    printf("%c, ", ToBeSent2[i][j]);
                    srand(time(NULL));
                    r=(rand()%900+100)*1000;
                    for(m=0;m<r;m++){}
                }
            }
            printf("\ntotal number of letters transmitted: %d.\n", Number);
            printf("number of separate transmissions: %d.\n", bufferNumber1);
            printf("total number of bytes transmitted: %d.\n", size);
            printf("check sum: %hhd.\n\n", check_sum2);
            
            return 0;
        }
            
            /* send message */
            
        
            
        
    }
            /* close the socket */
            
            close(sock_connection);
    
}




