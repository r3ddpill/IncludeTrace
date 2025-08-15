#pragma once
/// include_graph.hpp / Does exactly what it says
#include <string>
#include <unordered_map>
#include <memory>
#include "include_node.hpp"

class include_graph
{
private:
    std::unordered_map<std::string, std::shared_ptr<include_node>> nodes;
    std::shared_ptr<include_node> get_or_create_node(const std::string &file);

public:
    void add_dependency(const std::string &file, const std::string &included_file);
    void export_dot(const std::string &out_file);
    void detect_cycles();
};
