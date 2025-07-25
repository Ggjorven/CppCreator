#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <expected>

namespace Cc
{

	class ArgumentParser;

	////////////////////////////////////////////////////////////////////////////////////
	// ParsedArguments
	////////////////////////////////////////////////////////////////////////////////////
	struct ParsedArguments // Note: Arguments are in format --KEY=Value or -flag
	{
	public:
		enum class ValueError : uint8_t { NoValue = 0, InvalidTypeConversion };
		struct Value
		{
		public:
			// Constructors & Destructor
			Value() = default;
			explicit Value(const std::string& value) noexcept(true);
			~Value() noexcept(true) = default;

			// Templated getters
			template<typename T>
			[[nodiscard]] std::expected<T, ValueError> As() const noexcept(true)
			{
				// Note: sizeof(T) == 0 is always false, but is only evaluated if the function is instantiated, not when the template is defined.
				static_assert(sizeof(T) == 0, "ParsedArguments: As<T>() is not supported for this type T.");
				return std::unexpected(ValueError::NoValue);
			}

			template<> [[nodiscard]] std::expected<std::string, ValueError> As<std::string>() const noexcept(true)
			{
				return m_Value;
			}

			// Getters
			[[nodiscard]] inline bool HasValue() const noexcept(true) { return !m_Value.empty(); }

		private:
			std::string m_Value;
		};

		enum class ParseErrorType : uint8_t { InvalidFormat = 0, Internal };
		struct ParseError
		{
		public:
			ParseErrorType Type;
			std::string String;

		public:
			// Constructors & Destructor
			ParseError() = default;
			explicit ParseError(ParseErrorType type) noexcept(true);
			explicit ParseError(ParseErrorType type, const std::string& string) noexcept(true);
			~ParseError() = default;
		};
	public:
		// Constructor & Destructor
		ParsedArguments() = default;
		~ParsedArguments() = default;

		// Getters
		[[nodiscard]] inline bool HasErrors() const noexcept(true) { return !m_Errors.empty(); }
		[[nodiscard]] inline const std::vector<ParseError>& Errors() const noexcept(true) { return m_Errors; }

		// TODO: Has

	//private:
	public: // TODO: make private again
		std::unordered_map<std::string, Value> m_Arguments;
		std::vector<ParseError> m_Errors;

		friend class ArgumentParser;
	};

	////////////////////////////////////////////////////////////////////////////////////
	// ArgumentParser
	////////////////////////////////////////////////////////////////////////////////////
	class ArgumentParser
	{
	public:
		// Static methods
		[[nodiscard]] static ParsedArguments Parse(int argc, char** argv) noexcept(true);
	};

}