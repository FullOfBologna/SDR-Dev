#include "HackRFDongle.h"

int HackRFDongle::FrequencySet(uint32_t freq)
{
    m_frequencyHz = freq;
    int result = hackrf_set_freq(mDevice.get(), m_frequencyHz);
    return result;
}

int HackRFDongle::SampleRateSet(uint32_t sampRate)
{
    m_sampleRateHz = sampRate;
    int result = hackrf_set_sample_rate(mDevice.get(), m_sampleRateHz);
    return result;
}

int HackRFDongle::VGAGainSet(uint32_t vgaGain_dB)
{
    mVGAGain_dB = vgaGain_dB;
    int result = hackrf_set_vga_gain(mDevice.get(), mVGAGain_dB);
    return result;
}

int HackRFDongle::LNAGainSet(uint32_t lnaGain_dB)
{
    mLNAGain_dB = lnaGain_dB;
    int result = hackrf_set_lna_gain(mDevice.get(), mLNAGain_dB);
    return result;
}

int HackRFDongle::AmpEnable(bool ampEnable)
{
    if(ampEnable)
    {
        mAmpEnable = 1;
    }
    else
    {
        mAmpEnable = 0;
    }

    int result = hackrf_set_amp_enable(mDevice.get(), mAmplEnale);
    return result;
}

/*
void HackRFDongle::DemodTargetSet(std::unique_ptr<Demod>&demodTarget)
{
    m_demodTarget = std::move(demodTarget);
}
*/

int HackRFDongle::StartRx()
{
//connect  back to sdrTarget?
    int result;
    result = hackrf_start_rx(mDevice, sdrCallback,NULL);
    return result;
}

int HackRFDongle::StopRx()
{
    int result;
    result = hackrf_stop_rx(mDevice);
    return result;
}

/* Internal Private Methods*/
/*int HackRfDongle::bufferTransferToDemodTarget()
{
    mChannel->put(mSampBuffer);
}
*/
int HackRFDongle::sdrCallback(hackrf_transfer* transfer)
{
    size_t bytesToWrite; 
    size_t bytesWritten;
    int result = HACKRF_SUCCESS;

    bytesToWrite = transfer->valid_length;
    
    std::cout << bytesToWrite << '\n';

    /*
    * Transfer hackrf_transfer uint8_t* to std::array for 
    */ 

    if(bytesToWrite <= MAXIMUM_BUF_LENGTH)
    {
        std::copy(transfer->buf,bytesToWrite,mSampBuffer.begin());
        mChannel->put(mSampBuffer);
    }
    else
    {
       //result =  
    }

    return HACKRF_SUCCESS;
//    demodTargetLock();
//    bufferTransferToDemodTarget();
//    demodTargetFree();
    //std::cout << bytesWritten << '\n';
}
