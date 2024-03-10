#pragma once

#include <socket/socket.h>
using namespace yazi::socket;

#include <routine/routine.h>
using namespace yazi::routine;

namespace yazi
{
    namespace async
    {
        class RequestRoutine : public Routine
        {
        public:
            RequestRoutine() = delete;
            RequestRoutine(int sockfd);
            ~RequestRoutine();

            virtual void run();

        private:
            int m_sockfd;
        };
    }
}
