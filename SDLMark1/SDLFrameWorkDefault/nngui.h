/*
 *  nnGUI is a minimalistic port for https://github.com/wjakob/nanogui
    nngui/nngui.h -- Pull in *everything* from nnGUI

    Original NanoGUI was developed by Wenzel Jakob <wenzel@inf.ethz.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    nnGUI was improved by Dalerank <dalerankn8@gmail.com>

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#ifndef NNGUI_HEADER_INCLUDE
#define NNGUI_HEADER_INCLUDE

#include <unordered_map>
#include <sstream>
#include <functional>
#include <atomic>
#include <vector>
#include <math.h>
#include <assert.h>
#include <istream>

#ifdef NNGUI_SDL
union SDL_Event;
struct SDL_Window;
#elif defined NNGUI_GLFW
struct GLFWwindow;
#endif

#if !defined(NAMESPACE_BEGIN)
#define NAMESPACE_BEGIN(name) namespace name {
#endif

#if !defined(NAMESPACE_END)
#define NAMESPACE_END(name) }
#endif

#if defined(_WIN32)
    #if defined(NNGUI_BUILD)
    /* Quench a few warnings on when compiling NNGUI on Windows */
    #pragma warning(disable : 4127) // warning C4127: conditional expression is constant
    #pragma warning(disable : 4244) // warning C4244: conversion from X to Y, possible loss of data
    #endif
//#pragma warning(disable : 4251) // warning C4251: class X needs to have dll-interface to be used by clients of class Y
//#pragma warning(disable : 4714) // warning C4714: funtion X marked as __forceinline not inlined
#endif

struct NVGcontext;
struct NVGcolor;
struct NVGglyphPosition;

NAMESPACE_BEGIN(nngui)

#ifdef _MSC_VER
#define NNGUI_SNPRINTF _snprintf
#else
#define NNGUI_SNPRINTF snprintf
#endif

enum class Alignment : uint8_t {
    Minimum = 0,
    Middle,
    Maximum,
    Fill
};

enum class Orientation {
    Horizontal = 0,
    Vertical
};

/**
 * This is a list of icon codes for the entypo.ttf font
 * by Daniel Bruce
 */
#define ENTYPO_ICON_PHONE                0x1F4DE
#define ENTYPO_ICON_MOBILE               0x1F4F1
#define ENTYPO_ICON_MOUSE                0xE789
#define ENTYPO_ICON_ADDRESS              0xE723
#define ENTYPO_ICON_MAIL                 0x2709
#define ENTYPO_ICON_PAPER_PLANE          0x1F53F
#define ENTYPO_ICON_PENCIL               0x270E
#define ENTYPO_ICON_FEATHER              0x2712
#define ENTYPO_ICON_ATTACH               0x1F4CE
#define ENTYPO_ICON_INBOX                0xE777
#define ENTYPO_ICON_REPLY                0xE712
#define ENTYPO_ICON_REPLY_ALL            0xE713
#define ENTYPO_ICON_FORWARD              0x27A6
#define ENTYPO_ICON_USER                 0x1F464
#define ENTYPO_ICON_USERS                0x1F465
#define ENTYPO_ICON_ADD_USER             0xE700
#define ENTYPO_ICON_VCARD                0xE722
#define ENTYPO_ICON_EXPORT               0xE715
#define ENTYPO_ICON_LOCATION             0xE724
#define ENTYPO_ICON_MAP                  0xE727
#define ENTYPO_ICON_COMPASS              0xE728
#define ENTYPO_ICON_DIRECTION            0x27A2
#define ENTYPO_ICON_HAIR_CROSS           0x1F3AF
#define ENTYPO_ICON_SHARE                0xE73C
#define ENTYPO_ICON_SHAREABLE            0xE73E
#define ENTYPO_ICON_HEART                0x2665
#define ENTYPO_ICON_HEART_EMPTY          0x2661
#define ENTYPO_ICON_STAR                 0x2605
#define ENTYPO_ICON_STAR_EMPTY           0x2606
#define ENTYPO_ICON_THUMBS_UP            0x1F44D
#define ENTYPO_ICON_THUMBS_DOWN          0x1F44E
#define ENTYPO_ICON_CHAT                 0xE720
#define ENTYPO_ICON_COMMENT              0xE718
#define ENTYPO_ICON_QUOTE                0x275E
#define ENTYPO_ICON_HOME                 0x2302
#define ENTYPO_ICON_POPUP                0xE74C
#define ENTYPO_ICON_SEARCH               0x1F50D
#define ENTYPO_ICON_FLASHLIGHT           0x1F526
#define ENTYPO_ICON_PRINT                0xE716
#define ENTYPO_ICON_BELL                 0x1F514
#define ENTYPO_ICON_LINK                 0x1F517
#define ENTYPO_ICON_FLAG                 0x2691
#define ENTYPO_ICON_COG                  0x2699
#define ENTYPO_ICON_TOOLS                0x2692
#define ENTYPO_ICON_TROPHY               0x1F3C6
#define ENTYPO_ICON_TAG                  0xE70C
#define ENTYPO_ICON_CAMERA               0x1F4F7
#define ENTYPO_ICON_MEGAPHONE            0x1F4E3
#define ENTYPO_ICON_MOON                 0x263D
#define ENTYPO_ICON_PALETTE              0x1F3A8
#define ENTYPO_ICON_LEAF                 0x1F342
#define ENTYPO_ICON_NOTE                 0x266A
#define ENTYPO_ICON_BEAMED_NOTE          0x266B
#define ENTYPO_ICON_NEW                  0x1F4A5
#define ENTYPO_ICON_GRADUATION_CAP       0x1F393
#define ENTYPO_ICON_BOOK                 0x1F4D5
#define ENTYPO_ICON_NEWSPAPER            0x1F4F0
#define ENTYPO_ICON_BAG                  0x1F45C
#define ENTYPO_ICON_AIRPLANE             0x2708
#define ENTYPO_ICON_LIFEBUOY             0xE788
#define ENTYPO_ICON_EYE                  0xE70A
#define ENTYPO_ICON_CLOCK                0x1F554
#define ENTYPO_ICON_MIC                  0x1F3A4
#define ENTYPO_ICON_CALENDAR             0x1F4C5
#define ENTYPO_ICON_FLASH                0x26A1
#define ENTYPO_ICON_THUNDER_CLOUD        0x26C8
#define ENTYPO_ICON_DROPLET              0x1F4A7
#define ENTYPO_ICON_CD                   0x1F4BF
#define ENTYPO_ICON_BRIEFCASE            0x1F4BC
#define ENTYPO_ICON_AIR                  0x1F4A8
#define ENTYPO_ICON_HOURGLASS            0x23F3
#define ENTYPO_ICON_GAUGE                0x1F6C7
#define ENTYPO_ICON_LANGUAGE             0x1F394
#define ENTYPO_ICON_NETWORK              0xE776
#define ENTYPO_ICON_KEY                  0x1F511
#define ENTYPO_ICON_BATTERY              0x1F50B
#define ENTYPO_ICON_BUCKET               0x1F4FE
#define ENTYPO_ICON_MAGNET               0xE7A1
#define ENTYPO_ICON_DRIVE                0x1F4FD
#define ENTYPO_ICON_CUP                  0x2615
#define ENTYPO_ICON_ROCKET               0x1F680
#define ENTYPO_ICON_BRUSH                0xE79A
#define ENTYPO_ICON_SUITCASE             0x1F6C6
#define ENTYPO_ICON_TRAFFIC_CONE         0x1F6C8
#define ENTYPO_ICON_GLOBE                0x1F30E
#define ENTYPO_ICON_KEYBOARD             0x2328
#define ENTYPO_ICON_BROWSER              0xE74E
#define ENTYPO_ICON_PUBLISH              0xE74D
#define ENTYPO_ICON_PROGRESS_3           0xE76B
#define ENTYPO_ICON_PROGRESS_2           0xE76A
#define ENTYPO_ICON_PROGRESS_1           0xE769
#define ENTYPO_ICON_PROGRESS_0           0xE768
#define ENTYPO_ICON_LIGHT_DOWN           0x1F505
#define ENTYPO_ICON_LIGHT_UP             0x1F506
#define ENTYPO_ICON_ADJUST               0x25D1
#define ENTYPO_ICON_CODE                 0xE714
#define ENTYPO_ICON_MONITOR              0x1F4BB
#define ENTYPO_ICON_INFINITY             0x221E
#define ENTYPO_ICON_LIGHT_BULB           0x1F4A1
#define ENTYPO_ICON_CREDIT_CARD          0x1F4B3
#define ENTYPO_ICON_DATABASE             0x1F4F8
#define ENTYPO_ICON_VOICEMAIL            0x2707
#define ENTYPO_ICON_CLIPBOARD            0x1F4CB
#define ENTYPO_ICON_CART                 0xE73D
#define ENTYPO_ICON_BOX                  0x1F4E6
#define ENTYPO_ICON_TICKET               0x1F3AB
#define ENTYPO_ICON_RSS                  0xE73A
#define ENTYPO_ICON_SIGNAL               0x1F4F6
#define ENTYPO_ICON_THERMOMETER          0x1F4FF
#define ENTYPO_ICON_WATER                0x1F4A6
#define ENTYPO_ICON_SWEDEN               0xF601
#define ENTYPO_ICON_LINE_GRAPH           0x1F4C8
#define ENTYPO_ICON_PIE_CHART            0x25F4
#define ENTYPO_ICON_BAR_GRAPH            0x1F4CA
#define ENTYPO_ICON_AREA_GRAPH           0x1F53E
#define ENTYPO_ICON_LOCK                 0x1F512
#define ENTYPO_ICON_LOCK_OPEN            0x1F513
#define ENTYPO_ICON_LOGOUT               0xE741
#define ENTYPO_ICON_LOGIN                0xE740
#define ENTYPO_ICON_CHECK                0x2713
#define ENTYPO_ICON_CROSS                0x274C
#define ENTYPO_ICON_SQUARED_MINUS        0x229F
#define ENTYPO_ICON_SQUARED_PLUS         0x229E
#define ENTYPO_ICON_SQUARED_CROSS        0x274E
#define ENTYPO_ICON_CIRCLED_MINUS        0x2296
#define ENTYPO_ICON_CIRCLED_PLUS         0x2295
#define ENTYPO_ICON_CIRCLED_CROSS        0x2716
#define ENTYPO_ICON_MINUS                0x2796
#define ENTYPO_ICON_PLUS                 0x2795
#define ENTYPO_ICON_ERASE                0x232B
#define ENTYPO_ICON_BLOCK                0x1F6AB
#define ENTYPO_ICON_INFO                 0x2139
#define ENTYPO_ICON_CIRCLED_INFO         0xE705
#define ENTYPO_ICON_HELP                 0x2753
#define ENTYPO_ICON_CIRCLED_HELP         0xE704
#define ENTYPO_ICON_WARNING              0x26A0
#define ENTYPO_ICON_CYCLE                0x1F504
#define ENTYPO_ICON_CW                   0x27F3
#define ENTYPO_ICON_CCW                  0x27F2
#define ENTYPO_ICON_SHUFFLE              0x1F500
#define ENTYPO_ICON_BACK                 0x1F519
#define ENTYPO_ICON_LEVEL_DOWN           0x21B3
#define ENTYPO_ICON_RETWEET              0xE717
#define ENTYPO_ICON_LOOP                 0x1F501
#define ENTYPO_ICON_BACK_IN_TIME         0xE771
#define ENTYPO_ICON_LEVEL_UP             0x21B0
#define ENTYPO_ICON_SWITCH               0x21C6
#define ENTYPO_ICON_NUMBERED_LIST        0xE005
#define ENTYPO_ICON_ADD_TO_LIST          0xE003
#define ENTYPO_ICON_LAYOUT               0x268F
#define ENTYPO_ICON_LIST                 0x2630
#define ENTYPO_ICON_TEXT_DOC             0x1F4C4
#define ENTYPO_ICON_TEXT_DOC_INVERTED    0xE731
#define ENTYPO_ICON_DOC                  0xE730
#define ENTYPO_ICON_DOCS                 0xE736
#define ENTYPO_ICON_LANDSCAPE_DOC        0xE737
#define ENTYPO_ICON_PICTURE              0x1F304
#define ENTYPO_ICON_VIDEO                0x1F3AC
#define ENTYPO_ICON_MUSIC                0x1F3B5
#define ENTYPO_ICON_FOLDER               0x1F4C1
#define ENTYPO_ICON_ARCHIVE              0xE800
#define ENTYPO_ICON_TRASH                0xE729
#define ENTYPO_ICON_UPLOAD               0x1F4E4
#define ENTYPO_ICON_DOWNLOAD             0x1F4E5
#define ENTYPO_ICON_SAVE                 0x1F4BE
#define ENTYPO_ICON_INSTALL              0xE778
#define ENTYPO_ICON_CLOUD                0x2601
#define ENTYPO_ICON_UPLOAD_CLOUD         0xE711
#define ENTYPO_ICON_BOOKMARK             0x1F516
#define ENTYPO_ICON_BOOKMARKS            0x1F4D1
#define ENTYPO_ICON_OPEN_BOOK            0x1F4D6
#define ENTYPO_ICON_PLAY                 0x25B6
#define ENTYPO_ICON_PAUS                 0x2016
#define ENTYPO_ICON_RECORD               0x25CF
#define ENTYPO_ICON_STOP                 0x25A0
#define ENTYPO_ICON_FF                   0x23E9
#define ENTYPO_ICON_FB                   0x23EA
#define ENTYPO_ICON_TO_START             0x23EE
#define ENTYPO_ICON_TO_END               0x23ED
#define ENTYPO_ICON_RESIZE_FULL          0xE744
#define ENTYPO_ICON_RESIZE_SMALL         0xE746
#define ENTYPO_ICON_VOLUME               0x23F7
#define ENTYPO_ICON_SOUND                0x1F50A
#define ENTYPO_ICON_MUTE                 0x1F507
#define ENTYPO_ICON_FLOW_CASCADE         0x1F568
#define ENTYPO_ICON_FLOW_BRANCH          0x1F569
#define ENTYPO_ICON_FLOW_TREE            0x1F56A
#define ENTYPO_ICON_FLOW_LINE            0x1F56B
#define ENTYPO_ICON_FLOW_PARALLEL        0x1F56C
#define ENTYPO_ICON_LEFT_BOLD            0xE4AD
#define ENTYPO_ICON_DOWN_BOLD            0xE4B0
#define ENTYPO_ICON_UP_BOLD              0xE4AF
#define ENTYPO_ICON_RIGHT_BOLD           0xE4AE
#define ENTYPO_ICON_LEFT                 0x2B05
#define ENTYPO_ICON_DOWN                 0x2B07
#define ENTYPO_ICON_UP                   0x2B06
#define ENTYPO_ICON_RIGHT                0x27A1
#define ENTYPO_ICON_CIRCLED_LEFT         0xE759
#define ENTYPO_ICON_CIRCLED_DOWN         0xE758
#define ENTYPO_ICON_CIRCLED_UP           0xE75B
#define ENTYPO_ICON_CIRCLED_RIGHT        0xE75A
#define ENTYPO_ICON_TRIANGLE_LEFT        0x25C2
#define ENTYPO_ICON_TRIANGLE_DOWN        0x25BE
#define ENTYPO_ICON_TRIANGLE_UP          0x25B4
#define ENTYPO_ICON_TRIANGLE_RIGHT       0x25B8
#define ENTYPO_ICON_CHEVRON_LEFT         0xE75D
#define ENTYPO_ICON_CHEVRON_DOWN         0xE75C
#define ENTYPO_ICON_CHEVRON_UP           0xE75F
#define ENTYPO_ICON_CHEVRON_RIGHT        0xE75E
#define ENTYPO_ICON_CHEVRON_SMALL_LEFT   0xE761
#define ENTYPO_ICON_CHEVRON_SMALL_DOWN   0xE760
#define ENTYPO_ICON_CHEVRON_SMALL_UP     0xE763
#define ENTYPO_ICON_CHEVRON_SMALL_RIGHT  0xE762
#define ENTYPO_ICON_CHEVRON_THIN_LEFT    0xE765
#define ENTYPO_ICON_CHEVRON_THIN_DOWN    0xE764
#define ENTYPO_ICON_CHEVRON_THIN_UP      0xE767
#define ENTYPO_ICON_CHEVRON_THIN_RIGHT   0xE766
#define ENTYPO_ICON_LEFT_THIN            0x2190
#define ENTYPO_ICON_DOWN_THIN            0x2193
#define ENTYPO_ICON_UP_THIN              0x2191
#define ENTYPO_ICON_RIGHT_THIN           0x2192
#define ENTYPO_ICON_ARROW_COMBO          0xE74F
#define ENTYPO_ICON_THREE_DOTS           0x23F6
#define ENTYPO_ICON_TWO_DOTS             0x23F5
#define ENTYPO_ICON_DOT                  0x23F4
#define ENTYPO_ICON_CC                   0x1F545
#define ENTYPO_ICON_CC_BY                0x1F546
#define ENTYPO_ICON_CC_NC                0x1F547
#define ENTYPO_ICON_CC_NC_EU             0x1F548
#define ENTYPO_ICON_CC_NC_JP             0x1F549
#define ENTYPO_ICON_CC_SA                0x1F54A
#define ENTYPO_ICON_CC_ND                0x1F54B
#define ENTYPO_ICON_CC_PD                0x1F54C
#define ENTYPO_ICON_CC_ZERO              0x1F54D
#define ENTYPO_ICON_CC_SHARE             0x1F54E
#define ENTYPO_ICON_CC_REMIX             0x1F54F
#define ENTYPO_ICON_DB_LOGO              0x1F5F9
#define ENTYPO_ICON_DB_SHAPE             0x1F5FA
#define ENTYPO_ICON_GITHUB               0xF300
#define ENTYPO_ICON_C_GITHUB             0xF301
#define ENTYPO_ICON_FLICKR               0xF303
#define ENTYPO_ICON_C_FLICKR             0xF304
#define ENTYPO_ICON_VIMEO                0xF306
#define ENTYPO_ICON_C_VIMEO              0xF307
#define ENTYPO_ICON_TWITTER              0xF309
#define ENTYPO_ICON_C_TWITTER            0xF30A
#define ENTYPO_ICON_FACEBOOK             0xF30C
#define ENTYPO_ICON_C_FACEBOOK           0xF30D
#define ENTYPO_ICON_S_FACEBOOK           0xF30E
#define ENTYPO_ICON_GOOGLEPLUS           0xF30F
#define ENTYPO_ICON_C_GOOGLEPLUS         0xF310
#define ENTYPO_ICON_PINTEREST            0xF312
#define ENTYPO_ICON_C_PINTEREST          0xF313
#define ENTYPO_ICON_TUMBLR               0xF315
#define ENTYPO_ICON_C_TUMBLR             0xF316
#define ENTYPO_ICON_LINKEDIN             0xF318
#define ENTYPO_ICON_C_LINKEDIN           0xF319
#define ENTYPO_ICON_DRIBBBLE             0xF31B
#define ENTYPO_ICON_C_DRIBBBLE           0xF31C
#define ENTYPO_ICON_STUMBLEUPON          0xF31E
#define ENTYPO_ICON_C_STUMBLEUPON        0xF31F
#define ENTYPO_ICON_LASTFM               0xF321
#define ENTYPO_ICON_C_LASTFM             0xF322
#define ENTYPO_ICON_RDIO                 0xF324
#define ENTYPO_ICON_C_RDIO               0xF325
#define ENTYPO_ICON_SPOTIFY              0xF327
#define ENTYPO_ICON_C_SPOTIFY            0xF328
#define ENTYPO_ICON_QQ                   0xF32A
#define ENTYPO_ICON_INSTAGRAM            0xF32D
#define ENTYPO_ICON_DROPBOX              0xF330
#define ENTYPO_ICON_EVERNOTE             0xF333
#define ENTYPO_ICON_FLATTR               0xF336
#define ENTYPO_ICON_SKYPE                0xF339
#define ENTYPO_ICON_C_SKYPE              0xF33A
#define ENTYPO_ICON_RENREN               0xF33C
#define ENTYPO_ICON_SINA_WEIBO           0xF33F
#define ENTYPO_ICON_PAYPAL               0xF342
#define ENTYPO_ICON_PICASA               0xF345
#define ENTYPO_ICON_SOUNDCLOUD           0xF348
#define ENTYPO_ICON_MIXI                 0xF34B
#define ENTYPO_ICON_BEHANCE              0xF34E
#define ENTYPO_ICON_GOOGLE_CIRCLES       0xF351
#define ENTYPO_ICON_VK                   0xF354
#define ENTYPO_ICON_SMASHING             0xF357

