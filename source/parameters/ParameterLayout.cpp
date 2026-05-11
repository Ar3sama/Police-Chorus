#include "ParameterLayout.h"
#include "ParameterIDs.h"

namespace Parameters
{
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
    {
        std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

        parameters.push_back (std::make_unique<juce::AudioParameterFloat> (
            ParameterIDs::rate,
            "Rate",
            juce::NormalisableRange<float> { 0.05f, 8.0f, 0.01f, 0.45f },
            0.80f,
            juce::AudioParameterFloatAttributes().withLabel ("Hz")));

        parameters.push_back (std::make_unique<juce::AudioParameterFloat> (
            ParameterIDs::depth,
            "Depth",
            juce::NormalisableRange<float> { 0.0f, 1.0f, 0.001f },
            0.55f));

        parameters.push_back (std::make_unique<juce::AudioParameterFloat> (
            ParameterIDs::mix,
            "Mix",
            juce::NormalisableRange<float> { 0.0f, 1.0f, 0.001f },
            0.35f));

        parameters.push_back (std::make_unique<juce::AudioParameterFloat> (
            ParameterIDs::volume,
            "Volume",
            juce::NormalisableRange<float> { -24.0f, 6.0f, 0.1f },
            0.0f,
            juce::AudioParameterFloatAttributes().withLabel ("dB")));

        parameters.push_back (std::make_unique<juce::AudioParameterBool> (
            ParameterIDs::bypass,
            "Bypass",
            false));

        return { parameters.begin(), parameters.end() };
    }
}
