include "sqlserver.h"

SQLserver::SQLserver()
{
    connect();
}

// 关闭数据库连接
SQLserver::~SQLserver()
{
    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    SQLDisconnect(hdbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, henv);
}

// 数据库连接函数
void SQLserver::connect()
{
    SQLAllocHandle(SQL_HANDLE_ENV, NULL, &henv);//申请环境
    SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);//设置环境
    SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);//申请数据库连接
    SQLCHAR* connStr = (SQLCHAR*)"DRIVER={SQL Server};SERVER=43.143.200.197,1433;"
                                 "DATABASE=MeowTiger;UID=sa;PWD=123456;";
    ret = SQLDriverConnect(hdbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);
    // 判断数据库是否连接成功
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        std::cerr<<"database connect failed! "<<std::endl;
    } else {
        std::cout<<"database connect success! "<<std::endl;
    }
}

// 执行查询的接口
void SQLserver::execute_query(const SQLTCHAR *query)
{
    // 申请句柄
    ret = SQLAllocHandle(SQL_HANDLE_STMT,hdbc,&hstmt);
    // 执行查询
    ret = SQLExecDirect(hstmt, (SQLTCHAR *)query, SQL_NTS);
    if (SQL_SUCCEEDED(ret)|| ret == SQL_SUCCESS_WITH_INFO){
        std::cout << "Query executed successfully!" << std::endl;
        SQLCHAR str1[30],str2[10],str3[20],str4[20];
        SQLINTEGER len_str1, len_str2, len_str3,len_str4;//字符串对应长度，你有几列就定义几个变量
        while (SQLFetch(hstmt) != SQL_NO_DATA)
        {
            SQLGetData(hstmt, 1, SQL_C_CHAR, str1, 50, &len_str1);   //获取第一列数据
            SQLGetData(hstmt, 2, SQL_C_CHAR, str2, 50, &len_str2);   //获取第二列数据
            SQLGetData(hstmt, 3, SQL_C_CHAR, str3, 50, &len_str3);   //获取第三列数据
            SQLGetData(hstmt, 4, SQL_C_CHAR, str4, 50, &len_str4);   //获取第一列数
            std::cout  << str1 <<"\t"<< str2<< "\t"<< str3 << "\t"<< str4 <<std::endl;
        }
    }
    else
    {
        std::cerr << "Error executing query." << std::endl;
        show_error(hstmt, SQL_HANDLE_STMT);
    }

    SQLFreeStmt(hstmt, SQL_CLOSE); // Free statement handle resources
}

// 处理数据库错误
void SQLserver::show_error(SQLHANDLE handle, SQLSMALLINT type)
{
    SQLINTEGER i = 0;
    SQLINTEGER native;
    SQLCHAR state[7];
    SQLCHAR text[256];
    SQLSMALLINT len;
    SQLRETURN ret;

    do
    {
        ret = SQLGetDiagRec(type, handle, ++i, state, &native, text,
                            sizeof(text), &len);
        if (SQL_SUCCEEDED(ret))
            std::cerr << "SQL Error: " << state << "(" << native << "): " << text << std::endl;
    } while (ret == SQL_SUCCESS);
}
