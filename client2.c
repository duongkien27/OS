/*1. Thêm các thư viện cần thiết*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	int sockfd;
	int len;
	
	struct sockaddr_in address;
	int result;
	char ch = 'A';

/*2. Tạo socket cho Client.*/
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	/*Đặt tên và gán địa chỉ kết nối cho socket theo giao thức Internet*/
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = 9734;


/*3. Gán tên của socket trên máy chủ cần kết nối */
	len = sizeof(address);
	
/*4. Thực hiện kết nối */
	result = connect (sockfd, (struct sockaddr*)&address, len);
	
	if (result == -1) {
		perror("oops: client2 problem");
		exit(1);
	}
/*5. Sau khi socket kết nối, chúng ta có thể đọc ghi dữ liệu của socket tương tự trên đọc ghi file */
	write(sockfd, &ch,1);
	read(sockfd, &ch,1);
	printf("char from server = %c\n", ch);
	exit(0);
	

}
