#ifndef GEFX_COLOR_H_
#define GEFX_COLOR_H_
namespace Fx{
struct RGB{
union{struct{unsigned char r; unsigned char g; unsigned char b;};struct{float el[3];};};

constexpr int operator[](const unsigned char& ind)
{
    if(ind>2)return -1;
    return el[ind];
}

constexpr void invert()
{
    r=255-r;
    g=255-g;
    b=255-b;
}
constexpr void lighten()
{
const float fact{0.0625};
r+=(255-r)*fact;
g+=(255-g)*fact;
b+=(255-b)*fact;
}
constexpr void darken()
{
const float fact{0.9375};
r*=fact;
g*=fact;
b*=fact;
}
};


constexpr unsigned char RGB_CAP{255};
//Standard colors 
constexpr RGB MAROON{128,0,0};
constexpr RGB DARK_RED{139,0,0};
constexpr RGB BROWN{165,42,42};
constexpr RGB FIREBRICK{178,34,34};
constexpr RGB CRIMSON{220,20,60};
constexpr RGB RED {255,0,0};
constexpr RGB TOMATO{255,99,71};
constexpr RGB CORAL{255,127,80};
constexpr RGB INDIAN_RED{205,92,92};
constexpr RGB LIGHT_CORAL{240,128,128};
constexpr RGB DARK_SALMON{233,150,122};
constexpr RGB SALMON{250,128,114};
constexpr RGB LIGHT_SALMON{255,160,122};
constexpr RGB ORANGE_RED{255,69,0};
constexpr RGB DARK_ORANGE{255,140,0};
constexpr RGB ORANGE{255,165,0};
constexpr RGB GOLD{255,215,0};
constexpr RGB DARK_GOLDEN_ROD{184,134,11};
constexpr RGB GOLDEN_ROD{218,165,32};
constexpr RGB PALE_GOLDEN_ROD{238,232,170};
constexpr RGB DARK_KHAKI{189,183,107};
constexpr RGB KHAKI{240,230,140};
constexpr RGB OLIVE{128,128,0};
constexpr RGB YELLOW{255,255,0};
constexpr RGB YELLOW_GREEN{154,205,50};
constexpr RGB DARK_OLIVE_GREEN{85,107,47};
constexpr RGB OLIVE_DRAB{107,142,35};
constexpr RGB LAWN_GREEN{124,252,0};
constexpr RGB CHARTREUSE{127,255,0};
constexpr RGB GREEN_YELLOW{173,255,47};
constexpr RGB DARK_GREEN{0,100,0};
constexpr RGB GREEN{0,128,0};
constexpr RGB FOREST_GREEN{24,139,34};
constexpr RGB LIME{0,255,0};
constexpr RGB LIME_GREEN{50,205,50};
constexpr RGB LIGHT_GREEN{144,238,144};
constexpr RGB PALE_GREEN{152,251,152};
constexpr RGB DARK_SEA_GREEN{143,188,143};
constexpr RGB MEDIUM_SPRING_GREEN{0,250,154};
constexpr RGB SPRING_GREEN{0,255,127};
constexpr RGB SEA_GREEN{46,139,87};
constexpr RGB MEDIUM_AQUA_MARINE{102,205,170};
constexpr RGB MEDIUM_SEA_GREEN{60,179,113};
constexpr RGB LIGHT_SEA_GREEN{32,178,170};
constexpr RGB DARK_SLATE_GRAY{47,79,79};
constexpr RGB TEAL{0,128,128};
constexpr RGB DARK_CYAN{0,139,139};
constexpr RGB AQUA{0,255,255};
constexpr RGB CYAN{0,255,255};
constexpr RGB LIGHT_CYAN{224,225,225};
constexpr RGB DARK_TURQUOISE{0,206,209};
constexpr RGB TURQUOISE{64,224,208};
constexpr RGB MEDIUM_TURQUOISE{72,209,204};
constexpr RGB PALE_TURQUOISE{175,238,238};
constexpr RGB AQUAMARINE{127,255,212};
constexpr RGB POWDER_BLUE{176,224,230};
constexpr RGB CADET_BLUE{95,158,160};
constexpr RGB STEEL_BLUE{70,130,180};
constexpr RGB CORN_FLOWER_BLUE{100,149,237};
constexpr RGB DEEP_SKY_BLUE{0,191,255};
constexpr RGB DODGER_BLUE{30,144,255};
constexpr RGB LIGHT_BLUE{173,216,230};
constexpr RGB SKY_BLUE{135,206,235};
constexpr RGB LIGHT_SKY_BLUE{135,206,250};
constexpr RGB MIDNIGHT_BLUE{25,25,112};
constexpr RGB NAVY{0,0,128};
constexpr RGB DARK_BLUE{0,0,139};
constexpr RGB MEDIUM_BLUE{0,0,205};
constexpr RGB BLUE{0,0,255};
constexpr RGB ROYAL_BLUE{65,105,225};
constexpr RGB BLUE_VIOLET{138,43,226};
constexpr RGB INDIGO{75,0,130};
constexpr RGB DARK_SLATE_BLUE{72,61,139};
constexpr RGB SLATE_BLUE{106,90,205};
constexpr RGB MEDIUM_SLATE_BLUE{123,104,238};
constexpr RGB MEDIUM_PURPLE{147,112,219};
constexpr RGB DARK_MAGENTA{139,0,139};
constexpr RGB DARK_VIOLET{148,0,211};
constexpr RGB DARK_ORCHID{153,50,204};
constexpr RGB MEDIUM_ORCHID{186,85,211};
constexpr RGB PURPLE{128,0,128};
constexpr RGB THISTLE{216,191,216};
constexpr RGB PLUM{221,160,221};
constexpr RGB VIOLET{238,130,238};
constexpr RGB MAGENTA{255,0,255};
constexpr RGB ORCHID{218,112,214};
constexpr RGB MEDIUM_VIOLET_RED{199,21,133};
constexpr RGB PALE_VIOLET_RED{219,112,147};
constexpr RGB DEEP_PINK{255,20,147};
constexpr RGB HOT_PINK{255,105,180};
constexpr RGB LIGHT_PINK{255,182,193};
constexpr RGB PINK{255,192,203};
constexpr RGB ANTIQUE_WHITE{250,235,215};
constexpr RGB BEIGE{245,245,220};
constexpr RGB BISQUE{255,228,196};
constexpr RGB BLANCHED_ALMOND{255,235,205};
constexpr RGB WHEAT{245,222,179};
constexpr RGB CORN_SILK{255,248,220};
constexpr RGB LEMON_CHIFFON{255,250,205};
constexpr RGB LIGHT_GOLDEN_ROD_YELLOW{250,250,210};
constexpr RGB LIGHT_YELLOW{255,255,224};
constexpr RGB SADDLE_BROWN{139,69,19};
constexpr RGB SIENNA{160,82,45};
constexpr RGB CHOCOLATE{210,105,30};
constexpr RGB PERU{205,133,63};
constexpr RGB SANDY_BROWN{244,164,96};
constexpr RGB BURLY_WOOD{222,184,135};
constexpr RGB TAN{210,180,140};
constexpr RGB ROSY_BROWN{188,143,143};
constexpr RGB MOCCASIN{255,228,181};
constexpr RGB NAVAJO_WHITE{255,222,173};
constexpr RGB PEACH_PUFF{255,218,185};
constexpr RGB MISTY_ROSE{255,228,225};
constexpr RGB LAVENDER_BLUSH{255,240,245};
constexpr RGB LINEN{250,240,230};
constexpr RGB OLD_LACE{253,245,230};
constexpr RGB PAPAYA_WHIP{255,239,213}; 
constexpr RGB SEA_SHELL{255,245,238};
constexpr RGB MINT_CREAM{245,255,250};
constexpr RGB SLATE_GRAY{112,128,144};
constexpr RGB LIGHT_SLATE_GRAY{119,136,153};
constexpr RGB LIGHT_STEEL_BLUE{176,196,222};
constexpr RGB LAVENDER{230,230,250};
constexpr RGB FLORAL_WHITE{255,250,240};
constexpr RGB ALICE_BLUE{240,248,255};
constexpr RGB GHOST_WHITE{248,248,255};
constexpr RGB HONEYDEW{240,255,240};
constexpr RGB IVORY{255,255,240};
constexpr RGB AZURE{240,255,255};
constexpr RGB SNOW{255,250,250};
constexpr RGB BLACK{0,0,0};
constexpr RGB DIM_GRAY{105,105,105};
constexpr RGB GRAY{128,128,128};
constexpr RGB DARK_GRAY{169,169,169};
constexpr RGB SILVER{192,192,192};
constexpr RGB LIGHT_GRAY{211,211,211};
constexpr RGB GAINSBORO{220,220,220};
constexpr RGB WHITE_SMOKE{245,245,245};
constexpr RGB WHITE{255,255,255};

constexpr RGB invert(const RGB& color)
{
    return {static_cast<unsigned char>(RGB_CAP-color.r),static_cast<unsigned char>(RGB_CAP-color.g),static_cast<unsigned char>(RGB_CAP-color.b)};
}
}
#endif