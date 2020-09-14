#include <ostream>

#include <gtest/gtest.h>

#include "../source/generator.hpp"
#include "../source/resize_method.hpp"

TEST(GeneratorTests, ResizeMethodTest)
{
	ascii_refrigerator::generator generator(ascii_refrigerator::resize_method::bilinear);

	ASSERT_EQ(generator.get_resize_method(), ascii_refrigerator::resize_method::bilinear);
}

TEST(GeneratorTests, CharacterSpaceTest)
{
	ascii_refrigerator::generator generator(ascii_refrigerator::character_space(" .+#"));

	ASSERT_STREQ(generator.get_character_space().get_characters().c_str(), " .+#");
}

TEST(GeneratorTests, Read1BitTest)
{
	std::stringstream outputStream;
	ascii_refrigerator::generator generator(ascii_refrigerator::character_space(" #"));

	generator.generate("rgb1.bmp", outputStream);

	ASSERT_STREQ(outputStream.str().c_str(), " # \n# #\n # \n");
}

TEST(GeneratorTests, Read4BitTest)
{
	std::stringstream outputStream;
	ascii_refrigerator::generator generator(ascii_refrigerator::character_space(" #"));

	generator.generate("rgb4.bmp", outputStream);

	ASSERT_STREQ(outputStream.str().c_str(), " # \n# #\n # \n");
}

TEST(GeneratorTests, Read8BitTest)
{
	std::stringstream outputStream;
	ascii_refrigerator::generator generator(ascii_refrigerator::character_space(" #"));

	generator.generate("rgb8.bmp", outputStream);

	ASSERT_STREQ(outputStream.str().c_str(), " # \n# #\n # \n");
}

TEST(GeneratorTests, Read8BitAlphaTest)
{
	std::stringstream outputStream;
	ascii_refrigerator::generator generator(ascii_refrigerator::character_space(" #"));

	generator.generate("rgba8.bmp", outputStream);

	ASSERT_STREQ(outputStream.str().c_str(), " # \n# #\n # \n");
}
