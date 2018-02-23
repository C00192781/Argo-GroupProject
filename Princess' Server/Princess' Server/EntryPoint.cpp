#include "Server.h"

int main(int argc, char** argv)
{
	Server server;

	if (server.start())
	{
		while (server.getRunning())
		{
			server.update();
		}
	}

	return 0;
}