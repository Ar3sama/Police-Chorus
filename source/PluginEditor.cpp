#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "PluginConfig.h"
#include "parameters/ParameterIDs.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    setLookAndFeel (&lookAndFeel);

    titleLabel.setText ("Police Chorus", juce::dontSendNotification);
    titleLabel.setJustificationType (juce::Justification::centred);
    titleLabel.setFont (juce::FontOptions { 20.0f, juce::Font::bold });
    addAndMakeVisible (titleLabel);

    configureRotarySlider (rateSlider, rateLabel, "Rate");
    configureRotarySlider (depthSlider, depthLabel, "Depth");
    configureRotarySlider (mixSlider, mixLabel, "Mix");
    configureRotarySlider (volumeSlider, volumeLabel, "Volume");

    bypassButton.setClickingTogglesState (true);
    addAndMakeVisible (bypassButton);

    rateAttachment = std::make_unique<SliderAttachment> (
        processorRef.parameters, ParameterIDs::rate, rateSlider);
    depthAttachment = std::make_unique<SliderAttachment> (
        processorRef.parameters, ParameterIDs::depth, depthSlider);
    mixAttachment = std::make_unique<SliderAttachment> (
        processorRef.parameters, ParameterIDs::mix, mixSlider);
    volumeAttachment = std::make_unique<SliderAttachment> (
        processorRef.parameters, ParameterIDs::volume, volumeSlider);
    bypassAttachment = std::make_unique<ButtonAttachment> (
        processorRef.parameters, ParameterIDs::bypass, bypassButton);

    setSize (PluginConfig::defaultEditorWidth, PluginConfig::defaultEditorHeight);
}


AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
    setLookAndFeel (nullptr);
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (findColour (juce::ResizableWindow::backgroundColourId));
}

void AudioPluginAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced (PluginConfig::editorMargin);

    titleLabel.setBounds (area.removeFromTop (40));
    area.removeFromTop (18);

    auto controlsArea = area.removeFromTop (180);
    const auto controlWidth = controlsArea.getWidth() / 4;

    auto placeControl = [&controlsArea, controlWidth] (juce::Slider& slider, juce::Label& label)
    {
        auto controlArea = controlsArea.removeFromLeft (controlWidth).reduced (8, 0);
        label.setBounds (controlArea.removeFromBottom (24));
        slider.setBounds (controlArea);
    };

    placeControl (rateSlider, rateLabel);
    placeControl (depthSlider, depthLabel);
    placeControl (mixSlider, mixLabel);
    placeControl (volumeSlider, volumeLabel);

    bypassButton.setBounds (area.removeFromBottom (26).withSizeKeepingCentre (76, 24));
}

void AudioPluginAudioProcessorEditor::configureRotarySlider (juce::Slider& slider,
                                                             juce::Label& label,
                                                             const juce::String& labelText)
{
    slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 72, 20);
    slider.setDoubleClickReturnValue (true, 0.0);
    addAndMakeVisible (slider);

    label.setText (labelText, juce::dontSendNotification);
    label.setJustificationType (juce::Justification::centred);
    label.setFont (juce::FontOptions { 14.0f, juce::Font::bold });
    addAndMakeVisible (label);
}
