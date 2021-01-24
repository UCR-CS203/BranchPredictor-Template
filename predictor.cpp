#include "predictor.h"
#include <sstream>
#include <iomanip>

Predictor::Predictor(unsigned int m, unsigned int n, unsigned int addrLength, bool debug){
    this->historyBits = m; // Size of global history
    this->globalHistory = 0; 
    this->addrBits = addrLength;
    this->debug = debug;
    this->correct = 0;
    this->total = 0;
    printf("Address length: %u\n", this->addrBits);
    printf("History length: %u\n", this->historyBits);
    printf("Debug mode: %u\n", this->debug);
};


void Predictor::updateGlobalHistory(bool expected){
    globalHistory = globalHistory << 1;
    globalHistory = globalHistory | expected;
    unsigned int mask = (1 << this->historyBits) - 1;
    globalHistory = globalHistory & mask; 
}

bool Predictor::makePrediction(string input, bool expected){
    // Convert Hex address to integer address
    unsigned int address = truncateAddress(hexToInt(input));

    // Currently, this simple branch predictor simulator simply takes 
    // the previous observed branch direction as the next prediction.
    // Predict branch based on last observed branch
    bool predicted = globalHistory & 1; 
   
    // Update global history 
    updateGlobalHistory(expected);

    // Update statistics
    if(predicted == expected){
        this->correct++;
    }
    this->total++;

    return predicted;
}

/*
 * Print out branch predictor statistics
 */
void Predictor::printStats(){ 
    printf("------------------------------------------\n"); 
    if(total == 0){
        printf("Error, Cannot get rate \n");
    }
    else{
        printf("Misclassification rate: %.2f%%\n", 100.00 * (1 - (double)(this->correct)/this->total));
    } 
    
    printf("correct: %d\n", this->correct);
    printf("total: %d\n",this->total);


    // Update the following line to print out the number of BHT entires used.
    printf("BHT used %lu entries\n",0);  
}

/*
 * DO NOT MODIFY BELOW THIS
 */


/*
 * Convert Hex string from trace file to integer address
 */
unsigned int Predictor::hexToInt(string input){
    istringstream converter(input);
    unsigned int result;
    converter >> std::hex >> result; 
    return result;
}

/*
 * Truncate Address to specified number of address bits
 */
unsigned int Predictor::truncateAddress(unsigned int input){
    unsigned int mask = (1 << this->addrBits) - 1;
    unsigned int result = input & mask;

    return result;
}

