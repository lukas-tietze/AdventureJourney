#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <iomanip>

namespace util
{
	std::string ReadFile(const std::string& file);
	bool TryReadFile(const std::string& file, std::string& buf);
	void WriteFile(const std::string& file, const std::string& data);
	void WriteFile(const std::string& path, const std::vector<std::string>& data);
	bool TryWriteFile(const std::string& file, const std::string& data);
	bool TryWriteFile(const std::string& path, const std::vector<std::string>& data);
} // namespace util