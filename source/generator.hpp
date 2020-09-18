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
#ifndef ASCII_REFRIGERATOR_GENERATOR_HPP
#define ASCII_REFRIGERATOR_GENERATOR_HPP

#include <string>
#include <ostream>

#include <boost/gil.hpp>

#include "character_space.hpp"
#include "resize_method.hpp"

namespace ascii_refrigerator
{
	class generator
	{
		public:
		const static character_space bwSpace;
		const static character_space gradient9Space;

		generator();
		generator(const character_space characterSpace);
		generator(const resize_method resizeMethod);
		generator(const resize_method resizeMethod, const character_space characterSpace);

		resize_method get_resize_method() const;

		character_space get_character_space() const;

		void generate(const std::string fileName, int width, int height, std::ostream& outputStream, const bool invertCharacterSpace = false) const;
		void generate(const std::string fileName, std::ostream& outputStream, const bool invertCharacterSpace = false) const;

		protected:
		const resize_method resizeMethod;
		const character_space characterSpace;

		void resize_view(boost::gil::gray8c_view_t sourceView, boost::gil::gray8_view_t destinationView) const;

		void generate_ascii(boost::gil::gray8c_view_t sourceView, std::ostream& outputStream, bool invertCharacterSpace = false) const;
	};
}

#endif
