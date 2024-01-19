#include <async/connect_routine.h>
#include <async/request_routine.h>
using namespace yazi::async;

#include <socket/server_socket.h>
using namespace yazi::socket;

#include <frame/server.h>
using namespace yazi::frame;

ConnectRoutine::ConnectRoutine(int sockfd) : Routine(), m_sockfd(sockfd)
{
}

ConnectRoutine::~ConnectRoutine()
{

}

void ConnectRoutine::run()
{
	log_debug("connect routine run");
	Socket server(m_sockfd);
	while (true)
	{
		int sockfd = server.accept();
		if (sockfd < 0)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
			{
				// log_debug("sock accept would block");
				yield(); // 没有新链接，立刻切换到下一个协程，让出 cpu
			}
			else if (errno == EINTR)
			{
				log_debug("sock accept interrupted");
				yield(); // 被断开链接，立刻切换到下一个协程，让出 cpu
			}
			else
			{
				log_debug("sock accept error: errno=%d, errmsg=%s", errno, strerror(errno));
				break;
			}
		}
		else
		{
			// 接收到新的链接
			Socket client(sockfd);
			client.set_non_blocking();
			auto r = new RequestRoutine(sockfd);
			Singleton<Server>::instance()->append(r);
		}
	}
	server.close();
}

