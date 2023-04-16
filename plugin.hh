#pragma once
#include <lv2plugin.hpp>
#include <stdint.h>
#include "dynamite.peg"

using namespace LV2;

namespace Dynamite {
    enum PluginPort {
        IN, OUT, DRIVE, THRESHOLD, GAIN, MIX
    };

    class Drive : public Plugin<Drive> {
    public:
        Drive(double rate) : Plugin<Drive>(p_n_ports) {}
        void run(uint32_t n_samples);
    };
}