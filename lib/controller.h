#pragma once

#include <iostream>
#include <memory>

#include "parser.h"

class FilterCreationError : public std::invalid_argument {
    using std::invalid_argument::invalid_argument;
};

std::shared_ptr<Filter> CreateFilter(FilterConfig config);

std::vector<std::shared_ptr<Filter>> CreateFilters(const std::vector<FilterConfig>& filter_configs);

void ProcessImage(int argc, char** argv);
