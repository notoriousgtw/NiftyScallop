#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <NiftyScallopApp.h>
#include <iostream>

int main() {
	try
	{
		Nifty::NiftyScallop scallop_app = Nifty::NiftyScallop();
		scallop_app.Loop();
	}
	catch (const std::runtime_error & e)
	{
		std::cerr << "Caught an exception: " << e.what() << std::endl;
		return -1;
	}
	return 0;
}