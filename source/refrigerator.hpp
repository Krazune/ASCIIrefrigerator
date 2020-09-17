#ifndef ASCII_REFRIGERATOR_REFRIGERATOR_HPP
#define ASCII_REFRIGERATOR_REFRIGERATOR_HPP

#include <boost/program_options.hpp>

namespace ascii_refrigerator
{
	// This could be a function, but it is not for future proofing reasons.
	class refrigerator
	{
		public:
		refrigerator();
		bool generate(int argc, char* argv[]) const;

		protected:
		void print_help_message(const boost::program_options::options_description& options) const;
		void print_usage_message() const;
		void print_version_message() const;
	};
}

#endif
