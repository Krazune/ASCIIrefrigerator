#include <gtest/gtest.h>

#include "../source/character_space.hpp"

TEST(CharacterSpaceTests, SubscriptOperatorTest)
{
	ascii_refrigerator::character_space characterSpace("+=#");

	ASSERT_EQ(characterSpace[0], '+');
	ASSERT_EQ(characterSpace[1], '=');
	ASSERT_EQ(characterSpace[2], '#');
}

TEST(CharacterSpaceTests, SizeTest)
{
	ascii_refrigerator::character_space characterSpace("+=#");

	ASSERT_EQ(characterSpace.size(), 3);
}

TEST(CharacterSpaceTests, AtTest)
{
	ascii_refrigerator::character_space characterSpace("+=#");

	ASSERT_EQ(characterSpace.at(0), '+');
	ASSERT_EQ(characterSpace.at(1), '=');
	ASSERT_EQ(characterSpace.at(2), '#');
}

TEST(CharacterSpaceTests, AtReversedTest)
{
	ascii_refrigerator::character_space characterSpace("+=#");

	ASSERT_EQ(characterSpace.at_reversed(0), '#');
	ASSERT_EQ(characterSpace.at_reversed(1), '=');
	ASSERT_EQ(characterSpace.at_reversed(2), '+');
}

TEST(CharacterSpaceTests, CharactersTest)
{
	ascii_refrigerator::character_space characterSpace("1234567890");

	ASSERT_STREQ(characterSpace.get_characters().c_str(), "1234567890");
}
