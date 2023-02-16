#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

void test()
{
	//1. 创建监听服务器的套接字
	int listenfd = ::socket(AF_INET, SOCK_STREAM, 0);	

	if(listenfd < 0)
    {
		perror("socket");
		return;
	}

	//网络地址需要采用网络字节序存储(大端模式)
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(8888);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	socklen_t length = sizeof(serveraddr);

#if 0
	//设置网络地址可以重用
	int on = 1;
	if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int)) < 0) 
    {
		perror("setsockopt");
		close(listenfd);
		return;
	}

	//当端口设置为可以重用时， 就实现了系统级别的负载均衡
	if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(int)) < 0) 
    {
		perror("setsockopt");
		close(listenfd);
		return;
	}
#endif

	//2. 绑定服务器的网络地址
	if(::bind(listenfd, (struct sockaddr*)&serveraddr, length) < 0)
    {
		perror("bind");
		//文件描述符是比较稀缺的，所以不用的时候要回收
		close(listenfd);
		return;
	}

	//3. 让服务器开始监听
	if(::listen(listenfd, 10) < 0)
    {
		perror("listen");
		close(listenfd);
		return;
	} 
	printf("server is listening...\n");

	//4. 获取对端的文件描述符，并与对端进行通信
	int peerfd = ::accept(listenfd, nullptr, nullptr);

	//5. 需求：希望服务器可以与客户端通过终端进行聊天
	while(1) 
    {
		char buff[128] = {0};
		recv(peerfd, buff, sizeof(buff), 0);
		printf(">> recv msg from client: %s\n", buff);

		//从终端获取一行数据
		cout << ">> pls input some message:";
		string line;
		getline(cin, line);
		send(peerfd, line.c_str(),  line.size(), 0);
	}
	
	close(peerfd);// 关闭连接
	close(listenfd);
}
 
int main(void)
{
	test();
	return 0;
}
