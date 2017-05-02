#include "classificator.h"
#include <math.h>

Classificator::Classificator(
        const vector<Descriptor> & bagOfWords, const vector<vector<double>> & prob)
{
    _bagOfWords = bagOfWords;
    _prob = prob;
}

vector<Descriptor> Classificator::bagOfWords() const
{
    return _bagOfWords;
}

vector<vector<double> > Classificator::probs() const
{
    return _prob;
}

Classificator::Solve Classificator::classify(const Matrix &m) const
{
    auto descr = SIDiscrBuilder().build(m);
    auto nums = vector<int>(_bagOfWords.size(),0);

    for(auto & d:descr){
        bool first = true;
        double ro = 0;
        int idx = -1;
        for(int i = 0; i < _bagOfWords.size(); i++){
            double curRo = PointMatcher().computeEuclide(d,_bagOfWords[i]);
            if(curRo < EPS){
                if(first){
                    ro = curRo;
                    idx = i;
                    first = false;
                } else {
                    if(ro < curRo){
                        idx = i;
                    }
                    break;
                }
            }
        }
        if(idx >= 0){
            nums[idx] += 1;
        }
    }

    Solve s;
    s.classId = -1;
    s.exp = -9999999999;
    s.mant = -9999999999;
    for(int i = 0; i < _prob.size(); i++){
        long double curProb = 1.0;
        long double mant = 1;
        int degree = 0;
        double testSum = 0;
        for(int j = 0; j < _prob[i].size(); j++){
            testSum += _prob[i][j];
            long double p = pow(_prob[i][j],nums[j]);
            int exp = 0;
            mant *= frexp(p,&exp);
            degree += exp;
            curProb *= p;
        }

        if((s.exp < degree) || (s.exp == degree && s.mant < mant)){
            s.exp = degree;
            s.mant = mant;
            s.classId = i;
        }
    }
    return s;
}
