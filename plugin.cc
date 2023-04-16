#include "plugin.hh"

#include <cmath>

#include "util.hh"

using namespace std;

namespace Dynamite {
    void Drive::run(uint32_t n_samples) {
        const float coeff = dbCo(*p(p_drive));
        const float threshCoeff = dbCo(*p(p_threshold));
        const float gainCoeff = dbCo(*p(p_gain));
        const float mix = *p(p_mix);
        const float algoMix = *p(p_algorithm_mix);
        const float transmogrifier = dbCo(*p(p_transmogrify_gain));
        const float transmogrifyThreshold = dbCo(*p(p_transmogrify_threshold));

        const float *input = p(p_audio_in);
        float *output = p(p_audio_out);

        for(uint32_t pos = 0; pos < n_samples; pos++) {
            float dist = input[pos] * coeff;

            if(dist > threshCoeff) {
                dist = threshCoeff;
            } else if (dist < -threshCoeff) {
                dist = -threshCoeff;
            }

            dist = dist * gainCoeff;

            float transmogrified = (input[pos] < 0 ? -transmogrifier : transmogrifier);

            if(abs(input[pos]) < transmogrifyThreshold) transmogrified = 0;

            output[pos] = (mix * ((algoMix * transmogrified) + ((1.0 - algoMix) * dist))) + ((1.0 - mix) * input[pos] * gainCoeff);
        }
    }
}
