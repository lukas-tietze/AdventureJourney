#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <iomanip>

#include "String.hpp"

namespace util
{
	void WaitForKeyPress();
	void WaitForKeyPress(const std::string&);
	std::string ReadFile(const std::string& file);
	bool TryReadFile(const std::string& file, std::string& buf);
	void WriteFile(const std::string& file, const std::string& data);
	void WriteFile(const std::string& path, const std::vector<std::string>& data);
	bool TryWriteFile(const std::string& file, const std::string& data);
	bool TryWriteFile(const std::string& path, const std::vector<std::string>& data);

	template <class T>
	int Print(const T& arg)
	{
		std::stringstream s;
		s << arg;

		return std::printf("%s", s.str().c_str());
	}

	template <class TFirst, class... TArgs>
	int Print(const std::string& format, const TFirst& first, const TArgs& ... args)
	{
		return std::printf("%s", util::Format(format, first, args...).c_str());
	}

	template <class T>
	int PrintLine(const T& arg)
	{
		std::stringstream s;
		s << arg;

		return std::printf("%s\n", s.str().c_str());
	}

	template <class TFirst, class... TArgs>
	int PrintLine(const std::string& format, const TFirst& first, const TArgs& ... args)
	{
		return std::printf("%s\n", util::Format(format, first, args...).c_str());
	}

	class Channel
	{
	private:
		std::FILE* file;
		bool active;

		bool showTime;

		static const std::string TimeFormat;

	public:
		Channel();
		Channel(const Channel& copyFrom);
		Channel(std::FILE*);

		Channel& operator=(const Channel& copyFrom);

		bool IsActive() const;
		bool IsOpen() const;
		void Close();
		void SetActive(bool active);
		void SetShowTime(bool showTime);

		const std::FILE* GetTarget() const;
		std::FILE* GetTarget();
		void SetTarget(std::FILE*);

		template <class TFirst, class... TArgs>
		int Write(const std::string& format, const TFirst& first, const TArgs& ... args)
		{
			auto now = std::time(nullptr);

			return this->showTime
				? std::fprintf(this->file, "[%s] %s", std::put_time(&now, TimeFormat), util::Format(format, first, args...).c_str())
				: std::fprintf(this->file, "%s", util::Format(format, first, args...).c_str());
		}

		template <class TFirst, class... TArgs>
		int WriteLine(const std::string& format, const TFirst& first, const TArgs& ... args)
		{
			auto res = this->Write(format, first, args...) + std::fprintf(this->file, "\n");

			std::fflush(this->file);

			return res;
		}

		template <class T>
		int Write(const T& arg)
		{
			auto now = std::time(nullptr);
			std::stringstream s;
			s << arg;

			if (this->showTime) {
				s << '[' << std::put_time(&now, TimeFormat) << ']';
			}

			return std::fprintf(this->file, "%s", s.str().c_str());
		}

		template <class T>
		int WriteLine(const T& arg)
		{
			auto res = this->Write(arg) + std::fprintf(this->file, "\n");

			std::fflush(this->file);

			return res;
		}

		void WriteLine();
	};

	enum class CommunicationLevel
	{
		None = 0,
		Error = 1,
		Message = 2,
		Debug = 3,
	};

	class Communicator
	{
	private:
		Channel message;
		Channel debug;
		Channel error;
		Channel deadChannel;

		CommunicationLevel communicationLevel;

		Channel& SelectChannel(CommunicationLevel);

	public:
		Communicator();
		Communicator(const Communicator& copyFrom);

		Communicator& operator=(const Communicator&);

		CommunicationLevel GetCommunicationLevel() const;
		void SetCommunicationLevel(CommunicationLevel level);

		Channel& GetMessageChanell();
		Channel& GetDebugChannel();
		Channel& GetErrorChannel();

		const Channel& GetMessageChanell() const;
		const Channel& GetDebugChannel() const;
		const Channel& GetErrorChannel() const;

		template <class TFirst, class... TArgs>
		int Write(CommunicationLevel importance, const std::string& format, const TFirst& first, const TArgs& ... args)
		{
			return this->SelectChannel(importance).Write(format, first, args...);
		}

		template <class TFirst, class... TArgs>
		int WriteLine(CommunicationLevel importance, const std::string& format, const TFirst& first, const TArgs& ... args)
		{
			return this->SelectChannel(importance).WriteLine(format, first, args...);
		}

		template <class T>
		int Write(CommunicationLevel importance, const T& arg)
		{
			return this->SelectChannel(importance).Write(arg);
		}

		template <class T>
		int WriteLine(CommunicationLevel importance, const T& arg)
		{
			return this->SelectChannel(importance).WriteLine(arg);
		}

		template <class TFirst, class... TArgs>
		Communicator& Message(const std::string& format, const TFirst& first, const TArgs& ... args)
		{
			this->SelectChannel(CommunicationLevel::Message).WriteLine(format, first, args...);

			return *this;
		}

		template <class TFirst, class... TArgs>
		Communicator& Debug(const std::string& format, const TFirst& first, const TArgs& ... args)
		{
			this->SelectChannel(CommunicationLevel::Debug).WriteLine(format, first, args...);

			return *this;
		}

		template <class TFirst, class... TArgs>
		Communicator& Error(const std::string& format, const TFirst& first, const TArgs& ... args)
		{
			this->SelectChannel(CommunicationLevel::Error).WriteLine(format, first, args...);

			return *this;
		}
	};
	extern Channel out;
	extern Channel err;
	extern Channel dbg;
	extern Communicator com;
} // namespace util