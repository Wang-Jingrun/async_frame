#include <async/connect_routine.h>
#include <async/request_routine.h>
using namespace yazi::async;

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
                // log_debug("socket accept would block");
                yield(); // 没有新连接，立刻切换到下一个协程，让出 CPU
            }
            else if (errno == EINTR)
            {
                log_debug("socket accept interrupted");
                yield(); // 没有新连接，立刻切换到下一个协程，让出 CPU
            }
            else
            {
                log_debug("socket accept error: errno=%d, errmsg=%s", errno, strerror(errno));
                break;
            }
        }
        else
        {
            Socket client(sockfd);
            client.set_non_blocking();
            Singleton<Server>::instance()->append(new RequestRoutine(sockfd));
        }
    }
    server.close();
}