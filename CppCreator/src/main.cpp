#include "Core/ArgumentParser.hpp"
#include "Core/Logging.hpp"

#include "Text/Replace.hpp"
#include "Text/Utilities.hpp"

using namespace Cc;

int main(int argc, char* argv[])
{
	(void)argc; (void)argv;

	ParsedArguments args = ArgumentParser::Parse(argc, argv);

	for (const auto& error : args.m_Errors)
	{
		CC_LOG_ERROR("{}", error.String);
	}

	for (const auto& [key, value] : args.m_Arguments)
	{
		if (value.HasValue())
			CC_LOG_TRACE("{} - {}", key, value.As<std::string>().value());
		else
			CC_LOG_TRACE("{}", key);
	}

	return 0;
}