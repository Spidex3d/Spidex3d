#include "Header/FileManager.h"


void FileManager::findFiles()
{
	for (const auto& entry : fs::directory_iterator(directoryPath)) {
		if (entry.is_regular_file() && entry.path().extension() == fileExtention) {
			fileName.push_back(entry.path().filename().string());
		}
	}
	fileCount = fileName.size();
}

const std::vector<std::string>& FileManager::getFileNames() const
{
	// TODO: insert return statement here
	return fileName;
}

size_t FileManager::getFileCount() const
{
	return fileCount;
}
