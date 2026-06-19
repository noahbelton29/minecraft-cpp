#pragma once

#include <string>

namespace Minecraft {
  /**
   * @brief Helper functions for working with files.
   */
  class FileUtils {
  public:
    /**
     * @brief Reads an entire file into a string.
     * @param path Path to the file.
     * @return The file's contents as a string.
     */
    static std::string readFileToString(const std::string &path);
  };
} // namespace Minecraft
