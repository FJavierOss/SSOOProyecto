#include "frames.h"

Frame frame_init(){
    Frame f;
    for (int byte = 0; byte < 8388608; byte ++){
        f.info[byte] = 0;
    }
    return f;
};

Frames frames_init(){
    Frames fs;
    for (int frame = 0; frame < 128; frame ++){
        fs.frames[frame] = frame_init();
    }
    return fs;
};
