# PyoFilter
Filter Plug in using Juce and Pyo

This is my first attempt to build plug-ins using Juce and Pyo.

Audio Units build and work well in some hosts.  VST plugins will build, but will not load into any host.
I am a novice C++ programmer which probably explains the known issues.

You must have Pyo installed to run the plug-in.
http://ajaxsoundstudio.com/software/pyo/

This plug-in is based on:

Olivier Bélanger's Pyo embedded tutorial.

https://github.com/belangeo/pyo/tree/master/embedded/juceplugin


Juce tutorials

https://www.juce.com/tutorials


Redwood Audio's Tutorial

http://www.redwoodaudio.net/Tutorials/juce_for_vst_development__intro3.html


Known Issues

OSX
- Audio Units will build and load into Reaper and Logic but fail to load into Max, Juce Plugin Host,Tracktion.
- VST will build but fail to load into any host

Win
- VST will build but fail to load into any host.


