#include <socket/client_socket.h>
using namespace yazi::socket;

int main()
{
	Singleton<Logger>::instance()->open("../log/client.log");
	ClientSocket client("127.0.0.1", 8080);

	// 向服务端发送数据
	string data = "hello world";
	log_info("send: %s", data.c_str());
	client.send(data.c_str(), data.size());

	// 接收服务端的响应
	char buf[1024] = { 0 };
	client.recv(buf, sizeof(buf));
	log_info("recv: %s", buf);

	client.close();
	return 0;
}