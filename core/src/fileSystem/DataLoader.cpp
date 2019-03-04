#include "fileSystem/DataLoader.hpp"

#include <fstream>

logic::Loader::Loader() : Loader("./dirs.cfg")
{
}

logic::Loader::Loader(const std::string &config)
{
    std::ifstream readCfg;
    std::string line;

    readCfg.open(config);

    while (readCfg.good() && readCfg.is_open() && !readCfg.eof() && std::getline(readCfg, line);)
    {
    }
}