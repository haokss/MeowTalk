#ifndef MEOWBASE_H
#define MEOWBASE_H

#include <ctime>
#include <iostream>

// 返回当前时间
inline void Meow_now_time(){
    std::time_t now_time = std::time(nullptr);
    struct tm* now = localtime(&now_time);
    char str[50];
    strftime(str, sizeof(str),"%Y/%m/%d %H:%M:%S",now);
    std::cout<<str;
}


#endif // MEOWBASE_H
