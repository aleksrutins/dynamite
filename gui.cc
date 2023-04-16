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
        Scale *transmogrify_scale;
        Scale *create_scale(p_port_enum nport, Orientation orient = ORIENTATION_VERTICAL) {
            auto port = p_ports[nport];
            Scale *result = manage(orient == ORIENTATION_VERTICAL ? (Scale *)new VScale(port.min, port.max, 0.01) : (Scale *)new HScale(port.min, port.max, 0.01));
            auto scale_slot = bind<0>(bind<0>(bind<0>(&DriveGUI::write_control_ptr, this), (uint32_t)nport), result);
            result->signal_value_changed().connect(scale_slot);
            return result;
        }
    public:
        DriveGUI(const std::string &url) {
            auto vbox = manage(new VBox(false, 6));
            auto hbox = manage(new HBox(false, 6));

            vbox->add(*manage(new Label("Dynamite")));

            drive_scale = create_scale(p_drive);
            hbox->add(*manage(new LabeledWidget("Drive", *drive_scale)));
            threshold_scale = create_scale(p_threshold);
            hbox->add(*manage(new LabeledWidget("Threshold", *threshold_scale)));
            gain_scale = create_scale(p_gain);
            hbox->add(*manage(new LabeledWidget("Gain", *gain_scale)));
            
            vbox->add(*hbox);

            transmogrify_scale = create_scale(p_algorithm_mix, ORIENTATION_HORIZONTAL);
            vbox->add(*manage(new LabeledWidget("Transmogrify", *transmogrify_scale)));
            mix_scale = create_scale(p_mix, ORIENTATION_HORIZONTAL);
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
                case p_algorithm_mix:
                    transmogrify_scale->set_value(value); break;
                case p_mix:
                    mix_scale->set_value(value); break;

            }
        }
    };
}

static int _ = Dynamite::DriveGUI::register_class("https://github.com/aleksrutins/dynamite/gui");
