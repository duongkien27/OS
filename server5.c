/*1. Thêm các thư viện cần thiết*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

int main()
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	int result;
	fd_set readfds, testfds;
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
	FD_ZERO(&readfds);
/*6. Lập liên tục chờ và xử lý kết nối của client*/
	FD_SET(server_sockfd,&readfds);
	while(1){
		char ch;
		int fd;
		int nread;
		
		testfds = readfds;
		printf("server5 waiting\n");
		
		result = select(FD_SETSIZE, &testfds, (fd_set*)0, (fd_set *)0, (struct timeval *)0);
		if(result < 1){
			perror("server5");
			exit(1);
		}
		for(fd=0; fd < FD_SETSIZE; fd++) {
			if(FD_ISSET(fd,&testfds)){
			/*Nếu là socket của server*/
				if(fd==server_sockfd){
					/*Tạo socket cho tương ứng kết nối với client*/
					client_sockfd = accept(server_sockfd,(struct sockaddr*)&server_address, &client_len);
				/*Đưa socket này vào danh sách đợi của hàm select*/
					FD_SET(client_sockfd, &readfds);
					printf("adding client on fd %d\n"), client_sockfd);
				}
			/*Nếu không phải socket của server - trường hợp này là socket của client gửi dữ liệu đến*/
			else{
				ioctl(fd, FIONREAD, &nread);
				/*Đóng kết nối nếu không còn dữ liệu để đọc*/
				if(nread == 0){
					close(fd);
				/*Loại socket của client ra khỏi danh sách chờ*/
					FD_CLR(fd, &readfds);
					printf("removing client on fd %d\n", fd);
				}
				else{
			/*Xử lí dữ liệu đọc được*/
					read(fd,&ch,1);
					sleep(5);
					printf("serving client on fd %d \n", fd);
					ch++;
					write(fd, &ch,1);
					}
				}
			}
		}
	}
}