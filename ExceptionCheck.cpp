#include "ExceptionCheck.h"
#include <sstream>


ExceptionCheck::ExceptionCheck(int line, const char* file) noexcept
	:
	line(line),
	file(file)
{}

const char* ExceptionCheck::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* ExceptionCheck::GetType() const noexcept
{
	return "Chili Exception";
}

int ExceptionCheck::GetLine() const noexcept
{
	return line;
}

const std::string& ExceptionCheck::GetFile() const noexcept
{
	return file;
}

std::string ExceptionCheck::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}