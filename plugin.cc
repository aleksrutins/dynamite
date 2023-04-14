#include <lv2/core/lv2.h>
#include "plugin.hh"
#include "util.hh"

namespace Dynamite {
    void Plugin::activate() {
        
    }

    void Plugin::connect_port(PluginPort port, void* data) {
        switch(port) {
            case IN:
                input = (const float *)data;
                break;
            case OUT:
                output = (float *)data;
                break;
            case DRIVE:
                drive = (const float *)data;
                break;
        }
    }

    void Plugin::run(uint32_t n_samples) {
        const float coeff = dbCo(*drive);

        for(uint32_t pos = 0; pos < n_samples; pos++) {
            output[pos] = input[pos] * coeff;
        }
    }

    void Plugin::deactivate() {}
}