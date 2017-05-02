#ifndef FILEUTILS_H
#define FILEUTILS_H
#include "matrix.h"
#include "classificator.h"
#include <QString>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>


using namespace std;

class FileUtils
{
public:
    FileUtils();

    static vector<vector<Matrix>> dataLoad(const QString & file);

    static Matrix loagImage(const QString & path);

    static void save(const Classificator & classificator, const QString & file);
    static Classificator load(const QString & path);
};

#endif // FILEUTILS_H
