#ifndef MEOWBASE_H
#define MEOWBASE_H

#include <ctime>
#include <iostream>

// 返回当前时间
inline void MeowNowTime(){
    std::time_t now_time = std::time(nullptr);
    struct tm* now = localtime(&now_time);
    char str[50];
    strftime(str, sizeof(str),"%Y/%m/%d %H:%M:%S",now);
    std::cout<<str;
}

// 时间戳转换时间
inline void MeowTimeStampToTime(const std::time_t& time){
    struct tm* now = localtime(&time);
    char str[50];
    strftime(str, sizeof(str),"%Y/%m/%d %H:%M:%S",now);
    std::cout<<str;
}

// 获取随机ID
//int MeowGetRandomId(){

//}

#endif // MEOWBASE_H
