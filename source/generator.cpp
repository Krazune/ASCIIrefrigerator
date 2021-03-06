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
#include <ostream>

#include <boost/gil.hpp>
#include <boost/gil/extension/io/bmp.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>

#include "generator.hpp"
#include "resize_method.hpp"

namespace ascii_refrigerator
{
	const character_space generator::bwSpace(" @");
	const character_space generator::gradient9Space(" .:;*+%#@");

	generator::generator() : resizeMethod(resize_method::nearest_neighbor), characterSpace(character_space(" #")) {}
	generator::generator(character_space characterSpace) : resizeMethod(resize_method::nearest_neighbor), characterSpace(characterSpace) {}
	generator::generator(resize_method resizeMethod) : resizeMethod(resizeMethod), characterSpace(character_space(" #")) {}
	generator::generator(resize_method resizeMethod, character_space characterSpace) : resizeMethod(resizeMethod), characterSpace(characterSpace) {}

	resize_method generator::get_resize_method() const
	{
		return resizeMethod;
	}

	character_space generator::get_character_space() const
	{
		return characterSpace;
	}

	void generator::generate(const std::string fileName, int width, int height, std::ostream &outputStream, const bool invertCharacterSpace) const
	{
		boost::gil::gray8_image_t inputFile;

		boost::gil::read_and_convert_image(fileName, inputFile, boost::gil::bmp_tag());

		if (width == 0)
		{
			width = inputFile.width();
		}

		if (height == 0)
		{
			height = inputFile.height();
		}

		if (width != inputFile.width() || height != inputFile.width())
		{
			boost::gil::gray8_image_t resizedImage(width, height);

			resize_view(boost::gil::const_view(inputFile), boost::gil::view(resizedImage));

			inputFile = resizedImage;
		}

		generate_ascii(boost::gil::const_view(inputFile), outputStream, invertCharacterSpace);
	}

	void generator::generate(const std::string fileName, std::ostream& outputStream, const bool invertCharacterSpace) const
	{
		generate(fileName, 0, 0, outputStream, invertCharacterSpace);
	}

	void generator::resize_view(boost::gil::gray8c_view_t sourceView, boost::gil::gray8_view_t destinationView) const
	{
		switch (resizeMethod)
		{
			case resize_method::nearest_neighbor:
			boost::gil::resize_view(sourceView, destinationView, boost::gil::nearest_neighbor_sampler());
			break;

			case resize_method::bilinear:
			boost::gil::resize_view(sourceView, destinationView, boost::gil::bilinear_sampler());
			break;
		}
	}

	void generator::generate_ascii(boost::gil::gray8c_view_t sourceView, std::ostream &outputStream, bool invertCharacterSpace) const
	{
		for (int y = 0; y < sourceView.height(); ++y)
		{
			for (int x = 0; x < sourceView.width(); ++x)
			{
				float grayValue = *sourceView.at(x, y) / 255.0f;
				std::size_t characterIndex = std::round(grayValue * static_cast<float>(characterSpace.size() - 1));
				char outputCharacter;

				if (invertCharacterSpace)
				{
					outputCharacter = characterSpace.at_reversed(characterIndex);
				}
				else
				{
					outputCharacter = characterSpace.at(characterIndex);
				}

				outputStream << outputCharacter;
			}

			outputStream << '\n';
		}
	}
}
