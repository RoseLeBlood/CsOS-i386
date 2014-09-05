#ifndef __CSOS_CONFIG_HPP__
#define __CSOS_CONFIG_HPP__

#define COMPILER_NAME "gcc"
#define COMPILER_VERSION (__GNUC__ * 10000 \
                    	 + __GNUC_MINOR__ * 100 \
                         + __GNUC_PATCHLEVEL__)


#define VERSION                 		"0.54.00"
#define NAME                    		"CS/OS"
#define RELEASE_NAME    				"Abby"
#define MACHINE							"i686"
#define NETWORKNAME						"csos"

#define CSOS_LIBVERSION					0x002615
#define CSOS_LIBVERSION_STRING			std::string("0.26.15")

#define USE_RTL8139						1
#define USE_PCNET						0
#define	KEYBOARD_LANG					<dev/klang/de_de.h>

#define	LIB_TAB_SIZE					4

/* Version Brief:

	0.4.0:
		add Version Brief
		kernel ready
	0.51.53:
		klibc, klibcxx
		add fs
	0.52.01:
		add wchar. wtype
		add Driver random, Keyboard, cga, serial
		add Device Manager
		add Initrd
	0.53.2051:
		add wstring
	0.54.00:
		add pci
		add pagging get phys addr
		add rtl8139 drv ( 30 % )
		
*/
#endif