#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    std::cout << "Hello, World!" << std::endl;
//
//    //create socket
//    int serv_sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
//
//    //bind ip and port with socket
//    struct sockaddr_in serv_addr;
//    memset(&serv_addr, 0, sizeof(serv_addr));
//    serv_addr.sin_family = AF_INET;//ipv4
//    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//local ip
//    serv_addr.sin_port = htons(1234);
//    bind(serv_sock,(struct sockaddr *)&serv_addr, sizeof(serv_addr));
//
//    listen(serv_sock,20);//waiting queue size is 20
//
//    //receive client request
//    struct sockaddr_in clnt_addr;
//    socklen_t clnt_addr_size = sizeof(clnt_addr);
//    int clnt_sock = accept(serv_sock,(sockaddr *)&clnt_addr,&clnt_addr_size);
//
//
//    //向客户端发送数据
//    char str[] = "Hello World!";
//    write(clnt_sock, str, sizeof(str));
//
//    //关闭套接字
//    close(clnt_sock);
//    close(serv_sock);



    return 0;
}
