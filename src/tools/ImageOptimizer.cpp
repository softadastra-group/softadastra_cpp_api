// Fichier : src/tools/ImageOptimizer.cpp

#include "tools/ImageOptimizer.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

namespace Softadastra {
namespace Tools {

bool ImageOptimizer::optimize(const std::string& inputPath,
                              const std::string& outputPath,
                              int maxWidth,
                              int quality) {
    cv::Mat image = cv::imread(inputPath);
    if (image.empty()) {
        std::cerr << "Erreur : impossible de lire l'image " << inputPath << std::endl;
        return false;
    }

    if (image.cols > maxWidth) {
        float scale = static_cast<float>(maxWidth) / image.cols;
        cv::resize(image, image, cv::Size(), scale, scale);
    }

    std::vector<int> params = {cv::IMWRITE_JPEG_QUALITY, quality};
    if (!cv::imwrite(outputPath, image, params)) {
        std::cerr << "Erreur : échec de l'écriture de l'image optimisée " << outputPath << std::endl;
        return false;
    }

    return true;
}

} // namespace Tools
} // namespace Softadastra