/* Cursor shapes */
enum class Cursor {
    Arrow = 0,
    IBeam,
    Crosshair,
    Hand,
    HResize,
    VResize,
    CursorCount
};

/// Stores an RGBA color value
class Color {
public:
    Color() : Color(0, 0, 0, 0) {}

    //Color(const Eigen::Vector4f &color) : Eigen::Vector4f(color) { }

    //Color(const Eigen::Vector3f &color, float alpha)
      //  : Color(color(0), color(1), color(2), alpha) { }

    //Color(const Eigen::Vector3i &color, int alpha)
      //  : Color(color.cast<float>() / 255.f, alpha / 255.f) { }

    //Color(const Eigen::Vector3f &color) : Color(color, 1.0f) {}

    //Color(const Eigen::Vector3i &color)
      //  : Color((Vector3f)(color.cast<float>() / 255.f)) { }

    //Color(const Eigen::Vector4i &color)
      //  : Color((Vector4f)(color.cast<float>() / 255.f)) { }

    Color(float intensity, float alpha)
    { _d.r = _d.g = _d.b = intensity; _d.a = alpha; }

    Color(int intensity, int alpha)
    { _d.r = _d.g = _d.b = (intensity / 255.f); _d.a = alpha / 255.f; }

    Color(float r, float g, float b, float a)
    {  _d.r = r; _d.g = g; _d.b = b; _d.a = a;  }

    Color(int r, int g, int b, int a)
    {  _d.r = r/255.f; _d.g = g/255.f; _d.b = b/255.f; _d.a = a/255.f;  }

    /// Construct a color vector from MatrixBase (needed to play nice with Eigen)
    //template <typename Derived> Color(const Eigen::MatrixBase<Derived>& p)
      //  : Base(p) { }

    /// Assign a color vector from MatrixBase (needed to play nice with Eigen)
    /*template <typename Derived> Color &operator=(const Eigen::MatrixBase<Derived>& p) {
        this->Base::operator=(p);
        return *this;
    }*/

    /// Return a reference to the red channel
    float &r() { return _d.r; }
    /// Return a reference to the red channel (const version)
    const float &r() const { return _d.r; }
    /// Return a reference to the green channel
    float &g() { return _d.g; }
    /// Return a reference to the green channel (const version)
    const float &g() const { return _d.g; }
    /// Return a reference to the blue channel
    float &b() { return _d.b; }
    /// Return a reference to the blue channel (const version)
    const float &b() const { return _d.b; }

    float &a() { return _d.a; }
    const float &a() const { return _d.a; }

    void setAlpha(float a) { _d.a = a; }

    Color withAlpha(float a) const {
        Color c = *this;
        c._d.a = a;
        return c;
    }

    bool operator!=(const Color& c)
    {
        return !(c.a() == a() && c.r() == r() && c.g() == g() && c.b() == b());
    }

    Color contrastingColor() const {
        float luminance = r() * 0.299f + g() * 0.587f + b() * 0.144f;
        return Color(luminance < 0.5f ? 1.f : 0.f, 1.f);
    }

    Color operator*(float m) const
    {
        return Color(r()*m, g()*m, b()*m, a()*m);
    }

    Color operator+(const Color& c) const
    {
        return Color(r() + c.r(), g() + c.g(), b() + c.b(), a() + c.a());
    }

    inline operator const NVGcolor &() const {
        return reinterpret_cast<const NVGcolor &>(this->_d);
    }
private:
    struct _Data {
        union {
            float rgba[4];
            struct {
                float r,g,b,a;
            };
        };
    };
    _Data _d;
};


/// Determine whether an icon ID is a texture loaded via nvgImageIcon
inline bool nvgIsImageIcon(int value) { return value < 1024; }

/// Determine whether an icon ID is a font-based icon (e.g. from the entypo.ttf font)
inline bool nvgIsFontIcon(int value) { return value >= 1024; }

/**
 * \brief Open a native file open/save dialog.
 *
 * \param filetypes
 *     Pairs of permissible formats with descriptions like
 *     <tt>("png", "Portable Network Graphics")</tt>
 */
extern std::string file_dialog(const std::vector<std::pair<std::string, std::string>> &filetypes, bool save);

#if defined(__APPLE__)
/**
 * \brief Move to the application bundle's parent directory
 *
 * This is function is convenient when deploying .app bundles on OSX. It
 * adjusts the file path to the parent directory containing the bundle.
 */
extern void chdir_to_bundle_parent();
#endif

