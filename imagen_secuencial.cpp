#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(int argc , char *argv[]) {

    auto start = chrono::high_resolution_clock::now();

    Mat ImagenColor = imread(argv[1], IMREAD_COLOR);

    cout << "Número de filas: " << ImagenColor.rows << endl;
	cout << "Número de columnas: " << ImagenColor.cols << endl;

    Mat ImagenGris = (argc == 2) ? imread(argv[2], IMREAD_COLOR) : Mat(ImagenColor.rows, ImagenColor.cols, CV_8UC1);

    for (int r=0; r<ImagenColor.rows; r++) {
        for ( int c = 0;c<ImagenColor.cols; c++) {
            Point3_<uchar>* p = ImagenColor.ptr<Point3_<uchar> >(r, c) ;
            // x :B y :G z :R
            ImagenGris.at<uchar>(r, c) = 0.21 * p->z + 0.72 * p->y + 0.07 * p->x;
        }
    }

    imwrite(argv[2], ImagenGris);

	auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "Time elapsed: " << elapsed.count() << " seconds" << endl;

return 0;
}