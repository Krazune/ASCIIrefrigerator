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
#ifndef ASCII_REFRIGERATOR_CHARACTER_SPACE_HPP
#define ASCII_REFRIGERATOR_CHARACTER_SPACE_HPP

#include <string>
#include <cstdlib>

namespace ascii_refrigerator
{
	class character_space
	{
		public:
		character_space();
		character_space(const std::string characters);

		const char& operator[](std::size_t index) const;

		std::size_t size() const;

		char at(const std::size_t index) const;
		char at_reversed(const std::size_t index) const;

		std::string get_characters() const;

		protected:
		std::string characters;
	};
}

#endif
