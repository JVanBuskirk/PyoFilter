/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PyoAUEditor.h"



//==============================================================================
PyoFilterAudioProcessor::PyoFilterAudioProcessor():
#ifndef JucePlugin_PreferredChannelConfigurations
        AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
        parameters (*this, nullptr)
{
        parameters.createAndAddParameter ("cfreq",       // parameterID
                                          "C. Freq.",       // parameter name
                                          String(),     // parameter label (suffix)
                                          NormalisableRange<float> (50.0f, 5000.0f),    // range
                                          440.0f,         // default value
                                          nullptr,
                                          nullptr);

        parameters.createAndAddParameter ("q",       // parameterID
                                          "Q",       // parameter name
                                          String(),     // parameter label (suffix)
                                          NormalisableRange<float> (1.0f, 100.0f),    // range
                                          5.0f,         // default value
                                          nullptr,
                                          nullptr);




        parameters.state = ValueTree (Identifier ("APVTSPyoAu"));
}

PyoFilterAudioProcessor::~PyoFilterAudioProcessor()
{
}

//==============================================================================
const String PyoFilterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PyoFilterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PyoFilterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double PyoFilterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PyoFilterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PyoFilterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PyoFilterAudioProcessor::setCurrentProgram (int index)
{
}

const String PyoFilterAudioProcessor::getProgramName (int index)
{
    return {};
}

void PyoFilterAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void PyoFilterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
        pyo.setup(getTotalNumOutputChannels(), samplesPerBlock, sampleRate);
        pyo.exec(BinaryData::pyoFilter_py);
}

void PyoFilterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PyoFilterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PyoFilterAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
        pyo.value("cfreq", *parameters.getRawParameterValue ("cfreq"));
        pyo.value("q", *parameters.getRawParameterValue ("q"));
        pyo.process(buffer);
}

//==============================================================================
bool PyoFilterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PyoFilterAudioProcessor::createEditor()
{
    return new PyoAuEditor (*this, parameters);
}

//==============================================================================
void PyoFilterAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    ScopedPointer<XmlElement> xml (parameters.state.createXml());
        copyXmlToBinary (*xml, destData);
}

void PyoFilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

        if (xmlState != nullptr)
            if (xmlState->hasTagName (parameters.state.getType()))
                parameters.state = ValueTree::fromXml (*xmlState);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PyoFilterAudioProcessor();
}
