#pragma once

#include <string>
#include <vector>
#include <sstream>

namespace util
{
std::string read_file(const std::string &file);

bool try_read_file(const std::string &file, std::string &buf);

void write_file(const std::string &file, const std::string &data);

void write_file(const std::string &path, const std::vector<std::string &> data);

bool try_write_file(const std::string &file, const std::string &data);

bool try_write_file(const std::string &path, const std::vector<std::string &> data);

template <class T>
int printr(const T &obj)
{
    std::stringstream stream;

    stream << obj << std::endl;

    return std::printf("%s", stream.str().c_str());
}

template <class T>
int printp(const T *obj)
{
    std::stringstream stream;

    obj->operator<<(stream);

    stream << std::endl;

    return std::printf("%s", stream.str().c_str());
}
} // namespace util