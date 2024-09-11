#include "WavOutput.hpp"

WavOutput::WavOutput(std::string filename, int SdrType, uint32_t sampleRate)
    : m_sdrType(SdrType),
    m_sampleRate(sampleRate)
{
    switch m_sdrType:
        case(SDR_TYPE::RTL_SDR):
            break;
        case(SDR_TYPE::HACK_RF):
            m_bitsPerChannelSample = 16;
            break;

    WavFileInitialize(filename);
}

WavOutput::~WavOutput()
{

}

WavOutput::WavFileInitialize(std::string filename)
{
    m_outFile = std::ofstream(filename);
    


}

//TODO - connect the incoming RF Sample Data received from the HackRf, through
// the channel port. 
WavOutput::WavFileSave()
{

}

//TODO - Upon completion of writing to the wavefile, need to read the header of
// the file back in, in order to update the subchunk2size value and the fileSize 
// in the header. 
//

WavOutput::WavFileClose()
{

}
