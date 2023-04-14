#include <lv2/core/lv2.h>
#include "plugin.hh"

using Dynamite::Plugin;

static LV2_Handle
instantiate(const LV2_Descriptor*     descriptor,
            double                    rate,
            const char*               bundle_path,
            const LV2_Feature* const* features)
{
    return new Plugin;
}

static void
cleanup(LV2_Handle instance)
{
    delete (Plugin *)instance;
}

static const void*
extension_data(const char *uri)
{
    return nullptr;
}

static const LV2_Descriptor descriptor = {
    "https://github.com/aleksrutins/dynamite",
    instantiate,
    (void (*)(LV2_Handle, uint32_t, void*)) &Plugin::connect_port,
    (void (*)(LV2_Handle)) &Plugin::activate,
    (void (*)(LV2_Handle, uint32_t)) &Plugin::run,
    (void (*)(LV2_Handle)) &Plugin::deactivate,
    cleanup,
    extension_data
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index) {
    return index == 0 ? &descriptor : nullptr;
}