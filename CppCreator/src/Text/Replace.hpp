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
    [[nodiscard]] inline std::expected<std::string, TextError> Replace(std::string_view input, std::string_view from, std::string_view to) noexcept(true)
    {
        std::string result = std::string(input);

        size_t begin = result.find(from);

        // Return on not found
        if (begin == std::string::npos)
            return std::unexpected(TextError::NotFound);

        result.erase(begin, from.size());
        result.insert(begin, to);

        return result;
    }

    [[nodiscard]] inline std::string ReplaceAll(std::string_view input, std::string_view from, std::string_view to) noexcept(true)
    {
        std::string result = std::string(input);

        size_t startPos = 0;
        while ((startPos = result.find(from, startPos)) != std::string::npos)
        {
            result.replace(startPos, from.length(), to);
            startPos += to.length(); // Advance past the replaced portion
        }

        return result;
    }

    // Note: Adds the amount of indentation at the replace position to each newline specified in the value
    // Needs \t / tab character, spaces do not work.
    [[nodiscard]] inline std::expected<std::string, TextError> ReplaceWithIndentation(std::string_view input, std::string_view from, std::string_view to) noexcept(true)
    {
        std::string result = std::string(input);

        size_t begin = result.find(from);

        // Return on not found
        if (begin == std::string::npos)
            return std::unexpected(TextError::NotFound);

        result.erase(begin, from.size());
        
        std::string indentedValue = std::string(to);
        indentedValue.reserve(to.size() * 2); // Reserve space for the additional indentation
        {
            uint32_t tabCount = 0;

            for (size_t i = begin - 1; i <= begin; i--)
            {
                char c = result[i];
                if (c == '\n')
                    break;
                else if (c == '\t')
                    tabCount++;
            }
            
            indentedValue = Text::ReplaceAll(indentedValue, "\n", std::string("\n") + std::string(tabCount, '\t'));
        }

        result.insert(begin, indentedValue);

        return result;
    }

}