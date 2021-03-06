#pragma once

#include "../mec_push2.h"

namespace mec {

class P2_ModuleMode : public P2_DisplayMode {
public:
    P2_ModuleMode(mec::Push2 &parent, const std::shared_ptr<Push2API::Push2> &api);

    void processNoteOn(unsigned n, unsigned v) override;
    void processNoteOff(unsigned n, unsigned v) override;
    void processCC(unsigned cc, unsigned v) override;
    void activate() override;
private:
    void displayPage();
    void drawParam(unsigned pos, const Kontrol::Parameter &param);

    Push2 &parent_;
    std::shared_ptr<Push2API::Push2> push2Api_;
    std::shared_ptr<Kontrol::KontrolModel> model_;
    std::set<std::string>  modules_;
    std::set<std::string> categories_;

    unsigned selectedModuleIdx_;
    unsigned moduleOffset_;
    unsigned selectedCatIdx_;
    unsigned catOffset_;
};

}
