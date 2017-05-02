#include "trainer.h"
#include "convertutils.h"

vector<vector<vector<Descriptor>> > Trainer::computeDescriptors(
                      const vector<vector<Matrix> > &matrixes) const
{
    vector<vector<vector<Descriptor>>> result;
    for(auto & eachClass:matrixes){
        result.push_back(vector<vector<Descriptor>>());
        for(auto & eachImage:eachClass){
            result.back().emplace_back(SIDiscrBuilder().build(eachImage));
        }
    }
    return result;
}

vector<Descriptor> Trainer::computeBagOfWords(
        const vector<vector<vector<Descriptor> > > &descr, const int clusterCount) const
{
    assert(clusterCount > 0);
    auto trainer = BOWKMeansTrainer(clusterCount);
    auto trMatr = Mat();

    for(auto & eachClass:descr){
        for(auto & eachPicture:eachClass){
            for(auto & eachDescr:eachPicture){
                trMatr.push_back(Converter::vectorToMat(eachDescr.data));
            }
        }
    }
    trainer.add(trMatr);
    return Converter::matToDVector(trainer.cluster());
}

vector<vector<double>> Trainer::computeProbability(
        const vector<vector<vector<Descriptor> > > &descr,
        const vector<Descriptor> &bagOfWords) const
{
    const double EPS = 0.35;
    const double V = bagOfWords.size();
    vector<vector<vector<int>>> N;

    for(auto & eachClass:descr){
        N.push_back(vector<vector<int>>());
        for(auto & eachImage:eachClass){
            N.back().push_back(vector<int>(bagOfWords.size(),0));
            for(auto & eachDescr:eachImage){
                for(int j = 0; j<bagOfWords.size(); j++){
                    double ro = PointMatcher().computeEuclide(bagOfWords[j],eachDescr);
                    if(ro < EPS){
                        N.back().back()[j] += 1;
                    }
                }
            }
        }
    }

    vector<vector<int>> sums;
    vector<int> allSums;

    for(auto & eachClass:N){
        sums.push_back(vector<int>(bagOfWords.size(),0));
        int sumAll = 0;
        for(auto & eachImage:eachClass){
            for(int i = 0; i < eachImage.size(); i++){
                sums.back()[i] += eachImage[i];
                sumAll += eachImage[i];
            }
        }
        allSums.push_back(sumAll);
    }

    vector<vector<double>> probability(descr.size(),vector<double>(bagOfWords.size(),0));

    for(int i = 0; i < sums.size(); i++){
        for(int j = 0; j < sums[i].size(); j++){
            probability[i][j] = (1 + sums[i][j])/(double)(bagOfWords.size()+allSums[i]);
        }
    }

    return probability;
}
