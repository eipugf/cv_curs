#ifndef TRAINER_H
#define TRAINER_H
#include <vector>
#include <memory.h>
#include "scalespace.h"
#include <QRunnable>
#include <QLabel>
#include <QTimer>
#include <QString>
#include <QProgressBar>

#include <opencv2/imgproc/imgproc.hpp>

#include <features2d.hpp>

using namespace std;
using namespace cv;

class Trainer
{
public:
    vector<vector<vector<Descriptor>>> computeDescriptors(
           const vector<vector<Matrix>> & matrixes) const;

    vector<Descriptor> computeBagOfWords(
            const vector<vector<vector<Descriptor>>> & descr,
                const int clusterCount) const;

    vector<vector<double>> computeProbability(
            const vector<vector<vector<Descriptor>>> & descr,
            const vector<Descriptor> & bagOfWords) const;
};

#endif // TRAINER_H
