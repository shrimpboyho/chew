#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctime>
#include <dirent.h>

/* Typedef a byte */
typedef unsigned char BYTE;

/* Returns a vector of each file name in the directory specified */
std::vector <std::string> getFileNames(std::string dirname)
{
    std::vector <std::string> names;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (dirname.c_str())) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL)
        {
            names.push_back(ent->d_name);
        }
        closedir (dir);
        return names;
    }
    else
    {
        /* could not open directory */
        perror ("");
        return names;
    }
}

/* Converts an integer to a string */
inline std::string intToString(int a)
{
    std::ostringstream ss;
    ss << a;
    return ss.str();
}

/* Reads in a binary file to a byte vector */
std::vector<BYTE> slurp(const char *filename)
{
    // open the file:
    std::streampos fileSize;
    std::ifstream file(filename, std::ios::binary);

    // get its size:
    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // read the data:
    std::vector<BYTE> fileData(fileSize);
    file.read((char *) &fileData[0], fileSize);
    return fileData;
}

inline void printDivider()
{
    std::cout << "==============" << std::endl;
}

inline bool checkBitExt(std::string t)
{
    int last = t.size() - 1;
    if (t[last] == 't'
            && t[last - 1] == 'i'
            && t[last - 2] == 'b'
            && t[last - 3] == '.')
        return true;
    else
        return false;
}

inline bool containsKey(std::vector<BYTE> thing, std::vector<BYTE> key)
{
    int i;
    for (i = 0; i < key.size(); i++)
        if (key[i] != thing[i])
            return false;
    return true;
}

int main(int argc, char *argv[])
{
    /* Assemble the pieces */
    if (argc == 1)
    {
        /* Find all the bitfiles */
        std::vector <std::string> files = getFileNames("./");
        std::vector <std::string> bitfiles;
        printDivider();
        int i;
        for (i = 0; i < files.size(); i++)
        {

            std::cout << files[i] << std::endl;
            if (checkBitExt(files[i]))
                bitfiles.push_back(files[i]);
        }
        printDivider();
        printDivider();
        for (i = 0; i < bitfiles.size(); i++)
            std::cout << bitfiles[i] << std::endl;
        printDivider();

        /* Assemble all the bitfiles */
        std::vector < std::vector<BYTE> > bitfilesdata;
        for (i = 0; i < bitfiles.size(); i++)
            bitfilesdata.push_back(slurp(bitfiles[i].c_str()));
        std::vector < std::vector<BYTE> > ordered;
        int k;
        for (i = 0; i < bitfiles.size(); i++)
        {
            std::string key = "$" + intToString(i) + "$";
            const char *cstr = key.c_str();
            std::vector<BYTE> keyvec(cstr, cstr + strlen(cstr));
            for (k = 0; k < bitfilesdata.size(); k++)
            {
                std::vector<BYTE> data = bitfilesdata[k];
                if (containsKey(data, keyvec))
                {
                    data.erase(data.begin(), data.begin() + keyvec.size());
                    ordered.push_back(data);
                    break;
                }
            }
        }
        std::cout << "SIZE OF ORDERED:" << intToString(ordered[0].size() * sizeof(BYTE)) << "\n";
        std::ofstream mf("thing", std::ios::binary);
        for (i = 0; i < ordered.size(); i++)
        {
            std::vector<BYTE> current = ordered[i];
            mf.seekp(0, std::ios::end);
            mf.write((const char *) &current[0], current.size());
        }

        mf.close();

        /* Delete the bitfiles */
        for (i = 0; i < bitfiles.size(); i++)
            remove(bitfiles[i].c_str());

        return 0;
    }
    if (argc == 1)
    {
        std::cout << "Please specify the number of chunks you want to split the file into." << std::endl;
        return 0;
    }
    /* Create the pieces */
    if (argc > 2)
    {
        std::string f(argv[1]);
        std::cout << "Chewing up the file '" << f << "'" << std::endl;
        std::vector <BYTE> b = slurp(f.c_str());
        double s = b.size() * sizeof(unsigned char);
        std::cout << "Size of file: " << s << " bytes" << std::endl;
        double chunks = atoi(argv[2]);
        double bytes = (int) ceil(s / chunks);
        std::cout << "Splitting into " << chunks << " chunks, each with a size of " << bytes << " bytes" << std::endl;
        int i;
        std::vector < std::vector <BYTE> > frags;
        for (i = 0; i < b.size(); i += bytes)
        {
            if (i + bytes > s)
                bytes = s - i;
            std::vector<BYTE> piece;//(b.begin() + i, b.end() + bytes);
            std::copy ( b.begin() + i, b.begin() + i + bytes, std::back_inserter(piece) );
            std::cout << "PIECE SIZE: " << piece.size() << "\n";
            frags.push_back(piece);
        }

        srand(time(NULL));
        for (i = 0; i < frags.size(); i++)
        {
            std::string n = intToString(rand() % 1000000) + ".bit";
            std::ofstream mf(n.c_str(), std::ios::binary);
            const char *dollar = "$";
            mf.write(dollar, 1);
            mf.write(&(intToString(i)[0]), 1);
            mf.write(dollar, 1);
            mf.write((const char *) & (frags[i][0]), frags[i].size() * sizeof (BYTE));
            mf.close();
        }
    }

    return 0;
}