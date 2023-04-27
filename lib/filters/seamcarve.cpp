#include "seamcarve.h"

#include <cmath>

#include "sobel.h"

SeamCarving::SeamCarving(size_t height, size_t width) : height_(height), width_(width) {
}

std::vector<std::vector<float>> SeamCarving::EdgeMatrix(const Image& image) const {
    std::vector<std::vector<UnboundedColor>> sobel_y = SobelFilterY().ApplyMatrix(image);
    std::vector<std::vector<UnboundedColor>> sobel_x = SobelFilterX().ApplyMatrix(image);
    std::vector<std::vector<float>> matrix(image.GetHeight(), std::vector<float>(image.GetWidth(), 0.));
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            float y_sq = static_cast<float>(std::pow(sobel_y[y][x].red, 2) + std::pow(sobel_y[y][x].green, 2) +
                                            std::pow(sobel_y[y][x].blue, 2));
            float x_sq = static_cast<float>(std::pow(sobel_x[y][x].red, 2) + std::pow(sobel_x[y][x].green, 2) +
                                            std::pow(sobel_x[y][x].blue, 2));
            matrix[y][x] = std::sqrt(y_sq + x_sq);
        }
    }
    return matrix;
}

struct Node {
    size_t previous{0};
    float value{0.};
};

void SeamCarving::CarveHor(Image& image) const {
    std::vector<std::vector<float>> edge_matrix = EdgeMatrix(image);
    std::vector<std::vector<Node>> path_matrix(image.GetHeight(), std::vector<Node>(image.GetWidth(), Node()));
    for (size_t j = 0; j < image.GetHeight(); ++j) {
        path_matrix[j][0].value = edge_matrix[j][0];
    }
    for (size_t i = 1; i < image.GetWidth(); ++i) {
        for (size_t j = 0; j < image.GetHeight(); ++j) {
            path_matrix[j][i].previous = j;
            path_matrix[j][i].value = path_matrix[j][i - 1].value;
            if (j >= 1 && path_matrix[j][i].value > path_matrix[j - 1][i - 1].value) {
                path_matrix[j][i].previous = j - 1;
                path_matrix[j][i].value = path_matrix[j - 1][i - 1].value;
            }
            if (j + 2 <= image.GetHeight() && path_matrix[j][i].value > path_matrix[j + 1][i - 1].value) {
                path_matrix[j][i].previous = j + 1;
                path_matrix[j][i].value = path_matrix[j + 1][i - 1].value;
            }
            path_matrix[j][i].value += edge_matrix[j][i];
        }
    }
    size_t least_path = 0;
    for (size_t j = 0; j < image.GetHeight(); ++j) {
        if (path_matrix[j][image.GetWidth() - 1].value < path_matrix[least_path][image.GetWidth() - 1].value) {
            least_path = j;
        }
    }
    std::vector<size_t> removed(image.GetWidth(), 0);
    removed[image.GetWidth() - 1] = least_path;
    for (size_t i = 1; i < image.GetWidth(); ++i) {
        removed[image.GetWidth() - 1 - i] = path_matrix[removed[image.GetWidth() - i]][image.GetWidth() - i].previous;
    }
    for (size_t i = 0; i < image.GetWidth(); ++i) {
        for (size_t j = removed[i] + 1; j < image.GetHeight(); ++j) {
            image.SetPixel(j - 1, i, image.GetPixel(j, i));
        }
    }
    image.SetHeight(image.GetHeight() - 1);
}

void SeamCarving::CarveVert(Image& image) const {
    std::vector<std::vector<float>> edge_matrix = EdgeMatrix(image);
    std::vector<std::vector<Node>> path_matrix(image.GetHeight(), std::vector<Node>(image.GetWidth(), Node()));
    for (size_t j = 0; j < image.GetWidth(); ++j) {
        path_matrix[0][j].value = edge_matrix[0][j];
    }
    for (size_t i = 1; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            path_matrix[i][j].previous = j;
            path_matrix[i][j].value = path_matrix[i - 1][j].value;
            if (j >= 1 && path_matrix[i][j].value > path_matrix[i - 1][j - 1].value) {
                path_matrix[i][j].previous = j - 1;
                path_matrix[i][j].value = path_matrix[i - 1][j - 1].value;
            }
            if (j + 2 <= image.GetWidth() && path_matrix[i][j].value > path_matrix[i - 1][j + 1].value) {
                path_matrix[i][j].previous = j + 1;
                path_matrix[i][j].value = path_matrix[i - 1][j + 1].value;
            }
            path_matrix[i][j].value += edge_matrix[i][j];
        }
    }
    size_t least_path = 0;
    for (size_t j = 0; j < image.GetWidth(); ++j) {
        if (path_matrix[image.GetHeight() - 1][j].value < path_matrix[image.GetHeight() - 1][least_path].value) {
            least_path = j;
        }
    }
    std::vector<size_t> removed(image.GetHeight(), 0);
    removed[image.GetHeight() - 1] = least_path;
    for (size_t i = 1; i < image.GetHeight(); ++i) {
        removed[image.GetHeight() - 1 - i] =
            path_matrix[image.GetHeight() - i][removed[image.GetHeight() - i]].previous;
    }
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = removed[i] + 1; j < image.GetWidth(); ++j) {
            image.SetPixel(i, j - 1, image.GetPixel(i, j));
        }
    }
    image.SetWidth(image.GetWidth() - 1);
}

#include <iostream>

void SeamCarving::Apply(Image& image) const {
    size_t carve_hor_total = std::max(image.GetHeight(), height_) - height_;
    size_t carve_vert_total = std::max(image.GetWidth(), width_) - width_;
    size_t carve_hor_left = carve_hor_total;
    size_t carve_vert_left = carve_vert_total;
    while (carve_hor_left + carve_vert_left > 0) {
        std::cout << carve_vert_total + carve_hor_total - carve_vert_left - carve_hor_left << " seams carved out of ";
        std::cout << carve_vert_total + carve_hor_total << "\n";
        if (carve_hor_left * carve_vert_total > carve_vert_left * carve_hor_total) {
            CarveHor(image);
            --carve_hor_left;
        } else if (carve_hor_left * carve_vert_total < carve_vert_left * carve_hor_total) {
            CarveVert(image);
            --carve_vert_left;
        } else if (carve_hor_total >= carve_vert_total) {
            CarveHor(image);
            --carve_hor_left;
        } else {
            CarveVert(image);
            --carve_vert_left;
        }
    }
}

Image SeamCarving::ConstApply(const Image& image) const {
    Image new_image = image;
    Apply(new_image);
    return new_image;
}
