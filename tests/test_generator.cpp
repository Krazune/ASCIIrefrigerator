/*
	MIT License

	Copyright (c) 2020 Miguel Sousa

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/
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
