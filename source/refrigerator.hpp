#ifndef ASCII_REFRIGERATOR_REFRIGERATOR_HPP
#define ASCII_REFRIGERATOR_REFRIGERATOR_HPP

#include <fstream>

#include <boost/program_options.hpp>

#include "resize_method.hpp"
#include "character_space.hpp"

namespace ascii_refrigerator
{
	class refrigerator
	{
		public:
		refrigerator();
		bool generate(int argc, char* argv[]) const;

		protected:
		boost::program_options::options_description options;
		boost::program_options::options_description visibleOptions;
		boost::program_options::options_description hiddenOptions;
		boost::program_options::positional_options_description positionalOptions;

		void set_up_options();
		void set_up_visible_options();
		void set_up_hidden_options();
		void set_up_positional_options();
		void join_options();

		bool process_secondary_usages(const boost::program_options::variables_map& optionsMap) const;
		resize_method get_resize_method_argument(const boost::program_options::variables_map& optionsMap) const;
		character_space get_character_space_argument(const boost::program_options::variables_map& optionsMap) const;
		std::ofstream get_output_file_argument(const boost::program_options::variables_map& optionsMap) const;

		void print_help_message(const boost::program_options::options_description& options) const;
		void print_usage_message() const;
		void print_version_message() const;
	};
}

#endif
