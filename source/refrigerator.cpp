#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include <boost/program_options.hpp>

#include "refrigerator.hpp"
#include "generator.hpp"

namespace ascii_refrigerator
{
	refrigerator::refrigerator() {}

	bool refrigerator::generate(int argc, char **argv) const
	{
		boost::program_options::options_description visibleOptions("Options");
		int width;
		int height;

		visibleOptions.add_options()
				("output-file,o", boost::program_options::value<std::string>(), "output file name")
				("width,w", boost::program_options::value<int>(&width)->default_value(0), "output width")
				("height,h", boost::program_options::value<int>(&height)->default_value(0), "output height")
				("resize-method", boost::program_options::value<std::string>()->default_value("nearest-neighbor"), "resize sampling method (nearest-neighbor, or bilinear)")
				("character-space", boost::program_options::value<std::string>(), "predefined character space (gradient9, or bw)")
				("custom-character-space", boost::program_options::value<std::string>(), "custom character space string")
				("invert", "invert output character space");

		boost::program_options::options_description hiddenOptions("Hidden");

		hiddenOptions.add_options()
				("help", "print help message")
				("version", "print version information")
				("input-file", boost::program_options::value<std::string>()->required(), "input file");

		boost::program_options::positional_options_description positionalOptions;

		positionalOptions.add("input-file", 1);

		boost::program_options::options_description options;

		options.add(visibleOptions).add(hiddenOptions);

		boost::program_options::variables_map optionsMap;

		// Throws exceptions.
		boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(options).positional(positionalOptions).run(), optionsMap);

		if (optionsMap.count("help") > 0)
		{
			print_help_message(visibleOptions);

			return true;
		}

		if (optionsMap.count("version") > 0)
		{
			print_version_message();

			return true;
		}

		// Throws exceptions.
		boost::program_options::notify(optionsMap);

		std::string inputFileName = optionsMap["input-file"].as<std::string>();

		resize_method resizeMethod;

		if (optionsMap["resize-method"].as<std::string>() == "nearest-neighbor")
		{
			resizeMethod = resize_method::nearest_neighbor;
		}
		else if (optionsMap["resize-method"].as<std::string>() == "bilinear")
		{
			resizeMethod = resize_method::bilinear;
		}
		else
		{
			boost::program_options::invalid_option_value error(optionsMap["resize-method"].as<std::string>());

			error.set_option_name("--resize-method");

			throw error;
		}

		character_space characterSpace = generator::gradient9Space;

		if (optionsMap.count("character-space") > 0)
		{
			if (optionsMap.count("custom-character-space") > 0)
			{
				// Throw some error.
				throw;
			}

			if (optionsMap["character-space"].as<std::string>() == "gradient9")
			{
			}
			else if (optionsMap["character-space"].as<std::string>() == "bw")
			{
				characterSpace = generator::bwSpace;
			}
			else
			{
				boost::program_options::invalid_option_value error(optionsMap["character-space"].as<std::string>());

				error.set_option_name("--character-space");

				throw error;
			}
		}

		if (optionsMap.count("custom-character-space") > 0)
		{
			if (optionsMap["custom-character-space"].as<std::string>() == "")
			{
				boost::program_options::invalid_option_value error(optionsMap["custom-character-space"].as<std::string>());

				error.set_option_name("--custom-character-space");

				throw error;
			}

			characterSpace = character_space(optionsMap["custom-character-space"].as<std::string>());
		}

		generator generator(resizeMethod, characterSpace);

		std::ofstream outputFileStream;

		if (optionsMap.count("output-file") > 0)
		{
			// Throws exceptions.
			outputFileStream.open(optionsMap["output-file"].as<std::string>(), std::ofstream::out | std::ofstream::app);
		}

		bool invert = optionsMap.count("invert") > 0;

		// Throws exceptions - close output file.
		generator.generate(inputFileName, width, height, (outputFileStream.is_open()) ? outputFileStream : std::cout, invert); // Temporary ternary.

		return true;
	}

	void refrigerator::print_version_message() const
	{
		std::cout << "ASCIIrefrigerator\nVersion: 1.0.0\n";
	}

	void refrigerator::print_usage_message() const
	{
		std::cout << "ASCIIrefrigerator\n";
		std::cout << "Usage:\n";
		std::cout << "  asciirefrigerator --help\n";
		std::cout << "  asciirefrigerator --version\n";
		std::cout << "  asciirefrigerator <input file> [options]\n\n";
	}

	void refrigerator::print_help_message(const boost::program_options::options_description& options) const
	{
		print_usage_message();

		std::cout << options << "\n";
	}
}
