/*
 ==============================================================================

 This file is part of the JUCE library.
 Copyright (c) 2015 - ROLI Ltd.

 Permission is granted to use this software under the terms of either:
 a) the GPL v2 (or any later version)
 b) the Affero GPL v3

 Details of these licenses can be found at: www.gnu.org/licenses

 JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

 ------------------------------------------------------------------------------

 To release a closed-source product which uses JUCE, commercial licenses are
 available: visit www.juce.com for more information.

 ==============================================================================
 */



class PyoAuEditor : public AudioProcessorEditor
{
public:
    enum
    {
        paramControlHeight = 40,
        paramLabelWidth    = 80,
        paramSliderWidth   = 300
    };


    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    PyoAuEditor (AudioProcessor& parent, AudioProcessorValueTreeState& vts)
        : AudioProcessorEditor (parent),
          valueTreeState (vts)
    {
        cfreqLabel.setText ("C. Freq", dontSendNotification);
        addAndMakeVisible (cfreqLabel);

        qLabel.setText ("Q", dontSendNotification);
        addAndMakeVisible (qLabel);

        addAndMakeVisible (cfreqSlider);
        cfreqAttachment = new SliderAttachment (valueTreeState, "cfreq", cfreqSlider);

        addAndMakeVisible (qSlider);
        qAttachment = new SliderAttachment (valueTreeState, "q", qSlider);

        setSize (paramSliderWidth + paramLabelWidth, paramControlHeight * 2);
    }

    ~PyoAuEditor()
    {
    }

    void resized() override
    {
        Rectangle<int> r = getLocalBounds();

        {
            Rectangle<int> cfreqRect = r.removeFromTop (paramControlHeight);
            Rectangle<int> qRect = r.removeFromTop (paramControlHeight);
            cfreqLabel.setBounds (cfreqRect.removeFromLeft (paramLabelWidth));
            qLabel.setBounds (qRect.removeFromLeft (paramLabelWidth));
            cfreqSlider.setBounds (cfreqRect);
            qSlider.setBounds (qRect);
        }
    }

    void paint (Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    }


private:
    AudioProcessorValueTreeState& valueTreeState;

    Label cfreqLabel;
    Slider cfreqSlider;
    ScopedPointer<SliderAttachment> cfreqAttachment;

    Label qLabel;
    Slider qSlider;
    ScopedPointer<SliderAttachment> qAttachment;


};
