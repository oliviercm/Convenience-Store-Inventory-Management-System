#pragma once

#include <fstream>
#include <string>

class FileIO
{
public:
	FileIO();
	virtual ~FileIO();

	/**
	* parseString
	*
	* @brief Returns a substring of the passed string starting at the (skip + 1)th instance of "<delimiter>" and ending after the subsequent instance of "</delimiter>".
	*	The angle brackets and delimiters are removed from the substring.
	*	If skip is greater than the number of delimiters in the string, an empty string is returned.
	*
	* @detail Example: parseString("<txt>Foo</txt> <txt>Bar</txt>", "txt", 0) will return "Foo".
	*
	* @param str The string to parse. The string should contain "<delimiter>" and "</delimiter>" tags.
	*
	* @param delimiter The string to act as a delimiter. This function adds angle brackets around the delimiter, so they should not be included in the passed delimiter.
	*
	* @param skip The number of times to skip an instance of the delimiter.
	*
	* @return A substring of the passed string starting at the (skip + 1)th instance of "<delimiter>" and ending after the subsequent instance of "</delimiter>".
	*	The angle brackets and delimiters are removed from the substring.
	*	If skip is greater than the number of delimiters in the string, an empty string is returned.
	*/
	static std::string parseString(const std::string str, const std::string delimiter);
	static std::string parseString(const std::string str, const std::string delimiter, const int skip);
	/**
	* fileToString
	*
	* @brief Returns the contents of the file located at path as a string. If the file at path doesn't exist, returns an empty string.
	*
	* @param path The path of the file to convert contents to a string.
	*
	* @return The contents of the file from path as a string. If the file at path doesn't exist, returns an empty string.
	*/
	static std::string fileToString(std::string path);
};