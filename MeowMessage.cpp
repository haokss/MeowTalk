#include"MeowMessage.hpp"
//MeowMessage::MeowMessage(int id, char *pwd){
//    this->send_time = 0;
//    this->type = static_cast<MeowDataType>(1);
//    this->send_id = 0;
//    this->receive_id = 0;
//}

MeowMessage::~MeowMessage(){
    delete []content;
}

char* MeowMessage::Serialize() const{
    std::string data = std::to_string(send_time)+"#"+std::to_string((int)type)+"#"+std::to_string(send_id)+"#"+
    std::to_string(receive_id)+"#"+content;
    std::cout<<"string data:"<<data<<std::endl;
    char *SerializeData = new char[data.size()+1];
    strcpy(SerializeData, data.c_str());
    return SerializeData;
}

void MeowMessage::DeSerialize(char* Buffer){
    char * token = strtok(Buffer,"#");
    // 默认除Content以外，其他类型都不可能出现\n
    MeowData md = MeowData::TIME;
    while(token!=NULL){
        switch (md)
        {
        case MeowData::TIME:{
            this->send_time = std::stol(token);
            md = MeowData::TYPE;
        }break;
        case MeowData::TYPE:{
            this->type = static_cast<MeowDataType>(std::stoi(token));
            md = MeowData::SENDER;
        }break;
        case MeowData::SENDER:{
            send_id = std::stoi(token);
            md = MeowData::RECEIVE;
        }break;
        case MeowData::RECEIVE:{
            receive_id = std::stoi(token);
            md = MeowData::CONTENT;
        }break;
        case MeowData::CONTENT:{
            content = new char[strlen(token) + 1];
            strcpy(content, token);
        }break;
        default:
            std::cerr<<"receive unknow datatype";
            break;
        }
        token = strtok(NULL, "#");
    }

}

