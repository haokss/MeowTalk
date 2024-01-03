#include"MeowMessage.hpp"

MeowMessage::MeowMessage(const std::string &line)
{
    std::istringstream iss(line);
    std::string content;
    MeowMessageType infoType = MeowMessageType::MSGID;
    while(std::getline(iss,content,'\t')){
        switch (infoType) {
        case MeowMessageType::MSGID:{
            type = static_cast<MeowDataType>(3);
            infoType = MeowMessageType::SENDER;
        }break;
        case MeowMessageType::SENDER:{
            send_id = std::stoi(content);
            infoType = MeowMessageType::RECEIVE;
        }break;
        case MeowMessageType::RECEIVE:{
            receive_id = std::stoi(content);
            infoType = MeowMessageType::CONTENT;
        }break;
        case MeowMessageType::CONTENT:{
            this->content = content.c_str();
            infoType = MeowMessageType::TIME;
        }break;
        case MeowMessageType::TIME:{
            this->send_time = std::stoi(content);
        }break;
        default:
            std::cerr<<"receive unknow datatype";
            break;
        }
    }
}

MeowMessage::~MeowMessage(){

}

std::string MeowMessage::Serialize() const{
    std::string data = std::to_string(send_time)+"#"+std::to_string((int)type)+"#"+std::to_string(send_id)+"#"+
    std::to_string(receive_id)+"#"+content;
    std::cout<<"string data:"<<data<<std::endl;
    return data;
}

void MeowMessage::DeSerialize(char* Buffer){
    const char * token = strtok(Buffer,"#");
    // 默认除Content以外，其他类型都不可能出现\n
    MeowMessageType md = MeowMessageType::TIME;
    while(token!=NULL){
        switch (md)
        {
        case MeowMessageType::TIME:{
            this->send_time = std::stol(token);
            md = MeowMessageType::TYPE;
        }break;
        case MeowMessageType::TYPE:{
            this->type = static_cast<MeowDataType>(std::stoi(token));
            md = MeowMessageType::SENDER;
        }break;
        case MeowMessageType::SENDER:{
            send_id = std::stoi(token);
            md = MeowMessageType::RECEIVE;
        }break;
        case MeowMessageType::RECEIVE:{
            receive_id = std::stoi(token);
            md = MeowMessageType::CONTENT;
        }break;
        case MeowMessageType::CONTENT:{
            content = token;
        }break;
        default:
            std::cerr<<"receive unknow datatype";
            break;
        }
        token = strtok(NULL, "#");
    }
}

