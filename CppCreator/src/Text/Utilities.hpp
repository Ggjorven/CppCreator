#pragma once

#include <cstdint>
#include <string>
#include <string_view>

namespace Cc::Text
{

	////////////////////////////////////////////////////////////////////////////////////
    // Utilities
	////////////////////////////////////////////////////////////////////////////////////
    [[nodiscard]] constexpr uint32_t LineCount(std::string_view str) noexcept(true)
    {
        if (str.empty()) 
            return 0;

        uint32_t count = 0;
        for (char c : str)
        {
            if (c == '\n')
                count++;
        }

        // If the string doesn't end with a newline, count the last line.
        if (str.back() != '\n')
            count++;

        return count;
    }

    constexpr void ReplaceAll(std::string& str, std::string_view from, std::string_view to) noexcept(true)
    {
        if (from.empty()) 
            return;

        size_t startPos = 0;
        while ((startPos = str.find(from, startPos)) != std::string::npos)
        {
            str.replace(startPos, from.length(), to);
            startPos += to.length(); // Advance past the replaced portion
        }
    }

}