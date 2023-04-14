#include "plugin.hh"
#include "util.hh"

namespace Dynamite {
    void Drive::connect_port(uint32_t port, void* data) {
        switch((PluginPort)port) {
            case IN:
                input = (const float *)data;
                break;
            case OUT:
                output = (float *)data;
                break;
            case DRIVE:
                drive = (const float *)data;
                break;
            case THRESHOLD:
                threshold = (const float *)data;
                break;
        }
    }

    void Drive::run(uint32_t n_samples) {
        const float coeff = dbCo(*drive);

        for(uint32_t pos = 0; pos < n_samples; pos++) {
            output[pos] = input[pos] * coeff;
            if(output[pos] > *threshold) {
                output[pos] = *threshold;
            } else if (output[pos] < -*threshold) {
                output[pos] = -*threshold;
            }
        }
    }
}