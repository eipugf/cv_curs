#include "fileutils.h"
#include "convertutils.h"
#include <QDir>

#include <opencv2/imgproc/imgproc.hpp>

#include <features2d.hpp>

using namespace std;
using namespace cv;

FileUtils::FileUtils()
{

}

vector<vector<Matrix> > FileUtils::dataLoad(const QString &file)
{
    QDir dir(file);
    QFileInfoList list = dir.entryInfoList();
    vector<vector<Matrix>> classes;
    for(int i = 0; i < list.size(); i++){
        QFileInfo fileInfo = list.at(i);
        QString dirName = fileInfo.fileName();
        if(!dirName.compare(".") || !dirName.compare(".."))
            continue;
        QDir classDir(fileInfo.absoluteFilePath());
        classes.push_back(vector<Matrix>());
        QFileInfoList pictList = classDir.entryInfoList();
        for(int j = 0; j < pictList.size(); j++){
            QString picName = pictList.at(j).fileName();
            if(!picName.compare(".") || !picName.compare(".."))
                continue;
            classes.back().emplace_back(
                        FileUtils::loagImage(pictList.at(j).absoluteFilePath()));
        }
    }
    return classes;
}

Matrix FileUtils::loagImage(const QString &path)
{
    return Converter::qimageToMatrix(QImage(path));
}



void FileUtils::save(const Classificator &classificator, const QString &path)
{
    cv::FileStorage storage(path.toUtf8().constData(), cv::FileStorage::WRITE);
    Mat data = Converter::vectorToMat(classificator.bagOfWords());
    Mat probs =  Converter::vector2Tomat(classificator.probs());
    storage << "bow" << data;
    storage << "prob" << probs;
    storage.release();
}

Classificator FileUtils::load(const QString &path)
{
    cv::FileStorage storage(path.toUtf8().constData(),cv::FileStorage::READ);
    Mat bagOfWords;
    Mat probs;
    storage["bow"] >> bagOfWords;
    storage["prob"] >> probs;
    storage.release();
    return Classificator(Converter::matToDVector(bagOfWords),
                                            Converter::mat2ToVector(probs));
}


