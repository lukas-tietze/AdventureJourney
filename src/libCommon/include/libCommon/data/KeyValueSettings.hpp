#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

namespace util
{
enum class SettingType
{
    Number,
    String,
    Reference,
};

class SettingCollection
{
  private:
    SettingType type;
    std::string name;
    std::string value;
    double parsedValue;

  public:
    SettingCollection(const SettingCollection &);

    SettingCollection(const std::string &, SettingType, const std::string &);
    SettingCollection(const std::string &, double);

    SettingType GetType() const;
    double GetValueAsDouble() const;
    const std::string &GetValue() const;
    const std::string &GetReferenceTarget() const;
    const std::string &GetName() const;
    
    static int ReadSettings(std::istream &in, std::unordered_map<std::string, std::string> &);
    static int ParseSettings(const std::unordered_map<std::string, std::string> &, std::unordered_map<std::string, SettingCollection> &);
};
} // namespace util