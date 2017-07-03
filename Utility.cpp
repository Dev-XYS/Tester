#include "Utility.h"

namespace Utility
{
	string operator + (string __String, int __Integer)
	{
		string res = __String;
		if (__Integer < 0)
		{
			res += '-';
			__Integer = -__Integer;
		}
		else if (__Integer == 0)
		{
			__Integer += '0';
		}
		else
		{
			string tmp;
			while (__Integer > 0)
			{
				tmp += (char)(__Integer % 10 + '0');
				__Integer /= 10;
			}
			for (int i = tmp.size() - 1; i >= 0; i--)
			{
				res += tmp[i];
			}
		}
		return res;
	}
}
