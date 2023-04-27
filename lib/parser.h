#pragma once

#include <string>

#include "filters/filter.h"

struct FilterConfig {
    std::string name;
    std::vector<std::string> args;
};

struct ParsedArguments {
    std::string input_path;
    std::string output_path;
    std::vector<FilterConfig> filters;
};

ParsedArguments Parse(int argc, char** argv);
