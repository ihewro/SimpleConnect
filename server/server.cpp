#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <string>
#include "server.h"

using std::cout;
using std::string;
using std::endl;
using std::vector;


const char * processor(int sock, fd_set fdRead);

int main() {
    std::cout << "Hello, World!" << std::endl;

    //create socket
    int serv_sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    cout << "��ǰsocket" <<serv_sock << endl;
    //bind ip and port with socket
    sockaddr_in serv_addr{};
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;//ipv4
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//local ip
    serv_addr.sin_port = htons(1237);

    if (bind(serv_sock,(struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        cout << "bind error!" << endl;
        return 1;
    } else {
        cout << "bind success!" << endl;
    }

    if (listen(serv_sock,20) == -1){
        cout << "����1234�˿�ʧ��" << endl;
    }//waiting queue size is 20


    //receive client request
    sockaddr_in client_addr{};
    socklen_t client_addr_size = sizeof(client_addr);

    vector<int> c_list;

    while (true){

        fd_set fdRead;
        fd_set fdWrite;
        fd_set fdExp;

        //�ÿ�
        FD_ZERO(&fdRead);
        FD_ZERO(&fdWrite);
        FD_ZERO(&fdExp);

        FD_SET(serv_sock, &fdRead);
        FD_SET(serv_sock, &fdWrite);
        FD_SET(serv_sock, &fdExp);

        //ѭ���ļ�������
        cout << "���ӵĿͻ��˵���Ŀ" << c_list.size() <<endl;
        for (int i = 0; i < c_list.size() ; i++) {
            //���¼���Ŀͻ��˷ŵ��ɶ����������ڲ�ѯ
            FD_SET(c_list[i], &fdRead);
        }

        cout << "�ȴ��ɶ��¼�" << endl;

        int len = sizeof(fdRead.fds_bits) / sizeof(fdRead.fds_bits[0]);
        for( int i=0;i<len;i++ )
            cout << fdRead.fds_bits[i] <<" " ;
        cout <<endl ;
        timeval t{1};

        int max;
        if (!c_list.empty()){
            max = c_list[c_list.size()-1];
        }else{
            max = serv_sock ;
        }
//        cout << "�ļ���������Χ" << max <<endl;
        int r = select(max+1, &fdRead, &fdWrite, &fdExp, NULL);
//        cout << "����ɶ��¼���Ŀ"<< r << endl;

        if (FD_ISSET(serv_sock, &fdRead)) {//
            FD_CLR(serv_sock, &fdRead);
            cout << "���µ�client����" << endl;
            //4. �ȴ��ͻ�������accept
            sockaddr_in clientAddr = {};
            socklen_t nAddrLen = sizeof(sockaddr_in);
            int _cSock = accept(serv_sock, (sockaddr*)&clientAddr, &nAddrLen); //�׽��֣��յ��ͻ���socket��ַ������socket��ַ�Ĵ�С
            if (_cSock == -1) {
                perror("client socket error!\n");
            } else {
                c_list.push_back(_cSock);
                send(_cSock, "server", 128,0);

                printf("client socket success! socket = %d, IP = %s \n", _cSock, inet_ntoa(clientAddr.sin_addr)); //��ӡ�ͻ���socket��IP��ַ

//                char _recvBuf[128] = {};
//                cout << "�ȴ���������" <<endl;
//                int nLen = recv(_cSock, _recvBuf, 128, 0);
//                cout << "����������" <<endl;
//                if (nLen <= 0) {
//                    cout << "nLen <= 0, connection with server has quit!" <<endl;
//                }else{
//                    cout << "�յ���Ϣ" <<_recvBuf <<endl;
//                }

            }
        }

        cout << "this is ok" << endl;
        //ѭ�����ý��̴�����
        for (int n = c_list.size() - 1; n >= 0; --n){
            const char *r= processor(c_list[n],fdRead);

            if (r == "-1"){ //����ͻ����������ݳ���<=0��ӿͻ���������hɾ����socket
                cout << "��ǰclientû�з�����" <<endl;
//                auto it = find(c_list.begin(), c_list.end(), c_list[n]);
//                if (it != c_list.end())
//                    c_list.erase(it);
            }else{
                //�ַ�����
//                cout << "�յ���Ϣ" <<endl;
                for(int i =0;i<c_list.size();i++){
                    //��ͻ��˷�������
                    send(c_list[i], r, 128,0);
                }
            }
        }




    }

    //�رշ�������
    close(serv_sock);

    return 0;
}

const char * processor(int sock, fd_set fdRead){
    if (FD_ISSET(sock,&fdRead)){
        char _recvBuf[128] = {};
        int nLen = recv(sock, _recvBuf, 128, 0);
        if (nLen <= 0) {
            printf("nLen <= 0, connection with server has quit!\n");
            return "-1";
        }else{
            cout << "�յ���Ϣ" << _recvBuf <<endl;
            return _recvBuf;
        }
    }else{
        return  "-1";
    }

}

void Server::createSock() {


}
