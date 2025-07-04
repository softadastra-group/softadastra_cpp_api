// Fichier : include/tools/ImageOptimizer.hpp

#ifndef IMAGE_OPTIMIZER_HPP
#define IMAGE_OPTIMIZER_HPP

#include <string>

namespace Softadastra {
namespace Tools {

class ImageOptimizer {
public:
    // Optimise une image (redimensionnement + compression)
    // Retourne true si succès, false sinon
    static bool optimize(const std::string& inputPath,
                         const std::string& outputPath,
                         int maxWidth = 800,
                         int quality = 70);
};

} // namespace Tools
} // namespace Softadastra

#endif