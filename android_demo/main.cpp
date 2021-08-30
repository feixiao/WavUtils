//
// Created by frank on 2021/8/30.
//

#include "WavReader.hpp"

int main() {
    WavReader* wr = new WavReader();
    wr->initialize(nullptr);
    wr->prepareToRead();  // Metadata available after this
    wr->readData(nullptr, wr->getSampleDataSize());
    wr->finishReading();
    return 0;
}

