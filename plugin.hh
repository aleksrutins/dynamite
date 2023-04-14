#pragma once
#include <lv2plugin.hpp>
#include <stdint.h>

using namespace LV2;

namespace Dynamite {
    enum PluginPort {
        IN, OUT, DRIVE, THRESHOLD
    };

    class Drive : public Plugin<Drive> {
        const float *drive;
        const float *input;
        float *output;
    public:
        Drive(double rate) : Plugin<Drive>(1) {}
        void connect_port(uint32_t port, void* data);
        void run(uint32_t n_samples);
    };
}