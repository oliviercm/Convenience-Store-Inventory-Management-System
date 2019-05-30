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

std::string InventoryDatabase::parseString(const std::string str, const std::string delimiter) const
{
	const std::string delimitBeg = "<" + delimiter + ">";
	const std::string delimitEnd = "</" + delimiter + ">";

	//Find the positions of the first instances of the beginning and ending delimiters
	const size_t delimitBegPos = str.find(delimitBeg);
	const size_t delimitEndPos = str.find(delimitEnd);

	if (delimitBegPos != std::string::npos)
	{
		return str.substr(delimitBegPos + delimitBeg.length(), delimitEndPos - delimitBegPos - delimitBeg.length());
	}
	else
	{
		//The delimiter doesn't exist in the string, return an empty string
		return std::string();
	}
}

std::string InventoryDatabase::parseString(const std::string str, const std::string delimiter, const int skip) const
{
	const std::string delimitBeg = "<" + delimiter + ">";
	const std::string delimitEnd = "</" + delimiter + ">";

	//Set the starting position to after the (skip)th delimiter
	size_t startingPos = 0;
	for (int i = 0; i < skip; i++)
	{
		size_t delimiterPos = str.find(delimitEnd, startingPos);
		if (delimiterPos != std::string::npos)
		{
			startingPos = str.find(delimitEnd, startingPos) + delimitEnd.length();
		}
		else
		{
			//The starting position is after the last delimiter, return an empty string
			return std::string();
		}
	}

	//From the starting position, find the positions of the first instances of the beginning and ending delimiters
	const size_t delimitBegPos = str.find(delimitBeg, startingPos);
	const size_t delimitEndPos = str.find(delimitEnd, startingPos);

	//Return the substring between the beginning and ending delimiters
	return str.substr(delimitBegPos + delimitBeg.length(), delimitEndPos - delimitBegPos - delimitBeg.length());
}

/**
* fileToString
*
* @brief Returns the contents of the file located at path as a string. If the file at path doesn't exist, returns an empty string.
*
* @param path The path of the file to convert contents to a string.
*
* @return The contents of the file from path as a string. If the file at path doesn't exist, returns an empty string.
*/

std::string InventoryDatabase::fileToString(std::string path) const
{
	std::ifstream in(path);

	if (in)
	{
		std::string str;

		//Reserve space in the string to store the entire file, not strictly required
		in.seekg(0, std::ios::end);
		str.reserve(in.tellg());
		in.seekg(0, std::ios::beg);

		//Store the entire file in the string by iterating from beginning to end
		str.assign((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

		return str;
	}
	else
	{
		//If the file doesn't exist or isn't openable, return an empty string
		return std::string();
	}
}