#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <iostream>
using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main()
{
    string degree;
    char buffer[256]="Default";
    bool getinfo=true;              //declaring stuff
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    string portnumber;
    string servername;
    do{ //a do while loop to allow for multiple requests
    if(getinfo){
    cout<<"Enter the port number: ";//getting port number and setting it
    getline(cin,portnumber);
    portno = stoi(portnumber);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    cout<<"Enter the server name: ";
    getline(cin,servername); //retrieving the name of the server and setting it
    const char *cstr = servername.c_str();
    server = gethostbyname(cstr);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    } getinfo=false;}
    else //Have to set it repeatedly or there is an error but no need to ask for it after the first time.
    {
        portno = stoi(portnumber);
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        server = server;
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");


        printf("Please enter the degree: "); //Getting the degree and storing it to be sent
        bzero(buffer,256);
        gets(buffer);

        size_t length = strlen(buffer)-1;
        if(buffer[length]=='\0') //If the user enters nothing then it will break out of the loop
        {
            break;
        }
        n = write(sockfd,buffer,strlen(buffer)); //writing to socket and sending
        if (n < 0)
             error("ERROR writing to socket");
        bzero(buffer,256);
        n = read(sockfd,buffer,256);
        if (n < 0)
             error("ERROR reading from socket");
        printf("%s\n",buffer);
        close(sockfd);
    }while(1); //Endless loop unless broken by the user just pressing enter
    return 0;
}
