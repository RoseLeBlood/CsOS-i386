#ifndef __DRIVER_LIST_H__
#define __DRIVER_LIST_H__

#include <cxx/common.hpp>
#include <cxx/algorithm.hpp>
#include <cxx/list.hpp>

#include <dev/Driver.hpp>

typedef std::list<dev::Driver*> listDriver;

namespace dev
{
	class DriverList 
	{
	public:
		DriverList();
		~DriverList();

		bool		Add(Driver *driver);
		Driver *    Get(const char *devname);
		void        Rem(const char *devname);
		
		listDriver	GetDriverList() { return m_driver; }
		
	
	private:
		listDriver		m_driver;
	};
}
#endif