/**
 * \brief Convert a single UTF32 character code to UTF8
 *
 * nnGUI uses this to convert the icon character codes
 */
std::array<char, 8> __nngui_utf8(int c);

/// Load a directory of PNG images and upload them to the GPU (suitable for use with ImagePanel)
std::vector<std::pair<int, std::string>>
    loadImageDirectory(NVGcontext *ctx, const std::string &path);

/// Convenience function for instanting a PNG icon from the application's data segment (via bin2c)
#define nvgImageIcon(ctx, name) nngui::__nngui_get_image(ctx, #name, name##_png, name##_png_size)
/// Helper function used by nvgImageIcon
extern int __nngui_get_image(NVGcontext *ctx, const std::string &name, uint8_t *data, uint32_t size);

namespace math
{
    //! Constant for PI.
    const double PI64		= 3.1415926535897932384626433832795028841971693993751;

    const float ROUNDING_ERROR_f32 = 0.000001f;
    //! 64bit constant for converting from degrees to radians (formally known as GRAD_PI2)
    const double DEGTORAD64 = PI64 / 180.0;
    const double ROUNDING_ERROR_f64 = 0.00000001;
    const double RADTODEG64 = 180.0 / PI64;

    template<class T>
    inline bool isEqual(const T a, const T b)
    {
        return (a + ROUNDING_ERROR_f32 >= b) && (a - ROUNDING_ERROR_f32 <= b);
    }

    template<class T>
    inline bool isEqual(const T a, const T b, const T tolerance)
    {
        return (a + tolerance >= b) && (a - tolerance <= b);
    }
}

template <class T>
class Vec2
{
public:
  //! Default constructor (null vector)
  Vec2() : _x(0), _y(0) {}
  //! Constructor with two different values
  Vec2(T nx, T ny) : _x(nx), _y(ny) {}
  //! Constructor with the same value for both members
  explicit Vec2(T n) : _x(n), _y(n) {}
  //! Copy constructor
  Vec2(const Vec2<T>& other) : _x(other._x), _y(other._y) {}

  static Vec2 Constant(T v) { return Vec2(v,v); }
  static Vec2 Zero() { return Vec2(0,0); }

  // operators
  Vec2<T> operator-() const { return Vec2<T>(-_x, -_y); }

  Vec2<T>& operator=(const Vec2<T>& other) { _x = other._x; _y = other._y; return *this; }

  Vec2<T> operator+(const Vec2<T>& other) const { return Vec2<T>(_x + other._x, _y + other._y); }
  Vec2<T>& operator+=(const Vec2<T>& other) { _x+=other._x; _y+=other._y; return *this; }
  Vec2<T> operator+(const T v) const { return Vec2<T>(_x + v, _y + v); }
  Vec2<T>& operator+=(const T v) { _x+=v; _y+=v; return *this; }

  Vec2<T> operator-(const Vec2<T>& other) const { return Vec2<T>(_x - other._x, _y - other._y); }
  Vec2<T>& operator-=(const Vec2<T>& other) { _x-=other._x; _y-=other._y; return *this; }
  Vec2<T> operator-(const T v) const { return Vec2<T>(_x - v, _y - v); }
  Vec2<T>& operator-=(const T v) { _x-=v; _y-=v; return *this; }

  Vec2<T> operator*(const Vec2<T>& other) const { return Vec2<T>(_x * other._x, _y * other._y); }
  Vec2<T>& operator*=(const Vec2<T>& other) { _x*=other._x; _y*=other._y; return *this; }
  Vec2<T> operator*(const T v) const { return Vec2<T>(_x * v, _y * v); }
  Vec2<T>& operator*=(const T v) { _x*=v; _y*=v; return *this; }

  Vec2<T> operator/(const Vec2<T>& other) const { return Vec2<T>(_x / other._x, _y / other._y); }
  Vec2<T>& operator/=(const Vec2<T>& other) { _x/=other._x; _y/=other._y; return *this; }
  Vec2<T> operator/(const T v) const { return Vec2<T>(_x / v, _y / v); }
  Vec2<T>& operator/=(const T v) { _x/=v; _y/=v; return *this; }

  //! sort in order X, Y. Equality with rounding tolerance.
  bool operator<=(const Vec2<T>& other) const
  {
    return (_x<other._x || math::isEqual(_x, other._x)) ||
           (math::isEqual(_x, other._x) && (_y<other._y || math::isEqual(_y, other._y)));
  }

  //! sort in order X, Y. Equality with rounding tolerance.
  bool operator>=(const Vec2<T>&other) const
  {
    return (_x>other._x || math::isEqual(_x, other._x)) ||
            (math::isEqual(_x, other._x) && (_y>other.Y || math::isEqual(_y, other._y)));
  }

  //! sort in order X, Y. Difference must be above rounding tolerance.
  bool operator<(const Vec2<T>&other) const
  {
    return (_x<other._x && !math::isEqual(_x, other._x)) ||
           (math::isEqual(_x, other.X) && _y<other.Y && !math::isEqual(_y, other._y));
  }

  //! sort in order X, Y. Difference must be above rounding tolerance.
  bool operator>(const Vec2<T>&other) const
  {
    return (_x>other._x && !math::isEqual(_x, other._x)) ||
           (math::isEqual(_x, other._x) && _y>other._y && !math::isEqual(_y, other._y));
  }

  bool operator==(const Vec2<T>& other) const { return IsEqual(other, math::ROUNDING_ERROR_f32); }
  bool operator!=(const Vec2<T>& other) const { return !IsEqual(other, math::ROUNDING_ERROR_f32); }

  // functions

  //! Checks if this vector equals the other one.
  /** Takes floating point rounding errors into account.
  \param other Vector to compare with.
  \return True if the two vector are (almost) equal, else false. */
  bool IsEqual(const Vec2<T>& other, float tolerance) const
  {
    return math::isEqual<T>(_x, other._x, tolerance) && math::isEqual<T>(_y, other._y, tolerance);
  }

  Vec2<T>& set(T nx, T ny) {_x=nx; _y=ny; return *this; }
  Vec2<T>& set(const Vec2<T>& p) { _x=p._x; _y=p._y; return *this; }

  //! Gets the length of the vector.
  /** \return The length of the vector. */
  float getLength() const { return sqrt( (float)_x*(float)_x + (float)_y*(float)_y ); }

  //! Get the squared length of this vector
  /** This is useful because it is much faster than getLength().
  \return The squared length of the vector. */
  T getLengthSQ() const { return _x*_x + _y*_y; }

  //! Get the dot product of this vector with another.
  /** \param other Other vector to take dot product with.
  \return The dot product of the two vectors. */
  T dotProduct(const Vec2<T>& other) const
  {
    return _x*other._x + _y*other._y;
  }

  template< class A >
  Vec2<A> As()
  {
    return Vec2<A>( (A)_x, (A)_y );
  }

  template< class A >
  Vec2<A> As() const
  {
    return Vec2<A>( (A)_x, (A)_y );
  }

  //! Gets distance from another point.
  /** Here, the vector is interpreted as a point in 2-dimensional space.
  \param other Other vector to measure from.
  \return Distance from other point. */
  float getDistanceFrom(const Vec2<T>& other) const
  {
          return Vec2<T>(_x - other._x, _y - other._y).getLength();
  }

  //! Returns squared distance from another point.
  /** Here, the vector is interpreted as a point in 2-dimensional space.
  \param other Other vector to measure from.
  \return Squared distance from other point. */
  T getDistanceFromSQ(const Vec2<T>& other) const
  {
          return Vec2<T>(_x - other._x, _y - other._y).getLengthSQ();
  }

  //! rotates the point anticlockwise around a center by an amount of degrees.
  /** \param degrees Amount of degrees to rotate by, anticlockwise.
  \param center Rotation center.
  \return This vector after transformation. */
  Vec2<T>& rotateBy(float degrees, const Vec2<T>& center=Vec2<T>())
  {
    degrees *= math::DEGTORAD64;
            const float cs = cos(degrees);
            const float sn = sin(degrees);

            _x -= center._x;
            _y -= center._y;

            set((T)(_x*cs - _y*sn), (T)(_x*sn + _y*cs));

            _x += center._x;
            _y += center._y;
            return *this;
  }

  //! Normalize the vector.
  /** The null vector is left untouched.
  \return Reference to this vector, after normalization. */
  Vec2<T>& normalize()
  {
    float length = (float)(_x*_x + _y*_y);

    if (math::isEqual(length, 0.f))
                    return *this;
    length = 1.f / sqrt( length );
    _x = (T)(_x * length);
    _y = (T)(_y * length);
        return *this;
  }

  //! Calculates the angle of this vector in degrees in the trigonometric sense.
  /** 0 is to the right (3 o'clock), values increase counter-clockwise.
  This method has been suggested by Pr3t3nd3r.
  \return Returns a value between 0 and 360. */
  float getAngleTrig() const
  {
    if (_y == 0)
      return _x < 0 ? 180 : 0;
    else if (_x == 0)
      return _y < 0 ? 270 : 90;

    if ( _y > 0)
    {
      if (_x > 0)
        return atanf((float)_y/(float)_x) * math::RADTODEG64;
      else
        return 180.0-atanf((float)_y/-(float)_x) * math::RADTODEG64;
    }
    else
    {
      if (_x > 0)
        return 360.0-atanf(-(float)_y/(float)_x) * math::RADTODEG64;
      else
        return 180.0+atanf(-(float)_y/-(float)_x) * math::RADTODEG64;
    }
  }

  //! Calculates the angle of this vector in degrees in the counter trigonometric sense.
  /** 0 is to the right (3 o'clock), values increase clockwise.
  \return Returns a value between 0 and 360. */
  inline float getAngle() const
  {
    if (_y == 0) // corrected thanks to a suggestion by Jox
            return _x < 0 ? 180 : 0;
    else if (_x == 0)
            return _y < 0 ? 90 : 270;

    // don't use getLength here to avoid precision loss with s32 vectors
    float tmp = _y / sqrt((float)(_x*_x + _y*_y));
    tmp = atanf( sqrt(1.f - tmp*tmp) / tmp) * math::RADTODEG64;

    if (_x>0 && _y>0)
      return tmp + 270;
    else if (_x>0 && _y<0)
      return tmp + 90;
    else if (_x<0 && _y<0)
      return 90 - tmp;
    else if (_x<0 && _y>0)
      return 270 - tmp;

    return tmp;
  }

  //! Calculates the angle between this vector and another one in degree.
  /** \param b Other vector to test with.
  \return Returns a value between 0 and 90. */
  inline float getAngleWith(const Vec2<T>& b) const
  {
    double tmp = _x*b._x + _y*b._y;

    if (tmp == 0.0)
      return 90.0;

    tmp = tmp / sqrtf((float)((_x*_x + _y*_y) * (b._x*b._x + b._y*b._y)));
    if (tmp < 0.0)
      tmp = -tmp;

    return atanf(sqrtf(1 - tmp*tmp) / tmp) * math::RADTODEG64;
  }

  //! Returns if this vector interpreted as a point is on a line between two other points.
  /** It is assumed that the point is on the line.
  \param begin Beginning vector to compare between.
  \param end Ending vector to compare between.
  \return True if this vector is between begin and end, false if not. */
  bool isBetweenPoints(const Vec2<T>& begin, const Vec2<T>& end) const
  {
    if (begin._x != end._x)
    {
      return ((begin._x <= _x && _x <= end._x) ||
              (begin._x >= _x && _x >= end._x));
    }
    else
    {
      return ((begin._y <= _y && _y <= end._y) ||
              (begin._y >= _y && _y >= end._y));
    }
  }

  T& seq(int index)
  {
    return index == 0 ? _x : _y;
  }

  const T& seq(int index) const
  {
    return index == 0 ? _x : _y;
  }

  //! Creates an interpolated vector between this vector and another vector.
  /** \param other The other vector to interpolate with.
  \param d Interpolation value between 0.0f (all the other vector) and 1.0f (all this vector).
  Note that this is the opposite direction of interpolation to getInterpolated_quadratic()
  \return An interpolated vector.  This vector is not modified. */
  Vec2<T> getInterpolated(const Vec2<T>& other, T d) const
  {
    float inv = 1.0f - (float)d;
    return Vec2<T>((T)(other._x*inv + _x*d), (T)(other._y*inv + _y*d));
  }

