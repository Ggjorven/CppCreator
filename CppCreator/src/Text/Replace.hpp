#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <expected>

#include "Text/Utilities.hpp"

namespace Cc::Text
{

	////////////////////////////////////////////////////////////////////////////////////
    // TextError
	////////////////////////////////////////////////////////////////////////////////////
    enum class TextError : uint8_t
    {
        None = 0, NotFound 
    };

	////////////////////////////////////////////////////////////////////////////////////
    // Replace methods
	////////////////////////////////////////////////////////////////////////////////////
    [[nodiscard]] std::expected<std::string, TextError> Replace(std::string_view input, std::string_view replace, std::string_view value) noexcept(true)
    {
        std::string result = std::string(input);

        size_t begin = result.find(replace);

        // Return on not found
        if (begin == std::string::npos)
            return std::unexpected(TextError::NotFound);

        result.erase(begin, replace.size());
        result.insert(begin, value);

        return result;
    }

    // Note: Adds the amount of indentation at the replace position to each newline specified in the value
    // Needs \t / tab character, spaces do not work.
    [[nodiscard]] std::expected<std::string, TextError> ReplaceWithIndentation(std::string_view input, std::string_view replace, std::string_view value) noexcept(true)
    {
        std::string result = std::string(input);

        size_t begin = result.find(replace);

        // Return on not found
        if (begin == std::string::npos)
            return std::unexpected(TextError::NotFound);

        result.erase(begin, replace.size());
        
        std::string indentedValue = std::string(value);
        indentedValue.reserve(value.size() * 2); // Reserve space for the additional indentation
        {
            uint32_t tabCount = 0;

            for (size_t i = begin; i > 0ull; i--)
            {
                char c = result[i];
                if (c == '\n')
                    break;
                else if (c == '\t')
                    tabCount++;
            }
            
            Text::ReplaceAll(indentedValue, "\n", std::string("\n") + std::string('\t', tabCount));
        }

        result.insert(begin, indentedValue);

        return result;
    }

}