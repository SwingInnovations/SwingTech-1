#ifndef SWINGTECH1_STFONTMETRICS_H
#define SWINGTECH1_STFONTMETRICS_H

extern "C"{
#include <ft2build.h>
#include FT_FREETYPE_H
};

#include <string>

struct FTFontMetics{
    static void bounds(const std::string& text, const int fontSize, const std::string fontFile, int* width, int* height){
        FT_Library ft;
        if(FT_Init_FreeType(&ft)){ return; }

        FT_Face face;
        if(FT_New_Face(ft, fontFile.c_str(), 0, &face)){ return; }
        for(unsigned int i = 0; i < 128; i++){
            if(FT_Load_Char(face, i, FT_LOAD_RENDER)){ continue; }
                //TODO Parse through files to find bounds.
        }
    }
};

#endif //SWINGTECH1_STFONTMETRICS_H
