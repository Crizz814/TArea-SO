#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>
#include <mutex>

using namespace cv;
using namespace std;

mutex mtx;

void processImagePart(Mat& ImagenColor, Mat& ImagenGris, int startRow, int endRow) {
    for (int r = startRow; r < endRow; r++) {
        for (int c = 0; c < ImagenColor.cols; c++) {
            mtx.lock();
            Vec3b& color = ImagenColor.at<Vec3b>(r, c);
            ImagenGris.at<uchar>(r, c) = 0.21 * color[2] + 0.72 * color[1] + 0.07 * color[0];
            mtx.unlock();
        }
    }
}

int main(int argc , char *argv[]) {

	auto start = chrono::high_resolution_clock::now();

    Mat ImagenColor = imread(argv[1], IMREAD_COLOR);
    int numThreads = stoi(argv[3]);

	cout << "Número de filas: " << ImagenColor.rows << endl;
	cout << "Número de columnas: " << ImagenColor.cols << endl;

    Mat ImagenGris = (argc == 3) ? imread(argv[2], IMREAD_COLOR) : Mat(ImagenColor.rows, ImagenColor.cols, CV_8UC1);
    vector<thread> threads(numThreads);
    int rowsPerThread = ImagenColor.rows / numThreads;

    for (int i = 0; i < numThreads; i++) {
        int startRow = i * rowsPerThread;
        int endRow = (i == numThreads - 1) ? ImagenColor.rows : startRow + rowsPerThread;
        threads[i] = thread(processImagePart, ref(ImagenColor), ref(ImagenGris), startRow, endRow);
    }

    for (auto& t : threads) {
        t.join();
    }

    imwrite(argv[2], ImagenGris);

	auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "Time elapsed: " << elapsed.count() << " seconds" << endl;

    return 0;
}
