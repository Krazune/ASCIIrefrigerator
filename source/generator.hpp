#ifndef ASCII_REFRIGERATOR_GENERATOR_HPP
#define ASCII_REFRIGERATOR_GENERATOR_HPP

#include <string>
#include <iostream>

#include <boost/gil.hpp>

#include "resize_method.hpp"

namespace ascii_refrigerator
{
	class generator
	{
		public:
		generator();
		generator(std::string symbolSet);
		generator(resize_method resizeMethod);
		generator(resize_method resizeMethod, std::string symbolSet);

		void set_resize_method(resize_method newResizeMethod);
		resize_method get_resize_method() const;

		void set_symbol_set(std::string newSymbolSet);
		std::string get_symbol_set() const;

		void generate(std::string fileName, int width, int height, std::ostream& outputStream) const;

		protected:
		std::string symbolSet; // Temporary - this represents the symbols that will be used to generate the output.
		resize_method resizeMethod;

		void read_image(std::string fileName, boost::gil::rgb8_image_t& destinationImage) const;

		void resize_view(boost::gil::rgb8c_view_t sourceView, boost::gil::rgb8_view_t destinationView) const;

		void generate_ascii(boost::gil::rgb8c_view_t sourceView, std::ostream& outputStream) const;

		float get_pixel_grayscale(boost::gil::rgb8c_pixel_t pixel) const;
	};
}

#endif
