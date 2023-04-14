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
            case GAIN:
                gain = (const float *)data;
        }
    }

    void Drive::run(uint32_t n_samples) {
        const float coeff = dbCo(*drive);
        const float threshCoeff = dbCo(*threshold);
        const float gainCoeff = dbCo(*gain);

        for(uint32_t pos = 0; pos < n_samples; pos++) {
            output[pos] = input[pos] * coeff;
            if(output[pos] > threshCoeff) {
                output[pos] = threshCoeff;
            } else if (output[pos] < -threshCoeff) {
                output[pos] = -threshCoeff;
            }
            output[pos] = output[pos] * gainCoeff;
        }
    }
}