  //! Creates a quadratically interpolated vector between this and two other vectors.
  /** \param v2 Second vector to interpolate with.
  \param v3 Third vector to interpolate with (maximum at 1.0f)
  \param d Interpolation value between 0.0f (all this vector) and 1.0f (all the 3rd vector).
  Note that this is the opposite direction of interpolation to getInterpolated() and interpolate()
  \return An interpolated vector. This vector is not modified. */
  Vec2<T> getInterpolated_quadratic(const Vec2<T>& v2, const Vec2<T>& v3, const T d) const
  {
    // this*(1-d)*(1-d) + 2 * v2 * (1-d) + v3 * d * d;
    const float inv = 1.0f - d;
    const float mul0 = inv * inv;
    const float mul1 = 2.0f * d * inv;
    const float mul2 = d * d;

    return Vec2<T> ( (T)(_x * mul0 + v2.X * mul1 + v3.X * mul2),
                        (T)(_y * mul0 + v2.Y * mul1 + v3.Y * mul2));
  }

  Vec2<T> cwiseMax(T rx, T ry) const
  {
      return Vec2<T>(std::max(x(), rx), std::max(y(), ry));
  }

  Vec2<T> cwiseMax(const Vec2<T>& o) const
  {
      return Vec2<T>(std::max(x(), o.x()), std::max(y(), o.y()));
  }

  Vec2<T> cwiseMin(const Vec2<T>& o) const
  {
      return Vec2<T>(std::min(x(), o.x()), std::min(y(), o.y()));
  }

  //! Sets this vector to the linearly interpolated vector between a and b.
  /** \param a first vector to interpolate with, maximum at 1.0f
  \param b second vector to interpolate with, maximum at 0.0f
  \param d Interpolation value between 0.0f (all vector b) and 1.0f (all vector a)
  Note that this is the opposite direction of interpolation to getInterpolated_quadratic()
  */
  Vec2<T>& interpolate(const Vec2<T>& a, const Vec2<T>& b, const T d)
  {
    _x = (T)((float)b._x + ( ( a._x - b._x ) * d ));
    _y = (T)((float)b._y + ( ( a._y - b._y ) * d ));
    return *this;
  }

  inline T x() const { return _x; }
  inline T y() const { return _y; }

  inline T& rx() { return _x; }
  inline T& ry() { return _y; }

  inline void setX( T xv ) { _x = xv; }
  inline void setY( T yv ) { _y = yv; }

  template <class B>
  inline Vec2<B> cast() const { return Vec2<B>(static_cast<B>(x()), static_cast<B>(y())); }

protected:
  //! X coordinate of vector.
  T _x;

  //! Y coordinate of vector.
  T _y;
};

typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;

/// Reference counted object base class
class Object {
public:
    /// Default constructor
    Object() { }

    /// Copy constructor
    Object(const Object &) : m_refCount(0) {}

    /// Return the current reference count
    int getRefCount() const { return m_refCount; }

    /// Increase the object's reference count by one
    void incRef() const { ++m_refCount; }

    /** \brief Decrease the reference count of
     * the object and possibly deallocate it.
     *
     * The object will automatically be deallocated once
     * the reference count reaches zero.
     */
    void decRef(bool dealloc = true) const
    {
        --m_refCount;
        if (m_refCount == 0 && dealloc)
            delete this;
        else if (m_refCount < 0)
            throw std::runtime_error("Internal error: reference count < 0!");
    }
protected:
    /** \brief Virtual protected deconstructor.
     * (Will only be called by \ref ref)
     */
    virtual ~Object() { }
private:
    mutable std::atomic<int> m_refCount { 0 };
};

/**
 * \brief Reference counting helper
 *
 * The \a ref refeference template is a simple wrapper to store a
 * pointer to an object. It takes care of increasing and decreasing
 * the reference count of the object. When the last reference goes
 * out of scope, the associated object will be deallocated.
 *
 * \ingroup libcore
 */
template <typename T> class ref {
public:
    /// Create a nullptr reference
    ref() : m_ptr(nullptr) { }

    /// Construct a reference from a pointer
    ref(T *ptr) : m_ptr(ptr) {
        if (m_ptr) ((Object *) m_ptr)->incRef();
    }

    /// Copy constructor
    ref(const ref &r) : m_ptr(r.m_ptr) {
        if (m_ptr)
            ((Object *) m_ptr)->incRef();
    }

    /// Move constructor
    ref(ref &&r) : m_ptr(r.m_ptr) {
        r.m_ptr = nullptr;
    }

    /// Destroy this reference
    ~ref() {
        if (m_ptr)
            ((Object *) m_ptr)->decRef();
    }

    /// Move another reference into the current one
    ref& operator=(ref&& r) {
        if (*this == r)
            return *this;
        if (m_ptr)
            ((Object *) m_ptr)->decRef();
        m_ptr = r.m_ptr;
        r.m_ptr = nullptr;
        return *this;
    }

    /// Overwrite this reference with another reference
    ref& operator=(const ref& r) {
        if (m_ptr == r.m_ptr)
            return *this;
        if (m_ptr)
            ((Object *) m_ptr)->decRef();
        m_ptr = r.m_ptr;
        if (m_ptr)
            ((Object *) m_ptr)->incRef();
        return *this;
    }

    /// Overwrite this reference with a pointer to another object
    ref& operator=(T *ptr) {
        if (m_ptr == ptr)
            return *this;
        if (m_ptr)
            ((Object *) m_ptr)->decRef();
        m_ptr = ptr;
        if (m_ptr)
            ((Object *) m_ptr)->incRef();
        return *this;
    }

    /// Compare this reference with another reference
    bool operator==(const ref &r) const { return m_ptr == r.m_ptr; }

    /// Compare this reference with another reference
    bool operator!=(const ref &r) const { return m_ptr != r.m_ptr; }

    /// Compare this reference with a pointer
    bool operator==(const T* ptr) const { return m_ptr == ptr; }

    /// Compare this reference with a pointer
    bool operator!=(const T* ptr) const { return m_ptr != ptr; }

    /// Access the object referenced by this reference
    T* operator->() { return m_ptr; }

    /// Access the object referenced by this reference
    const T* operator->() const { return m_ptr; }

    /// Return a C++ reference to the referenced object
    T& operator*() { return *m_ptr; }

    /// Return a const C++ reference to the referenced object
    const T& operator*() const { return *m_ptr; }

    /// Return a pointer to the referenced object
    operator T* () { return m_ptr; }

    /// Return a const pointer to the referenced object
    T* get() { return m_ptr; }

    /// Return a pointer to the referenced object
    const T* get() const { return m_ptr; }

    /// Check if the object is defined
    operator bool() const { return m_ptr != nullptr; }
private:
    T *m_ptr;
};

class Theme : public Object {
public:
    Theme(NVGcontext *ctx);

    /* Fonts */
    int mFontNormal;
    int mFontBold;
    int mFontIcons;

    /* Spacing-related parameters */
    int mStandardFontSize;
    int mButtonFontSize;
    int mTextBoxFontSize;
    int mWindowCornerRadius;
    int mWindowHeaderHeight;
    int mWindowDropShadowSize;
    int mButtonCornerRadius;

    /* Generic options */
    bool mButtonHaveLigthBorder;

    /* Generic colors */
    Color mDropShadow;
    Color mTransparent;
    Color mBorderDark;
    Color mBorderLight;
    Color mBorderMedium;
    Color mTextColor;
    Color mDisabledTextColor;
    Color mTextColorShadow;
    Color mIconColor;

    /* Button colors */
    Color mButtonGradientTopFocused;
    Color mButtonGradientBotFocused;
    Color mButtonGradientTopUnfocused;
    Color mButtonGradientBotUnfocused;
    Color mButtonGradientTopPushed;
    Color mButtonGradientBotPushed;

    /* Window colors */
    Color mWindowFillUnfocused;
    Color mWindowFillFocused;
    Color mWindowTitleUnfocused;
    Color mWindowTitleFocused;

    Color mWindowHeaderGradientTop;
    Color mWindowHeaderGradientBot;
    Color mWindowHeaderSepTop;
    Color mWindowHeaderSepBot;

    Color mWindowPopup;
    Color mWindowPopupTransparent;
protected:
    virtual ~Theme() { };
};


class Layout;
class Window;
class Label;
/**
 * \brief Base class of all widgets
 *
 * \ref Widget is the base class of all widgets in \c nngui. It can
 * also be used as an panel to arrange an arbitrary number of child
 * widgets using a layout generator (see \ref Layout).
 */
class Widget : public Object
{
public:
    typedef std::function<void (const Vec2i& pos, Widget* parent)> ContextCallback;

    template<typename WidgetClass, typename... Args>
    WidgetClass& add( const Args&... args)
    {
      WidgetClass* widget = new WidgetClass( this, args... );
      return *widget;
    }

    /// Construct a new widget with the given parent widget
    Widget(Widget *parent);

    /// Return the parent widget
    Widget *parent() { return mParent; }
    /// Return the parent widget
    const Widget *parent() const { return mParent; }
    /// Set the parent widget
    void setParent(Widget *parent) { mParent = parent; }

    /// Return the used \ref Layout generator
    Layout *layout() { return mLayout; }
    /// Return the used \ref Layout generator
    const Layout *layout() const { return mLayout.get(); }
    /// Set the used \ref Layout generator
    void setLayout(Layout *layout) { mLayout = layout; }

    /// Return the \ref Theme used to draw this widget
    Theme *theme() { return mTheme; }
    /// Return the \ref Theme used to draw this widget
    const Theme *theme() const { return mTheme.get(); }
    /// Set the \ref Theme used to draw this widget
    void setTheme(Theme *theme) { mTheme = theme; }

    /// Return the position relative to the parent widget
    const Vec2i &position() const { return mPos; }
    /// Set the position relative to the parent widget
    void setPosition(const Vec2i &pos) { mPos = pos; }

    /// Return the absolute position on screen
    Vec2i absolutePosition() const {
        return mParent ?
            (parent()->absolutePosition() + mPos) : mPos;
    }

    /// Return the size of the widget
    const Vec2i &size() const { return mSize; }
    /// set the size of the widget
    void setSize(const Vec2i &size) { mSize = size; }

    /// Return the width of the widget
    int width() const { return mSize.x(); }
    /// Set the width of the widget
    void setWidth(int width) { mSize.setX(width); }

    /// Return the height of the widget
    int height() const { return mSize.y(); }
    /// Set the height of the widget
    void setHeight(int height) { mSize.setY(height); }

    /**
     * \brief Set the fixed size of this widget
     *
     * If nonzero, components of the fixed size attribute override any values
     * computed by a layout generator associated with this widget. Note that
     * just setting the fixed size alone is not enough to actually change its
     * size; this is done with a call to \ref setSize or a call to \ref performLayout()
     * in the parent widget.
     */
    void setFixedSize(const Vec2i &fixedSize) { mFixedSize = fixedSize; }

    /// Return the fixed size (see \ref setFixedSize())
    const Vec2i &fixedSize() const { return mFixedSize; }

    // Return the fixed width (see \ref setFixedSize())
    int fixedWidth() const { return mFixedSize.x(); }
    // Return the fixed height (see \ref setFixedSize())
    int fixedHeight() const { return mFixedSize.y(); }
    /// Set the fixed width (see \ref setFixedSize())
    void setFixedWidth(int width) { mFixedSize.setX(width); }
    /// Set the fixed height (see \ref setFixedSize())
    void setFixedHeight(int height) { mFixedSize.setY(height); }

    /// Return whether or not the widget is currently visible (assuming all parents are visible)
    bool visible() const { return mVisible; }
    /// Set whether or not the widget is currently visible (assuming all parents are visible)
    void setVisible(bool visible) { mVisible = visible; }

    /// Check if this widget is currently visible, taking parent widgets into account
    bool visibleRecursive() const {
        bool visible = true;
        const Widget *widget = this;
        while (widget) {
            visible &= widget->visible();
            widget = widget->parent();
        }
        return visible;
    }

    /// Return the number of child widgets
    int childCount() const { return (int) mChildren.size(); }

    /// Return the list of child widgets of the current widget
    const std::vector<Widget *> &children() const { return mChildren; }

    /**
     * \brief Add a child widget to the current widget
     *
     * This function almost never needs to be called by hand,
     * since the constructor of \ref Widget automatically
     * adds the current widget to its parent
     */
    void addChild(Widget *widget);

    /// Remove a child widget by index
    void removeChild(int index);

    /// Remove a child widget by value
    void removeChild(const Widget *widget);

    // Walk up the hierarchy and return the parent window
    Window *window();

    /// Associate this widget with an ID value (optional)
    void setId(const std::string &id) { mId = id; }
    /// Return the ID value associated with this widget, if any
    const std::string &id() const { return mId; }

    /// Return whether or not this widget is currently enabled
    bool enabled() const { return mEnabled; }
    /// Set whether or not this widget is currently enabled
    void setEnabled(bool enabled) { mEnabled = enabled; }

