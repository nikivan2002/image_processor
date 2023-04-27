#include "parser.h"

ParsedArguments Parse(int argc, char** argv) {
    ParsedArguments parsed_arguments;
    parsed_arguments.input_path = argv[1];
    parsed_arguments.output_path = argv[2];
    FilterConfig config;
    for (size_t i = 3; i < static_cast<size_t>(argc); ++i) {
        if (argv[i][0] == '-') {
            if (i != 3) {
                parsed_arguments.filters.push_back(config);
            }
            config.name = std::string(argv[i]).substr(1);
            config.args.clear();
        } else {
            config.args.push_back(std::string(argv[i]));
        }
    }
    if (argc > 3) {
        parsed_arguments.filters.push_back(config);
    }
    return parsed_arguments;
}
