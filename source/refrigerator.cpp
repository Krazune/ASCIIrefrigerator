#include <string>
#include <fstream>
#include <iostream>

#include <boost/program_options.hpp>

#include "refrigerator.hpp"
#include "generator.hpp"
#include "resize_method.hpp"
#include "character_space.hpp"

namespace ascii_refrigerator
{
	refrigerator::refrigerator() : visibleOptions("Options"), hiddenOptions("Hidden")
	{
		set_up_options();
	}

	bool refrigerator::generate(int argc, char **argv) const
	{
		boost::program_options::variables_map optionsMap;
		boost::program_options::parsed_options parsedOptions = boost::program_options::command_line_parser(argc, argv).options(options).positional(positionalOptions).run(); // Throws exceptions.

		boost::program_options::store(parsedOptions, optionsMap); // Throws exceptions.

		if (process_secondary_usages(optionsMap))
		{
			return true;
		}

		boost::program_options::notify(optionsMap); // Throws exceptions.

		resize_method resizeMethod = get_resize_method_argument(optionsMap); // Throws exceptions.
		character_space characterSpace = get_character_space_argument(optionsMap); // Throws exceptions

		generator generator(resizeMethod, characterSpace);

		std::string inputFileName = optionsMap["input-file"].as<std::string>();
		int width = optionsMap["width"].as<int>();
		int height = optionsMap["height"].as<int>();
		std::ofstream outputFileStream = get_output_file_argument(optionsMap);  // Throws exceptions.
		std::ostream& outputStream = (outputFileStream.is_open()) ? outputFileStream : std::cout;
		bool invert = optionsMap.count("invert") > 0;

		generator.generate(inputFileName, width, height, outputStream, invert); // Throws exceptions.

		if (outputFileStream.is_open())
		{
			outputFileStream.close();
		}

		return true;
	}

	void refrigerator::set_up_options()
	{
		set_up_visible_options();
		set_up_hidden_options();
		set_up_positional_options();
		join_options();
	}

	void refrigerator::set_up_visible_options()
	{
		visibleOptions.add_options()
				("output-file,o", boost::program_options::value<std::string>(), "output file name")
				("width,w", boost::program_options::value<int>()->default_value(0), "output width")
				("height,h", boost::program_options::value<int>()->default_value(0), "output height")
				("resize-method", boost::program_options::value<std::string>()->default_value("nearest-neighbor"), "resize sampling method (nearest-neighbor, or bilinear)")
				("character-space", boost::program_options::value<std::string>(), "predefined character space (gradient9, or bw)")
				("custom-character-space", boost::program_options::value<std::string>(), "custom character space string")
				("invert", "invert output character space");
	}

	void refrigerator::set_up_hidden_options()
	{
		hiddenOptions.add_options()
				("help", "print help message")
				("version", "print version information")
				("input-file", boost::program_options::value<std::string>()->required(), "input file");
	}

	void refrigerator::set_up_positional_options()
	{
		positionalOptions.add("input-file", 1);
	}

	void refrigerator::join_options()
	{
		options.add(visibleOptions).add(hiddenOptions);
	}

	bool refrigerator::process_secondary_usages(const boost::program_options::variables_map& optionsMap) const
	{
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

		return false;
	}

	resize_method refrigerator::get_resize_method_argument(const boost::program_options::variables_map &optionsMap) const
	{
		std::string resizeMethodString = optionsMap["resize-method"].as<std::string>();

		if (resizeMethodString == "nearest-neighbor")
		{
			return resize_method::nearest_neighbor;
		}
		else if (resizeMethodString == "bilinear")
		{
			return resize_method::bilinear;
		}

		boost::program_options::invalid_option_value error(optionsMap["resize-method"].as<std::string>());

		error.set_option_name("--resize-method");

		throw error;
	}

	character_space refrigerator::get_character_space_argument(const boost::program_options::variables_map &optionsMap) const
	{
		if (optionsMap.count("character-space") > 0)
		{
			if (optionsMap.count("custom-character-space") > 0)
			{
				// Not the best exception type.
				boost::program_options::multiple_occurrences error;

				error.set_option_name("character-space");

				throw error;
			}

			std::string characterSpaceString = optionsMap["character-space"].as<std::string>();

			if (characterSpaceString == "gradient9")
			{
				return generator::gradient9Space;
			}
			else if (characterSpaceString == "bw")
			{
				return generator::bwSpace;
			}

			boost::program_options::invalid_option_value error(optionsMap["character-space"].as<std::string>());

			error.set_option_name("--character-space");

			throw error;
		}

		if (optionsMap.count("custom-character-space") > 0)
		{
			std::string customSpaceString = optionsMap["custom-character-space"].as<std::string>();

			if (customSpaceString.empty())
			{
				boost::program_options::invalid_option_value error(optionsMap["custom-character-space"].as<std::string>());

				error.set_option_name("--custom-character-space");

				throw error;
			}

			return character_space(customSpaceString);
		}

		return generator::gradient9Space;
	}

	std::ofstream refrigerator::get_output_file_argument(const boost::program_options::variables_map& optionsMap) const
	{
		std::ofstream outputFileStream;

		if (optionsMap.count("output-file") > 0)
		{
			outputFileStream.open(optionsMap["output-file"].as<std::string>(), std::ofstream::out | std::ofstream::app);
		}

		return outputFileStream;
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
