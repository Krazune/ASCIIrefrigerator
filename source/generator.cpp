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

	void generator::generate(std::string fileName, int width, int height, std::ostream &outputStream, bool invertCharacterSpace) const
	{
		boost::gil::rgb8_image_t inputFile;

		read_image(fileName, inputFile);

		boost::gil::rgb8_image_t resizedImage(width, height);

		resize_view(boost::gil::const_view(inputFile), boost::gil::view(resizedImage));

		generate_ascii(boost::gil::const_view(resizedImage), outputStream, invertCharacterSpace);
	}

	void generator::read_image(std::string fileName, boost::gil::rgb8_image_t& destinationImage) const
	{
		boost::gil::read_and_convert_image(fileName, destinationImage, boost::gil::bmp_tag());
	}

	void generator::resize_view(boost::gil::rgb8c_view_t sourceView, boost::gil::rgb8_view_t destinationView) const
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

	void generator::generate_ascii(boost::gil::rgb8c_view_t sourceView, std::ostream &outputStream, bool invertCharacterSpace) const
	{
		for (int y = 0; y < sourceView.height(); ++y)
		{
			for (int x = 0; x < sourceView.width(); ++x)
			{
				float pixelGrayscale = get_pixel_grayscale(*(sourceView.at(x, y)));
				int characterIndex = std::round(pixelGrayscale * (float)(characterSpace.size() - 1));
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

	float generator::get_pixel_grayscale(boost::gil::rgb8c_pixel_t pixel) const
	{
		float r = (float)boost::gil::semantic_at_c<0>(pixel) / 255;
		float g = (float)boost::gil::semantic_at_c<1>(pixel) / 255;
		float b = (float)boost::gil::semantic_at_c<2>(pixel) / 255;

		return (r + r + g + g + g + b) / 6; // Higher values = brighter pixel. Aproximate formula - can be improved.
	}
}
