#include "ccpch.h"
#include "ArgumentParser.hpp"

#include "Core/Logging.hpp"

#include <Nano/Nano.hpp>

namespace Cc
{

	////////////////////////////////////////////////////////////////////////////////////
	// Constructors & Destructor
	////////////////////////////////////////////////////////////////////////////////////
	ParsedArguments::Value::Value(const std::string& value) noexcept(true)
		: m_Value(value)
	{
	}

	////////////////////////////////////////////////////////////////////////////////////
	// Constructors & Destructor
	////////////////////////////////////////////////////////////////////////////////////
	ParsedArguments::ParseError::ParseError(ParseErrorType type) noexcept(true)
		: Type(type)
	{
	}

	ParsedArguments::ParseError::ParseError(ParseErrorType type, const std::string& string) noexcept(true)
		: Type(type), String(string)
	{
	}

	////////////////////////////////////////////////////////////////////////////////////
	// Static methods
	////////////////////////////////////////////////////////////////////////////////////
	ParsedArguments ArgumentParser::Parse(int argc, char** argv) noexcept(true)
	{
		ParsedArguments result = {};

		// Note: We skip the first arg/executable name
		for (int arg = 1; arg < argc; arg++)
		{
			std::string_view argStr = argv[arg];

			// First basic error handling
			if (argStr.empty()) [[unlikely]]
			{
				result.m_Errors.push_back(ParsedArguments::ParseError(ParsedArguments::ParseErrorType::Internal, "Got an argument with an empty string."));
				continue;
			}

			if ((argStr.size() == 1) || (argStr[0] != '-') || (argStr.size() == 2 && argStr[1] == '-')) // Too short, only a - or -- with nothing behind
			{
				result.m_Errors.push_back(ParsedArguments::ParseError(ParsedArguments::ParseErrorType::InvalidFormat, std::string(argStr)));
				continue;
			}

			// Parse flags -flag
			if (argStr[1] != '-') // Note: argStr[0] is guarenteed to be - if it passed the previous checks
			{
				result.m_Arguments[std::string(argStr.begin() + 1, argStr.end())] = ParsedArguments::Value();
				continue;
			}
			// Parse key/value flag --key=value
			else
			{
				std::string key;
				key.reserve(argStr.size());
				std::string value;
				value.reserve(argStr.size());

				// Note: We start at 2 to avoid the first two -'s
				bool foundEquals = false;
				for (size_t i = 2; i < argStr.size(); i++)
				{
					char c = argStr[i];

					if (c == '=')
					{
						if (!foundEquals)
							foundEquals = true;
						else
							break; // Note: Below is a check if the value is empty and will throw an InvalidFormat error.

						continue;
					}

					if (!foundEquals)
						key.push_back(c);
					else
						value.push_back(c);
				}

				if (key.empty() || value.empty())
				{
					result.m_Errors.push_back(ParsedArguments::ParseError(ParsedArguments::ParseErrorType::InvalidFormat, std::string(argStr)));
					continue;
				}

				result.m_Arguments[key] = ParsedArguments::Value(value);
				continue;
			}
		}

		return result;
	}

}