    /// Return whether or not this widget is currently focused
    bool focused() const { return mFocused; }
    /// Set whether or not this widget is currently focused
    void setFocused(bool focused) { mFocused = focused; }
    /// Request the focus to be moved to this widget
    void requestFocus();

    const std::string &tooltip() const { return mTooltip; }
    void setTooltip(const std::string &tooltip) { mTooltip = tooltip; }

    /// Return current font size. If not set the default of the current theme will be returned
    int fontSize() const;
    /// Set the font size of this widget
    void setFontSize(int fontSize) { mFontSize = fontSize; }
    /// Return whether the font size is explicitly specified for this widget
    bool hasFontSize() const { return mFontSize > 0; }

    /// Return a pointer to the cursor of the widget
    Cursor cursor() const { return mCursor; }
    /// Set the cursor of the widget
    void setCursor(Cursor cursor) { mCursor = cursor; }

    /// Check if the widget contains a certain position
    bool contains(const Vec2i &p) const {
        auto d = p-mPos;
        return d.x() >= 0 && d.y() >= 0 && d.x() < mSize.x() && d.y() < mSize.y();
    }

    /// Determine the widget located at the given position value (recursive)
    Widget *findWidget(const Vec2i &p);

    /// Handle a mouse button event (default implementation: propagate to children)
    virtual bool mouseButtonEvent(const Vec2i &p, int button, bool down, int modifiers);

    /// Handle a mouse motion event (default implementation: propagate to children)
    virtual bool mouseMotionEvent(const Vec2i &p, const Vec2i &rel, int button, int modifiers);

    /// Handle a mouse drag event (default implementation: do nothing)
    virtual bool mouseDragEvent(const Vec2i &p, const Vec2i &rel, int button, int modifiers);

    /// Handle a mouse enter/leave event (default implementation: record this fact, but do nothing)
    virtual bool mouseEnterEvent(const Vec2i &p, bool enter);

    /// Handle a mouse scroll event (default implementation: propagate to children)
    virtual bool scrollEvent(const Vec2i &p, const Vec2f &rel);

    /// Handle a focus change event (default implementation: record the focus status, but do nothing)
    virtual bool focusEvent(bool focused);

    /// Handle a keyboard event (default implementation: do nothing)
    virtual bool keyboardEvent(int key, int scancode, int action, int modifiers);

    /// Handle text input (UTF-32 format) (default implementation: do nothing)
    virtual bool keyboardCharacterEvent(unsigned int codepoint);

    /// Compute the preferred size of the widget
    virtual Vec2i preferredSize(NVGcontext *ctx) const;

    /// Invoke the associated layout generator to properly place child widgets, if any
    virtual void performLayout(NVGcontext *ctx);

    /// Draw the widget (and all child widgets)
    virtual void draw(NVGcontext *ctx);

    virtual void setContextCallback(const ContextCallback& function) { mContextCallback = function; }

    Widget& withPosition( const Vec2i& pos ) { setPosition( pos); return *this; }
    Widget& withFontSize(int size) { setFontSize(size); return *this; }
    Widget& withFixedSize(const Vec2i& size) { setFixedSize(size); return *this; }
    Widget& withTooltip(const std::string& tooltip) { setTooltip(tooltip); return *this; }

    template<typename LayoutClass,typename... Args>
    Widget& withLayout( const Args&... args)
    {
      auto* layout = new LayoutClass( args... );
      setLayout( layout );
      return *this;
    }

protected:
    /// Free all resources used by the widget and any children
    virtual ~Widget();

protected:
    Widget *mParent;
    ref<Theme> mTheme;
    ref<Layout> mLayout;
    std::string mId;
    Vec2i mPos, mSize, mFixedSize;
    std::vector<Widget *> mChildren;
    bool mVisible, mEnabled;
    bool mFocused, mMouseFocus;
    std::string mTooltip;
    int mFontSize;
    Cursor mCursor;
    ContextCallback mContextCallback;
};

class Window : public Widget {
    friend class Popup;
public:
    Window(Widget *parent, const std::string &title = "Untitled");

    /// Return the window title
    const std::string &title() const { return mTitle; }
    /// Set the window title
    void setTitle(const std::string &title) { mTitle = title; }

    /// Is this a model dialog?
    bool modal() const { return mModal; }
    /// Set whether or not this is a modal dialog
    void setModal(bool modal) { mModal = modal; }

    /// Return the panel used to house window buttons
    Widget *buttonPanel();

    /// Dispose the window
    void dispose();

    /// Center the window in the current \ref Screen
    void center();

    /// Draw the window
    virtual void draw(NVGcontext *ctx);

    /// Handle window drag events
    virtual bool mouseDragEvent(const Vec2i &p, const Vec2i &rel, int button, int modifiers);
    /// Handle mouse events recursively and bring the current window to the top
    virtual bool mouseButtonEvent(const Vec2i &p, int button, bool down, int modifiers);
    /// Accept scroll events and propagate them to the widget under the mouse cursor
    virtual bool scrollEvent(const Vec2i &p, const Vec2f &rel);
    /// Compute the preferred size of the widget
    virtual Vec2i preferredSize(NVGcontext *ctx) const;
    /// Invoke the associated layout generator to properly place child widgets, if any
    virtual void performLayout(NVGcontext *ctx);
protected:
    /// Internal helper  to maintain nested window position values; overridden in \ref Popup
    virtual void refreshRelativePlacement();
protected:
    std::string mTitle;
    Widget *mButtonPanel;
    bool mModal;
    bool mDrag;
};

/**
 * \brief Popup window for combo boxes, popup buttons, nested dialogs etc.
 *
 * Usually the Popup instance is constructed by another widget (e.g. \ref PopupButton)
 * and does not need to be created by hand.
 */
class Popup : public Window {
public:
    /// Create a new popup parented to a screen (first argument) and a parent window
    Popup(Widget *parent, Window *parentWindow);

    /// Return the anchor position in the parent window; the placement of the popup is relative to it
    void setAnchorPos(const Vec2i &anchorPos) { mAnchorPos = anchorPos; }
    /// Set the anchor position in the parent window; the placement of the popup is relative to it
    const Vec2i &anchorPos() const { return mAnchorPos; }

    /// Set the anchor height; this determines the vertical shift relative to the anchor position
    void setAnchorHeight(int anchorHeight) { mAnchorHeight = anchorHeight; }
    /// Return the anchor height; this determines the vertical shift relative to the anchor position
    int anchorHeight() const { return mAnchorHeight; }

    /// Return the parent window of the popup
    Window *parentWindow() { return mParentWindow; }
    /// Return the parent window of the popup
    const Window *parentWindow() const { return mParentWindow; }

    /// Invoke the associated layout generator to properly place child widgets, if any
    virtual void performLayout(NVGcontext *ctx);

    /// Draw the popup window
    virtual void draw(NVGcontext* ctx);
protected:
    /// Internal helper function to maintain nested window position values
    virtual void refreshRelativePlacement();

protected:
    Window *mParentWindow;
    Vec2i mAnchorPos;
    int mAnchorHeight;
};

class ContextMenu : public Window {
public:
    ContextMenu(Widget* parent);

    /// Invoke the associated layout generator to properly place child widgets, if any
    //virtual void performLayout(NVGcontext *ctx);

    /// Draw the popup window
    //virtual void draw(NVGcontext* ctx);

protected:
    /// Internal helper function to maintain nested window position values
    //virtual void refreshRelativePlacement();
};

class Slider : public Widget {
public:
    typedef std::function<void(float)> Callback;
    Slider(Widget *parent);

    float value() const { return mValue; }
    void setValue(float value) { mValue = value; }

    const Color &highlightColor() const { return mHighlightColor; }
    void setHighlightColor(const Color &highlightColor) { mHighlightColor = highlightColor; }

    std::pair<float, float> highlightedRange() const { return mHighlightedRange; }
    void setHighlightedRange(std::pair<float, float> highlightedRange) { mHighlightedRange = highlightedRange; }

    Callback callback() const { return mCallback; }
    void setCallback(const Callback& callback) { mCallback = callback; }

    Callback finalCallback() const { return mFinalCallback; }
    void setFinalCallback(const Callback& callback) { mFinalCallback = callback; }

    virtual Vec2i preferredSize(NVGcontext *ctx) const;
    virtual bool mouseDragEvent(const Vec2i &p, const Vec2i &rel, int button, int modifiers);
    virtual bool mouseButtonEvent(const Vec2i &p, int button, bool down, int modifiers);
    virtual void draw(NVGcontext* ctx);

    void setKnobInnerRadiusKoeff(float koeff) { mKnobRadiusKoeff.inner = koeff; }
    void setKnobOutterRadiusKoeff(float koeff) { mKnobRadiusKoeff.outter = koeff; }

protected:
    float mValue;

    struct {
        float inner=0.5f;
        float outter=2.f;
    } mKnobRadiusKoeff;

    Callback mCallback;
    Callback mFinalCallback;
    std::pair<float, float> mHighlightedRange;
    Color mHighlightColor;
};

class Button : public Widget
{
public:
    /// Flags to specify the button behavior (can be combined with binary OR)
    enum Flags {
        NormalButton = 1,
        RadioButton  = 2,
        ToggleButton = 4,
        PopupButton  = 8
    };

    enum class IconPosition {
        Left,
        LeftCentered,
        RightCentered,
        Right
    };

    Button(Widget *parent, const std::string& caption = "Untitled", int icon = 0);
    Button(Widget *parent, const std::string& caption,
           const std::function<void()>& callback,
           int icon = 0);

    const std::string &caption() const { return mCaption; }
    void setCaption(const std::string &caption) { mCaption = caption; }

    const Color &backgroundColor() const { return mBackgroundColor; }
    void setBackgroundColor(const Color &backgroundColor) { mBackgroundColor = backgroundColor; }

    const Color &textColor() const { return mTextColor; }
    void setTextColor(const Color &textColor) { mTextColor = textColor; }

    int icon() const { return mIcon; }
    void setIcon(int icon) { mIcon = icon; }

    int flags() const { return mFlags; }
    void setFlags(int buttonFlags) { mFlags = buttonFlags; }

    IconPosition iconPosition() const { return mIconPosition; }
    void setIconPosition(IconPosition iconPosition) { mIconPosition = iconPosition; }

    bool pushed() const { return mPushed; }
    void setPushed(bool pushed) { mPushed = pushed; }

    /// Set the push callback (for any type of button)
    std::function<void()> callback() const { return mCallback; }
    void setCallback(const std::function<void()> &callback) { mCallback = callback; }

    /// Set the change callback (for toggle buttons)
    std::function<void(bool)> changeCallback() const { return mChangeCallback; }
    void setChangeCallback(const std::function<void(bool)>& callback) { mChangeCallback = callback; }

    Button& withCallback(const std::function<void()> &callback) { setCallback( callback ); return *this; }
    Button& withFlags(int flags) { setFlags( flags); return *this; }
    Button& withChangeCallback(const std::function<void(bool)>& callback) { setChangeCallback( callback ); return *this; }
    Button& withBackgroundColor(const Color& color) { setBackgroundColor( color ); return *this; }
    Button& withIcon(int icon) { setIcon( icon ); return *this; }

    /// Set the button group (for radio buttons)
    void setButtonGroup(const std::vector<Button *> &buttonGroup) { mButtonGroup = buttonGroup; }
    const std::vector<Button *> &buttonGroup() const { return mButtonGroup; }

    virtual Vec2i preferredSize(NVGcontext *ctx) const;
    virtual bool mouseButtonEvent(const Vec2i &p, int button, bool down, int modifiers);
    virtual void draw(NVGcontext *ctx);
protected:
    std::string mCaption;
    int mIcon;
    IconPosition mIconPosition;
    bool mPushed;
    int mFlags;
    Color mBackgroundColor;
    Color mTextColor;
    std::function<void()> mCallback;
    std::function<void(bool)> mChangeCallback;
    std::vector<Button *> mButtonGroup;
};

class PopupButton : public Button
{
public:
    PopupButton(Widget *parent, const std::string &caption = "Untitled",
                int buttonIcon = 0,
                int chevronIcon = ENTYPO_ICON_CHEVRON_SMALL_RIGHT);

    void setChevronIcon(int icon) { mChevronIcon = icon; }
    int chevronIcon() const { return mChevronIcon; }

    Popup *popup() { return mPopup; }
    const Popup* popup() const { return mPopup; }

    virtual void draw(NVGcontext* ctx);
    virtual Vec2i preferredSize(NVGcontext *ctx) const;
    virtual void performLayout(NVGcontext *ctx);

protected:
    Popup *mPopup;
    int mChevronIcon;
};

