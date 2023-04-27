#include "io.h"

#include <bit>
#include <iostream>
#include <fstream>

static const uint16_t BMP_HEADER = 0x4d42;
static const size_t HEADER_SIZE = 14;
static const size_t SUPPORTED_INFO_HEADER_SIZE = 40;
static const uint16_t SUPPORTED_COLOR_DEPTH = 24;

static_assert(std::endian::native == std::endian::little);

#pragma pack(push, 1)

struct Header {
    uint16_t file_type{BMP_HEADER};
    uint32_t file_size{0};
    uint16_t reserved1{0};
    uint16_t reserved2{0};
    uint32_t offset_data{0};
    uint32_t info_header_size{SUPPORTED_INFO_HEADER_SIZE};
    int32_t width{0};
    int32_t height{0};
    uint16_t color_planes{1};
    uint16_t color_depth{SUPPORTED_COLOR_DEPTH};
    uint32_t compression_method{0};
    uint32_t image_size{0};
    int32_t x_pixels_per_meter{0};
    int32_t y_pixels_per_meter{0};
    uint32_t colors_used{0};
    uint32_t colors_important{0};
};

#pragma pack(pop)

BMPImageError::BMPImageError() {
}

BMPImageError::BMPImageError(const std::string& message) : message_(message) {
}

std::string BMPImageError::Message() const {
    return message_;
}

Image ReadBitmap(const std::string& file_name) {
    std::ifstream file;
    file.open(file_name, std::ios::binary | std::ios::in);
    if (!file.is_open()) {
        throw BMPImageError("Error opening the file");
    }
    std::vector<uint8_t> bytes;
    char c = 0;
    while (file.get(c)) {
        bytes.push_back(c);
    }
    if (bytes.size() < HEADER_SIZE + SUPPORTED_INFO_HEADER_SIZE) {
        file.close();
        throw BMPImageError("File too small to be an appropriate image");
    }
    Header header = *reinterpret_cast<Header*>(&bytes[0]);
    if (header.file_type != BMP_HEADER) {
        file.close();
        throw BMPImageError("Incorrect file type");
    }
    if (header.info_header_size != SUPPORTED_INFO_HEADER_SIZE) {
        file.close();
        throw BMPImageError("Unimplemented bitmap information header type");
    }
    if (header.color_depth != SUPPORTED_COLOR_DEPTH) {
        file.close();
        throw BMPImageError("Unimplemented color depth");
    }
    if (header.width < 0) {
        file.close();
        throw BMPImageError("Negative image width");
    }
    if (header.compression_method != 0) {
        file.close();
        throw BMPImageError("Unimplemented compression method");
    }
    size_t height = static_cast<size_t>(std::abs(header.height));
    bool negative_height = header.height < 0;
    size_t width = static_cast<size_t>(header.width);
    size_t row_length = (width * 3 + 3) / 4 * 4;
    if (row_length * height + header.offset_data > bytes.size()) {
        file.close();
        throw BMPImageError("Declared image size is greater than the file size");
    }
    std::vector<std::vector<Color>> pixels(height, std::vector<Color>());
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            size_t pixel_offset = header.offset_data + i * row_length + j * 3;
            pixels[negative_height ? i : height - 1 - i].push_back(
                Color(*reinterpret_cast<uint8_t*>(&bytes[pixel_offset + 2]),
                      *reinterpret_cast<uint8_t*>(&bytes[pixel_offset + 1]),
                      *reinterpret_cast<uint8_t*>(&bytes[pixel_offset])));
        }
    }
    file.close();
    return Image(pixels, height, width);
}

void WriteBitmap(const std::string& file_name, const Image& image) {
    std::ofstream file;
    file.open(file_name, std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        throw BMPImageError("Error creating the new file");
    }
    size_t row_length = (image.GetWidth() * 3 + 3) / 4 * 4;
    Header header;
    header.file_size = HEADER_SIZE + SUPPORTED_INFO_HEADER_SIZE + row_length * image.GetHeight();
    header.offset_data = HEADER_SIZE + SUPPORTED_INFO_HEADER_SIZE;
    header.height = static_cast<int32_t>(image.GetHeight());
    header.width = static_cast<int32_t>(image.GetWidth());
    file.write(reinterpret_cast<char*>(&header), sizeof(header));
    size_t row_padding = row_length - 3 * image.GetWidth();
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            Color c = image.GetPixel(image.GetHeight() - i - 1, j);
            file.put(static_cast<int8_t>(c.blue));
            file.put(static_cast<int8_t>(c.green));
            file.put(static_cast<int8_t>(c.red));
        }
        for (size_t j = 0; j < row_padding; ++j) {
            file.put(0);
        }
    }
    file.close();
}
