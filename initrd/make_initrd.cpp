#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <string>

const char* GetFileName(const std::string& FileName)
{
    if(FileName.find_last_of("/") != std::string::npos)
        return FileName.substr(FileName.find_last_of("/")+1).c_str();
    return "";
}

struct initrd_header
{

	unsigned char magic;
	char name[64];
	unsigned int offset;
	unsigned int length;
	
	void sets(const char* _name,  unsigned int off, unsigned int len)
	{
		strcpy(name, (_name));
		offset = off;
		length = len;
		magic = 0xBE;
	}
};

int main(int argc, char **argv)
{
	
	int nheaders = (argc);
	initrd_header headers[64];
	
	printf("size of header: %d\n", (int)sizeof(initrd_header));
	unsigned int off = sizeof(initrd_header) * 64 + sizeof(int);
	
	int i ;
	for(i = 1; i < nheaders; i++)
	{
	    const char* name = GetFileName( argv[i]);
		printf("writing file %s at 0x%x\n", name, off);
		
		
		FILE *stream = fopen(argv[i], "r");
		if(stream == 0)
		{
			printf("Error: file not found: %s\n", argv[i]);
			return 1;
		}
		
		fseek(stream, 0, SEEK_END);
		headers[i].sets(name, off, ftell(stream));
		
		off += headers[i].length;
		fclose(stream);
	}
	
	FILE *wstream = fopen("./initrd.mod", "w");
	unsigned char *data = (unsigned char *)malloc(off);
	fwrite(&nheaders, sizeof(int), 1, wstream);
	fwrite(headers, sizeof(struct initrd_header), 64, wstream);
	
	for(i = 0; i < nheaders; i++)
	{
		FILE *stream = fopen(argv[i], "r");
		unsigned char *buf = (unsigned char *)malloc(headers[i].length);
		fread(buf, 1, headers[i].length, stream);
		fwrite(buf, 1, headers[i].length, wstream);
		fclose(stream);
		free(buf);
	}
	
	fclose(wstream);
	free(data);

	return 0;	
}
