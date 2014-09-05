#include <string.h>
#include <stdio.h>
#include <iostream.hpp>
#include <iob.h>
#include <time.h>
#include <kernel/kernel.hpp>
#include <dev/bus/PciBus.hpp>

fs_node_t *shell_fsnode;

typedef struct
{
        char    Name[128];
        char    Description[512];
        int     (*Call)(int argc, char **argv);
} ShellCommand;


int ShellHelp                   (int argc, char **argv);
int ShellShutdown               (int argc, char **argv);
int ShellLsPci                  (int argc, char **argv);
int ShellPwd                    (int argc, char **argv);
int ShellCd                     (int argc, char **argv);
int ShellLs                     (int argc, char **argv);
int ShellClear                  (int argc, char **argv);
int ShellUmount                 (int argc, char **argv);
int ShellNow					(int argc, char **argv);
int ShellDev					(int argc, char **argv);

ShellCommand _commands[] =
{
       { "lspci", "List pci devices", ShellLsPci },
       { "lsdev", "List current used devices", ShellDev },
       { "help", "This help", ShellHelp },
       { "pwd", "Show current directory", ShellPwd },
       { "cd", "Chang directory", ShellCd },
       { "ls", "List directory contents", ShellLs },
       { "umount", " unmount file systems", ShellUmount },
       { "clear", "clear the terminal screen", ShellClear },
       { "shutdown", "Shutdown or reboot the system", ShellShutdown },
       { "now", "Current date time", ShellNow },
};
#define _COMMANDS_N             (sizeof(_commands) / sizeof(ShellCommand))

char string[128];
char path[1024];


void get()
{
	int p = 0;
    char ch;
    
    
    while((ch = getch()) != '\n')
    {
        if((ch == '\b') && (p == 0))
                continue;

        std::cout <<(ch);
        if(ch == '\b')
        {
                p--;
        }
        else
        {
                string[p] = ch;
                p++;
        }
    }
    string[p] = 0;
    std::cout << std::endl;
}
void drawPreamble(int ret)
{
	if(ret != 0)
	{
		std::cout << std::textcolor::Red << ret << " " 
				  << std::textcolor::White << "kshell "
				  << std::textcolor::LightBlue 
			  	  << path << std::textcolor::LightGrey << " > " ;
		ret = 0;
	}
	else
	{
		std::cout << std::textcolor::White << "kshell "
				  << std::textcolor::LightBlue 
			  	  << path << std::textcolor::LightGrey << " > " ;
	}
}
int run()
{
	if(strcmp(string, "\0"))
  	{
        for(uint32_t i = 0; i < _COMMANDS_N; i++)
        {
            if(!strcmp(string, _commands[i].Name))
            {
            		
             	return _commands[i].Call(0, NULL);
            }
        }
    }
    iodelay();
    return 255;
}
extern "C" void kernel_shell()
{
    bool exit = false;
    strcpy(path, "/");
    drawPreamble(0);
    
    shell_fsnode = fs_root;
    
    while(!exit)
    {
       	get();
        drawPreamble(run());
    }
}
int ShellEcho (int argc, char **argv)
{
	return 0;
}



int ShellUmount(int argc, char **argv)
{
        return 0;
}

int ShellCd(int argc, char **argv)
{
	shell_fsnode = finddir_fs(shell_fsnode, "dev");
	strcat(path, shell_fsnode->name);
    return 0;
}


int ShellLs(int argc, char **argv)
{
	int i = 0;
	struct dirent *node = 0;
	while ( (node = readdir_fs(shell_fsnode, i)) != 0)
	{
		fs_node_t *fsnode = finddir_fs(shell_fsnode, node->name);

		if ((fsnode->flags&0x7) == FS_DIRECTORY)
		{
			if(strcmp(node->name, ""))
				std::cout << std::textcolor::LightBlue << node->name << std::textcolor::LightGrey << " ";
		}
		else 
		{
			if(strcmp(node->name, ""))
				std::cout << std::textcolor::Green << node->name << std::textcolor::LightGrey << " ";
		}
		i++;
	}
	std::cout << std::endl;
	return 0;
}


int ShellPwd(int argc, char **argv)
{
        printf("%s\n", path);
        return 0;
}
int ShellClear(int argc, char **argv)
{
        cls();
        
	
        return 0;
}


int ShellHelp(int argc, char **argv)
{
        unsigned i;

        for(i = 0; i < _COMMANDS_N; i++)
        {
        	std::cout << std::tab << "-> "<< _commands[i].Name << " - " << _commands[i].Description << std::endl;
        }

        return 0;
}
int ShellLsPci(int argc, char **argv)
{
	((dev::bus::pci_bus*)(Kernel::Instance().GetDriver("pci0")))->Dump();
	return 0;
}

int ShellShutdown(int argc, char **argv)
{
        
        return 0;
}
const char *mon_name[] = 
{
	"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun",
	"Dec", "Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};
int ShellNow(int argc, char **argv)
{
	tm* timeptr= localtime(NULL);
	
	std::cout << std::tab << mon_name[timeptr->tm_mon + 7];

	int day = timeptr->tm_mday;
	int hour = timeptr->tm_hour;
	int min = timeptr->tm_min;
	int sec = timeptr->tm_sec;
	
	std::cout << " " << (day < 10 ? "0" : "") << day ;
	std::cout << " " << (hour < 10 ? "0" : "") << hour;
	std::cout << ":" << (min < 10 ? "0" : "") << min;
	std::cout << ":" << (sec < 10 ? "0" : "") << sec;
	
	std::cout << " " << timeptr->tm_year << std::endl;
	
	return 0;
}
int ShellDev					(int argc, char **argv)
{
	dev::listDevices *drv = Kernel::Instance().GetDevices()->getList();
	
	for(dev::listDevices::iterator i = drv->begin() ; i != drv->end(); i++)
	{
		std::cout << "\t" << (*i)->getName() << " : " << (*i)->getDriver()->getName() << std::endl;
	}
	
	return 0;
}