class ComboBox : public PopupButton
{
public:
    /// Create an empty combo box
    ComboBox(Widget *parent);

    /// Create a new combo box with the given items
    //ComboBox(Widget *parent, const std::vector<std::string>& items={});
    ComboBox(Widget *parent, const std::vector<std::string>& items);

    /**
     * \brief Create a new combo box with the given items, providing both short and
     * long descriptive labels for each item
     */
    ComboBox(Widget *parent, const std::vector<std::string> &items,
             const std::vector<std::string> &itemsShort);

    std::function<void(int)> callback() const { return mCallback; }
    void setCallback(const std::function<void(int)> &callback) { mCallback = callback; }

    int selectedIndex() const { return mSelectedIndex; }
    void setSelectedIndex(int idx);

    void setItems(const std::vector<std::string> &items, const std::vector<std::string> &itemsShort);
    void setItems(const std::vector<std::string> &items) { setItems(items, items); }
    const std::vector<std::string> &items() const { return mItems; }
    const std::vector<std::string> &itemsShort() const { return mItemsShort; }

    ComboBox& withItems(const std::vector<std::string>& items) {setItems(items); return *this;}
protected:
    std::vector<std::string> mItems, mItemsShort;
    std::function<void(int)> mCallback;
    int mSelectedIndex;
};

class CheckBox : public Widget
{
public:
    CheckBox(Widget *parent, const std::string &caption = "Untitled",
             const std::function<void(bool)> &callback = std::function<void(bool)>());

    const std::string &caption() const { return mCaption; }
    void setCaption(const std::string &caption) { mCaption = caption; }

    const bool &checked() const { return mChecked; }
    void setChecked(const bool &checked) { mChecked = checked; }

    CheckBox& withChecked(bool value) { setChecked(value); return *this; }

    const bool &pushed() const { return mPushed; }
    void setPushed(const bool &pushed) { mPushed = pushed; }

    std::function<void(bool)> callback() const { return mCallback; }
    void setCallback(const std::function<void(bool)> &callback) { mCallback = callback; }

    virtual bool mouseButtonEvent(const Vec2i &p, int button, bool down, int modifiers);
    virtual Vec2i preferredSize(NVGcontext *ctx) const;
    virtual void draw(NVGcontext *ctx);
protected:
    std::string mCaption;
    bool mPushed, mChecked;
    std::function<void(bool)> mCallback;
};

class MessageDialog : public Window {
public:
    enum class Type {
        Information,
        Question,
        Warning
    };

    MessageDialog(Widget *parent, Type type, const std::string &title = "Untitled",
                  const std::string &message = "Message",
                  const std::string &buttonText = "OK",
                  const std::string &altButtonText = "Cancel", bool altButton = false);

    Label *messageLabel() { return mMessageLabel; }
    const Label *messageLabel() const { return mMessageLabel; }

    std::function<void(int)> callback() const { return mCallback; }
    void setCallback(const std::function<void(int)> &callback) { mCallback = callback; }

    MessageDialog& withCallback(const std::function<void(int)> &callback)
    { setCallback( callback ); return *this; }
protected:
    std::function<void(int)> mCallback;
    Label *mMessageLabel;
};

class ColorWheel : public Widget
{
public:
    ColorWheel(Widget *parent, const Color& color = { 1.f, 0.f, 0.f, 1.f });

    /// Set the change callback
    std::function<void(const Color &)> callback() const                  { return mCallback;     }
    void setCallback(const std::function<void(const Color &)> &callback) { mCallback = callback; }

    /// Get the current color
    Color color() const;
    /// Set the current color
    void setColor(const Color& color);

    virtual Vec2i preferredSize(NVGcontext *ctx) const;
    virtual void draw(NVGcontext *ctx);
    virtual bool mouseButtonEvent(const Vec2i &p, int button, bool down, int modifiers);
    virtual bool mouseDragEvent(const Vec2i &p, const Vec2i &rel, int button, int modifiers);

private:
    enum Region {
        None = 0,
        InnerTriangle = 1,
        OuterCircle = 2,
        Both = 3
    };

    Color hue2rgb(float h) const;
    Region adjustPosition(const Vec2i &p, Region consideredRegions = Both);

protected:
    float mHue;
    float mWhite;
    float mBlack;
    Region mDragRegion;
    std::function<void(const Color &)> mCallback;
};

class ColorPicker : public PopupButton {
public:
    ColorPicker(Widget *parent, const Color& color = { 1.f, 0.f, 0.f, 1.f });

    /// Set the change callback
    std::function<void(const Color &)> callback() const                  { return mCallback; }
    void setCallback(const std::function<void(const Color &)> &callback) { mCallback = callback; }

    /// Get the current color
    Color color() const;
    /// Set the current color
    void setColor(const Color& color);

protected:
    std::function<void(const Color &)> mCallback;
    ColorWheel *mColorWheel;
    Button *mPickButton;
};

class ImageView : public Widget
{
public:
    enum class SizePolicy {
       Fixed,
       Expand
    };

    ImageView(Widget *parent, int image = 0, SizePolicy policy = SizePolicy::Fixed);

    void setImage(int img)      { mImage = img; }
    int  image() const          { return mImage; }

    void       setPolicy(SizePolicy policy) { mPolicy = policy; }
    SizePolicy policy() const { return mPolicy; }

    ImageView& withPolicy(SizePolicy policy) { setPolicy(policy); return *this; }
    ImageView& withImage(int img) { setImage(img); return *this; }

    virtual Vec2i preferredSize(NVGcontext *ctx) const;
    virtual void draw(NVGcontext* ctx);

protected:
    int mImage;
    SizePolicy mPolicy;
};

class ImagePanel : public Widget {
public:
    typedef std::vector<std::pair<int, std::string>> Images;
public:
    ImagePanel(Widget *parent);

    void setImages(const Images &data) { mImages = data; }
    const Images& images() const { return mImages; }

    std::function<void(int)> callback() const { return mCallback; }
    void setCallback(const std::function<void(int)> &callback) { mCallback = callback; }

    virtual bool mouseMotionEvent(const Vec2i &p, const Vec2i &rel, int button, int modifiers);
    virtual bool mouseButtonEvent(const Vec2i &p, int button, bool down, int modifiers);
    virtual Vec2i preferredSize(NVGcontext *ctx) const;
    virtual void draw(NVGcontext* ctx);

    ImagePanel& withImages(const Images& data ) { setImages(data); return *this; }
protected:
    Vec2i gridSize() const;
    int indexForPosition(const Vec2i &p) const;
protected:
    Images mImages;
    std::function<void(int)> mCallback;
    int mThumbSize;
    int mSpacing;
    int mMargin;
    int mMouseIndex;
};

/// Basic interface of a layout engine
class Layout : public Object {
public:
    virtual void performLayout(NVGcontext *ctx, Widget *widget) const = 0;
    virtual Vec2i preferredSize(NVGcontext *ctx, const Widget *widget) const = 0;
protected:
    virtual ~Layout() { }
};

/**
 * \brief Simple horizontal/vertical box layout
 *
 * This widget stacks up a bunch of widgets horizontally or vertically. It adds
 * margins around the entire container and a custom spacing between adjacent
 * widgets
 */
class BoxLayout : public Layout {
public:
    /**
     * \brief Construct a box layout which packs widgets in the given \c orientation
     * \param alignment
     *    Widget alignment perpendicular to the chosen orientation.
     * \param margin
     *    Margin around the layout container
     * \param spacing
     *    Extra spacing placed between widgets
     */
    BoxLayout(Orientation orientation, Alignment alignment = Alignment::Middle,
              int margin = 0, int spacing = 0);

    Orientation orientation() const { return mOrientation; }
    void setOrientation(Orientation orientation) { mOrientation = orientation; }

    Alignment alignment() const { return mAlignment; }
    void setAlignment(Alignment alignment) { mAlignment = alignment; }

    int margin() const { return mMargin; }
    void setMargin(int margin) { mMargin = margin; }

    int spacing() const { return mSpacing; }
    void setSpacing(int spacing) { mSpacing = spacing; }

    /* Implementation of the layout interface */
    Vec2i preferredSize(NVGcontext *ctx, const Widget *widget) const;
    void performLayout(NVGcontext *ctx, Widget *widget) const;

protected:
    Orientation mOrientation;
    Alignment mAlignment;
    int mMargin;
    int mSpacing;
};

/**
 * \brief Special layout for widgets grouped by labels
 *
 * This widget resembles a box layout in that it arranges a set of widgets
 * vertically. All widgets are indented on the horizontal axis except for
 * \ref Label widgets, which are not indented.
 *
 * This creates a pleasing layout where a number of widgets are grouped
 * under some high-level heading.
 */
class GroupLayout : public Layout {
public:
    GroupLayout(int margin = 15, int spacing = 6, int groupSpacing = 14,
                int groupIndent = 20)
        : mMargin(margin), mSpacing(spacing), mGroupSpacing(groupSpacing),
          mGroupIndent(groupIndent) {}

    int margin() const { return mMargin; }
    void setMargin(int margin) { mMargin = margin; }

    int spacing() const { return mSpacing; }
    void setSpacing(int spacing) { mSpacing = spacing; }

    int groupIndent() const { return mGroupIndent; }
    void setGroupIndent(int groupIndent) { mGroupIndent = groupIndent; }

    int groupSpacing() const { return mGroupSpacing; }
    void setGroupSpacing(int groupSpacing) { mGroupSpacing = groupSpacing; }

    /* Implementation of the layout interface */
    Vec2i preferredSize(NVGcontext *ctx, const Widget *widget) const;
    void performLayout(NVGcontext *ctx, Widget *widget) const;

protected:
    int mMargin;
    int mSpacing;
    int mGroupSpacing;
    int mGroupIndent;
};

/**
 * \brief Grid layout
 *
 * Widgets are arranged in a grid that has a fixed grid resolution \c resolution
 * along one of the axes. The layout orientation indicates the fixed dimension;
 * widgets are also appended on this axis. The spacing between items can be
 * specified per axis. The horizontal/vertical alignment can be specified per
 * row and column.
 */
class GridLayout : public Layout {
public:
    /// Create a 2-column grid layout by default
    GridLayout(Orientation orientation = Orientation::Horizontal, int resolution = 2,
               Alignment alignment = Alignment::Middle,
               int margin = 0, int spacing = 0)
        : mOrientation(orientation), mResolution(resolution), mMargin(margin) {
        mDefaultAlignment[0] = mDefaultAlignment[1] = alignment;
        mSpacing = Vec2i::Constant(spacing);
    }

    Orientation orientation() const { return mOrientation; }
    void setOrientation(Orientation orientation) {
        mOrientation = orientation;
    }

    int resolution() const { return mResolution; }
    void setResolution(int resolution) { mResolution = resolution; }

    int spacingX() const { return mSpacing.x(); }
    void setSpacingX(int spacing) { mSpacing.setX(spacing); }
    void setSpacing(int spacing) { mSpacing.set(spacing, spacing); }
    void setSpacing(const Vec2i& sp) { mSpacing = sp; }

    int margin() const { return mMargin; }
    void setMargin(int margin) { mMargin = margin; }

    Alignment alignment(int axis, int item) const {
        if (item < (int) mAlignment[axis].size())
            return mAlignment[axis][item];
        else
            return mDefaultAlignment[axis];
    }
    void setColAlignment(Alignment value) { mDefaultAlignment[0] = value; }
    void setRowAlignment(Alignment value) { mDefaultAlignment[1] = value; }
    void setColAlignment(const std::vector<Alignment> &value) { mAlignment[0] = value; }
    void setRowAlignment(const std::vector<Alignment> &value) { mAlignment[1] = value; }

    /* Implementation of the layout interface */
    Vec2i preferredSize(NVGcontext *ctx, const Widget *widget) const;
    void performLayout(NVGcontext *ctx, Widget *widget) const;

protected:
    // Compute the maximum row and column sizes
    void computeLayout(NVGcontext *ctx, const Widget *widget,
                       std::vector<int> *grid) const;

protected:
    Orientation mOrientation;
    Alignment mDefaultAlignment[2];
    std::vector<Alignment> mAlignment[2];
    int mResolution;
    Vec2i mSpacing;
    int mMargin;
};

