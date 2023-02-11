#ifndef COMPILE_SHADERS_H_
#define COMPILE_SHADERS_H_
#include <string>
#include <fstream>

inline std::string CompileShader(const char* filepath)
{
    std::ifstream file;
    file.open(filepath);
    std::string line;
    std::string document;
    while(std::getline(file,line))
    {
        document+=line+"\n";
        line="";
    }
    return document; 
}





#endif