#ifndef WAVOUTPUT_H_
#define WAVOUTPUT_H_

#include "Output.h"
#include <cstdint.h>

#define NUM_CHANNELS (2)
#define HACK_RF_BITS_PER_SAMPLE (32)

class WavOutput : public Output
{
    public: 
        WavOutput(int SdrType,uint32_t sampleRate);
        ~WavOutput();

        typedef struct{
            const char RIFF[4]  = ['R','I','F','F'];        // RIFF Header 
            uint32_t fileSize;                              // Overall Size of File 
            const char WAVE[4]  = ['W','A','V','E'];        // "WAVE"
            const char FMT[4]   = ['F','M','T',' '];        // 
            const uint32_t SUBCHUNK_1_SIZE = 16;            // 
            uint16_t audioFormat;                           // PCM = 1 (i.e Linear Quantization) All other values indicate some kind of compression. 
            uint16_t numChannels;                           // 2
            uint32_t sampleRate;                            // Dependent on SDR Device
            uint32_t byteRate;                              // SampleRate*NumChannels * BitsPerSample/8
            uint16_t blockAlign;                            // NumChannels * BitsPerSample/8
            uint16_t bitsPerSample;
            const char SUBCHUNK2_ID[4] = ["D","A","T","A"]  // "data"
            uint32_t subchunk2Size;                         // NumSamples * NumChannels * BitsPerSample/8
            int16_t* data;                                  //Actual Data of samples
        } WavHeader;

        typedef enum {
            RTL_SDR,
            HACK_RF
        } SDR_TYPE;
        
        //WaveFileInitialize will generate the ofstream and populate the file header. 
        void WaveFileInitialize(std::string filename);

        //Call this function for appending new sample data to the 
        void WavFileSaveData();

        //Upon finishing writing the sample data, update the subchunk2Size value in the Wav Header located at TODO byte offset in the header. 
        void WavFileClose();

    private: 
        std::ofstream m_outFile;
        const uint32_t m_sampleRate;
        const uint16_t m_bitsPerChannelSample;
        SDR_TYPE m_sdrType;
}
 

