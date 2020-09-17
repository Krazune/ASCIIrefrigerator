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
