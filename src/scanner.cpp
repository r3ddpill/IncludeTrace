#include <filesystem>
#include <fstream>
#include <regex>
#include "include_graph.hpp"

//LOL

namespace fs = std::filesystem;

void scan_directory(const fs::path &path, include_graph &graph)
{
    std::regex include_pattern(R"(^\s*#\s*include\s*\"([^\"]+)\")");

    for (auto &entry : fs::recursive_directory_iterator(path))
    {
        if (entry.is_regular_file())
        {
            std::string ext = entry.path().extension().string();
            if (ext == ".cpp" || ext == ".hpp" || ext == ".h" || ext == ".cc")
            {
                std::ifstream file(entry.path());
                if (!file.is_open())
                    continue;

                std::string line;
                while (std::getline(file, line))
                {
                    std::smatch match;
                    if (std::regex_search(line, match, include_pattern))
                    {
                        std::string included = match[1].str();
                        graph.add_dependency(entry.path().filename().string(), included);
                    }
                }
            }
        }
    }
}
