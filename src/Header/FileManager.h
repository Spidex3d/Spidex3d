#pragma once
#include <imgui\imgui.h>
#include <iostream>
#include <string>
#include <filesystem> 

namespace fs = std::filesystem;

class FileManager
{
public:
	FileManager(const std::string& directory, const std::string& extension)
		: directoryPath(directory), fileExtention(extension) {}


	void findFiles();

	const std::vector<std::string>& getFileNames() const;

	size_t getFileCount() const;

private:
	
	std::string directoryPath;
	std::string fileExtention;
	std::vector<std::string> fileName;
	size_t fileCount = 0;


};

