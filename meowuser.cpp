#include "meowuser.h"
extern ClientSocket CSOCKET;
extern MeowUser SELFUSER;
bool login_Meow(int _id, std::string _pwd)
{
    std::string meowStr= "0#1#"+std::to_string(_id)+"#0#"+std::to_string(_id)+"$"+_pwd;
    const char *meowMsg = meowStr.c_str();
    // 将封装的消息发送
    CSOCKET.SendeMessages(meowMsg);
    // 等待回传
    MeowMessage mmsg;
    CSOCKET.ReceiveMessages(mmsg);
    if(mmsg.content=="1"){
        CSOCKET.ReceiveMessages(mmsg);
        // 初始化SELFUSER
        SELFUSER.InitMeowUser(mmsg.content);
        // 首次登录创建缓存
        std::string path = "D:/Qt_Project/Sql/cache/"+std::to_string(_id);
        if(access(path.c_str(),0)==-1){
            mkdir(path.c_str());
        }
        return true;
    }else{
        return false;
    }
}
bool register_Meow(int id,std::string username,std::string password){
    std::string msg = "0#2#"+std::to_string(id)+"#0#"+username+"$"+password;
    CSOCKET.SendeMessages(msg.c_str());
    MeowMessage mmsg;
    if(mmsg.content=="1"){
        return true;
    }else{
        return false;
    }
}

void MeowUser::InitMeowUser(const std::string &userData)
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
    // 加载好友请求消息
    MeowMessage mmsg;
    CSOCKET.ReceiveMessages(mmsg);
    while(mmsg.content != "0"){
        newFriends.push_back(mmsg);
        CSOCKET.ReceiveMessages(mmsg);
    }

}

void MeowUserData::printMeowUserData() const
{
    std::cout<<this->id<<std::endl;
}
