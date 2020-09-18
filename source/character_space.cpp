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

	char character_space::at(const std::size_t index) const
	{
		return characters.at(index);
	}

	char character_space::at_reversed(const std::size_t index) const
	{
		return characters.at(characters.size() - 1 - index);
	}

	std::string character_space::get_characters() const
	{
		return characters;
	}
}
