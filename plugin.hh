#pragma once
#include <stdint.h>

namespace Dynamite {
    enum PluginPort {
        IN, OUT, DRIVE
    };

    class Plugin {
        const float *drive;
        const float *input;
        float *output;
    public:
        void connect_port(PluginPort port, void* data);
        void activate();
        void run(uint32_t n_samples);
        void deactivate();
    };
}