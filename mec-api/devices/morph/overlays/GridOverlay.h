#ifndef MEC_GRIDOVERLAY_H
#define MEC_GRIDOVERLAY_H

#include "OverlayFunction.h"

namespace mec {
namespace morph {

class GridOverlay : public OverlayFunction {
public:
    GridOverlay(const std::string &name, ISurfaceCallback &surfaceCallback, ICallback &callback);

    virtual bool init(const Preferences &preferences);

    virtual bool interpretTouches(const Touches &touches);

private:
    int rows_;
    int columns_;
    float semitoneOffsetPerRow_;
    float baseNote_;

    float xyPosToNote(float xPos, float yPos);

    float normalizeXPos(float xPos);

    float normalizeYPos(float yPos);

    float normalizeZPos(float zPos);
};

}
}


#endif //MEC_GRIDOVERLAY_H
