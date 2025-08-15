#pragma once
/// include_node.hpp / Does what it says! (pretty useless, but I like organization!)
#include <string>
#include <unordered_set>

struct include_node
{
    std::string file_name;
    std::unordered_set<std::string> includes;
};
