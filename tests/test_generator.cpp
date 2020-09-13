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
