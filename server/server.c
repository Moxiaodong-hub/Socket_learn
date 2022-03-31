#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SEVERPORT 6666
#define MAXLINE 80

int main(){
	int lisenfd, clentfd, lisenbind;
	struct sockaddr_in severaddr;//定义服务器结构体
	struct sockaddr_in clentaddr;//定义客户端结构体
	char buff[MAXLINE];
	char str[INET_ADDRSTRLEN];

	lisenfd = socket(AF_INET, SOCK_STREAM, 0);//设置套接字
	//if(lisenfd != 0){
	//	printf("create socket faild \n");
	//	return 0;
	//}

	memset(&severaddr, 0, sizeof(severaddr));//清除缓存
	severaddr.sin_family = AF_INET;//使用IPv4
	severaddr.sin_port = htons(SEVERPORT);//定义端口
	severaddr.sin_addr.s_addr = htonl(INADDR_ANY);//定义IP 任意IP
	bind(lisenfd, (struct sockaddr *)&severaddr, sizeof(severaddr));
	if(lisenbind != 0){
		printf("bind socket faild \n");
		return 0;
	}

	listen(lisenfd, 32);
	
	printf("Waiting for connecting ... \n");

	while(1){
		int i, n;
		socklen_t clentlen = sizeof(clentaddr);
		clentfd = accept(lisenfd, (struct sockaddr *)&clentaddr, &clentlen);
		n = read(clentfd, buff, MAXLINE);
		printf("received from %s at port %d \n", inet_ntop(AF_INET, &clentaddr.sin_addr, str, sizeof(str)), ntohs(clentaddr.sin_port));

		for(int i = 0; i < n; i++)
			buff[i] = toupper(buff[i]);
		write(clentfd, buff, n);
		close(clentfd);

	}


	return 0;
}
