#pragma once

#include <string>
using std::string;

#include <utility/system.h>
#include <utility/logger.h>
#include <utility/ini_file.h>
#include <utility/singleton.h>
using namespace yazi::utility;

#include <routine/schedule.h>
using namespace yazi::routine;

namespace yazi
{
    namespace frame
    {
        class Server
        {
            SINGLETON(Server);
        public:
            void start();
			void append(Routine* r);

        private:
            string m_ip;
            int m_port = 0;
            int m_log_level = 0;
			int m_stack_size = 0;
			Schedule m_schedule;
        };
    }
}
