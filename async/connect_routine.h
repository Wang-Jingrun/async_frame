#pragma once

#include <utility/logger.h>
using namespace yazi::utility;

#include <routine/routine.h>
using namespace yazi::routine;

namespace yazi
{
    namespace async
    {
        class ConnectRoutine : public Routine
        {
        public:
            ConnectRoutine() = delete;
            ConnectRoutine(int sockfd);
            ~ConnectRoutine();

            virtual void run();

        private:
            int m_sockfd;
        };
    }
}
