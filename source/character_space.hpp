#ifndef ASCII_REFRIGERATOR_CHARACTER_SPACE_HPP
#define ASCII_REFRIGERATOR_CHARACTER_SPACE_HPP

#include <string>
#include <cstdlib>

namespace ascii_refrigerator
{
	class character_space
	{
		public:
		character_space(const std::string characters);

		const char& operator[](std::size_t index) const;

		std::size_t size() const;

		char at(std::size_t index) const;
		char at_reversed(std::size_t index) const;

		std::string get_characters() const;

		protected:
		const std::string characters;
	};
}

#endif
