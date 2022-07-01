#ifndef __AUDIO_SAMPLER_H__
#define __AUDIO_SAMPLER_H__

#define NUM_VERTICAL_LINES (4)
#define NUM_HORIZONTAL_LINES (8)

#define NUM_BARS (NUM_VERTICAL_LINES * 2)

#define STANDARD_WIDGET_SPACING (6)

#ifdef linux
#define ALSA_PCM_NEW_HW_PARAMS_API		// use new API
#include <alsa/asoundlib.h>
#include <fftw3.h>
#endif

class AudioSampler
{
public:
    AudioSampler();
    virtual ~AudioSampler();

    bool Update();
    bool Open(const char* alsa_device_name);

    void Analyze();

    float* GetMagnitudeArray();
    int GetMagnitudeCount();

private:

#ifdef linux
    snd_pcm_uframes_t m_frame_size;
    snd_pcm_t* m_alsa;
    fftw_plan m_fftw_plan;
#endif

    unsigned int m_rate;
    float*  m_frame_buffer;

    double* m_sample_buffer_double_in;
    double* m_sample_buffer_double_out;
    float* m_bar_magnitudes;

    int m_overrun_count;
    int m_underrun_count;
};

#endif
