#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <thread>
#include "client.h"


#define SOCKET_ERROR -1
using namespace std;


void handleInput(Client client){

    while (true){
        cout <<"输入文字：" << endl;

        char cmdBuf[128] = {}; //大小与服务器端匹配，防止溢出
        cin >> cmdBuf;

        //创建套接字
        //4. 处理请求命令
        if (0 == strcmp(cmdBuf, "exit")) {
            printf("receive quit message!");
        } else {
            //5. 向服务器端发送请求
            send(client.sock, cmdBuf, strlen(cmdBuf) + 1, 0);
            cout << "发送文字" <<endl;
        }
    }


}

int main(){

    Client client;

    client.connectSock();
    char cmdBuf[128] = "client加入";
//    send(client.sock, cmdBuf, strlen(cmdBuf) + 1, 0);

    //处理输入
    std::thread t(handleInput,client);

    //处理接收到的信息
    while (true){
        //6. 接受服务器信息recv
        char recvBuf[256] = {};
        int nlen = recv(client.sock, recvBuf, 256, 0); //返回接受数据的长度
        if (nlen > 0) {
            cout << "message:" << recvBuf <<endl;
        }else{
            cout << "not connect" <<endl;
        }
    }

    return 0;
}

void Client::connectSock() {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    cout << "当前client文件描述符" << sock << endl;
    //向服务器（特定的IP和端口）发起请求
    sockaddr_in serv_addr{};
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1237);  //端口


    int ret = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (ret == SOCKET_ERROR) {
        cout <<"connect error!" << endl;
    } else {
        cout <<"connect success!" << endl;

    }

}
