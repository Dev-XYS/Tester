#include "Process.h"

namespace Process
{
	int LastReturnValue;
	
	bool Exist(int __ProcessID)
	{
		return system((string("ps | grep ") + __ProcessID).c_str()) == 0;
	}
}
