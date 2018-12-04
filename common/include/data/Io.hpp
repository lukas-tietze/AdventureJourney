#pragma once

#include <string>
#include <vector>
#include <sstream>

namespace util
{
std::string ReadFile(const std::string &file);

bool TryReadFile(const std::string &file, std::string &buf);

void WriteFile(const std::string &file, const std::string &data);

void WriteFile(const std::string &path, const std::vector<std::string &> data);

bool TryWriteFile(const std::string &file, const std::string &data);

bool TryWriteFile(const std::string &path, const std::vector<std::string &> data);

template <class T>
int PrintR(const T &obj)
{
    std::stringstream stream;

    stream << obj;

    return std::printf("%s", stream.str().c_str());
}

template <class T>
int PrintP(const T *obj)
{
    std::stringstream stream;

    obj->operator<<(stream);

    stream << std::endl;

    return std::printf("%s", stream.str().c_str());
}
} // namespace util