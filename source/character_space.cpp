#include <string>
#include <cassert>
#include <cstdlib>

#include "character_space.hpp"

namespace ascii_refrigerator
{
	character_space::character_space() : characters("") {}

	character_space::character_space(const std::string characters) : characters(characters)
	{
		assert(!characters.empty());
	}

	const char& character_space::operator[](std::size_t index) const
	{
		return characters[index];
	}

	std::size_t character_space::size() const
	{
		return characters.size();
	}

	char character_space::at(std::size_t index) const
	{
		return characters.at(index);
	}

	char character_space::at_reversed(std::size_t index) const
	{
		return characters.at(characters.size() - 1 - index);
	}

	std::string character_space::get_characters() const
	{
		return characters;
	}
}
