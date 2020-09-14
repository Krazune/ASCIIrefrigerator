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
		generator(character_space characterSpace);
		generator(resize_method resizeMethod);
		generator(resize_method resizeMethod, character_space characterSpace);

		resize_method get_resize_method() const;

		character_space get_character_space() const;

		void generate(std::string fileName, int width, int height, std::ostream& outputStream, bool invertCharacterSpace = false) const;
		void generate(std::string fileName, std::ostream& outputStream, bool invertCharacterSpace = false) const;

		protected:
		const character_space characterSpace;
		const resize_method resizeMethod;

		void resize_view(boost::gil::gray8c_view_t sourceView, boost::gil::gray8_view_t destinationView) const;

		void generate_ascii(boost::gil::gray8c_view_t sourceView, std::ostream& outputStream, bool invertCharacterSpace = false) const;
	};
}

#endif
