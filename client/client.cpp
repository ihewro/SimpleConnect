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
        cout <<"�������֣�" << endl;

        char cmdBuf[128] = {}; //��С���������ƥ�䣬��ֹ���
        cin >> cmdBuf;

        //�����׽���
        //4. ������������
        if (0 == strcmp(cmdBuf, "exit")) {
            printf("receive quit message!");
        } else {
            //5. ��������˷�������
            send(client.sock, cmdBuf, strlen(cmdBuf) + 1, 0);
            cout << "��������" <<endl;
        }
    }


}

int main(){

    Client client;

    client.connectSock();
    char cmdBuf[128] = "client����";
//    send(client.sock, cmdBuf, strlen(cmdBuf) + 1, 0);

    //��������
    std::thread t(handleInput,client);

    //������յ�����Ϣ
    while (true){
        //6. ���ܷ�������Ϣrecv
        char recvBuf[256] = {};
        int nlen = recv(client.sock, recvBuf, 256, 0); //���ؽ������ݵĳ���
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
    cout << "��ǰclient�ļ�������" << sock << endl;
    //����������ض���IP�Ͷ˿ڣ���������
    sockaddr_in serv_addr{};
    memset(&serv_addr, 0, sizeof(serv_addr));  //ÿ���ֽڶ���0���
    serv_addr.sin_family = AF_INET;  //ʹ��IPv4��ַ
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //�����IP��ַ
    serv_addr.sin_port = htons(1237);  //�˿�


    int ret = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (ret == SOCKET_ERROR) {
        cout <<"connect error!" << endl;
    } else {
        cout <<"connect success!" << endl;

    }

}
