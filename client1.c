/*1. Thêm các thư viện cần thiết*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int sockfd;
	int len;
	
	struct sockaddr_un address;
	int result;
	char ch = 'A';

/*2. Tạo socket cho Client. Lưu lại số mô tả socket*/

	sockfd = socket (AF_UNIX, SOCK_STREAM, 0);
	address.sun_family = AF_UNIX;

/*3. Gán tên của socket trên máy chủ cần kết nối */
	strcpy (address.sun_path, "server_socket");
	len = sizeof(address);
	
/*4. Thực hiện kết nối */
	result = connect (sockfd, (struct sockaddr*)&address, len);
	
	if (result == -1) {
		perror("oops: client1 problem");
		exit(1);
	}
/*5. Sau khi socket kết nối, chúng ta có thể đọc ghi dữ liệu của socket tương tự trên đọc ghi file */
	write(sockfd, &ch,1);
	read(sockfd, &ch,1);
	printf("char from server = %c\n", ch);
	exit(0);

}
