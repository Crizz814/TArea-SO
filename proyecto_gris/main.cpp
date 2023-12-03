#include <iostream>
#include <opencv2/opencv.hpp>

// Función para convertir una imagen a escala de grises utilizando OpenMP
void convertToGrayscaleOpenMP(cv::Mat& img) {
    #pragma omp parallel for
    for (int i = 0; i < img.rows; ++i) {
        cv::Vec3b* row = img.ptr<cv::Vec3b>(i);
        for (int j = 0; j < img.cols; ++j) {
            uchar gray = 0.114 * row[j][0] + 0.587 * row[j][1] + 0.299 * row[j][2];
            row[j] = cv::Vec3b(gray, gray, gray);
        }
    }
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <imagen_entrada> <imagen_salida>" << std::endl;
        return -1;
    }

    // Lee la imagen
    cv::Mat img = cv::imread(argv[1]);

    if (img.empty()) {
        std::cerr << "Error al cargar la imagen." << std::endl;
        return -1;
    }

    // Mide el tiempo de ejecución
    auto start_time = std::chrono::high_resolution_clock::now();

    // Convierte la imagen a escala de grises utilizando OpenMP
    convertToGrayscaleOpenMP(img);

    // Mide el tiempo de ejecución
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end_time - start_time;

    // Guarda la imagen en escala de grises
    cv::imwrite(argv[2], img);

    // Imprime el tiempo de ejecución total
    std::cout << "Tiempo de ejecución: " << elapsed_time.count() << " segundos." << std::endl;

    return 0;
}
