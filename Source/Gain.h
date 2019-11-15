/*
  ==============================================================================

    Gain.h
    Created: 17 Dec 2018 1:34:34pm
    Author:  Guillermo Reyes

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class Gain :
    public dsp::ProcessorBase
{
public:
    struct Parameters :
        dsp::ProcessorState
    {
        float gain = 1.0f;
        using Ptr = ReferenceCountedObjectPtr<Parameters>;
    };

    Gain() = default;
    ~Gain() = default;

    void prepare(const dsp::ProcessSpec& spec) noexcept override
    {
        gain.prepare(spec);
        gain.processor.setRampDurationSeconds(0.1); // TODO: Test and tweak this.
    }

    void process(const dsp::ProcessContextReplacing<float>& context) noexcept override
    {
        gain.processor.setGainLinear(params->gain);
        gain.process(context);
    }

    void reset() noexcept override
    {
        gain.reset();
    }

    Parameters::Ptr params = new Parameters;

private:
    dsp::ProcessorWrapper<dsp::Gain<float>> gain;

};
