#include "minecraft/util/file_utils.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

std::string Minecraft::FileUtils::readFileToString(const std::string &path) {
  std::ifstream file(path, std::ios::in | std::ios::binary);

  if (!file) {
    throw std::runtime_error("Failed to open file: " + path);
  }

  file.seekg(0, std::ios::end);
  std::string content;
  content.resize(file.tellg());

  file.seekg(0, std::ios::beg);
  file.read(content.data(), content.size());

  return content;
}
