#ifndef INITSOCKET_HPP
#define INITSOCKET_HPP

#include<iostream>
#include<winsock2.h>
#include<thread>
#include"MeowMessage.hpp"
//#pragma comment(lib, "ws2_32.lib")


class ClientSocket{
private:
    void InitSocket() {
//        int RetVal;
        WSADATA Wsd;

        if (WSAStartup(MAKEWORD(2, 2), &Wsd) != 0) {
            std::cout << "init error" << std::endl;
            return;
        }

        ServerScoket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (ServerScoket == INVALID_SOCKET) {
            std::cout << "create socket error" << std::endl;
            WSACleanup();
            return;
        }

        SOCKADDR_IN ServerAddr;
        ServerAddr.sin_family = AF_INET;
        ServerAddr.sin_port = htons(2345);
        ServerAddr.sin_addr.S_un.S_addr = inet_addr("43.143.200.197");

        RetVal = connect(ServerScoket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));
        if (RetVal == SOCKET_ERROR) {
            std::cout << "link server error" << std::endl;
            closesocket(ServerScoket);
            WSACleanup();
            return ;
        }
    }
    void CleanSocket(){
        closesocket(ServerScoket);
        WSACleanup();
    }

public:
    ClientSocket(){
        InitSocket();
    }
    ~ClientSocket(){
        CleanSocket();
    }
    void ReceiveMessages(MeowMessage &mmsg) {
        char RECVBuff[BUF_SIZE];
//        int retVal;
//        ZeroMemory(RECVBuff, BUF_SIZE);
        RetVal = recv(ServerScoket, RECVBuff, BUF_SIZE, 0);
        if (RetVal == SOCKET_ERROR) {
            std::cout << "receive error" << std::endl;
            closesocket(ServerScoket);
            WSACleanup();
            return;
        }
        // 从服务器收到的消息似乎没有'\0'
        RECVBuff[RetVal] = '\0';
        MeowNowTime();
        std::cout<<"[receive from server]:"<<RECVBuff<<std::endl;
        // 解析服务器数据
        mmsg.DeSerialize(RECVBuff);
    }
    // 开辟新线程用
//    void ReceiveTalkMessages() {
//        char RECVBuff[BUF_SIZE];
//        while (true) {
//            ZeroMemory(RECVBuff, BUF_SIZE);
//            RetVal = recv(ServerScoket, RECVBuff, BUF_SIZE, 0);
//            if (RetVal == SOCKET_ERROR) {
//                std::cout << "receive error" << std::endl;
//                closesocket(ServerScoket);
//                WSACleanup();
//                return;
//            }
//            // 解析服务器数据
//            MeowMessage mmsg;
//            mmsg.DeSerialize(RECVBuff);
//            std::cout << "[receive from server]"<<mmsg.send_time<<"id:"<<mmsg.send_id << "message:"<<mmsg.content << std::endl;
//        }
//        delete []RECVBuff;
//    }
    void SendeMessages(const char *SendBuff){
//        ZeroMemory(SendBuff, BUF_SIZE);

        // 发送到服务器的消息应该是“标准的”
        RetVal = send(ServerScoket, SendBuff, strlen(SendBuff), 0);
        MeowNowTime();
        std::cout << "[Send to server]:"<<SendBuff<< std::endl;
        if (RetVal == SOCKET_ERROR) {
            std::cout << "send error" << std::endl;
            closesocket(ServerScoket);
            WSACleanup();
            return ;
        }

    }
private:
    const int BUF_SIZE = 512;
    int RetVal;
    SOCKET ServerScoket;

};
#endif // INITSOCKET_HPP
