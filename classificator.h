#ifndef CLASSIFICATOR_H
#define CLASSIFICATOR_H
#include "scalespace.h"

#include <memory>
#include <vector>

using namespace std;

class Classificator
{

    vector<Descriptor> _bagOfWords;
    vector<vector<double>> _prob;
    double EPS = 0.35;
public:

    struct Solve{
        long double mant;
        int exp;
        int classId;
    };

public:
    Classificator(const vector<Descriptor> & bagOfWords,
                            const vector<vector<double>> & prob);
    Classificator(Classificator && othe) = default;

    vector<Descriptor> bagOfWords() const;
    vector<vector<double>> probs() const;

    Solve classify(const Matrix & m) const;
};

#endif // CLASSIFICATOR_H
