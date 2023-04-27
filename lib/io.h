#pragma once

#include <string>

#include "image.h"

class BMPImageError : public std::exception {
public:
    BMPImageError();

    explicit BMPImageError(const std::string& message);

    std::string Message() const;

private:
    std::string message_;
};

Image ReadBitmap(const std::string& file_name);

void WriteBitmap(const std::string& file_name, const Image& image);
