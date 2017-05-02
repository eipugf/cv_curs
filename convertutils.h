#ifndef CONVERTUTILS_H
#define CONVERTUTILS_H

#include "matrix.h"
#include "utils.h"
#include <qimage.h>
#include <vector>
#include "descriptor.h"

#include <opencv2/imgproc/imgproc.hpp>

#include <features2d.hpp>

using namespace std;
using namespace cv;

class Converter
{
public:
    Converter();

    static Matrix qimageToMatrix(const QImage & image);

    static Mat vectorToMat(const vector<double> & v);
    static Mat vectorToMat(const vector<Descriptor> & v);
    static Mat vector2Tomat(const vector<vector<double>> & v);
    static vector<vector<double>> mat2ToVector(const Mat & m);
    static vector<double> matToVector(const Mat & m);
    static vector<Descriptor> matToDVector(const Mat & m);
};

#endif // CONVERTUTILS_H
