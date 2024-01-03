#ifndef MEOWMESSAGE_HPP
#define MEOWMESSAGE_HPP

#include<iostream>
#include<ctime>
#include<vector>
#include<string>
#include<sstream>
#include<string.h>
#include"MeowBase.h"
enum class MeowDataType{
    LOGIN = 1, REG = 2,MESSAGE = 3, ADD = 4, DEL = 5
};
enum class MeowMessageType{
    MSGID = -1,TIME =0, TYPE = 1, SENDER = 2, RECEIVE = 3, CONTENT = 4
};
// 定义数据的发送类型 必须严格按照格式
// 不同类型的数据用#分割，不同消息内容content用$区分,不同数据用|区分
//1、 Time: xxx\n
//2、 Type: xxx\n
//3、 Sender: xxxx\n   可选, 默认值为0
//4、 Receive: xxxx,xxxx\n  可选，默认值为0
//5、 Content: xxxx

class MeowMessage{
public:
    MeowMessage()=default;
    // login / register
    MeowMessage(int id,char *pwd);
    // history msg
    MeowMessage(const std::string& line);
    ~MeowMessage();
    // 序列化字节流
    // 请注意使用此函数一定要清除开辟的内存，防止内存泄漏
    std::string Serialize()const;
    // 反序列化
    void DeSerialize(char *Buffer);
    // 时间戳解析时间
public:
    std::time_t send_time;
    MeowDataType type;
    int send_id;
    int receive_id;
    std::string content;
};


#endif
