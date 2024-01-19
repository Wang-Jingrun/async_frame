#include <frame/server.h>
using namespace yazi::frame;

int main()
{
	try
	{
		Singleton<Server>::instance()->start();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}