#include <frame/server.h>
using namespace yazi::frame;

#include <socket/server_socket.h>
using namespace yazi::socket;

#include <async/connect_routine.h>
using namespace yazi::async;

void Server::start()
{
	// 系统初始化
	auto sys = Singleton<System>::instance();
	sys->init();
	string root_path = sys->get_root_path();

	// ini config
	auto ini = Singleton<IniFile>::instance();
	ini->load(root_path + "/config/server.ini");

	m_ip = (string)(*ini)["server"]["ip"];
	m_port = (*ini)["server"]["port"];
	m_log_level = (*ini)["server"]["log_level"];
	m_stack_size = (*ini)["server"]["stack_size"];

	// ini logger
	auto logger = Singleton<Logger>::instance();
	logger->open(root_path + "/log/server.log");
	logger->set_level(m_log_level);
	logger->set_console(false);

	// init schedule
	m_schedule.create(m_stack_size);
	auto r= new ConnectRoutine(ServerSocket(m_ip,m_port).fd());
	m_schedule.append(r);
	m_schedule.run();
}

void Server::append(Routine* r)
{
	m_schedule.append(r);
}