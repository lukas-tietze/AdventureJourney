#include "data/KeyValueSettings.hpp"

util::SettingCollection::SettingCollection(const std::string &name, SettingType type, const std::string &value) : name(name),
                                                                                               type(type),
                                                                                               value(value)
{
}

util::SettingCollection::SettingCollection(const std::string &name, double value) : name(name),
                                                                type(SettingType::Number),
                                                                parsedValue(value)
{
}

util::SettingCollection::SettingCollection(const util::SettingCollection &copy) : name(copy.name),
                                                    type(copy.type),
                                                    value(copy.value),
                                                    parsedValue(copy.parsedValue)
{
}

util::SettingType util::SettingCollection::GetType() const
{
    return this->type;
}

double util::SettingCollection::GetValueAsDouble() const
{
    return this->parsedValue;
}

const std::string &util::SettingCollection::GetValue() const
{
    return this->value;
}

const std::string &util::SettingCollection::GetReferenceTarget() const
{
    return this->value;
}

const std::string &util::SettingCollection::GetName() const
{
    return this->name;
}

int util::SettingCollection::ReadSettings(std::istream &in, std::unordered_map<std::string, std::string> &target)
{
    if (!in.good())
    {
        return -1;
    }

    std::string name;
    std::string value;
    bool nameRead = false;

    while (!in.eof())
    {
        char c;
        in.read(&c, 1);

        if (c == '=')
        {
            nameRead = true;
        }
        else if (c == ';')
        {
            target.insert(std::make_pair(name, value));
            name.clear();
            value.clear();
        }
        else if (nameRead)
        {
            value.push_back(c);
        }
        else
        {
            name.push_back(c);
        }
    }
}

int util::SettingCollection::ParseSettings(const std::unordered_map<std::string, std::string> &raw, std::unordered_map<std::string, SettingCollection> &target)
{
    for (const auto &kvp : raw)
    {
        char *end;
        double res = std::strtod(kvp.second.c_str(), &end);

        if (end - kvp.second.c_str() == kvp.second.length())
        {
            target.insert(std::make_pair(kvp.first, SettingCollection(kvp.first, res)));
        }
        else if (kvp.second.front() == '@' && raw.find(kvp.second.substr(1)) != raw.end())
        {
            target.insert(std::make_pair(kvp.first, SettingCollection(kvp.first, SettingType::Reference, kvp.second.substr(1))));
        }
        else
        {
            target.insert(std::make_pair(kvp.first, SettingCollection(kvp.first, SettingType::String, kvp.second)));
        }
    }

    return 0;
}