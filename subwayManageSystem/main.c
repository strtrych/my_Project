#include "main.h"
#include "subwayLineManage.h"
#include "login.h"


int main()
{
	if(mainLogin())
	{
		mainSLM();
	}
	return 0;
}




