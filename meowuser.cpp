#include "meowuser.h"
extern ClientSocket CSOCKET;
extern MeowUser SELFUSER;
bool login_Meow(int _id, std::string _pwd)
{
    std::string meowStr= "0#1#"+std::to_string(_id)+"#0#"+std::to_string(_id)+"$"+_pwd;
    char *meowMsg = new char(meowStr.size());
    strcpy(meowMsg,meowStr.c_str());
    // 将封装的消息发送
    CSOCKET.SendeMessages(meowMsg);
    // 等待回传
    MeowMessage mmsg;
    CSOCKET.ReceiveMessages(mmsg);
    if(strcmp(mmsg.content,"1")==0){
        CSOCKET.ReceiveMessages(mmsg);
        // 初始化SELFUSER
        SELFUSER.InitMeowUser(mmsg.content);
        return true;
    }else{
        return false;
    }

    delete meowMsg;
}

void MeowUser::InitMeowUser(char *userData)
{
    std::istringstream iss(userData);
    std::string friendToken;
    // 加载好友列表
    while(std::getline(iss,friendToken,'|')){
        // 信息中不存在$或者为空就直接退出
        if(friendToken.find("$")==friendToken.npos||friendToken == "")
            break;
        std::istringstream friendIss(friendToken);
        std::string token;
        MeowUserData friends;
        MeowInfoType infoType = MeowInfoType::ID;
        while(std::getline(friendIss,token,'$')){
            switch (infoType) {
            case MeowInfoType::ID:{
                if(self.id==0)
                    self.id = std::stoi(token);
                else
                    friends.id = std::stoi(token);
                infoType = MeowInfoType::NAME;
            }break;
            case MeowInfoType::NAME:{
                if(self.name=="")
                    self.name = token;
                else
                    friends.name = token;
                infoType = MeowInfoType::SIGN;
            }break;
            case MeowInfoType::SIGN:{
                if(self.sign=="")
                    self.sign = token;
                else
                    friends.sign = token;
            }break;
            default:
                std::cerr<<"receive unknow datatype";
                break;
            }
        }
        if(friends.name!="")
            this->friends.push_back(friends);
    }
    // 加载newfriend message
    MeowMessage mmsg;
    CSOCKET.ReceiveMessages(mmsg);
    while(strcmp(mmsg.content,"0")!=0){
        newFriends.push_back(mmsg);
        CSOCKET.ReceiveMessages(mmsg);
    }
}

void MeowUserData::printMeowUserData() const
{
    std::cout<<this->id<<std::endl;
}
