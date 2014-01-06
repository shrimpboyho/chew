#ifndef TOOLS_H
#define TOOLS_H

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

#endif /* TOOLS_H */