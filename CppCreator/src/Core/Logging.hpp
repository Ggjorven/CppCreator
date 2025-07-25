#pragma once

#include <Nano/Nano.hpp>

namespace Cc
{

	////////////////////////////////////////////////////////////////////////////////////
	// Logging & Asserting macros
	////////////////////////////////////////////////////////////////////////////////////
    #ifndef CC_CONFIG_DIST
        #define CC_LOG_TRACE(fmt, ...)       ::Nano::Log::PrintLvl<::Nano::Log::Level::Trace>(fmt __VA_OPT__(,) __VA_ARGS__)
        #define CC_LOG_INFO(fmt, ...)        ::Nano::Log::PrintLvl<::Nano::Log::Level::Info>(fmt __VA_OPT__(,) __VA_ARGS__)
        #define CC_LOG_WARN(fmt, ...)        ::Nano::Log::PrintLvl<::Nano::Log::Level::Warn>(fmt __VA_OPT__(,) __VA_ARGS__)
        #define CC_LOG_ERROR(fmt, ...)       ::Nano::Log::PrintLvl<::Nano::Log::Level::Error>(fmt __VA_OPT__(,) __VA_ARGS__)
        #define CC_LOG_FATAL(fmt, ...)       ::Nano::Log::PrintLvl<::Nano::Log::Level::Fatal>(fmt __VA_OPT__(,) __VA_ARGS__)

        #define CC_ASSERT(x, fmt, ...)          \
                    do                          \
                    {                           \
                        if (!(x))               \
                        {                       \
                            CC_LOG_FATAL("Assertion failed: ({0}), {1}.", #x, ::Nano::Text::Format(fmt __VA_OPT__(,) __VA_ARGS__)); \
                            NANO_DEBUG_BREAK(); \
                        }                       \
                    } while (false)

        #define CC_VERIFY(x, fmt, ...)          \
                    do                          \
                    {                           \
                        if (!(x))               \
                        {                       \
                            CC_LOG_FATAL("Verify failed: ({0}), {1}.", #x, ::Nano::Text::Format(fmt __VA_OPT__(,) __VA_ARGS__)); \
                        }                       \
                    } while (false)

        #define CC_UNREACHABLE() CC_ASSERT(false, "Unreachable")

    #else
        #define CC_LOG_TRACE(fmt, ...) 
        #define CC_LOG_INFO(fmt, ...) 
        #define CC_LOG_WARN(fmt, ...) 
        #define CC_LOG_ERROR(fmt, ...) 
        #define CC_LOG_FATAL(fmt, ...) 

        #define CC_ASSERT(x, fmt, ...)
        #define CC_VERIFY(x, fmt, ...)
        #define CC_UNREACHABLE()
    #endif

}