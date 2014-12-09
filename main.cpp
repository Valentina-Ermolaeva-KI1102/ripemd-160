#include <iostream>
#include "rip.h"

int main(int argc, char *argv[])
{
	char in_name[512], out_name[512];
	if (argc > 2)
	{
		strcpy(in_name, argv[1]);
		strcpy(out_name, argv[2]);
	}
	else if (argc == 2)
	{
		if(!strcmp("-h", argv[1]) || !strcmp("-H", argv[1]) || !strcmp("-help", argv[1]))
		{
			std::cout<<"this is program are created for calculate hash md5\nExample of using:\n md5.exe input_file_neme out_file_name\n md5.exe input_file_name\n md5.exe\n";
			return 1;
		}
		strcpy(in_name, argv[1]);
		std::cout<<"Enter the output file: ";
		std::cin>>out_name;
	}
	else 
	{
		std::cout<<"Enter the input file: ";
		std::cin>>in_name;
		std::cout<<"Enter the output file: ";
		std::cin>>out_name;
	}
	std::ifstream in(in_name, std::ios_base::in);
	if(!in)	return 1;
	std::ofstream out(out_name, std::ios_base::out);
	unsigned char *RIPEMD = ripemd(in);
	for(unsigned char *ptr = RIPEMD, i = 0; i < 20; ptr++, i++)
		out<<std::hex<<unsigned int(*ptr)<<" ";
	in.close();
	out.close();
	return 0;
}
