#include <cxx/stl.hpp>
#include <config.h>

namespace std
{
	string csos_getVersion()
	{
		return CSOS_LIBVERSION_STRING;
	}
}