/**
 * \brief Advanced Grid layout
 *
 * The is a fancier grid layout with support for items that span multiple rows
 * or columns, and per-widget alignment flags. Each row and column additionally
 * stores a stretch factor that controls how additional space is redistributed.
 * The downside of this flexibility is that a layout anchor data structure must
 * be provided for each widget.
 *
 * An example:
 *
 * <pre>
 *   using AdvancedGridLayout::Anchor;
 *   Label *label = new Label(window, "A label");
 *   // Add a centered label at grid position (1, 5), which spans two horizontal cells
 *   layout->setAnchor(label, Anchor(1, 5, 2, 1, Alignment::Middle, Alignment::Middle));
 * </pre>
 *
 * The grid is initialized with user-specified column and row size vectors
 * (which can be expanded later on if desired). If a size value of zero is
 * specified for a column or row, the size is set to the maximum preferred size
 * of any widgets contained in the same row or column. Any remaining space is
 * redistributed according to the row and column stretch factors.
 *
 * The high level usage somewhat resembles the classic HIG layout:
 * https://web.archive.org/web/20070813221705/http://www.autel.cz/dmi/tutorial.html
 * https://github.com/jaapgeurts/higlayout
 */
class AdvancedGridLayout : public Layout {
public:
    struct Anchor {
        uint8_t pos[2];
        uint8_t size[2];
        Alignment align[2];

        Anchor() { }

        Anchor(int x, int y, Alignment horiz = Alignment::Fill,
              Alignment vert = Alignment::Fill) {
            pos[0] = (uint8_t) x; pos[1] = (uint8_t) y;
            size[0] = size[1] = 1;
            align[0] = horiz; align[1] = vert;
        }

        Anchor(int x, int y, int w, int h,
              Alignment horiz = Alignment::Fill,
              Alignment vert = Alignment::Fill) {
            pos[0] = (uint8_t) x; pos[1] = (uint8_t) y;
            size[0] = (uint8_t) w; size[1] = (uint8_t) h;
            align[0] = horiz; align[1] = vert;
        }

        operator std::string() const {
            char buf[50];
            NNGUI_SNPRINTF(buf, 50, "Format[pos=(%i, %i), size=(%i, %i), align=(%i, %i)]",
                pos[0], pos[1], size[0], size[1], (int) align[0], (int) align[1]);
            return buf;
        }
    };

    AdvancedGridLayout(const std::vector<int> &cols = {}, const std::vector<int> &rows = {});

    int margin() const { return mMargin; }
    void setMargin(int margin) { mMargin = margin; }

    /// Return the number of cols
    int colCount() const { return (int) mCols.size(); }

    /// Return the number of rows
    int rowCount() const { return (int) mRows.size(); }

    /// Append a row of the given size (and stretch factor)
    void appendRow(int size, float stretch = 0.f) { mRows.push_back(size); mRowStretch.push_back(stretch); }

    /// Append a column of the given size (and stretch factor)
    void appendCol(int size, float stretch = 0.f) { mCols.push_back(size); mColStretch.push_back(stretch); }

    /// Set the stretch factor of a given row
    void setRowStretch(int index, float stretch) { mRowStretch.at(index) = stretch; }

    /// Set the stretch factor of a given column
    void setColStretch(int index, float stretch) { mColStretch.at(index) = stretch; }

    /// Specify the anchor data structure for a given widget
    void setAnchor(const Widget *widget, const Anchor &anchor) { mAnchor[widget] = anchor; }

    /// Retrieve the anchor data structure for a given widget
    Anchor anchor(const Widget *widget) const {
        auto it = mAnchor.find(widget);
        if (it == mAnchor.end())
            throw std::runtime_error("Widget was not registered with the grid layout!");
        return it->second;
    }

    /* Implementation of the layout interface */
    Vec2i preferredSize(NVGcontext *ctx, const Widget *widget) const;
    void performLayout(NVGcontext *ctx, Widget *widget) const;

protected:
    void computeLayout(NVGcontext *ctx, const Widget *widget,
                       std::vector<int> *grid) const;

protected:
    std::vector<int> mCols, mRows;
    std::vector<float> mColStretch, mRowStretch;
    std::unordered_map<const Widget *, Anchor> mAnchor;
    int mMargin;
};

typedef std::vector<float> VectorXf;

class Graph : public Widget {
public:
    Graph(Widget *parent, const std::string &caption = "Untitled");

    const std::string &caption() const { return mCaption; }
    void setCaption(const std::string &caption) { mCaption = caption; }

    const std::string &header() const { return mHeader; }
    void setHeader(const std::string &header) { mHeader = header; }

    const std::string &footer() const { return mFooter; }
    void setFooter(const std::string &footer) { mFooter = footer; }

    const Color &backgroundColor() const { return mBackgroundColor; }
    void setBackgroundColor(const Color &backgroundColor) { mBackgroundColor = backgroundColor; }

    const Color &foregroundColor() const { return mForegroundColor; }
    void setForegroundColor(const Color &foregroundColor) { mForegroundColor = foregroundColor; }

    const Color &textColor() const { return mTextColor; }
    void setTextColor(const Color &textColor) { mTextColor = textColor; }

    const VectorXf &values() const { return mValues; }
    VectorXf &values() { return mValues; }
    void setValues(const VectorXf &values) { mValues = values; }

    virtual Vec2i preferredSize(NVGcontext *ctx) const;
    virtual void draw(NVGcontext *ctx);
protected:
    std::string mCaption, mHeader, mFooter;
    Color mBackgroundColor, mForegroundColor, mTextColor;
    VectorXf mValues;
};

class ToolButton : public Button
{
public:
    ToolButton(Widget *parent, int icon=-1,
           const std::string &caption = "")
        : Button(parent, caption, icon)
    {
        setFlags(Flags::RadioButton | Flags::ToggleButton);
        setFixedSize(Vec2i(25, 25));
    }
};

class VScrollPanel : public Widget
{
public:
    VScrollPanel(Widget *parent);

    virtual void performLayout(NVGcontext *ctx);
    virtual Vec2i preferredSize(NVGcontext *ctx) const;
    virtual bool mouseDragEvent(const Vec2i &p, const Vec2i &rel, int button, int modifiers);
    virtual bool scrollEvent(const Vec2i &p, const Vec2f &rel);
    virtual bool mouseButtonEvent(const Vec2i &p, int button, bool down, int modifiers);
    virtual bool mouseMotionEvent(const Vec2i &p, const Vec2i &rel, int button, int modifiers);
    virtual void draw(NVGcontext *ctx);
protected:
    int mChildPreferredHeight;
    float mScroll;
};

class ProgressBar : public Widget
{
public:
    ProgressBar(Widget *parent);

    float value() { return mValue; }
    void setValue(float value) { mValue = value; }

    virtual Vec2i preferredSize(NVGcontext *ctx) const;
    virtual void draw(NVGcontext* ctx);
protected:
    float mValue;
};

class TextBox : public Widget
{
public:
    enum class Alignment {
        Left,
        Center,
        Right
    };

    TextBox(Widget *parent, const std::string &value = "Untitled");

    bool editable() const { return mEditable; }
    void setEditable(bool editable);

    const std::string &value() const { return mValue; }
    void setValue(const std::string &value) { mValue = value; }

    const std::string &defaultValue() const { return mDefaultValue; }
    void setDefaultValue(const std::string &defaultValue) { mDefaultValue = defaultValue; }

    Alignment alignment() const { return mAlignment; }
    void setAlignment(Alignment align) { mAlignment = align; }

    const std::string &units() const { return mUnits; }
    void setUnits(const std::string &units) { mUnits = units; }

    int unitsImage() const { return mUnitsImage; }
    void setUnitsImage(int image) { mUnitsImage = image; }

    /// Return the underlying regular expression specifying valid formats
    const std::string &format() const { return mFormat; }
    /// Specify a regular expression specifying valid formats
    void setFormat(const std::string &format) { mFormat = format; }

    /// Set the change callback
    std::function<bool(const std::string& str)> callback() const { return mCallback; }
    void setCallback(const std::function<bool(const std::string& str)> &callback) { mCallback = callback; }

    bool mouseButtonEvent(const Vec2i &p,int button,bool down,int modifiers);
    bool mouseMotionEvent(const Vec2i &p,const Vec2i &rel,int button,int modifiers);
    bool mouseDragEvent(const Vec2i &p,const Vec2i &rel,int button,int modifiers);
    bool mouseEnterEvent(const Vec2i &p,bool enter);
    bool focusEvent(bool focused);
    bool keyboardEvent(int key, int scancode, int action, int modifiers);
    bool keyboardCharacterEvent(unsigned int codepoint);

    Vec2i preferredSize(NVGcontext *ctx) const;
    void draw(NVGcontext* ctx);
protected:
    bool checkFormat(const std::string& input,const std::string& format);
    bool copySelection();
    void pasteFromClipboard();
    bool deleteSelection();

    void updateCursor(NVGcontext *ctx, float lastx,
                      const NVGglyphPosition *glyphs, int size);
    float cursorIndex2Position(int index, float lastx,
                               const NVGglyphPosition *glyphs, int size);
    int position2CursorIndex(float posx, float lastx,
                             const NVGglyphPosition *glyphs, int size);
protected:
    bool mEditable;
    bool mCommitted;
    std::string mValue;
    std::string mDefaultValue;
    Alignment mAlignment;
    std::string mUnits;
    std::string mFormat;
    int mUnitsImage;
    std::function<bool(const std::string& str)> mCallback;
    bool mValidFormat;
    std::string mValueTemp;
    int mCursorPos;
    int mSelectionPos;
    Vec2i mMousePos;
    Vec2i mMouseDownPos;
    Vec2i mMouseDragPos;
    int mMouseDownModifier;
    float mTextOffset;
    double mLastClick;
};

template <typename Scalar> class IntBox : public TextBox {
public:
    IntBox(Widget *parent, Scalar value = (Scalar) 0) : TextBox(parent) {
        setDefaultValue("0");
        setFormat(std::is_signed<Scalar>::value ? "[-]?[0-9]*" : "[0-9]*");
        setValue(value);
    }

    Scalar value() const {
        Scalar value;
        std::istringstream iss(TextBox::value());
        if (!(iss >> value))
            throw std::invalid_argument("Could not parse integer value!");
        return value;
    }

    void setValue(Scalar value) {
        TextBox::setValue(std::to_string(value));
    }

    void setCallback(const std::function<void(Scalar)> &cb) {
        TextBox::setCallback(
            [cb, this](const std::string &str) {
                std::istringstream iss(str);
                Scalar value;
                if (!(iss >> value))
                    throw std::invalid_argument("Could not parse integer value!");
                setValue(value);
                cb(value);
                return true;
            }
        );
    }
};

template <typename Scalar> class FloatBox : public TextBox {
public:
    FloatBox(Widget *parent, Scalar value = (Scalar) 0.f) : TextBox(parent) {
        mNumberFormat = sizeof(Scalar) == sizeof(float) ? "%.4g" : "%.7g";
        setDefaultValue("0");
        setFormat("[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?");
        setValue(value);
    }

    std::string numberFormat() const { return mNumberFormat; }
    void numberFormat(const std::string &format) { mNumberFormat = format; }

    Scalar value() const {
        return (Scalar) std::stod(TextBox::value());
    }

    void setValue(Scalar value) {
        char buffer[50];
        NNGUI_SNPRINTF(buffer, 50, mNumberFormat.c_str(), value);
        TextBox::setValue(buffer);
    }

    void setCallback(const std::function<void(Scalar)> &cb) {
        TextBox::setCallback([cb, this](const std::string &str) {
            Scalar scalar = (Scalar) std::stod(str);
            setValue(scalar);
            cb(scalar);
            return true;
        });
    }
private:
    std::string mNumberFormat;
};

/**
 * \brief Text label widget
 *
 * The font and color can be customized. When \ref Widget::setFixedWidth()
 * is used, the text is wrapped when it surpasses the specified width
 */
class Label : public Widget
{
public:
    Label(Widget *parent, const std::string &caption,
          const std::string &font = "sans", int fontSize = -1);

    /// Get the label's text caption
    const std::string &caption() const { return mCaption; }
    /// Set the label's text caption
    void setCaption(const std::string &caption) { mCaption = caption; }

    /// Set the currently active font (2 are available by default: 'sans' and 'sans-bold')
    void setFont(const std::string &font) { mFont = font; }
    /// Get the currently active font
    const std::string &font() const { return mFont; }

    /// Get the label color
    Color color() const { return mColor; }
    /// Set the label color
    void setColor(const Color& color) { mColor = color; }

    /// Compute the size needed to fully display the label
    virtual Vec2i preferredSize(NVGcontext *ctx) const;
    /// Draw the label
    virtual void draw(NVGcontext *ctx);
protected:
    std::string mCaption;
    std::string mFont;
    Color mColor;
};

