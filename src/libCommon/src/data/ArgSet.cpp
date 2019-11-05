#include <cstdlib>
#include <string>
#include <cstdio>
#include <vector>

#include "libCommon/data/ArgSet.hpp"

//TODO: Hier gibts auch noch einiges neu zu implementieren!

util::ArgSet::ArgSet(int argc, char** argv)
{
	this->items.reserve(argc);

	for (auto i = 0; i < argc; i++)
	{
		this->items.push_back(std::string(argv[i]));
	}
}

bool util::ArgSet::LoadNext() {
	return false;
}

std::string util::ArgSet::Next()
{
	if (this->LoadNext())
	{
		return std::string(this->Current());
	}
}

bool util::ArgSet::HasNext() const
{
	return this->readPos < this->items.size();
}

util::ArgSet::operator bool() const
{
	return this->HasNext();
}

const std::string& util::ArgSet::Current()
{
	return this->items[this->readPos];
}

bool util::ArgSet::Peek(std::string& target) const
{
	if (this->HasNext()) {
		target = this->items[this->readPos + 1];

		return true;
	}

	return false;
}

std::vector<std::string>::iterator util::ArgSet::begin()
{
	return this->items.begin();
}

std::vector<std::string>::const_iterator util::ArgSet::cbegin()
{
	return this->items.cbegin();
}

std::vector<std::string>::reverse_iterator util::ArgSet::rbegin()
{
	return this->items.rbegin();
}

std::vector<std::string>::const_reverse_iterator util::ArgSet::crbegin()
{
	return this->items.crbegin();
}

std::vector<std::string>::iterator util::ArgSet::end()
{
	return this->items.end();
}

std::vector<std::string>::const_iterator util::ArgSet::cend()
{
	return this->items.cend();
}

std::vector<std::string>::reverse_iterator util::ArgSet::rend()
{
	return this->items.rend();
}

std::vector<std::string>::const_reverse_iterator util::ArgSet::crend()
{
	return this->items.crend();
}
