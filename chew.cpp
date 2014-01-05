#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <ctime>

inline std::string intToString(int a)
{
	std::ostringstream ss;
	ss << a;
	return ss.str();
}

inline std::string slurp (const std::string& path)
{
	std::ostringstream buf;
	std::ifstream input (path.c_str());
	buf << input.rdbuf();
	return buf.str();
}

int main(int argc, char* argv[])
{ 
	/* Assemble the pieces */
	if(argc == 1)
	{
		return 0;
	}
	if(argc == 2)
	{
		std::cout << "Please specify the number of chunks you want to split the file into" << std::endl;
		return 0;
	}
	/* Create the pieces */
	if(argc > 2)
	{
		std::string f(argv[1]);
		std::cout << "Chewing up the file '" << f << "'" << std::endl;
		std::string b = slurp(f);
		std::cout << b << std::endl;
		double s = b.size() * sizeof(char);
		std::cout << "Size of file: " << s << " bytes" << std::endl;
		double chunks = atoi(argv[2]);
		int bytes = ceil(s / chunks);
		std::cout << "Splitting into " << chunks << " chunks, each with a size of " << bytes << " bytes" << std::endl;
		int i;
		std::vector<std::string> frags;
		for(i = 0; i < b.size(); i = i + bytes)
			frags.push_back(b.substr(i, bytes)); 
		for(i = 0; i < frags.size(); i++)
			std::cout << "$" << frags[i] << "$" <<std::endl;
		srand(time(NULL));
		for(i = 0; i < frags.size(); i++)
		{
			std::string n = intToString(rand() % 1000000) + ".bit";
			std::ofstream mf(n.c_str());
			mf << "$" << i << "$" << frags[i];
			mf.close();
		}
	}

	return 0;
}