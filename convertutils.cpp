#include "convertutils.h"

Converter::Converter()
{

}

Matrix Converter::qimageToMatrix(const QImage &image)
{
    auto m = Matrix(image.width(),image.height());
    for(int i = 0; i < image.width(); i++){
        for(int j = 0; j < image.height(); j++){
            m.set(i,j,
                Utils::gray(qRed(image.pixel(i,j)),
                            qGreen(image.pixel(i,j)),
                            qBlue(image.pixel(i,j))));
        }
    }
    return m;
}

Mat Converter::vectorToMat(const vector<double> &v)
{
    Mat row = Mat(v);
    row.convertTo(row, CV_32F);
    transpose(row,row);
    return row;
}

Mat Converter::vectorToMat(const vector<Descriptor> &v)
{
    Mat squareMat;
    transpose(squareMat,squareMat);
    for(auto & each:v){
        squareMat.push_back(vectorToMat(each.data));
    }
    return squareMat;
}

Mat Converter::vector2Tomat(const vector<vector<double> > &v)
{
    Mat squareMat;
    transpose(squareMat,squareMat);
    for(auto & each:v){
        squareMat.push_back(vectorToMat(each));
    }
    return squareMat;
}

vector<vector<double> > Converter::mat2ToVector(const Mat &m)
{
    vector<vector<double>> data;
    for(int i = 0; i < m.size().height; i++){
        Mat row = m.row(i);
        vector<double> rowData;
        row.copyTo(rowData);
        data.push_back(rowData);
    }
    return data;
}

vector<double> Converter::matToVector(const Mat &m)
{
    assert(m.size().height == 1);
    vector<double> data;
    m.row(0).copyTo(data);
    return data;
}

vector<Descriptor> Converter::matToDVector(const Mat &m)
{
    vector<Descriptor> data;
    for(int i = 0; i < m.size().height; i++){
        Mat row = m.row(i);
        vector<double> rowData;
        row.copyTo(rowData);
        data.push_back(Descriptor(0,0,rowData));
    }
    return data;
}

