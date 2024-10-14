#include <iostream>
#include <vector>
#include <string>

#include "FileReader.hpp"

int main() {

	std::vector<std::string> file_contents = readFile("Test");
	return 0;
}