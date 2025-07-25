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

}