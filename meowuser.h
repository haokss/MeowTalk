#ifndef MEOWUSER_H
#define MEOWUSER_H
#include<string>
#include<vector>
#include<sstream>
#include<iostream>
#include<io.h>
#include "InitSocket.hpp"
enum class MeowInfoType{
    ID = 1, NAME = 2, SIGN =3, SEX = 4, TELEPHONE = 5
};

class MeowUserData
{
public:
    MeowUserData()=default;
    void printMeowUserData()const;

public:
    int id;
    std::string name;
    std::string sign;
    bool sex;
    std::string telephone;
};

class MeowUser{
public:
    MeowUser()=default;
    // 从服务器回传消息中加载用户数据
    void InitMeowUser(const std::string &userData);
public:
    MeowUserData self;
    std::vector<MeowUserData> friends;
    std::vector<MeowMessage> newFriends;
};

// 判断账户登录/登录
bool login_Meow(int _id,std::string _pwd);
bool register_Meow(int id,std::string username,std::string password);
#endif // MEOWUSER_H
