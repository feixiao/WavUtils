//
// Created by frank on 2021/8/30.
//

#include <iostream>
#include "WavReader.hpp"

int main() {
    WavReader* wr = new WavReader();
    std::string file("/media/frank/aosp/github/WavUtils/Source/Test/ReferenceAudio/440HzSine1ChInt24.wav");
    if( !wr->initialize(file.c_str())) {
        printf("open file failed, file:%s\n", file.c_str());
        return -1 ;
    }

    if( !wr->prepareToRead() ) {
        printf("prepareToRead failed \n");
        return -1 ;
    }


    printf("%s : channel:%d sampleData:%d samples:%d\n", file.c_str(), wr->getNumChannels(), wr->getSampleDataSize(), wr->getNumSamples());
    uint8_t sampleData[1024*1024] = {"\0"};

    printf("sample data size:%d\n", wr->getSampleDataSize());
    wr->readData(sampleData, wr->getSampleDataSize());
    wr->finishReading();


    return 0;
}

