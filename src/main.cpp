#include <iostream>
#include "include_graph.hpp"

void scan_directory(const std::filesystem::path &path, include_graph &graph);

int main(int argc, char **argv)
{
    if (argc < 2)
    {
/// Warn user here about correct arguments?
// bro it already says it
        return 1;
    }

    include_graph graph;
    scan_directory(argv[1], graph);
    graph.detect_cycles();
  /// make it spawn in C:\ instead of directory annie
    graph.export_dot("output.dot");
// r we deadass
    std::cout << "[DONE] Check output.dot !\n";
    std::cout << "To view: dot -Tpng output.dot -o graph.png to visualize .\n";
    return 0;
}
