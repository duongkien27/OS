/*1. Thêm các thư viện cần thiết*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main()
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;
/*2. Loại bỏ các tên hay liên kết socket khác trước đó nếu có. Đồng thời thực hiện khỏi tạo socket mới cho server*/
	unlink("server_socket");
	server_sockfd = socket (AF_UNIX, SOCK_STREAM, 0);
/*3. Đặt tên cho socket của server*/
	server_address.sun_family = AF_UNIX;
	stpcpy(server_address.sun_path,"server_socket");
	server_len = sizeof(server_address);
/*4. Ràng buộc tên với socket*/
	bind(server_sockfd, (struct sockaddr*)&server_address, server_len);
/*5. Mở hàng đợi nhận kết nối - cho phép đặt vào hàng đợi tối đa 5 kết nối*/
	listen(server_sockfd, 5);
/*6. Lập liên tục chờ và xử lý kết nối của client*/
	while(1){
		char ch;
		printf("server1 waiting\n");
		/*Chờ và chấp nhận kết nối*/
		client_sockfd = accept(server_sockfd,(struct sockaddr*)&server_address, &client_len);
		/*Đọc dữ liệu do client gửi đến*/
		read(client_sockfd, &ch, 1);
		ch++;
		/*Gửi trả dữ liệu về cho client*/
		write(client_sockfd, &ch, 1);
		/*Đóng kết nối*/
		close(client_sockfd);
	}

}
