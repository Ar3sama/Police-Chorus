#include "PluginLookAndFeel.h"

PluginLookAndFeel::PluginLookAndFeel()
{
    setColour (juce::ResizableWindow::backgroundColourId, juce::Colour::fromRGB (24, 24, 24));
    setColour (juce::Label::textColourId, juce::Colours::white);
    setColour (juce::TextButton::buttonColourId, juce::Colour::fromRGB (52, 52, 56));
    setColour (juce::TextButton::buttonOnColourId, juce::Colour::fromRGB (220, 180, 70));
    setColour (juce::TextButton::textColourOffId, juce::Colours::white);
    setColour (juce::TextButton::textColourOnId, juce::Colours::black);
    setColour (juce::Slider::rotarySliderFillColourId, juce::Colour::fromRGB (220, 180, 70));
    setColour (juce::Slider::rotarySliderOutlineColourId, juce::Colour::fromRGB (70, 70, 76));
    setColour (juce::Slider::thumbColourId, juce::Colours::white);
    setColour (juce::Slider::textBoxTextColourId, juce::Colours::white);
    setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour::fromRGB (32, 32, 36));
    setColour (juce::Slider::textBoxOutlineColourId, juce::Colour::fromRGB (70, 70, 76));
}
