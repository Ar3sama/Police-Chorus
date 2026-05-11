#include "PluginDSP.h"

#include <cmath>

void PluginDSP::prepare (double sampleRate, int samplesPerBlock, int numChannels)
{
    juce::ignoreUnused (samplesPerBlock);

    currentSampleRate = sampleRate;

    constexpr double maximumDelayMilliseconds = 35.0;
    delayBufferSize = static_cast<int> ((maximumDelayMilliseconds / 1000.0) * currentSampleRate) + 2;

    delayLines.resize (static_cast<size_t> (numChannels));

    for (auto& delayLine : delayLines)
        delayLine.assign (static_cast<size_t> (delayBufferSize), 0.0f);

    reset();
}

void PluginDSP::reset()
{
    for (auto& delayLine : delayLines)
        std::fill (delayLine.begin(), delayLine.end(), 0.0f);

    writePosition = 0;
    lfoPhase = 0.0f;
}

void PluginDSP::processBlock (juce::AudioBuffer<float>& buffer,
                              float rateHz,
                              float depth,
                              float mix,
                              float volumeDecibels)
{
    if (delayLines.empty())
        return;

    const auto numChannels = juce::jmin (buffer.getNumChannels(), static_cast<int> (delayLines.size()));
    const auto numSamples = buffer.getNumSamples();

    constexpr float twoPi = juce::MathConstants<float>::twoPi;
    constexpr float minimumDelayMilliseconds = 10.0f;
    constexpr float baseDelayMilliseconds = 20.0f;
    constexpr float delaySwingMilliseconds = 10.0f;

    const auto clampedRate = juce::jlimit (0.05f, 8.0f, rateHz);
    const auto clampedDepth = juce::jlimit (0.0f, 1.0f, depth);
    const auto clampedMix = juce::jlimit (0.0f, 1.0f, mix);
    const auto outputGain = juce::Decibels::decibelsToGain (volumeDecibels);
    const auto phaseIncrement = twoPi * clampedRate / static_cast<float> (currentSampleRate);

    for (int sampleIndex = 0; sampleIndex < numSamples; ++sampleIndex)
    {
        // The LFO moves the wet delay around 20 ms. A fractional delay read creates
        // the small pitch movement that makes the doubled guitar sound chorus-like.
        const auto lfo = 0.5f + 0.5f * std::sin (lfoPhase);
        const auto delayMilliseconds = minimumDelayMilliseconds
                                     + (baseDelayMilliseconds - minimumDelayMilliseconds)
                                     + (lfo - 0.5f) * 2.0f * delaySwingMilliseconds * clampedDepth;
        const auto delaySamples = (delayMilliseconds / 1000.0f) * static_cast<float> (currentSampleRate);

        for (int channel = 0; channel < numChannels; ++channel)
        {
            auto* channelData = buffer.getWritePointer (channel);
            const auto drySample = channelData[sampleIndex];
            const auto wetSample = readDelayedSample (channel, delaySamples);

            pushSample (channel, drySample);

            channelData[sampleIndex] = ((drySample * (1.0f - clampedMix)) + (wetSample * clampedMix)) * outputGain;
        }

        ++writePosition;
        if (writePosition >= delayBufferSize)
            writePosition = 0;

        lfoPhase += phaseIncrement;
        if (lfoPhase >= twoPi)
            lfoPhase -= twoPi;
    }
}

float PluginDSP::readDelayedSample (int channel, float delayInSamples) const
{
    const auto& delayLine = delayLines[static_cast<size_t> (channel)];
    auto readPosition = static_cast<float> (writePosition) - delayInSamples;

    while (readPosition < 0.0f)
        readPosition += static_cast<float> (delayBufferSize);

    const auto index0 = static_cast<int> (readPosition);
    const auto index1 = (index0 + 1) % delayBufferSize;
    const auto fraction = readPosition - static_cast<float> (index0);

    return delayLine[static_cast<size_t> (index0)] * (1.0f - fraction)
         + delayLine[static_cast<size_t> (index1)] * fraction;
}

void PluginDSP::pushSample (int channel, float sample)
{
    delayLines[static_cast<size_t> (channel)][static_cast<size_t> (writePosition)] = sample;
}
