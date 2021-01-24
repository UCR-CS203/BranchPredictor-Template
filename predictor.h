#ifndef __BRANCH_H_
#define __BRANCH_H_

#include <iostream>
using namespace std;

class Predictor{
    private:

        unsigned int addrBits; //number of bits of address used to index
        unsigned int historyBits; //number of bits used for history
        unsigned int globalHistory; //record of global histroy
        int correct;
        int total;
        bool debug;
	unsigned int hexToInt(string);
        unsigned int truncateAddress (unsigned int);
        void updateGlobalHistory(bool); //update the history

    public:
        Predictor(unsigned int, unsigned int, unsigned int, bool);
        void makePrediction(string, bool);
        void printStats();
};

#endif
