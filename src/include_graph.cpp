#include "include_graph.hpp"
/// include_graph.cpp / Handles output, in a shit way!
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <functional>

/// Get the node if it exists, here
/* Can probably be changed in the future */

std::shared_ptr<include_node> include_graph::get_or_create_node(const std::string &file)
{
    auto it = nodes.find(file);
    if (it != nodes.end())
        return it->second;

    auto node_ptr = std::make_shared<include_node>();
    node_ptr->file_name = file;
    nodes[file] = node_ptr;
    return node_ptr;
}

void include_graph::add_dependency(const std::string &file, const std::string &included_file)
{
    auto file_node = get_or_create_node(file);
    file_node->includes.insert(included_file);
}

// Spit out the graph as a .dot file so Graphviz can make it pretty i guess
/// Why even neccessary?

void include_graph::export_dot(const std::string &out_file)
{
    std::ofstream out(out_file);
    out << "digraph Includes {\n";
    out << "  node [shape=box, style=filled, fillcolor=lightblue];\n";

    for (auto &pair : nodes)
    {
        auto &src = pair.first;
        for (auto &dst : pair.second->includes)
        {
            out << "  \"" << src << "\" -> \"" << dst << "\";\n";
        }
    }

    out << "}\n";
}

void include_graph::detect_cycles()
{
    std::unordered_set<std::string> visited, recursion_stack;
    bool found_cycle = false;

    std::function<bool(const std::string &)> dfs = [&](const std::string &file) -> bool
    {
        if (recursion_stack.count(file)) // Uh-oh, we're already on the stack, that's a loop
        {
            std::cout << "[CYCLE] involving: " << file << "\n"; // Who cares
            return true;
        }
        if (visited.count(file)) /// Already dealt with this one — might be redundant?
            return false;

        visited.insert(file);
        recursion_stack.insert(file);

        auto it = nodes.find(file);
        if (it != nodes.end())
        {
            for (auto &dep : it->second->includes)
            {
                if (dfs(dep))
                    found_cycle = true; // Poisoned
            }
        }

        recursion_stack.erase(file);
        return false;
    };

    for (auto &pair : nodes)
        dfs(pair.first);

    if (!found_cycle)
        std::cout << "[OK] No circular dependencies found .\n";
}
