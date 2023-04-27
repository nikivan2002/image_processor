#include "controller.h"

#include "filters/crop.h"
#include "filters/edge.h"
#include "filters/gs.h"
#include "filters/hues.h"
#include "filters/neg.h"
#include "filters/seamcarve.h"
#include "filters/sharp.h"
#include "io.h"

std::shared_ptr<Filter> CreateFilter(FilterConfig config) {
    if (config.name == "crop") {
        if (config.args.size() != 2) {
            throw FilterCreationError("Incorrect amount of arguments in crop");
        }
        try {
            return (std::make_shared<Crop>(std::stoul(config.args[0]), std::stoul(config.args[1])));
        } catch (std::invalid_argument& error) {
            throw FilterCreationError("Invalid argument in crop");
        }
    } else if (config.name == "edge") {
        if (config.args.size() != 1) {
            throw FilterCreationError("Incorrect amount of arguments in edge detection");
        }
        try {
            float threshold = std::stof(config.args[0]);
            return (std::make_shared<EdgeDetection>(static_cast<uint8_t>((threshold < 0)   ? 0
                                                                         : (threshold > 1) ? FULL_COLOR
                                                                                           : threshold * FULL_COLOR)));
        } catch (std::invalid_argument& error) {
            throw FilterCreationError("Invalid argument in edge detection");
        }
    } else if (config.name == "gs") {
        if (!config.args.empty()) {
            throw FilterCreationError("Incorrect amount of arguments in grayscale");
        }
        return std::make_shared<GrayScale>();
    } else if (config.name == "hues") {
        if (!config.args.empty()) {
            throw FilterCreationError("Incorrect amount of arguments in hues");
        }
        return std::make_shared<Hues>();
    } else if (config.name == "neg") {
        if (!config.args.empty()) {
            throw FilterCreationError("Incorrect amount of arguments in negative");
        }
        return std::make_shared<Negative>();
    } else if (config.name == "seamcarve") {
        if (config.args.size() != 2) {
            throw FilterCreationError("Incorrect amount of arguments in seam carving");
        }
        try {
            return (std::make_shared<SeamCarving>(std::stoul(config.args[0]), std::stoul(config.args[1])));
        } catch (std::invalid_argument& error) {
            throw FilterCreationError("Invalid argument in seam carving");
        }
    } else if (config.name == "sharp") {
        if (!config.args.empty()) {
            throw FilterCreationError("Incorrect amount of arguments in sharpening");
        }
        return std::make_shared<Sharpening>();
    } else {
        throw FilterCreationError("Invalid filter name");
    }
}

std::vector<std::shared_ptr<Filter>> CreateFilters(const std::vector<FilterConfig>& filter_configs) {
    std::vector<std::shared_ptr<Filter>> filters;
    for (const auto& config : filter_configs) {
        try {
            filters.push_back(CreateFilter(config));
        } catch (FilterCreationError& error) {
            std::cerr << error.what() << std::endl;
        }
    }
    return filters;
}

void ProcessImage(int argc, char** argv) {
    if (argc == 1) {
        std::cout << "Image Processor\n";
        std::cout << "A simple image manipulation utility.\n\n";
        std::cout << "Usage:\n";
        std::cout << "\timage_processor input_file output_file [FILTERS [ARGS]]\n\n";
        std::cout << "Filters:\n";
        std::cout << "\t-crop width height\t- Crop Image\n";
        std::cout << "\t-gs\t- Grayscale filter\n";
        std::cout << "\t-neg\t- Negative filter\n";
        std::cout << "\t-sharp\t- Sharpening\n";
        std::cout << "\t-edge threshold\t- Edge Detection\n";
        std::cout << "\t-hues\t- Edge Detection\n";
        std::cout << "\t-seamcarve width height\t- Seam Carving" << std::endl;
        return;
    }
    if (argc == 2) {
        std::cerr << "Incorrect amount of arguments" << std::endl;
        return;
    }
    try {
        ParsedArguments parsed_arguments = Parse(argc, argv);
        Image image = ReadBitmap(parsed_arguments.input_path);
        std::vector<std::shared_ptr<Filter>> filters = CreateFilters(parsed_arguments.filters);
        for (const auto& filter : filters) {
            filter->Apply(image);
        }
        WriteBitmap(parsed_arguments.output_path, image);
    } catch (BMPImageError& error) {
        std::cerr << error.Message() << std::endl;
    }
}
