#include <glibmm.h>
#include <gtkmm.h>
#include <lv2gui.hpp>
#include <stdint.h>
#include <stdlib.h>

#include "dynamite.peg"

using namespace sigc;
using namespace Gtk;

namespace Dynamite {
    class LabeledWidget : public VBox {
    public:
        LabeledWidget(const Glib::ustring &label, Widget &child) {
            add(child);
            add(*manage(new Label(label)));
        }
    };

    class DriveGUI : public LV2::GUI<DriveGUI> {
    protected:
        Scale *drive_scale;
        Scale *threshold_scale;
        Scale *gain_scale;
        Scale *mix_scale;
        Scale *create_vscale(p_port_enum nport) {
            auto port = p_ports[nport];
            auto result = manage(new VScale(port.min, port.max, 0.01));
            auto scale_slot = bind<0>(bind<0>(bind<0>(&DriveGUI::write_control_ptr, this), (uint32_t)nport), result);
            result->signal_value_changed().connect(scale_slot);
            return result;
        }
    public:
        DriveGUI(const std::string &url) {
            auto vbox = manage(new VBox(false, 6));
            auto hbox = manage(new HBox(false, 6));

            vbox->add(*manage(new Label("Dynamite")));

            drive_scale = create_vscale(p_drive);
            hbox->add(*manage(new LabeledWidget("Drive", *drive_scale)));
            threshold_scale = create_vscale(p_threshold);
            hbox->add(*manage(new LabeledWidget("Threshold", *threshold_scale)));
            gain_scale = create_vscale(p_gain);
            hbox->add(*manage(new LabeledWidget("Gain", *gain_scale)));
            
            vbox->add(*hbox);

            auto mix = p_ports[p_mix];
            mix_scale = manage(new HScale(mix.min, mix.max, 0.01));
            auto mix_slot = bind<0>(bind<0>(bind<0>(&DriveGUI::write_control_ptr, this), (uint32_t)p_mix), mix_scale);
            mix_scale->signal_value_changed().connect(mix_slot);
            vbox->add(*manage(new LabeledWidget("Mix", *mix_scale)));
            add(*vbox);
        }

        static void write_control_ptr(DriveGUI *self, uint32_t port, Scale *ctrl) {
            self->write_control(port, ctrl->get_value());
        }

        void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void *buffer) {
            auto value = *static_cast<const float *>(buffer);
            switch((p_port_enum)port) {
                case p_drive:
                    drive_scale->set_value(value); break;
                case p_threshold:
                    threshold_scale->set_value(value); break;
                case p_gain:
                    gain_scale->set_value(value); break;
                case p_mix:
                    mix_scale->set_value(value); break;

            }
        }
    };
}

static int _ = Dynamite::DriveGUI::register_class("https://github.com/aleksrutins/dynamite/gui");
