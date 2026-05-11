#pragma once

#include "PluginProcessor.h"
#include "ui/lookandfeel/PluginLookAndFeel.h"

//==============================================================================
class AudioPluginAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.


    AudioPluginAudioProcessor& processorRef;

    PluginLookAndFeel lookAndFeel;
    juce::Label titleLabel;
    juce::TextButton bypassButton { "Bypass" };

    juce::Slider rateSlider;
    juce::Slider depthSlider;
    juce::Slider mixSlider;
    juce::Slider volumeSlider;

    juce::Label rateLabel;
    juce::Label depthLabel;
    juce::Label mixLabel;
    juce::Label volumeLabel;

    std::unique_ptr<SliderAttachment> rateAttachment;
    std::unique_ptr<SliderAttachment> depthAttachment;
    std::unique_ptr<SliderAttachment> mixAttachment;
    std::unique_ptr<SliderAttachment> volumeAttachment;
    std::unique_ptr<ButtonAttachment> bypassAttachment;

    void configureRotarySlider (juce::Slider& slider, juce::Label& label, const juce::String& labelText);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
