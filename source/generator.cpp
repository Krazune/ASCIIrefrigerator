#include <string>

#include <boost/gil.hpp>
#include <boost/gil/extension/io/bmp.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>

#include "generator.hpp"
#include "resize_method.hpp"

namespace ascii_refrigerator
{
	generator::generator() : resizeMethod(resize_method::nearest_neighbor), symbolSet(" #") {}
	generator::generator(std::string symbolSet) : resizeMethod(resize_method::nearest_neighbor), symbolSet(symbolSet) {}
	generator::generator(resize_method resizeMethod) : resizeMethod(resizeMethod), symbolSet(" #") {}
	generator::generator(resize_method resizeMethod, std::string symbolSet) : resizeMethod(resizeMethod), symbolSet(symbolSet) {}

	void generator::set_resize_method(resize_method newResizeMethod)
	{
		resizeMethod = newResizeMethod;
	}

	resize_method generator::get_resize_method() const
	{
		return resizeMethod;
	}

	void generator::set_symbol_set(std::string newSymbolSet)
	{
		symbolSet = newSymbolSet;
	}

	std::string generator::get_symbol_set() const
	{
		return symbolSet;
	}

	void generator::generate(std::string fileName, int width, int height, std::ostream &outputStream) const
	{
		boost::gil::rgb8_image_t inputFile;

		read_image(fileName, inputFile);

		boost::gil::rgb8_image_t resizedImage(width, height);

		resize_view(boost::gil::const_view(inputFile), boost::gil::view(resizedImage));

		generate_ascii(boost::gil::const_view(resizedImage), outputStream);
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

	void generator::generate_ascii(boost::gil::rgb8c_view_t sourceView, std::ostream &outputStream) const
	{
		for (int y = 0; y < sourceView.height(); ++y)
		{
			for (int x = 0; x < sourceView.width(); ++x)
			{
				float pixelGrayscale = get_pixel_grayscale(*(sourceView.at(x, y)));

				outputStream << symbolSet[pixelGrayscale * (symbolSet.size() - 1)];
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