/**
 * \brief Represents a display surface (i.e. a full-screen or windowed GLFW window)
 * and forms the root element of a hierarchy of nanogui widgets
 */
class Screen : public Widget
{
    friend class Widget;
    friend class Window;
public:
#ifdef NNGUI_SDL
    typedef SDL_Window* ParentWindowPtr;
#elif defined NNGUI_GLFW
    typedef GLFWwindow* ParentWindowPtr;
#endif
    /// Create a new screen
    Screen(ParentWindowPtr window, const Vec2i &size, const std::string &caption,
            bool resizable = true, bool fullscreen = false);

    /// Release all resources
    virtual ~Screen();

    /// Get the window titlebar caption
    const std::string &caption() const { return mCaption; }

    /// Set the window titlebar caption
    void setCaption(const std::string &caption);

    /// Return the screen's background color
    const Color& background() const { return mBackground; }

    /// Set the screen's background color
    void setBackground(const Color& background) { mBackground = background; }

    /// Set the top-level window visibility (no effect on full-screen windows)
    void setVisible(bool visible);

    /// Set window size
    void setSize(const Vec2i& size);

    /// Draw the Screen contents
    virtual void drawAll();

#ifdef NNGUI_SDL
    virtual void onEvent(SDL_Event& event);
#endif

    /// Draw the window contents -- put your OpenGL draw calls here
    virtual void drawContents() { /* To be overridden */ }

    /// Handle a file drop event
    virtual bool dropEvent(const std::vector<std::string> & /* filenames */) { return false; /* To be overridden */ }

    /// Default keyboard event handler
    virtual bool keyboardEvent(int key, int scancode, int action, int modifiers);

    /// Text input event handler: codepoint is native endian UTF-32 format
    virtual bool keyboardCharacterEvent(unsigned int codepoint);

    /// Window resize event handler
    virtual bool resizeEvent(const Vec2i &) { return false; }

    /// Return the last observed mouse position value
    Vec2i mousePos() const { return mMousePos; }

    /// Return a pointer to the underlying GLFW window data structure
    ParentWindowPtr window() { return _window; }

    /// Return a pointer to the underlying nanoVG draw context
    NVGcontext *nvgContext() { return mNVGContext; }

    ///
    bool mayProcessEvents() const { return mProcessEvents; }

    /// Compute the layout of all widgets
    void performLayout();
public:
    /// Initialize the \ref Screen
    void initialize(ParentWindowPtr window);

    /* Event handlers */
    bool cursorPosCallbackEvent(double x, double y);
    bool mouseButtonCallbackEvent(int button, int action, int modifiers);
    bool keyCallbackEvent(int key, int scancode, int action, int mods);
    bool charCallbackEvent(unsigned int codepoint);
    bool dropCallbackEvent(int count, const char **filenames);
    bool scrollCallbackEvent(double x, double y);
    bool resizeCallbackEvent(int width, int height);

    /* Internal helper functions */
    void updateFocus(Widget *widget);
    void disposeWindow(Window *window);
    void centerWindow(Window *window);
    void moveWindowToFront(Window *window);
    void drawWidgets();

    void performLayout(NVGcontext *ctx);

protected:
    ParentWindowPtr _window;
    NVGcontext *mNVGContext;
    std::vector<Widget *> mFocusPath;
    Vec2i mFBSize;
    float mPixelRatio;
    int mMouseState, mModifiers;
    Vec2i mMousePos;
    bool mDragActive;
    Widget *mDragWidget = nullptr;
    double mLastInteraction;
    bool mProcessEvents;
    Color mBackground;
    std::string mCaption;
};
Screen* __nngui_findScreen(Screen::ParentWindowPtr);

/***************************************** formhelper *********************************/

NAMESPACE_BEGIN(detail)
template <typename T, typename sfinae = std::true_type> class FormWidget { };
NAMESPACE_END(detail)

/**
* \brief Convenience class to create simple AntTweakBar-style layouts that
*        expose variables of various types using NanoGUI widgets
*
* Example:
*
* <pre>
* [ ... initialize NanoGUI, construct screen ... ]
*
* FormHelper* h = new FormHelper(screen);
*
* // Add a new windows widget
* h->addWindow(Eigen::Vector2i(10,10),"Menu");
*
* // Start a new group
* h->addGroup("Group 1");
*
* // Expose an integer variable by reference
* h->addVariable("integer variable", aInt);
*
* // Expose a float variable via setter/getter functions
* h->addVariable(
*   [&](float value){ aFloat = value; },
*   [&](){ return *aFloat; },
*   "float variable");
*
* // add a new button
* h->addButton("Button",[&](){ std::cout << "Button pressed" << std::endl; });
* </pre>
*/

class FormHelper {
public:
    /// Create a helper class to construct NanoGUI widgets on the given screen
    FormHelper(Screen *screen) : mScreen(screen) { }

    /// Add a new top-level window
    Window *addWindow(const Vec2i &pos,
                         const std::string &title = "Untitled") {
        assert(mScreen);
        mWindow = new Window(mScreen, title);
        mLayout = new AdvancedGridLayout({10, 0, 10, 0}, {});
        mLayout->setMargin(10);
        mLayout->setColStretch(2, 1);
        mWindow->setPosition(pos);
        mWindow->setLayout(mLayout);
        mWindow->setVisible(true);
        return mWindow;
    }

    /// Add a new group that may contain several sub-widgets
    Label *addGroup(const std::string &caption) {
        Label* label = new Label(mWindow, caption, mGroupFontName, mGroupFontSize);
        if (mLayout->rowCount() > 0)
            mLayout->appendRow(mPreGroupSpacing); /* Spacing */
        mLayout->appendRow(0);
        mLayout->setAnchor(label, AdvancedGridLayout::Anchor(0, mLayout->rowCount()-1, 4, 1));
        mLayout->appendRow(mPostGroupSpacing);
        return label;
    }

    /// Add a new data widget controlled using custom getter/setter functions
    template <typename Type> detail::FormWidget<Type> *
    addVariable(const std::string &label, const std::function<void(Type)> &setter,
                const std::function<Type()> &getter, bool editable = true) {
        Label *labelW = new Label(mWindow, label, mLabelFontName, mLabelFontSize);
        auto widget = new detail::FormWidget<Type>(mWindow);
        auto refresh = [widget, getter] {
            Type value = getter(), current = widget->value();
            if (value != current)
                widget->setValue(value);
        };
        refresh();
        widget->setCallback(setter);
        widget->setEditable(editable);
        widget->setFontSize(mWidgetFontSize);
        Vec2i fs = widget->fixedSize();
        widget->setFixedSize(Vec2i(fs.x() != 0 ? fs.x() : mFixedSize.x(),
                                      fs.y() != 0 ? fs.y() : mFixedSize.y()));
        mRefreshCallbacks.push_back(refresh);
        if (mLayout->rowCount() > 0)
            mLayout->appendRow(mVariableSpacing);
        mLayout->appendRow(0);
        mLayout->setAnchor(labelW, AdvancedGridLayout::Anchor(1, mLayout->rowCount()-1));
        mLayout->setAnchor(widget, AdvancedGridLayout::Anchor(3, mLayout->rowCount()-1));
        return widget;
    }

    /// Add a new data widget that exposes a raw variable in memory
    template <typename Type> detail::FormWidget<Type> *
    addVariable(const std::string &label, Type &value, bool editable = true) {
        return addVariable<Type>(label,
            [&](Type v) { value = v; },
            [&]() -> Type { return value; },
            editable
        );
    }

    /// Add a button with a custom callback
    Button *addButton(const std::string &label, const std::function<void()> &cb) {
        Button *button = new Button(mWindow, label);
        button->setCallback(cb);
        button->setFixedHeight(25);
        if (mLayout->rowCount() > 0)
            mLayout->appendRow(mVariableSpacing);
        mLayout->appendRow(0);
        mLayout->setAnchor(button, AdvancedGridLayout::Anchor(1, mLayout->rowCount()-1, 3, 1));
        return button;
    }

    /// Add an arbitrary (optionally labeled) widget to the layout
    void addWidget(const std::string &label, Widget *widget) {
        mLayout->appendRow(0);
        if (label == "") {
            mLayout->setAnchor(widget, AdvancedGridLayout::Anchor(1, mLayout->rowCount()-1, 3, 1));
        } else {
            Label *labelW = new Label(mWindow, label, mLabelFontName, mLabelFontSize);
            mLayout->setAnchor(labelW, AdvancedGridLayout::Anchor(1, mLayout->rowCount()-1));
            mLayout->setAnchor(widget, AdvancedGridLayout::Anchor(3, mLayout->rowCount()-1));
        }
    }

    /// Cause all widgets to re-synchronize with the underlying variable state
    void refresh() {
        for (auto const &callback : mRefreshCallbacks)
            callback();
    }

    /// Access the currently active \ref Window instance
    Window *window() { return mWindow; }
    void setWindow(Window *window) {
        mWindow = window;
        mLayout = dynamic_cast<AdvancedGridLayout *>(window->layout());
        if (mLayout == nullptr)
            throw std::runtime_error(
                "Internal error: window has an incompatible layout!");
    }

    /// Specify a fixed size for newly added widgets
    void setFixedSize(const Vec2i &fw) { mFixedSize = fw; }
    Vec2i fixedSize() { return mFixedSize; }

    /* Set the font size / name of labels, group headers, and data widgets */
    const std::string &groupFontName() const { return mGroupFontName; }
    void setGroupFontName(const std::string &name) { mGroupFontName = name; }
    const std::string &labelFontName() const { return mLabelFontName; }
    void setLabelFontName(const std::string &name) { mLabelFontName = name; }
    int groupFontSize() const { return mGroupFontSize; }
    void setGroupFontSize(int value) { mGroupFontSize = value; }
    int labelFontSize() const { return mLabelFontSize; }
    void setLabelFontSize(int value) { mLabelFontSize = value; }
    int widgetFontSize() const { return mWidgetFontSize; }
    void setWidgetFontSize(int value) { mWidgetFontSize = value; }

protected:
    ref<Screen> mScreen;
    ref<Window> mWindow;
    ref<AdvancedGridLayout> mLayout;
    std::vector<std::function<void()>> mRefreshCallbacks;
    std::string mGroupFontName = "sans-bold";
    std::string mLabelFontName = "sans";
    Vec2i mFixedSize = Vec2i(0, 20);
    int mGroupFontSize = 20;
    int mLabelFontSize = 16;
    int mWidgetFontSize = 16;
    int mPreGroupSpacing = 15;
    int mPostGroupSpacing = 5;
    int mVariableSpacing = 5;
};

NAMESPACE_BEGIN(detail)
/* Various types of form widgets for different input types below */
template <> class FormWidget<bool, std::true_type> : public CheckBox {
public:
    FormWidget(Widget *p) : CheckBox(p, "") { setFixedWidth(20); }
    void setValue(bool v) { setChecked(v); }
    void setEditable(bool e) { setEnabled(e); }
    bool value() const { return checked(); }
};

template <typename T> class FormWidget<T, typename std::is_enum<T>::type> : public ComboBox {
public:
    FormWidget(Widget *p) : ComboBox(p) { }
    T value() const { return (T) selectedIndex(); }
    void setValue(T value) { setSelectedIndex((int) value); mSelectedIndex = (int) value; }
    void setCallback(const std::function<void(T)> &cb) {
        ComboBox::setCallback([cb](int v) { cb((T) v); });
    }
    void setEditable(bool e) { setEnabled(e); }
};

template <typename T> class FormWidget<T, typename std::is_integral<T>::type> : public IntBox<T> {
public:
    FormWidget(Widget *p) : IntBox<T>(p) { this->setAlignment(TextBox::Alignment::Right); }
};

template <typename T> class FormWidget<T, typename std::is_floating_point<T>::type> : public FloatBox<T> {
public:
    FormWidget(Widget *p) : FloatBox<T>(p) { this->setAlignment(TextBox::Alignment::Right); }
};

template <> class FormWidget<std::string, std::true_type> : public TextBox {
public:
    FormWidget(Widget *p) : TextBox(p) { setAlignment(TextBox::Alignment::Left); }
    void setCallback(const std::function<void(const std::string&)> &cb) {
        TextBox::setCallback([cb](const std::string &str) { cb(str); return true; });
    }
};

template <> class FormWidget<Color, std::true_type> : public ColorPicker {
public:
    FormWidget(Widget *p) : ColorPicker(p) { }
    void setValue(const Color &c) { setColor(c); }
    void setEditable(bool e) { setEnabled(e); }
    Color value() const { return color(); }
};

NAMESPACE_END(detail)

NAMESPACE_END(nngui)

#endif
