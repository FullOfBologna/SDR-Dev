#include "HackRFDongle.h"

int HackRFDongle::FrequencySet(uint32_t freq)
{
    m_frequency = freq;
    int result = hackrf_set_freq(mDevice.get(), m_frequency);

    return result;
}

int HackRFDongle::SampleRateSet(uint32_t sampRate)
{
    m_sampleRate = sampRate;
    int result = hackrf_set_sample_rate(mDevice.get(), m_sampleRate);

    return result;
}

int HackRFDongle::VGAGainSet(uint32_t vgaGain)
{
    mVGAGain = vgaGain;

    int result = hackrf_set_vga_gain(mDevice.get(), mVGAGain);

    return result;
}

int HackRFDongle::LNAGainSet(uint32_t lnaGain)
{
        mLNAGain = lnaGain;

    int result = hackrf_set_lna_gain(mDevice.get(), mLNAGain);

    return result;
}

int HackRFStartRx()
{

}

int HackRFStopRx()
{
    
}

/* Internal Private Methods*/

int HackRFDongle::sdrCallback(hackrf_transfer* transfer)
{
    size_t bytesToWrite; 
    size_t bytesWritten;
    int result = HACKRF_SUCCESS;

    bytesToWrite = transfer->valid_length;
    
    std::cout << bytesToWrite << '\n';

}