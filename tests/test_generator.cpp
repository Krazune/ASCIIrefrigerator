#include <gtest/gtest.h>

#include "../source/generator.hpp"
#include "../source/resize_method.hpp"

TEST(GeneratorTests, ResizeMethodTest)
{
	ascii_refrigerator::generator generator;

	generator.set_resize_method(ascii_refrigerator::resize_method::bilinear);

	ASSERT_EQ(generator.get_resize_method(), ascii_refrigerator::resize_method::bilinear);
}

TEST(GeneratorTests, SymbolSetTest)
{
	ascii_refrigerator::generator generator;

	generator.set_symbol_set(" .+#");

	ASSERT_STREQ(generator.get_symbol_set().c_str(), " .+#");
}
