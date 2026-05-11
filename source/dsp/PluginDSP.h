#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <vector>

class PluginDSP
{
public:
    void prepare (double sampleRate, int samplesPerBlock, int numChannels);
    void reset();

    void processBlock (juce::AudioBuffer<float>& buffer,
                       float rateHz,
                       float depth,
                       float mix,
                       float volumeDecibels);

private:
    float readDelayedSample (int channel, float delayInSamples) const;
    void pushSample (int channel, float sample);

    double currentSampleRate = 44100.0;
    int delayBufferSize = 1;
    int writePosition = 0;
    float lfoPhase = 0.0f;

    std::vector<std::vector<float>> delayLines;
};
