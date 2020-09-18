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

		void process_program_options_exceptions() const;
		void process_generator_exceptions() const;
		void process_output_file_exception() const;
	};
}

#endif
