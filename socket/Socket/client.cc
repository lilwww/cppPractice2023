#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main(int argc, char **argv)
{
    //1、创建套接字，使用socket函数
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd < 0)
    {
        perror("socket\n");
        return -1;
    }
    
    //2、主动发起连接请求，使用connect函数，但是需要知道
    //服务器的ip与端口号port，使用struct sockadd_in结构体
    struct sockaddr_in seraddr;
    memset(&seraddr, 0, sizeof(seraddr));//初始化seraddr
    seraddr.sin_family = AF_INET;
    
    //本机字节序转换为网络字节序(包括ip与端口号)
    seraddr.sin_port = htons(atoi(argv[2]));
    seraddr.sin_addr.s_addr = inet_addr(argv[1]);
    
    int ret = connect(listenfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    if(ret < 0)
    {
        perror("connect\n");
        close(listenfd);
        return -1;
    }
    
    //3、如果connect返回值是ok，那么就表明三次握手建立成功了
    //那么就可以进行数据的收发，也就是read/recv，或者
    //write/send函数
    while(1)
    {
        cout << "我客户端想发送数据给服务器" << endl;
        string line;
        getline(std::cin, line);
        int len2 = send(listenfd, line.data(), line.size(), 0);
        if(len2 < 0)
        {
            cout << "客户端发送出错" << endl;
        }
        else if(0 == len2)
        {
            cout << "0 == len2" << endl;
        }
        else
        {
            cout << "客户端发送正常" << endl;
        }

        char buf[128] = { };
        int len = recv(listenfd, buf, sizeof(buf), 0);
        if(len < 0)
        {
            cout << "客户端接收失败" << endl;
        }
        else if(0 == len)
        {
            cout << "len == 0" << endl;
        }
        else
        {
            cout << "recv msg from server: " << buf << endl;
        }
    }
    
    //4、关闭文件描述符
    close(listenfd);
    return 0;
}

