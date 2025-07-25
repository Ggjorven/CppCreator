#include "Core/Logging.hpp"

#include "Text/Replace.hpp"

using namespace Cc;

int main(int argc, char* argv[])
{
	(void)argc; (void)argv;

	CC_LOG_INFO("Hello, world!");
	CC_LOG_INFO("Replaced text: \n{0}", Text::Replace("Hi, CC_NAME_IDENTIFIER, welcome!", "CC_NAME_IDENTIFIER", "Jorben").value());
	CC_LOG_INFO("Replaced text: \n{0}", 
		Text::ReplaceWithIndentation("Hi, "
			"\n\tCC_NAME_IDENTIFIER"
			"\nwelcome!",
			
			"CC_NAME_IDENTIFIER", "Jorben,\nMore").value()
	);

	CC_LOG_INFO("\n{0}", Text::ReplaceWithIndentation("\tCC_NAME_IDENTIFIER", "CC_NAME_IDENTIFIER", "Test\nTest2\nTest3").value());

	return 0;
}