#pragma once

#include <string>

namespace util
{
namespace io
{
class Writer
{
private:
    bool active;
    bool showTime;
    std::string TimeFormat;

public:
    Writer();

    bool IsActive() const;
    bool IsOpen() const;
    void Close();
    void SetActive(bool active);
    void SetShowTime(bool showTime);

    template <class TFirst, class... TArgs>
    int Write(const std::string &format, const TFirst &first, const TArgs &... args)
    {
        auto now = std::time(nullptr);

        return this->showTime
                   ? std::fprintf(this->file, "[%s] %s", std::put_time(&now, TimeFormat), util::Format(format, first, args...).c_str())
                   : std::fprintf(this->file, "%s", util::Format(format, first, args...).c_str());
    }

    template <class TFirst, class... TArgs>
    int WriteLine(const std::string &format, const TFirst &first, const TArgs &... args)
    {
        auto res = this->Write(format, first, args...) + std::fprintf(this->file, "\n");

        std::fflush(this->file);

        return res;
    }

    template <class T>
    int Write(const T &arg)
    {
        auto now = std::time(nullptr);
        std::stringstream s;
        s << arg;

        if (this->showTime)
        {
            s << '[' << std::put_time(&now, TimeFormat) << ']';
        }

        return std::fprintf(this->file, "%s", s.str().c_str());
    }

    template <class T>
    int WriteLine(const T &arg)
    {
        auto res = this->Write(arg) + std::fprintf(this->file, "\n");

        std::fflush(this->file);

        return res;
    }

    void WriteLine();
};

extern Writer out;
extern Writer err;
} // namespace io

} // namespace util
