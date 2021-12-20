/*1. Thêm các thư viện cần thiết*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>

int main()
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;

	server_sockfd = socket (AF_INET, SOCK_STREAM, 0);
/*3. Đặt tên cho socket của server*/
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(9734);
	server_len = sizeof(server_address);
/*4. Ràng buộc tên với socket*/
	bind(server_sockfd, (struct sockaddr*)&server_address, server_len);
/*5. Mở hàng đợi nhận kết nối, yêu cầu bỏ qua tín hiệu kết thúc của các tiến trình con gửi đến tiến trình cha.
Tạo vòng lặp chờ kết nối từ tiến trình khách*/
	listen(server_sockfd, 5);
	signal(SIGCHLD, SIG_IGN);
/*6. Lập liên tục chờ và xử lý kết nối của client*/
	while(1){
		char ch;
		printf("server4 waiting\n");
		/*Chờ và chấp nhận kết nối*/
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd,(struct sockaddr*)&server_address, &client_len);
		/*Đọc dữ liệu do client gửi đến*/
		if(fork() == 0 ) {
			read(client_sockfd, &ch, 1);
			ch++;
			/*Gửi trả dữ liệu về cho client*/
			write(client_sockfd, &ch, 1);
			/*Đóng kết nối*/
			close(client_sockfd);
			exit();
		}
		else {
			close(client_sockfd);
		}
	}

}