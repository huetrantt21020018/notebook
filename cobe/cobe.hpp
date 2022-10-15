/*
#  File            : cobe.hpp   (C++ header file)
#  Version         : 1.3.1 (2020-04-12 16:55)
#
#  Author          : Trung Thanh Nguyen
#                    --> Facebook: https://www.facebook.com/thanh.it95
#                    --> Email   : thanh.it1995@gmail.com
#
#  Description     : cobe - a small & fast graphics library for console terminal
#
#  Supported OS    : Windows and Linux (tested on Windows 7, Windows 10 v1909/VC++ 2013 & gcc, Ubuntu 19.10/gcc 9.2.1, Manjaro 19.0.2/gcc 9.2.1)
#
#  License         : GNU Lesser General Public License 3.0
#
#  Usage           : #include "cobe.hpp" (that's all, very simple)
#
*/

/*
Comment from the author: All functions (and variables) are defined in this header file, which might be a bad practice but it makes beginners feel comfortable.
*/


#ifndef _COBE_HEADER_INCLUDED_
#define _COBE_HEADER_INCLUDED_



// FEATURES -----------------------------------------------
#define COBE_SAFE_COORDINATE
#define COBE_WIN32_OPTIMIZED_BUFFER
//#define COBE_WIN32_SUPPORT_SOUND
#define COBE_LINUX_SUPPORT_MOUSE_EVENTS
// END FEATURES -------------------------------------------



// PLATFORM DETECTION -------------------------------------
#if defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32 )

#define COBE_PLATFORM_WIN32

#elif defined( __linux__ )

#define COBE_PLATFORM_LINUX

#endif
// END PLATFORM DETECTION ---------------------------------



// CONFIGURATIONS -----------------------------------------
#if defined COBE_PLATFORM_WIN32
#define COBE_SCREEN_BEGIN_OFFSET 0
#elif defined COBE_PLATFORM_LINUX
#define COBE_SCREEN_BEGIN_OFFSET 1
#endif


#if defined COBE_PLATFORM_WIN32
#define COBE_WIN32_MAX_CONSOLE_BUFFER_SIZE 12000
#endif


#define COBE_MAX_CAPTURE_MOUSE_EVENTS_COUNT 10


#define COBE_SHAPE_BUFFER_MAX_DATA_SIZE 1024


#if defined COBE_PLATFORM_LINUX
#define cobe_esc_seq "\x1b["
#endif


#ifndef __FUNCTION__
#define __FUNCTION__    __func__
#endif


#if defined _MSC_VER
//#define _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 4996 )
#endif
// END CONFIGURATIONS -------------------------------------



// LIBRARIES ----------------------------------------------
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <ctime>
#include <cstdarg>
#include <cmath>
#include <climits>
#include <vector>
#include <string>

// for sound playing
#include <set>
#include <algorithm>

#if defined COBE_PLATFORM_WIN32

#define _WIN32_WINNT 0x0500

#include <tchar.h>
#include <Windows.h>

#elif defined COBE_PLATFORM_LINUX

#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <fcntl.h>

#endif
// END LIBRARIES ------------------------------------------



// CUSTOM MACROS ------------------------------------------
#if defined COBE_PLATFORM_WIN32
#define cobe_gui_display_err(str) MessageBoxA(NULL, str, "cobe", MB_ICONERROR | MB_OK);
#elif defined COBE_PLATFORM_LINUX
#define cobe_gui_display_err(str) ;
#endif


#define cobe_err(format, ...) { \
                                char buffer[300] = { 0 }; std::sprintf(buffer, format, ##__VA_ARGS__); \
                                std::fprintf(stderr, "%s -- error at file %s, function %s, line %d \r\n", buffer, __FILE__, __FUNCTION__, __LINE__); \
                                cobe_gui_display_err(buffer) \
                                std::exit(EXIT_FAILURE); }

#define cobe_check_err(errorCondition, format, ...) if (errorCondition) cobe_err(format, ##__VA_ARGS__);


#define cobe_max(a,b)   (((a) > (b)) ? (a) : (b))
#define cobe_min(a,b)   (((a) < (b)) ? (a) : (b))


#define cobe_check_invalid_color(color) ((color) < 0 || (color) > 16)


#if defined COBE_SAFE_COORDINATE

#define cobe_expr_bound_x(x, screenMaxWidth) ((x) >= 0 && (x) < screenMaxWidth)
#define cobe_expr_bound_y(y, screenMaxHeight) ((y) >= 0 && (y) < screenMaxHeight)

#endif


#define cobe_display_error_win32_support_sound \
        { \
            this->printfAndUpdate(1, 1, "Sound playing is only available in Microsoft Windows            "); \
            this->printfAndUpdate(1, 2, "To enable this function, follow these steps:                    "); \
            this->printfAndUpdate(1, 3, "  Step 1. Link library winmm.                                   "); \
            this->printfAndUpdate(1, 4, "  Step 2. Add preprocessor definition: COBE_WIN32_SUPPORT_SOUND "); \
            this->printfAndUpdate(1, 5, "                                                                "); \
            this->printfAndUpdate(1, 6, "Press ESC key to continue.                                      "); \
            this->pause(COKEY_ESC); \
        }
// END CUSTOM MACROS --------------------------------------



// DLL LOADING ----------------------------------------
namespace libcobe
{


#if defined COBE_PLATFORM_WIN32

//static NTSTATUS(__stdcall *NtDelayExecution)(BOOL Alertable, PLARGE_INTEGER DelayInterval);
//static NTSTATUS(__stdcall *ZwSetTimerResolution)(IN ULONG RequestedResolution, IN BOOLEAN Set, OUT PULONG ActualResolution);
static LONG(WINAPI *NtDelayExecution)(BOOL Alertable, PLARGE_INTEGER DelayInterval) = (LONG(WINAPI*)(BOOL, PLARGE_INTEGER)) ::GetProcAddress(::GetModuleHandle(_TEXT("ntdll.dll")), "NtDelayExecution");
static LONG(WINAPI *ZwSetTimerResolution)(IN ULONG RequestedResolution, IN BOOLEAN Set, OUT PULONG ActualResolution) = (LONG(WINAPI*)(ULONG, BOOLEAN, PULONG)) ::GetProcAddress(::GetModuleHandle(_TEXT("ntdll.dll")), "ZwSetTimerResolution");

#endif
}
// END DLL LOADING ------------------------------------







///////////////////////////////////////////////////////////
//                        CONSTANTS                      //
///////////////////////////////////////////////////////////
namespace libcobe
{
    static char const* const cobe_const_listFgColors[] = {
        "30",   // 0  = BLACK
        "34",   // 1  = BLUE
        "32",   // 2  = GREEN
        "36",   // 3  = CYAN
        "31",   // 4  = RED
        "35",   // 5  = PURPLE
        "33",   // 6  = YELLOW
        "37",   // 7  = LIGHT_GRAY
        "90",   // 8  = DARK_GRAY
        "94",   // 9  = LIGHT BLUE
        "92",   // 10 = LIGHT GREEN
        "96",   // 11 = LIGHT CYAN
        "91",   // 12 = LIGHT RED
        "95",   // 13 = LIGHT PURPLE
        "93",   // 14 = LIGHT YELLOW
        "97",   // 15 = WHITE
        "39",   // 16 = DEFAULT
    };

    static char const* const cobe_const_listBgColors[] = {
        "40",   // 0  = BLACK
        "44",   // 1  = BLUE
        "42",   // 2  = GREEN
        "46",   // 3  = CYAN
        "41",   // 4  = RED
        "45",   // 5  = PURPLE
        "43",   // 6  = YELLOW
        "47",   // 7  = LIGHT_GRAY
        "100",  // 8  = DARK_GRAY
        "104",  // 9  = LIGHT BLUE
        "102",  // 10 = LIGHT GREEN
        "106",  // 11 = LIGHT CYAN
        "101",  // 12 = LIGHT RED
        "105",  // 13 = LIGHT PURPLE
        "103",  // 14 = LIGHT YELLOW
        "107",  // 15 = WHITE
        "49",   // 16 = DEFAULT
    };


    // VIRTUAL KEYS
    static int const COKEY_ENTER = 13;
    static int const COKEY_ESC = 27;
    static int const COKEY_SPACE = 32;

#if defined COBE_PLATFORM_WIN32
    static int const COKEY_LEFT = VK_LEFT;
    static int const COKEY_RIGHT = VK_RIGHT;
    static int const COKEY_UP = VK_UP;
    static int const COKEY_DOWN = VK_DOWN;
#elif defined COBE_PLATFORM_LINUX
    static int const COKEY_LEFT = 0x25;
    static int const COKEY_RIGHT = 0x27;
    static int const COKEY_UP = 0x26;
    static int const COKEY_DOWN = 0x28;
#endif // platform
}






///////////////////////////////////////////////////////////
//                     STRUCTS & ENUMS                   //
///////////////////////////////////////////////////////////

namespace libcobe
{
    struct CoVect
    {
        int x, y;

        inline CoVect() : x(0), y(0) { }
        inline CoVect(const int x, const int y) : x(x), y(y) { }

        inline const float length() const {
            return std::sqrt((float)(x * x + y * y));
        }

        inline const int lengthSqr() const {
            return x * x + y * y;
        }

        inline const CoVect add(const CoVect &other) const {
            return CoVect::sum(*this, other);
        }

        inline const CoVect minus(const CoVect &other) const {
            return CoVect::subtract(*this, other);
        }

        inline const CoVect multiply(const int factor) const {
            return CoVect(x * factor, y * factor);
        }

        inline const CoVect translate(const CoVect &transVec) const
        {
            return CoVect(x + transVec.x, y + transVec.y);
        }

        inline const CoVect reverse() const
        {
            return CoVect(-x, -y);
        }

        inline static const CoVect sum(const CoVect &a, const CoVect &b) {
            return CoVect(a.x + b.x, a.y + b.y);
        }

        inline static const CoVect subtract(const CoVect &a, const CoVect &b) {
            return CoVect(a.x - b.x, a.y - b.y);
        }

        inline static int dot(const CoVect &a, const CoVect &b) {
            return a.x * b.x + a.y * b.y;
        }

        inline static int cross(const CoVect &a, const CoVect &b) {
            return a.x * b.y - a.y * b.x;
        }

        inline friend const CoVect operator+ (const CoVect &a, const CoVect &b) {
            return CoVect::sum(a, b);
        }

        inline friend const CoVect operator- (const CoVect &a, const CoVect &b) {
            return CoVect::subtract(a, b);
        }

        inline friend const CoVect operator* (const CoVect &a, const int factor) {
            return a.multiply(factor);
        }

        inline friend const CoVect operator* (const int factor, const CoVect &a) {
            return a.multiply(factor);
        }
    };

    struct CoVectf
    {
        float x, y;

        inline CoVectf() : x(0), y(0) { }
        inline CoVectf(const float x, const float y) : x(x), y(y) { }

        inline const float length() const {
            return std::sqrt(x * x + y * y);
        }

        inline const float lengthSqr() const {
            return x * x + y * y;
        }

        inline const CoVectf normalize() const {
            float mag = length();
            return CoVectf(x / mag, y / mag);
        }

        inline const CoVectf add(const CoVectf &other) const {
            return CoVectf::sum(*this, other);
        }

        inline const CoVectf minus(const CoVectf &other) const {
            return CoVectf::subtract(*this, other);
        }

        inline const CoVectf multiply(const float factor) const {
            return CoVectf(x * factor, y * factor);
        }

        inline const CoVectf translate(const CoVectf &transVec) const
        {
            return CoVectf(x + transVec.x, y + transVec.y);
        }

        inline const CoVectf reverse() const
        {
            return CoVectf(-x, -y);
        }

        inline static const CoVectf sum(const CoVectf &a, const CoVectf &b) {
            return CoVectf(a.x + b.x, a.y + b.y);
        }

        inline static const CoVectf subtract(const CoVectf &a, const CoVectf &b) {
            return CoVectf(a.x - b.x, a.y - b.y);
        }

        inline static float dot(const CoVectf &a, const CoVectf &b) {
            return a.x * b.x + a.y * b.y;
        }

        inline static float cross(const CoVectf &a, const CoVectf &b) {
            return a.x * b.y - a.y * b.x;
        }

        inline friend const CoVectf operator+ (const CoVectf &a, const CoVectf &b) {
            return CoVectf::sum(a, b);
        }

        inline friend const CoVectf operator- (const CoVectf &a, const CoVectf &b) {
            return CoVectf::subtract(a, b);
        }

        inline friend const CoVectf operator* (const CoVectf &a, const float factor) {
            return a.multiply(factor);
        }

        inline friend const CoVectf operator* (const float factor, const CoVectf &a) {
            return a.multiply(factor);
        }

        inline friend const CoVectf operator/ (const CoVectf &a, const float factor) {
            return a.multiply(1.0f / factor);
        }
    };


    inline static bool operator==(const CoVect &A, const CoVect &B)
    {
        return A.x == B.x && A.y == B.y;
    }

    inline static bool operator==(const CoVectf &A, const CoVectf &B)
    {
        return A.x == B.x && A.y == B.y;
    }
}


namespace libcobe
{
    enum CoMouseButton
    {
        COMOUSE_ALL = 0,
        COMOUSE_LEFT = 1,
        COMOUSE_RIGHT = 2,
        COMOUSE_DOUBLECLICK = 3
    };

    struct CoMouseRecord
    {
        CoMouseButton button;
        CoVect position;
    };

    struct CoMouseEvents
    {
        CoMouseRecord records[COBE_MAX_CAPTURE_MOUSE_EVENTS_COUNT];
        int numEvents;
    };
}










///////////////////////////////////////////////////////////
//                       COBE LIBRARY                    //
///////////////////////////////////////////////////////////


namespace libcobe
{
    // UTILITIES ------------------------------------------
    class CoUtils
    {
    public:
        inline static int random(int minValue, int maxValue)
        {
            cobe_check_err(minValue > maxValue, "Invalid argument minValue = %d, maxValue = %d", minValue, maxValue);
            return minValue + std::rand() % (maxValue - minValue + 1);
        }

        inline static char* strupper(char* const str)
        {
            for (char *p = str; (*p = (char)std::toupper(*p)); ++p);
            return str;
        }

        inline static void lowerstr(std::string &str)
        {
            int n = str.length();
            for (int i = 0; i < n; ++i)
                str[i] = std::tolower(str[i]);
        }
    };
    // END UTILITIES --------------------------------------



    // COLOR ----------------------------------------------
    class CoColor
    {
    public:
        static int const BLACK          = 0;
        static int const BLUE           = 1;
        static int const GREEN          = 2;
        static int const CYAN           = 3;
        static int const RED            = 4;
        static int const PURPLE         = 5;
        static int const YELLOW         = 6;
        static int const LIGHT_GRAY     = 7;
        static int const DARK_GRAY      = 8;
        static int const LIGHT_BLUE     = 9;
        static int const LIGHT_GREEN    = 10;
        static int const LIGHT_CYAN     = 11;
        static int const LIGHT_RED      = 12;
        static int const LIGHT_PURPLE   = 13;
        static int const LIGHT_YELLOW   = 14;
        static int const WHITE          = 15;
        static int const DEFAULT        = 16;
        
    public:
        inline static int getRandomColor(int excludingBlackColor = 1)
        {
            int t = excludingBlackColor ? 1 : 0;
            return t + std::rand() % (16 - t);
        }
    };
    // END COLOR ------------------------------------------
    





    // SHAPES ---------------------------------------------
    namespace coshapeinternal
    {
        enum CoShapeElementType { CHAR_ELE, STRING_ELE };


        struct CoShapeElement
        {
            CoVect pos;

            char ch;
            std::string str;

            CoShapeElementType type;

            inline CoShapeElement(int posX, int posY) : pos(posX, posY), ch(0), type(CHAR_ELE)
            {

            }
        };


        class CoShapeBuffer
        {
        public:
            char data[COBE_SHAPE_BUFFER_MAX_DATA_SIZE];
            int dataWidth;
            int dataHeight;

        public:
            inline CoShapeBuffer(int width, int height) : dataWidth(width), dataHeight(height)
            {
                std::memset(data, 0, COBE_SHAPE_BUFFER_MAX_DATA_SIZE);

                cobe_check_err(dataWidth <= 0 || dataHeight <= 0, "Invalid width and/or height");
                cobe_check_err(dataWidth * dataHeight > COBE_SHAPE_BUFFER_MAX_DATA_SIZE, "Size is too large");
            }


            inline void plot(int x, int y, char ch)
            {
                data[y * dataWidth + x] = ch;
            }


            inline char* getDataPtr(int x, int y) {
                return data + y * dataWidth + x;
            }


            inline void outputToList(std::vector<CoShapeElement> &listEle) const
            {
                listEle.clear();
                char const *pdata = data;

                for (int y = 0; y < dataHeight; ++y)
                {
                    int xStart = -1;

                    if (pdata[0] != 0 && pdata[0] != ' ')
                        xStart = 0;

                    for (int x = 1; x < dataWidth; ++x) {
                        if ((pdata[x] == 0 || pdata[x] == ' ') && xStart >= 0) {
                            int strLength = x - xStart;
                            pushNewElement(listEle, pdata, xStart, y, strLength);
                            xStart = -1;
                        }
                        else if (pdata[x] != 0 && pdata[x] != ' ' && xStart < 0) {
                            xStart = x;
                        }
                    }

                    if (xStart >= 0) {
                        int strLength = dataWidth - xStart;
                        pushNewElement(listEle, pdata, xStart, y, strLength);
                        xStart = -1;
                    }

                    pdata += dataWidth;
                } 
            }


            inline void outputToListOptimized(std::vector<CoShapeElement> &listEle, int &dataWidth, int &dataHeight) const
            {
                outputToList(listEle);

                int maxX = INT_MIN;
                int maxY = INT_MIN;

                for (int i = (int)listEle.size() - 1; i >= 0; --i)
                {
                    CoShapeElement &ele = listEle[i];

                    maxY = cobe_max(maxY, ele.pos.y);
                    
                    if (ele.type == CHAR_ELE) {
                        maxX = cobe_max(maxX, ele.pos.x);
                    }
                    else {
                        maxX = cobe_max(maxX, ele.pos.x + (int)ele.str.length() - 1);
                    }
                }

                dataWidth = maxX + 1;
                dataHeight = maxY + 1;
            }

        private:
            inline void pushNewElement(std::vector<CoShapeElement> &listEle, char const *pdata, int x, int y, int strLength) const
            {
                CoShapeElement ele(x, y);

                if (strLength > 1) {
                    ele.str = std::string(pdata + x, strLength);
                    ele.type = STRING_ELE;
                }
                else {
                    ele.ch = pdata[x];
                    ele.type = CHAR_ELE;
                }

                listEle.push_back(ele);
            }
        };
    }


    class CoShape
    {
        friend class CobeManager;

    private:
        std::vector<coshapeinternal::CoShapeElement> listEle;

        int dataWidth;
        int dataHeight;

        CoVect coordTopLeft;
        CoVect coordCenter;

        std::string caption;
        CoVect captionPosition;

    public:
        inline CoShape(int xTopLeft = 0, int yTopLeft = 0) : dataWidth(0), dataHeight(0)
        {
            setTopLeftCoord(xTopLeft, yTopLeft);
            initCaption();
        }


        inline CoShape(const coshapeinternal::CoShapeBuffer &buffer, int xTopLeft = 0, int yTopLeft = 0)
        {
            setTopLeftCoord(xTopLeft, yTopLeft);
            initCaption();

            init(buffer);
        }


        inline CoShape(int width, char const* const str, int xTopLeft = 0, int yTopLeft = 0)
        {
            setTopLeftCoord(xTopLeft, yTopLeft);
            initCaption();

            init(width, str);
        }


        inline CoShape(char *fileName, int xTopLeft = 0, int yTopLeft = 0)
        {
            setTopLeftCoord(xTopLeft, yTopLeft);
            initCaption();

            init(fileName);
        }


        inline void init(const coshapeinternal::CoShapeBuffer &buffer)
        {
            coshapeinternal::CoShapeElement captionEle = listEle[0];

            buffer.outputToList(listEle);

            dataWidth = buffer.dataWidth;
            dataHeight = buffer.dataHeight;

            listEle.insert(listEle.begin(), captionEle);
        }


        inline void init(int width, char const* const str)
        {
            int strLength = std::strlen(str);

            cobe_check_err(width <= 0, "Invalid parameter: width");
            cobe_check_err(strLength <= 0, "str is empty");
            cobe_check_err(strLength % width != 0, "str length is not a multiple of width");

            int height = strLength / width;

            coshapeinternal::CoShapeBuffer buffer(width, height);
            std::memcpy(buffer.data, str, strLength);

            init(buffer);
        }


        inline void init(char *fileName)
        {
            char temp = 0;

            std::FILE *fin = std::fopen(fileName, "r");
            cobe_check_err(fin == NULL, "Can not open file %s", fileName);

            std::fscanf(fin, "%d %d", &dataWidth, &dataHeight);
            while (((temp = std::fgetc(fin)) != '\n') && !std::feof(fin));


            cobe_check_err(dataWidth < 1 || dataHeight < 1, "Invalid width and/or height");
            

            coshapeinternal::CoShapeBuffer buffer(dataWidth, dataHeight);


            char *pdata = buffer.data;
            char line[COBE_SHAPE_BUFFER_MAX_DATA_SIZE] = { 0 };


            for (int i = 0; i < dataHeight; ++i)
            {
                std::fscanf(fin, "%[^\n]%*c", line);
                int lineLength = std::strlen(line);

                cobe_check_err(lineLength != dataWidth, "Invalid shape data at line %d (different width)", i + 1);

                std::memcpy(pdata, line, dataWidth);
                pdata += dataWidth;
            }

            std::fclose(fin);


            init(buffer);
        }


        inline int getWidth() const { return dataWidth; }
        inline int getHeight() const { return dataHeight; }
        inline CoVect getTopLeftCoord() const { return coordTopLeft; }
        inline CoVect getCenterCoord() const { return coordCenter; }


        inline void setTopLeftCoord(const CoVect &coord)
        {
            coordTopLeft = coord;
            updateCenterCoord();
        }

        inline void setTopLeftCoord(const int x, const int y)
        {
            setTopLeftCoord(CoVect(x, y));
        }

        inline void setCenterCoord(const CoVect &coord)
        {
            coordCenter = coord;
            updateTopLeftCoord();
        }

        inline void setCenterCoord(const int x, const int y)
        {
            setCenterCoord(CoVect(x, y));
        }


        inline void moveX(int dx)
        {
            coordTopLeft.x += dx;
            updateCenterCoord();
        }

        inline void moveY(int dy)
        {
            coordTopLeft.y += dy;
            updateCenterCoord();
        }


        inline void setCaption(char const *captionStr)
        {
            if (!captionStr)
                return;

            int inpCapLen = std::strlen(captionStr);
            captionPosition.y = (dataHeight - 1) / 2;
            captionPosition.x = (dataWidth - inpCapLen) / 2;

            caption = std::string(captionStr);

            coshapeinternal::CoShapeElement &captionEle = listEle[0];
            captionEle.pos = captionPosition;
            captionEle.str = caption;
        }


        inline int checkPointInside(int xpoint, int ypoint) const
        {
            if (checkPointInBoundingBox(xpoint, ypoint) == 0)
                return 0;

            int xTopLeft = coordTopLeft.x;
            int yTopLeft = coordTopLeft.y;

            for (int i = (int)listEle.size() - 1; i >= 0; --i)
            {
                const coshapeinternal::CoShapeElement &ele = listEle[i];

                if (checkPointInShapeEle(xpoint, ypoint, xTopLeft, yTopLeft, ele))
                    return 1;
            }

            return 0;
        }


        inline int checkPointInside(const CoVect &point) const
        {
            return checkPointInside(point.x, point.y);
        }


        inline static int checkShapeOverlap(const CoShape &a, const CoShape &b)
        {
            if (checkShapeBoundingBoxOverlap(a, b) == 0)
                return 0;

            int xTopLeftA = a.coordTopLeft.x;
            int yTopLeftA = a.coordTopLeft.y;
            int xTopLeftB = b.coordTopLeft.x;
            int yTopLeftB = b.coordTopLeft.y;


            for (int i = (int)a.listEle.size() - 1; i >= 0; --i)
            {
                const coshapeinternal::CoShapeElement &eleA = a.listEle[i];

                int xStartA = eleA.pos.x + xTopLeftA;
                int yStartA = eleA.pos.y + yTopLeftA;
                int xEndA = (eleA.type == coshapeinternal::CHAR_ELE) ? xStartA : xStartA + eleA.str.length() - 1;

                for (int j = (int)b.listEle.size() - 1; j >= 0; --j)
                {
                    const coshapeinternal::CoShapeElement &eleB = b.listEle[j];

                    int xStartB = eleB.pos.x + xTopLeftB;
                    int yStartB = eleB.pos.y + yTopLeftB;
                    int xEndB = (eleB.type == coshapeinternal::CHAR_ELE) ? xStartB : xStartB + eleB.str.length() - 1;

                    if (yStartA != yStartB)
                        continue;

                    if (eleA.type == coshapeinternal::CHAR_ELE && eleB.type == coshapeinternal::CHAR_ELE) {
                        if (xStartA == xStartB)
                            return 1;
                    }
                    else if (eleA.type == coshapeinternal::CHAR_ELE) {
                        if (checkPointInShapeEle(xStartA, yStartA, xTopLeftB, yTopLeftB, eleB))
                            return 1;
                    }
                    else if (eleB.type == coshapeinternal::CHAR_ELE) {
                        if (checkPointInShapeEle(xStartB, yStartB, xTopLeftA, yTopLeftA, eleA))
                            return 1;
                    }
                    else {
                        if (xStartA <= xStartB && xStartB <= xEndA)
                            return 1;

                        if (xStartB <= xStartA && xStartA <= xEndB)
                            return 1;
                    }
                }
            }

            return 0;
        }


    private:
        inline void initCaption()
        {
            coshapeinternal::CoShapeElement captionEle(0, 0);
            captionEle.type = coshapeinternal::STRING_ELE;
            listEle.push_back(captionEle);
        }


        inline void updateCenterCoord()
        {
            coordCenter.x = coordTopLeft.x + dataWidth / 2;
            coordCenter.y = coordTopLeft.y + dataHeight / 2;
        }
        
        inline void updateTopLeftCoord()
        {
            coordTopLeft.x = coordCenter.x - dataWidth / 2;
            coordTopLeft.y = coordCenter.y - dataHeight / 2;
        }


        inline void getBoundingBox(int &xTopLeft, int &yTopLeft, int &xBottomRight, int &yBottomRight) const
        {
            xTopLeft = this->coordTopLeft.x;
            yTopLeft = this->coordTopLeft.y;
            xBottomRight = xTopLeft + this->dataWidth - 1;
            yBottomRight = yTopLeft + this->dataHeight - 1;
        }


        inline int checkPointInBoundingBox(int xpoint, int ypoint) const
        {
            int cond1 = (coordTopLeft.x <= xpoint && xpoint < coordTopLeft.x + dataWidth);
            int cond2 = (coordTopLeft.y <= ypoint && ypoint < coordTopLeft.y + dataHeight);
            return (cond1 && cond2);
        }


    private:
        inline static int checkRectOverlap(int axtopleft, int aytopleft, int axbotright, int aybotright,
            int bxtopleft, int bytopleft, int bxbotright, int bybotright)
        {
            int noOverlap = (
                axtopleft > bxbotright ||
                bxtopleft > axbotright ||
                aytopleft > bybotright ||
                bytopleft > aybotright
                );

            return !noOverlap;
        }


        inline static int checkShapeBoundingBoxOverlap(const CoShape &a, const CoShape &b)
        {
            int axtopleft, aytopleft, axbotright, aybotright;
            int bxtopleft, bytopleft, bxbotright, bybotright;

            a.getBoundingBox(axtopleft, aytopleft, axbotright, aybotright);
            b.getBoundingBox(bxtopleft, bytopleft, bxbotright, bybotright);

            int ret = CoShape::checkRectOverlap(axtopleft, aytopleft, axbotright, aybotright, bxtopleft, bytopleft, bxbotright, bybotright);
            return ret;
        }


        inline static int checkPointInShapeEle(int xpoint, int ypoint, int xTopLeftEle, int yTopLeftEle, const coshapeinternal::CoShapeElement &ele)
        {
            int xStart = ele.pos.x + xTopLeftEle;
            int yStart = ele.pos.y + yTopLeftEle;

            if (yStart != ypoint)
                return 0;

            if (xStart == xpoint)
                return 1;

            if (ele.type == coshapeinternal::STRING_ELE)
            {
                int strLength = ele.str.length();
                int xEnd = xStart + strLength - 1;

                if (xStart <= xpoint && xpoint <= xEnd)
                    return 1;
            }

            return 0;
        }
    };


    class CoShapeFactory
    {
    public:
        inline static CoShape createRectangle(int xTopLeft, int yTopLeft, int width, int height, char chFill = '*', char chBorder = 0, char const *caption = 0)
        {
            coshapeinternal::CoShapeBuffer buffer(width, height);

            constructDataRectangle(buffer, chFill, chBorder);

            CoShape shape(buffer, xTopLeft, yTopLeft);

            shape.setCaption(caption);

            return shape;
        }


        inline static CoShape createEllipse(int xCenter, int yCenter, int radiusWidth, int radiusHeight, char chFill = '*', char const *caption = 0)
        {
            int xTopLeft = xCenter - radiusWidth + 1;
            int yTopLeft = yCenter - radiusHeight + 1;
            int shapeWidth = radiusWidth * 2 - 1;
            int shapeHeight = radiusHeight * 2 - 1;

            coshapeinternal::CoShapeBuffer buffer(shapeWidth, shapeHeight);

            constructDataEllipse(buffer, xCenter, yCenter, radiusWidth, radiusHeight, chFill);

            CoShape shape(buffer, xTopLeft, yTopLeft);

            shape.setCaption(caption);

            return shape;
        }


        inline static CoShape createTriangle(CoVect vertA, CoVect vertB, CoVect vertC, char chFill = '*', char const *caption = 0)
        {
            int minX = cobe_min(vertA.x, cobe_min(vertB.x, vertC.x));
            int minY = cobe_min(vertA.y, cobe_min(vertB.y, vertC.y));
            int maxX = cobe_max(vertA.x, cobe_max(vertB.x, vertC.x));
            int maxY = cobe_max(vertA.y, cobe_max(vertB.y, vertC.y));

            CoVect topLeft(minX, minY);
            int width = maxX - minX + 1;
            int height = maxY - minY + 1;

            coshapeinternal::CoShapeBuffer buffer(width, height);

            constructDataTriangle(buffer, vertA, vertB, vertC, chFill, topLeft);

            CoShape shape(buffer, topLeft.x, topLeft.y);

            shape.setCaption(caption);

            return shape;
        }


        inline static CoShape createLine(int x1, int y1, int x2, int y2, char chStroke = '*')
        {
            CoVect topLeft(cobe_min(x1, x2), cobe_min(y1, y2));
            int maxX = cobe_max(x1, x2);
            int maxY = cobe_max(y1, y2);

            int width = maxX - topLeft.x + 1;
            int height = maxY - topLeft.y + 1;

            coshapeinternal::CoShapeBuffer buffer(width, height);

            constructDataLine(buffer, x1, y1, x2, y2, chStroke, topLeft);

            CoShape shape(buffer, topLeft.x, topLeft.y);

            return shape;
        }


    private:
        inline static void constructDataRectangle(coshapeinternal::CoShapeBuffer &buffer, char chFill, char chBorder)
        {
            int dataWidth = buffer.dataWidth;
            int dataHeight = buffer.dataHeight;

            if (chBorder == 0)
                chBorder = chFill;

            for (int y = 0; y < dataHeight; ++y) {
                for (int x = 0; x < dataWidth; ++x) {
                    if (x == 0 || y == 0 || x == dataWidth - 1 || y == dataHeight - 1)
                        buffer.plot(x, y, chBorder);
                    else
                        buffer.plot(x, y, chFill);
                }
            }
        }


        inline static void constructDataEllipse(coshapeinternal::CoShapeBuffer &buffer, int xCenter, int yCenter, int rWidth, int rHeight, char chFill)
        {
            int dataWidth = buffer.dataWidth;
            int xTopLeft = xCenter - rWidth + 1;
            int yTopLeft = yCenter - rHeight + 1;

            CoVect translateVec(-xTopLeft, -yTopLeft);

            --rWidth;
            --rHeight;

            int hh = rHeight * rHeight;
            int ww = rWidth * rWidth;
            int hhww = hh * ww;
            int x0 = rWidth;
            int dx = 0;

            // horizontal diameter
            CoVect posHori = CoVect(xCenter - rWidth, yCenter).translate(translateVec);
            char *pdatahori = buffer.getDataPtr(posHori.x, posHori.y);
            std::memset(pdatahori, (int)chFill, dataWidth * sizeof(char));
            

            // now do both halves at the same time, away from the diameter
            for (int y = 1; y <= rHeight; y++)
            {
                int x1 = x0 - (dx - 1);  // try slopes of dx - 1 or more

                for (; x1 > 0; x1--)
                    if (x1*x1*hh + y*y*ww <= hhww)
                        break;

                dx = x0 - x1;  // current approximation of the slope
                x0 = x1;


                int copySize = 2 * x0 + 1;

                CoVect pointA = CoVect(xCenter - x0, yCenter - y).translate(translateVec);
                CoVect pointB = CoVect(xCenter - x0, yCenter + y).translate(translateVec);

                char *pA = buffer.getDataPtr(pointA.x, pointA.y);
                char *pB = buffer.getDataPtr(pointB.x, pointB.y);

                std::memset(pA, (int)chFill, copySize * sizeof(char));
                std::memset(pB, (int)chFill, copySize * sizeof(char));
            }
        }


        // Barycentric algorithm
        inline static void constructDataTriangle(coshapeinternal::CoShapeBuffer &buffer, CoVect vertA, CoVect vertB, CoVect vertC, char chFill, CoVect topLeft)
        {
            CoVect translateVec = topLeft.reverse();

            // spanning vectors of edge (v1,v2) and (v1,v3)
            CoVect vs1 = CoVect(vertB.x - vertA.x, vertB.y - vertA.y);
            CoVect vs2 = CoVect(vertC.x - vertA.x, vertC.y - vertA.y);

            // cross product
            int crossv12 = CoVect::cross(vs1, vs2);

            // get the bounding box of the triangle
            int minX = cobe_min(vertA.x, cobe_min(vertB.x, vertC.x));
            int minY = cobe_min(vertA.y, cobe_min(vertB.y, vertC.y));
            int maxX = cobe_max(vertA.x, cobe_max(vertB.x, vertC.x));
            int maxY = cobe_max(vertA.y, cobe_max(vertB.y, vertC.y));

            for (int y = minY; y <= maxY; y++)
            {
                for (int x = minX; x <= maxX; x++)
                {
                    CoVect q = CoVect(x - vertA.x, y - vertA.y);

                    float s = (float)CoVect::cross(q, vs2) / crossv12;
                    float t = (float)CoVect::cross(vs1, q) / crossv12;

                    if ((s >= 0) && (t >= 0) && (s + t <= 1))
                    {
                        // inside triangle
                        CoVect point = CoVect(x, y).translate(translateVec);
                        buffer.plot(point.x, point.y, chFill);
                    }
                }
            }
        }


        // Bresenham's line algorithm
        inline static void constructDataLine(coshapeinternal::CoShapeBuffer &buffer, int x1, int y1, int x2, int y2, char chStroke, CoVect topLeft)
        {
            int deltax = x2 - x1;
            int deltay = y2 - y1;

            int stepx = (x1 <= x2) ? 1 : -1;
            int stepy = (y1 <= y2) ? 1 : -1;

            if (deltax == 0) {
                for (int y = y1; y != y2; y += stepy) {
                    buffer.plot(x1 - topLeft.x, y - topLeft.y, chStroke);
                }

                return;
            }


            float deltaerr = fabs((float)deltay / deltax);
            float error = 0;

            int y = y1;

            for (int x = x1; x != x2; x += stepx)
            {
                buffer.plot(x - topLeft.x, y - topLeft.y, chStroke);

                error = error + deltaerr;

                if (error >= 0.5f) {
                    int sign = (deltay >= 0) ? 1 : -1;
                    y = y + sign;
                    error = error - 1.f;
                }
            }
        }
    };
    // END SHAPES -----------------------------------------



    



    
    class CobeManager
    {

    ///////////////////////////////////////////////////////
    //      HELPER COMPONENTS FOR CLASS CobeManager      //
    ///////////////////////////////////////////////////////

    private:
        class CobeDisplay;

        class CobeDisplayHelper
        {
        public:
            inline static void printShape(CobeDisplay *display, const CoShape &shape)
            {
                CoVect topLeft = shape.getTopLeftCoord();
                int topLeftX = topLeft.x;
                int topLeftY = topLeft.y;

                int nEle = (int)shape.listEle.size();

                for (int i = 1; i < nEle; ++i)
                {
                    const coshapeinternal::CoShapeElement &ele = shape.listEle[i];

                    int xout = ele.pos.x + topLeftX;
                    int yout = ele.pos.y + topLeftY;
                    
                    if (ele.type == coshapeinternal::CHAR_ELE) {
                        display->print(xout, yout, ele.ch);
                    }
                    else {
                        if (ele.str.length() > 0)
                            display->print(xout, yout, ele.str.c_str());
                    }
                }

                display->print(shape.captionPosition.x + topLeftX, shape.captionPosition.y + topLeftY, shape.caption.c_str());
            }


            inline static void printLine(CobeDisplay *display, char chStroke, int x1, int y1, int x2, int y2)
            {
                int deltax = x2 - x1;
                int deltay = y2 - y1;

                int stepx = (x1 <= x2) ? 1 : -1;
                int stepy = (y1 <= y2) ? 1 : -1;

                if (deltax == 0) {
                    for (int y = y1; y != y2; y += stepy) {
                        display->print(x1, y, chStroke);
                    }

                    return;
                }


                float deltaerr = fabs((float)deltay / deltax);
                float error = 0;

                int y = y1;

                for (int x = x1; x != x2; x += stepx)
                {
                    display->print(x, y, chStroke);

                    error = error + deltaerr;

                    if (error >= 0.5f) {
                        int sign = (deltay >= 0) ? 1 : -1;
                        y = y + sign;
                        error = error - 1.f;
                    }
                }
            }


            inline static void clampCoordinateX(int &value, int screenMaxWidth)
            {
                if (value < 0)
                    value = 0;

                if (value >= screenMaxWidth)
                    value = screenMaxWidth - 1;
            }


            inline static void clampCoordinateY(int &value, int screenMaxHeight)
            {
                if (value < 0)
                    value = 0;

                if (value >= screenMaxHeight)
                    value = screenMaxHeight - 1;
            }


            inline static void calculatePrintIndex(char const *str, int x, int &xPosition, int &strStartIndex, int &strEndIndex, int screenMaxWidth)
            {
                strStartIndex = 0;
                strEndIndex = std::strlen(str) - 1;
                xPosition = x;

                if (x < 0) {
                    strStartIndex -= x;
                    xPosition = 0;
                }

                if (x + strEndIndex >= screenMaxWidth) {
                    strEndIndex = strEndIndex - (x + strEndIndex - screenMaxWidth) - 1;
                }
            }
        };


#if defined COBE_PLATFORM_WIN32
        class CobeDisplay
        {
        private:
            CobeManager *manager;
            ::CHAR_INFO buffer[COBE_WIN32_MAX_CONSOLE_BUFFER_SIZE];

            int defaultFgColor;
            int defaultBgColor;
            int currentColor;
            int currentFgColor;
            int currentBgColor;

            ::COORD pre_home;
            ::COORD pre_dwBufferSize; // {X = screenMaxWidth, Y = screenMaxHeight }
            ::SMALL_RECT pre_writeRegion;


        public:
            inline CobeDisplay(CobeManager *owner) : manager(owner)
            {
            }


            inline void init()
            {
                cobe_check_err(COBE_WIN32_MAX_CONSOLE_BUFFER_SIZE < manager->screenMaxWidth * manager->screenMaxHeight, \
                    "COBE_WIN32_MAX_CONSOLE_BUFFER_SIZE = %d, not enough with screen size, please change COBE_WIN32_MAX_CONSOLE_BUFFER_SIZE in cobe.hpp and try again", COBE_WIN32_MAX_CONSOLE_BUFFER_SIZE);

                std::memset(buffer, 0, COBE_WIN32_MAX_CONSOLE_BUFFER_SIZE * sizeof(::CHAR_INFO));

                pre_home.X = 0;
                pre_home.Y = 0;
                pre_dwBufferSize.X = manager->screenMaxWidth;
                pre_dwBufferSize.Y = manager->screenMaxHeight;

                pre_writeRegion.Top = pre_writeRegion.Left = 0;
                pre_writeRegion.Right = pre_writeRegion.Left + manager->screenMaxWidth - 1;
                pre_writeRegion.Bottom = pre_writeRegion.Top + manager->screenMaxHeight - 1;

#if defined COBE_WIN32_OPTIMIZED_BUFFER
                std::memset(bufferOp, 0, COBE_WIN32_MAX_CONSOLE_BUFFER_SIZE * sizeof(::CHAR_INFO));
                lastCoordTopLeft.X = lastCoordTopLeft.Y = 1000;
                lastCoordBottomRight.X = lastCoordBottomRight.Y = -1;
#endif

                // color
                defaultBgColor = CoColor::BLACK;
                defaultFgColor = CoColor::LIGHT_GRAY;
                setColor(CoColor::LIGHT_GRAY);
            }


            inline void update()
            {
#if defined COBE_WIN32_OPTIMIZED_BUFFER
                updateOptimized();
#else
                updateNormal();
#endif
            }


            inline void setForegroundColor(int color)
            {
                if (color == CoColor::DEFAULT)
                    color = defaultFgColor;

                currentFgColor = color;
                currentColor = getColorCode(currentFgColor, currentBgColor);
            }

            inline void setBackgroundColor(int color)
            {
                if (color == CoColor::DEFAULT)
                    color = defaultBgColor;

                currentBgColor = color;
                currentColor = getColorCode(currentFgColor, currentBgColor);
            }

            inline void resetColor()
            {
                setForegroundColor(defaultFgColor);
                setBackgroundColor(defaultBgColor);
            }

            
            inline void clearScreen()
            {
                int screenBufferLength = manager->screenMaxWidth * manager->screenMaxHeight;

                for (::CHAR_INFO *p = buffer + screenBufferLength; p >= buffer; --p) {
                    p->Char.UnicodeChar = (wchar_t)' ';
                    p->Attributes = (::WORD)defaultBgColor;
                }

#if defined (COBE_WIN32_OPTIMIZED_BUFFER)
                lastCoordTopLeft.X = 0;
                lastCoordTopLeft.Y = 0;
                lastCoordBottomRight.X = manager->screenMaxWidth - 1;
                lastCoordBottomRight.Y = manager->screenMaxHeight - 1;
#endif
            }


            inline void fillRect(int topLeftX, int topLeftY, int width, int height, int charValue = (int)' ', int fgColor = CoColor::DEFAULT, int bgColor = CoColor::DEFAULT)
            {
                int screenMaxWidth = manager->screenMaxWidth;
                int screenMaxHeight = manager->screenMaxHeight;

                if (width < 1 || height < 1 || topLeftX >= screenMaxWidth || topLeftY >= screenMaxHeight)
                    return;

                int rightX = topLeftX + width - 1;
                int bottomY = topLeftY + height - 1;
                CobeDisplayHelper::clampCoordinateX(topLeftX, screenMaxWidth);
                CobeDisplayHelper::clampCoordinateY(topLeftY, screenMaxHeight);
                CobeDisplayHelper::clampCoordinateX(rightX, screenMaxWidth);
                CobeDisplayHelper::clampCoordinateY(bottomY, screenMaxHeight);

                width = rightX - topLeftX + 1;
                height = bottomY - topLeftY + 1;

                // now, rectangle is: (topLeftX, topLeftY, width, height)

                ::CHAR_INFO cell;
                cell.Char.UnicodeChar = (wchar_t)charValue;
                cell.Attributes = getColorCode(fgColor, bgColor);

                int buffIndexStart = screenMaxWidth * topLeftY + topLeftX;
                ::CHAR_INFO *pcharInfoStartLine = buffer + buffIndexStart;

                for (int y = 0; y < height; ++y)
                {
                    ::CHAR_INFO *pchar = pcharInfoStartLine;

                    for (int x = 0; x < width; ++x) {
                        *pchar = cell;
                        ++pchar;
                    }

                    pcharInfoStartLine += screenMaxWidth;
                }

#if defined (COBE_WIN32_OPTIMIZED_BUFFER)
                lastCoordTopLeft.X = topLeftX;
                lastCoordTopLeft.Y = topLeftY;
                lastCoordBottomRight.X = rightX;
                lastCoordBottomRight.Y = bottomY;
#endif
            }


            inline void print(int x, int y, char ch)
            {
#if defined COBE_SAFE_COORDINATE
                if (!cobe_expr_bound_x(x, manager->screenMaxWidth) || !cobe_expr_bound_y(y, manager->screenMaxHeight)) {
                    return;
                }
#endif
                ::CHAR_INFO *pcharInfo = buffer + manager->screenMaxWidth * y + x;
                pcharInfo->Char.UnicodeChar = ch;
                pcharInfo->Attributes = currentColor;

#if defined (COBE_WIN32_OPTIMIZED_BUFFER)
                lastCoordTopLeft.X = cobe_min(lastCoordTopLeft.X, x);
                lastCoordTopLeft.Y = cobe_min(lastCoordTopLeft.Y, y);
                lastCoordBottomRight.X = cobe_max(lastCoordBottomRight.X, x);
                lastCoordBottomRight.Y = cobe_max(lastCoordBottomRight.Y, y);
#endif // COBE_WIN32_OPTIMIZED_BUFFER
            }


            inline void print(int x, int y, char const *str)
            {
#if defined COBE_SAFE_COORDINATE
                if (!cobe_expr_bound_y(y, manager->screenMaxHeight)) {
                    return;
                }
#endif
                int xPosition = x;
                int strStartIndex, strEndIndex;
                char const *pchar, *pcharEndUpper;

                CobeDisplayHelper::calculatePrintIndex(str, x, xPosition, strStartIndex, strEndIndex, manager->screenMaxWidth);

                int buffIndexStart = manager->screenMaxWidth * y + xPosition;
                ::CHAR_INFO *pcharInfo = buffer + buffIndexStart;

#if defined COBE_SAFE_COORDINATE
                pchar = str + strStartIndex;
                pcharEndUpper = str + strEndIndex + 1;

                for (; pchar < pcharEndUpper; ++pchar, ++pcharInfo) {
                    pcharInfo->Char.UnicodeChar = *pchar;
                    pcharInfo->Attributes = currentColor;
                }
#else
                for (pchar = str; (*pchar); ++pchar, ++pcharInfo) {
                    pcharInfo->Char.UnicodeChar = *pchar;
                    pcharInfo->Attributes = currentColor;
                }
#endif // COBE_SAFE_COORDINATE

#if defined (COBE_WIN32_OPTIMIZED_BUFFER)
                lastCoordTopLeft.X = cobe_min(lastCoordTopLeft.X, xPosition);
                lastCoordTopLeft.Y = cobe_min(lastCoordTopLeft.Y, y);
                lastCoordBottomRight.X = cobe_max(lastCoordBottomRight.X, xPosition + (strEndIndex - strStartIndex));
                lastCoordBottomRight.Y = cobe_max(lastCoordBottomRight.Y, y);
#endif // COBE_WIN32_OPTIMIZED_BUFFER
            }


            inline void print(const CoShape &shape)
            {
                CobeDisplayHelper::printShape(this, shape);
            }


            inline void printLine(char chStroke, int x1, int y1, int x2, int y2)
            {
                CobeDisplayHelper::printLine(this, chStroke, x1, y1, x2, y2);
            }


            inline void gotoxy(int x, int y)
            {
                ::COORD coord = { (short)x, (short)y };
                ::SetConsoleCursorPosition(manager->hStdOut, coord);
            }

        private:
            inline void updateNormal()
            {
                ::SMALL_RECT writeRegion = pre_writeRegion;
                /*int ret = */::WriteConsoleOutput(manager->hStdOut, buffer, pre_dwBufferSize, pre_home, &writeRegion);
            }

#if defined COBE_WIN32_OPTIMIZED_BUFFER
            ::COORD lastCoordTopLeft;
            ::COORD lastCoordBottomRight;
            ::CHAR_INFO bufferOp[COBE_WIN32_MAX_CONSOLE_BUFFER_SIZE];


            inline void updateOptimized()
            {
                int xLeft = lastCoordTopLeft.X;
                int xRight = lastCoordBottomRight.X;
                int yTop = lastCoordTopLeft.Y;
                int yBottom = lastCoordBottomRight.Y;

                int updateDX = xRight - xLeft + 1;
                int updateDY = yBottom - yTop + 1;

                if (updateDX < 1 || updateDY < 1)
                    return; // no print, no update

                if (updateDY >= manager->screenMaxHeight / 2) {
                    // should update in normal way
                    updateNormal();
                }
                else {
                    ::CHAR_INFO *pwrite = bufferOp;
                    ::CHAR_INFO *porigin = buffer + yTop * manager->screenMaxWidth + xLeft;

                    ::COORD writeBufferSize = { (short)updateDX, (short)updateDY };
                    ::SMALL_RECT writeRegion;

                    writeRegion.Left = xLeft;
                    writeRegion.Top = yTop;
                    writeRegion.Right = xRight;
                    writeRegion.Bottom = yBottom;

                    for (int i = 0; i < updateDY; ++i)
                    {
                        std::memcpy(pwrite, porigin, updateDX * sizeof(::CHAR_INFO));
                        pwrite += updateDX;
                        porigin += manager->screenMaxWidth;
                    }

                    /*int ret = */::WriteConsoleOutput(manager->hStdOut, bufferOp, writeBufferSize, pre_home, &writeRegion);
                }

                // reset
                lastCoordTopLeft.X = lastCoordTopLeft.Y = 1000;
                lastCoordBottomRight.X = lastCoordBottomRight.Y = -1;
            }
#endif

        private:
            inline int getColorCode(int foreground, int background)
            {
                if (foreground == CoColor::DEFAULT)
                    foreground = defaultFgColor;

                if (background == CoColor::DEFAULT)
                    background = defaultBgColor;

                int value = (background << 4) + foreground;
                return value;
            }

            inline void setColor(int colorCode)
            {
                //::SetConsoleTextAttribute(manager->hStdOut, colorCode);
                currentColor = colorCode;
                currentBgColor = (colorCode >> 4);
                currentFgColor = (colorCode & 0xF);
            }
        };

#elif defined COBE_PLATFORM_LINUX
        class CobeDisplay
        {
        private:
            CobeManager *manager;
            int currentFgColor;
            int currentBgColor;

        public:
            inline CobeDisplay(CobeManager *owner) : manager(owner)
            {
            }


            inline void init()
            {
                currentFgColor = CoColor::DEFAULT;
                currentBgColor = CoColor::DEFAULT;
            }


            inline void update() {
                std::fflush(stdout);
            }


            inline void setForegroundColor(int color)
            {
                currentFgColor = color;
                updateColorToScreen();
            }

            inline void setBackgroundColor(int color)
            {
                currentBgColor = color;
                updateColorToScreen();
            }

            inline void resetColor()
            {
                std::fputs(cobe_esc_seq "0m", stdout);
            }


            inline void clearScreen()
            {
                std::fputs(cobe_esc_seq "H" cobe_esc_seq "J", stdout);
                //std::fputs(cobe_esc_seq "2J" cobe_esc_seq "1;1H", stdout);
                //std::system("clear");
            }


            inline void fillRect(int topLeftX, int topLeftY, int width, int height, int charValue = (int)' ', int fgColor = CoColor::DEFAULT, int bgColor = CoColor::DEFAULT)
            {
                int screenMaxWidth = manager->screenMaxWidth;
                int screenMaxHeight = manager->screenMaxHeight;

                if (width < 1 || height < 1 || topLeftX >= screenMaxWidth || topLeftY >= screenMaxHeight)
                    return;

                int rightX = topLeftX + width - 1;
                int bottomY = topLeftY + height - 1;
                CobeDisplayHelper::clampCoordinateX(topLeftX, screenMaxWidth);
                CobeDisplayHelper::clampCoordinateY(topLeftY, screenMaxHeight);
                CobeDisplayHelper::clampCoordinateX(rightX, screenMaxWidth);
                CobeDisplayHelper::clampCoordinateY(bottomY, screenMaxHeight);

                width = rightX - topLeftX + 1;
                height = bottomY - topLeftY + 1;

                // now, rectangle is: (topLeftX, topLeftY, width, height)

                char *str = (char*)std::calloc(width + 1, sizeof(char));
                std::memset(str, charValue, (size_t)width);

                updateCustomColorToScreen(fgColor, bgColor);

                for (int i = 0; i < height; ++i) {
                    gotoxy(topLeftX, topLeftY + i);
                    std::fputs(str, stdout);
                }

                updateColorToScreen();
                std::free(str);
                str = NULL;
            }


            inline void print(int x, int y, char ch)
            {
#if defined COBE_SAFE_COORDINATE
                if (!cobe_expr_bound_x(x, manager->screenMaxWidth) || !cobe_expr_bound_y(y, manager->screenMaxHeight)) {
                    return;
                }
#endif
                manager->gotoxy(x, y);
                std::fputc(ch, stdout);
            }


            inline void print(int x, int y, char const *str)
            {
#if !defined COBE_SAFE_COORDINATE
                manager->gotoxy(x, y);
                std::fputs(str, stdout);
#else
                if (! cobe_expr_bound_y(y, manager->screenMaxHeight) ) {
                    return;
                }

                int xPosition = x;
                int strStartIndex, strEndIndex;
                char const *pchar, *pcharEndUpper;

                CobeDisplayHelper::calculatePrintIndex(str, x, xPosition, strStartIndex, strEndIndex, manager->screenMaxWidth);

                pchar = str + strStartIndex;
                pcharEndUpper = str + strEndIndex + 1;

                manager->gotoxy(xPosition, y);

                for (; pchar < pcharEndUpper; ++pchar) {
                    std::fputc(*pchar, stdout);
                }
#endif
            }


            inline void print(const CoShape &shape)
            {
                CobeDisplayHelper::printShape(this, shape);
            }


            inline void printLine(char chStroke, int x1, int y1, int x2, int y2)
            {
                CobeDisplayHelper::printLine(this, chStroke, x1, y1, x2, y2);
            }


            inline void gotoxy(int x, int y)
            {
                x += COBE_SCREEN_BEGIN_OFFSET;
                y += COBE_SCREEN_BEGIN_OFFSET;
                std::printf(cobe_esc_seq "%d;%df", y, x);
            }

        private:
            inline void updateColorToScreen() const
            {
                char const *fgStr = cobe_const_listFgColors[currentFgColor];
                char const *bgStr = cobe_const_listBgColors[currentBgColor];
                std::fprintf(stdout, cobe_esc_seq "0;%s;%sm", bgStr, fgStr);
            }

            inline void updateCustomColorToScreen(int fgColor, int bgColor) const
            {
                char const *fgStr = cobe_const_listFgColors[fgColor];
                char const *bgStr = cobe_const_listBgColors[bgColor];
                std::fprintf(stdout, cobe_esc_seq "0;%s;%sm", bgStr, fgStr);
            }
        };

#endif


        class CobeInputReader
        {
        private:
            CobeManager *manager;
            CoMouseEvents lastMouseEvents;
            CoVect lastMousePosition;

#if defined COBE_PLATFORM_LINUX
            struct VirtualKeyInfo {
                char buffer[32];
                int numRead;
            };
            VirtualKeyInfo virtualKeyInfo;
#endif

        public:
            inline CobeInputReader(CobeManager *owner) : manager(owner), lastMousePosition(CoVect(-1, -1))
            {
            }


            inline int getKey(int keyCode)
            {
#if defined COBE_PLATFORM_WIN32

                return ::GetAsyncKeyState(keyCode);

#elif defined COBE_PLATFORM_LINUX

                if (virtualKeyInfo.numRead > 0) {
                    if (std::strchr(virtualKeyInfo.buffer, keyCode)) {
                        return 1;
                    }
                }

#endif
                return 0;
            }


            inline CoVect getLastMousePosition() {
                return lastMousePosition;
            }


            inline CoMouseEvents getLastMouseEvents()
            {
                return lastMouseEvents;
            }


            // if successfully, output result to record and return 1
            // if no record match, return 0
            inline int getLastMouseRecord(CoMouseRecord &record, CoMouseButton buttonType = COMOUSE_ALL)
            {
                if (lastMouseEvents.numEvents < 1) {
                    return 0;
                }

                if (buttonType == COMOUSE_ALL) {
                    record = lastMouseEvents.records[0];
                    return 1;
                }

                CoMouseRecord *p = lastMouseEvents.records;
                CoMouseRecord *pend = lastMouseEvents.records + lastMouseEvents.numEvents;

                for (; p < pend; ++p)
                    if (buttonType == p->button) {
                        record = *p;
                        return 1;
                    }

                return 0;
            }


            inline void flushBuffer()
            {
#if defined COBE_PLATFORM_WIN32
                ::FlushConsoleInputBuffer(manager->hStdIn);
#elif defined COBE_PLATFORM_LINUX
                char buffer[101] = { 0 };
                int byteRead = 0;
                
                while ((byteRead = ::read(STDIN_FILENO, buffer, 100)) > 0);
#endif
            }


            inline void update()
            {
#if defined COBE_PLATFORM_WIN32
                updateMouseEvents();
#elif defined COBE_PLATFORM_LINUX
                dispatchEvents();
#endif
            }

        private:
#if defined COBE_PLATFORM_LINUX
            char bufferInput[301];

            inline void dispatchEvents()
            {
                std::memset(bufferInput, 0, 301);

                std::memset(virtualKeyInfo.buffer, 0, 32);
                lastMouseEvents.numEvents = 0;

                int byteRead = ::read(STDIN_FILENO, bufferInput, 300);

                if (byteRead <= 0)
                    return;

#if defined COBE_LINUX_SUPPORT_MOUSE_EVENTS
                char *pbufferend = bufferInput + byteRead;
                char *pESC = std::strstr(bufferInput, cobe_esc_seq);

                while (pESC != NULL && pESC < pbufferend)
                {
                    char escape_sequence_header = pESC[2];
                    int escape_sequence_count_chars = 3;

                    if (escape_sequence_header >= 65 && escape_sequence_header <= 68) {
                        // arrow key, map to predefined key code
                        escape_sequence_count_chars = 2;

                        if (escape_sequence_header == 65)
                            pESC[2] = COKEY_UP;
                        else if (escape_sequence_header == 66)
                            pESC[2] = COKEY_DOWN;
                        else if (escape_sequence_header == 67)
                            pESC[2] = COKEY_RIGHT;
                        else
                            pESC[2] = COKEY_LEFT;
                    }
                    else if (escape_sequence_header == '<') {
                        // mouse
                        int byteParsed = 0;
                        int ret = processMouseEvent(pESC, byteParsed);

                        if (ret > 0)
                            escape_sequence_count_chars = byteParsed;
                    }

                    std::strcpy(pESC, pESC + escape_sequence_count_chars);
                    pESC = std::strstr(pESC, cobe_esc_seq);
                }

                reverseListMouseEvents();

#endif // COBE_LINUX_SUPPORT_MOUSE_EVENTS

                // now "buffer" is character buffer
                CoUtils::strupper(bufferInput);
                virtualKeyInfo.numRead = std::strlen(bufferInput);
                std::strcpy(virtualKeyInfo.buffer, bufferInput);
            }

            // return 0 on no input, return 1 on mouse up event, return 2 on mouse down event, return 3 on mouse move,
            // return 4 on full list of mouse down events
            inline int processMouseEvent(char *str, int &byteParsed)
            {
                byteParsed = 0;
                int buttonType = 0, x = 0, y = 0;

                int ret = std::sscanf(str, cobe_esc_seq "<%d;%d;%d%n", &buttonType, &x, &y, &byteParsed);
                if (ret < 3 || byteParsed < 8)
                    return 0;

                if (! (str[byteParsed] == 'm' || str[byteParsed] == 'M') )
                    return 0; // invalid

                ++byteParsed;

                if (str[byteParsed - 1] == 'm') // mouse up, ignore this event
                    return 1;

                if (lastMouseEvents.numEvents >= COBE_MAX_CAPTURE_MOUSE_EVENTS_COUNT)
                    return 4;

                if (buttonType == 35) {
                    // mouse move
                    lastMousePosition.x = x - COBE_SCREEN_BEGIN_OFFSET;
                    lastMousePosition.y = y - COBE_SCREEN_BEGIN_OFFSET;
                    return 3;
                }
                
                CoMouseRecord &record = lastMouseEvents.records[lastMouseEvents.numEvents];
                
                if (buttonType == 0)
                    record.button = COMOUSE_LEFT;
                else if (buttonType == 2)
                    record.button = COMOUSE_RIGHT;

                record.position.x = x - COBE_SCREEN_BEGIN_OFFSET;
                record.position.y = y - COBE_SCREEN_BEGIN_OFFSET;

                ++lastMouseEvents.numEvents;
                return 2;
            }

            inline void reverseListMouseEvents()
            {
                int n = lastMouseEvents.numEvents;

                for (int i = n / 2 - 1; i >= 0; --i)
                {
                    CoMouseRecord &a = lastMouseEvents.records[i];
                    CoMouseRecord &b = lastMouseEvents.records[n - 1 - i];
                    CoMouseRecord temp = a;
                    a = b;
                    b = temp;
                }
            }
#endif // COBE_PLATFORM_LINUX


#if defined COBE_PLATFORM_WIN32
            inline void updateMouseEvents()
            {
                lastMouseEvents.numEvents = 0;

                ::INPUT_RECORD records[50];
                ::INPUT_RECORD *precord = records;
                int numEventsRead = 0;

                ::PeekConsoleInput(manager->hStdIn, records, 50, (::LPDWORD)&numEventsRead);

                precord = records + numEventsRead - 1;

                int gotLastMousePosition = 0;

                for (int i = numEventsRead - 1; i >= 0; --i, --precord) {
                    if (precord->EventType == MOUSE_EVENT)
                    {
                        ::MOUSE_EVENT_RECORD &mer = precord->Event.MouseEvent;
                        DWORD &eventFlags = mer.dwEventFlags;

                        int mousePoxX = (int)mer.dwMousePosition.X;
                        int mousePoxY = (int)mer.dwMousePosition.Y;

                        if (gotLastMousePosition == 0 && (eventFlags == MOUSE_MOVED || eventFlags == 0 || DOUBLE_CLICK)) {
                            lastMousePosition.x = mousePoxX;
                            lastMousePosition.y = mousePoxY;
                            gotLastMousePosition = 1;
                        }

                        int condition1 = (eventFlags == 0);
                        int condition1a = (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED);
                        int condition1b = (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED);
                        int condition2 = (eventFlags == DOUBLE_CLICK);

                        if ((condition1 && (condition1a || condition1b)) || condition2) {
                            CoMouseRecord &record = lastMouseEvents.records[lastMouseEvents.numEvents];

                            if (condition1) {
                                if (condition1a)
                                    record.button = COMOUSE_LEFT;
                                else if (condition1b)
                                    record.button = COMOUSE_RIGHT;
                            }
                            else if (condition2) {
                                record.button = COMOUSE_DOUBLECLICK;
                            }

                            record.position.x = mousePoxX;
                            record.position.y = mousePoxY;
                            ++lastMouseEvents.numEvents;
                        }

                        if (lastMouseEvents.numEvents >= COBE_MAX_CAPTURE_MOUSE_EVENTS_COUNT)
                            break;
                    }
                }
            }
#endif // COBE_PLATFORM_WIN32
        };
        


        class CobeSoundPlayer
        {
        private:
            std::set<std::string> listSoundFileNames;

        public:
            // return 1 on success, return 0 on error
            inline int play(std::string fileName)
            {
                CoUtils::lowerstr(fileName);

                if (listSoundFileNames.find(fileName) != listSoundFileNames.end()) {
                    /*int ret = */this->stop(fileName);
                }

#if defined( COBE_PLATFORM_WIN32 ) && defined( COBE_WIN32_SUPPORT_SOUND )
                std::string strCommand = "play " + fileName;
                int ret = (int)::mciSendStringA(strCommand.c_str(), NULL, 0, NULL);

                if (ret != 0)
                    return 0;

                listSoundFileNames.insert(fileName);
                return 1;
#endif
                return 0;
            }

            // return 1 on success, return 0 on error
            inline int stop(std::string fileName)
            {
                CoUtils::lowerstr(fileName);

                if (listSoundFileNames.find(fileName) == listSoundFileNames.end())
                    return 0;

#if defined( COBE_PLATFORM_WIN32 ) && defined( COBE_WIN32_SUPPORT_SOUND )
                std::string strCommand = "stop " + fileName;

                int ret = (int)::mciSendStringA(strCommand.c_str(), NULL, 0, NULL);

                if (ret != 0)
                    return 0;

                listSoundFileNames.erase(fileName);
                return 1;
#endif
                return 0;
            }

            inline void stopAll()
            {
                for (std::set<std::string>::iterator it = listSoundFileNames.begin(); it != listSoundFileNames.end(); ++it)
                {
#if defined( COBE_PLATFORM_WIN32 ) && defined( COBE_WIN32_SUPPORT_SOUND )
                    const std::string &fileName = *it;

                    std::string strCommand = "stop " + fileName;
                    /*int ret = (int)*/::mciSendStringA(strCommand.c_str(), NULL, 0, NULL);
#endif
                }
            }
        };



    ///////////////////////////////////////////////////////
    //              BEGIN CLASS CobeManager              //
    ///////////////////////////////////////////////////////


    // singleton + constructor + destructor ---------------
    public:
        inline static CobeManager& getInstance(int with_init_conio_terminal_mode = 0, int cursorVisibility = 0) {
            static CobeManager instance;
            static int firstRun = 0;

            if (firstRun == 0 || with_init_conio_terminal_mode) {
                firstRun = 1;
                instance.init(cursorVisibility);
            }
            
            return instance;
        }
    
    private:
        inline CobeManager() : display(this), inputReader(this)
        {
        }

        inline CobeManager(CobeManager const &) : display(this), inputReader(this)
        {
        }

        inline ~CobeManager()
        {
            inputReader.flushBuffer();
            setConioTerminalMode(0);
            soundPlayer.stopAll(); 
        }

        inline void operator=(CobeManager const &) { }
    // end singleton --------------------------------------


    // FIELDS ---------------------------------------------
    private:
        CobeDisplay display;
        CobeInputReader inputReader;
        CobeSoundPlayer soundPlayer;

        int screenMaxWidth;
        int screenMaxHeight;

#if defined COBE_PLATFORM_WIN32
        ::HWND hWindow;
        ::HANDLE hStdIn;
        ::HANDLE hStdOut;
        ::DWORD fdwOldConsoleMode, fdwCurrentConsoleMode, fdwDisabledInputNewConsoleMode, fdwEnabledInputNewConsoleMode;
        int userManualInputMode;
#elif defined COBE_PLATFORM_LINUX
        struct ::termios termiosOldSettings, termiosNewSettings;
#endif
    // END FIELDS -----------------------------------------


    // METHODS --------------------------------------------
    private:
        inline void init(int cursorVisibility, int userManualInputMode = 1, int windowWidth = 0, int windowHeight = 0)
        {
#if defined COBE_PLATFORM_WIN32
            hStdIn = ::GetStdHandle(STD_INPUT_HANDLE);
            hStdOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
            hWindow = ::GetConsoleWindow(); // need #define _WIN32_WINNT 0x0500

            cobe_check_err(hStdIn == INVALID_HANDLE_VALUE, "Unable to get stdin handle");
            cobe_check_err(hStdOut == INVALID_HANDLE_VALUE, "Unable to get stdout handle");
            cobe_check_err(hWindow == NULL, "Unable to console handle");
#endif

            getScreenSizeAPI(screenMaxWidth, screenMaxHeight);

#if defined COBE_PLATFORM_WIN32

            this->userManualInputMode = userManualInputMode;

            ::SetWindowLong(hWindow, GWL_STYLE, ::GetWindowLong(hWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

            ::ULONG actualResolution;
            ZwSetTimerResolution(1, TRUE, &actualResolution); // for sleep function

            ::GetConsoleMode(hStdIn, &fdwOldConsoleMode);
            fdwDisabledInputNewConsoleMode = ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
            fdwEnabledInputNewConsoleMode = fdwDisabledInputNewConsoleMode | (ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_ECHO_INPUT);

            setUserManualInputMode(this->userManualInputMode);

#elif defined COBE_PLATFORM_LINUX

            ::tcgetattr(STDIN_FILENO, &termiosOldSettings);
            termiosNewSettings = termiosOldSettings;
            ::cfmakeraw(&termiosNewSettings);
            
#endif

            if (windowWidth > 0 && windowHeight > 0) {
                resizeScreen(windowWidth, windowHeight);
            }

            // init conio terminal mode
            setConioTerminalMode(1);

            // init components & data
            display.init();
            setCursor(cursorVisibility);
            display.clearScreen();
            update();

            // init random seed
            std::srand((unsigned int)std::time((std::time_t*)0));
        }


    public:
        inline int update()
        {
            display.update();
            inputReader.update();
            inputReader.flushBuffer();
            gotoxy(0, screenMaxHeight - 2);
            return 1;
        }


        // for client call...
        inline int updateDisplay()
        {
            display.update();
            return 1;
        }


        inline int updateAndSleep(int sleepMiliSeconds)
        {
            int ret = update();

            if (sleepMiliSeconds > 0)
                sleep(sleepMiliSeconds);

            return ret;
        }


        inline int updateAndSleepFPS(int fps)
        {
            static std::clock_t lastSleepTime = -1;
            double minSleepTime = 1.0 / fps * CLOCKS_PER_SEC;

            if (lastSleepTime == -1)
                lastSleepTime = clock();

            int ret = update();

            while ((clock() - lastSleepTime) < minSleepTime);

            lastSleepTime = clock();
            return ret;
        }


        inline void clearScreen()
        {
            display.clearScreen();
        }


        inline void fillRect(int topLeftX, int topLeftY, int width, int height, int charValue = (int)' ', int fgColor = CoColor::DEFAULT, int bgColor = CoColor::DEFAULT)
        {
            display.fillRect(topLeftX, topLeftY, width, height, charValue, fgColor, bgColor);
        }


        inline void print(int x, int y, char ch)
        {
            display.print(x, y, ch);
        }


        inline void printAndUpdate(int x, int y, char ch)
        {
            display.print(x, y, ch);
            display.update();
        }


        inline void print(int x, int y, char const *str)
        {
            display.print(x, y, str);
        }


        inline void printAndUpdate(int x, int y, char const *str)
        {
            display.print(x, y, str);
            display.update();
        }


        inline void printf(int x, int y, char const *format, ...)
        {
            char buffer[256];
            std::va_list args;
            va_start(args, format);
            std::vsnprintf(buffer, 255, format, args);
            va_end(args);
            this->print(x, y, buffer);
        }


        inline void printfAndUpdate(int x, int y, char const *format, ...)
        {
            char buffer[256];
            std::va_list args;
            va_start(args, format);
            std::vsnprintf(buffer, 255, format, args);
            va_end(args);

            this->print(x, y, buffer);
            display.update();
        }


        inline void print(const CoShape &shape)
        {
            display.print(shape);
        }


        inline void printAndUpdate(const CoShape &shape)
        {
            display.print(shape);
            display.update();
        }


        inline void printLine(char chStroke, int x1, int y1, int x2, int y2)
        {
            display.printLine(chStroke, x1, y1, x2, y2);
        }


        inline void printLineAndUpdate(char chStroke, int x1, int y1, int x2, int y2)
        {
            display.printLine(chStroke, x1, y1, x2, y2);
            display.update();
        }


        inline void setForegroundColor(int color)
        {
            if (cobe_check_invalid_color(color))
                return;

            display.setForegroundColor(color);
        }


        inline void setBackgroundColor(int color)
        {
            if (cobe_check_invalid_color(color))
                return;

            display.setBackgroundColor(color);
        }


        inline void resetColor()
        {
            display.resetColor();
        }


        inline void gotoxy(int x, int y)
        {
            display.gotoxy(x, y);
        }


        inline int getKey(int keyCode)
        {
            return inputReader.getKey(keyCode);
        }
        
        
        inline int scanf(char const *format, ...)
        {
#if defined COBE_PLATFORM_WIN32
            setUserManualInputMode(1);
#elif defined COBE_PLATFORM_LINUX
            setConioTerminalMode(0);
#endif
            int ret = 0;
            std::va_list args;
            va_start(args, format);
            ret = std::vscanf(format, args);
            va_end(args);
            
#if defined COBE_PLATFORM_WIN32
            setUserManualInputMode(this->userManualInputMode);
#elif defined COBE_PLATFORM_LINUX
            setConioTerminalMode(1);
#endif
            return ret;
        }


        inline CoVect getLastMousePosition() {
            return inputReader.getLastMousePosition();
        }


        inline int getLastMouseRecord(CoMouseRecord &record, CoMouseButton buttonType = COMOUSE_ALL)
        {
            return inputReader.getLastMouseRecord(record, buttonType);
        }


        inline CoMouseEvents getLastMouseEvents()
        {
            return inputReader.getLastMouseEvents();
        }


        inline void flushInputBuffer()
        {
            inputReader.flushBuffer();
        }


        inline void sleepMicro(int microSeconds)
        {
#if defined COBE_PLATFORM_WIN32

            ::LARGE_INTEGER interval;
            interval.QuadPart = -1 * (microSeconds * 10);
            NtDelayExecution(FALSE, &interval);

#elif defined COBE_PLATFORM_LINUX

            ::usleep(microSeconds);

#endif
        }


        inline void sleep(int miliSeconds)
        {
            sleepMicro(1000 * miliSeconds);
        }


        // pause the program until user presses key; default keyCode = ESC
        inline void pause(int keyCode = COKEY_ESC)
        {
            while (update())
            {
                if (getKey(keyCode))
                    break;
            }

            flushInputBuffer();
        }


        inline void getScreenSize(int &width, int &height)
        {
            width = this->screenMaxWidth;
            height = this->screenMaxHeight;
        }


        inline void resizeScreen(int width, int height)
        {
#if defined COBE_PLATFORM_WIN32

            if (width <= 0 || height <= 0)
                return;

            ::COORD largestSize = ::GetLargestConsoleWindowSize(this->hStdOut);
            cobe_check_err(width > largestSize.X, "The width dimension is too large");
            cobe_check_err(height > largestSize.Y, "The height dimension is too large");
            
            if (width < this->screenMaxWidth || height < this->screenMaxHeight) {
                // window size needs to be adjusted before the buffer size can be reduced
                ::SMALL_RECT info_before =
                {
                    0,
                    0,
                    width < this->screenMaxWidth ? (short)(width - 1) : (short)(this->screenMaxWidth - 1),
                    height < this->screenMaxHeight ? (short)(height - 1) : (short)(this->screenMaxHeight - 1)
                };

                if (!::SetConsoleWindowInfo(this->hStdOut, TRUE, &info_before))
                    cobe_err("Unable to resize window before resizing buffer");
            }
            
            ::COORD size = { (short)width, (short)height };
            if (! ::SetConsoleScreenBufferSize(this->hStdOut, size) )
                cobe_err("Unable to resize screen buffer, try changing width and height");

            ::SMALL_RECT info = { 0, 0, (short)(width - 1), (short)(height - 1) };
            if (! ::SetConsoleWindowInfo(this->hStdOut, TRUE, &info) )
                cobe_err("Unable to resize window after resizing buffer");

#elif defined COBE_PLATFORM_LINUX

            std::fprintf(stdout, cobe_esc_seq "8;%d;%dt", height, width);
            std::fflush(stdout);
            ::tcdrain(STDOUT_FILENO);
            this->sleepMicro(200000);

            int oldScreenMaxWidth = this->screenMaxWidth;
            int oldScreenMaxHeight = this->screenMaxHeight;
#endif

            this->getScreenSizeAPI(this->screenMaxWidth, this->screenMaxHeight);
            this->display.init();

#if defined COBE_PLATFORM_LINUX
            // check screen size is not updated ==> update manually
            if (this->screenMaxWidth == oldScreenMaxWidth && this->screenMaxHeight == oldScreenMaxHeight
                    && (width != oldScreenMaxWidth || height != oldScreenMaxHeight)) {
                this->screenMaxWidth = width;
                this->screenMaxHeight = height;
            }
#endif
        }


        inline void setCursor(int visible)
        {
#if defined COBE_PLATFORM_WIN32

            ::DWORD size = 20; // default cursor size
            ::CONSOLE_CURSOR_INFO lpCursor;
            lpCursor.bVisible = visible;
            lpCursor.dwSize = size;
            ::SetConsoleCursorInfo(hStdOut, &lpCursor);

#elif defined COBE_PLATFORM_LINUX

            if (visible == 1)
                std::fputs("\e[?25h", stdout);
            else if (visible == 0)
                std::fputs("\e[?25l", stdout);

#endif
        }


        // return 1 on success, return 0 on error
        inline int soundPlay(char const *fileName)
        {
#if defined( COBE_PLATFORM_WIN32 ) && defined( COBE_WIN32_SUPPORT_SOUND )
            int ret = soundPlayer.play(std::string(fileName));
            return ret;
#else
            cobe_display_error_win32_support_sound
#endif
            return 0;
        }

        // return 1 on success, return 0 on error
        inline int soundStop(char const *fileName)
        {
#if defined( COBE_PLATFORM_WIN32 ) && defined( COBE_WIN32_SUPPORT_SOUND )
            int ret = soundPlayer.stop(std::string(fileName));
            return ret;
#else
            cobe_display_error_win32_support_sound
#endif
            return 0;
        }

        inline void soundStopAll()
        {
#if defined( COBE_PLATFORM_WIN32 ) && defined( COBE_WIN32_SUPPORT_SOUND )
            soundPlayer.stopAll();
#else
            cobe_display_error_win32_support_sound
#endif
        }

    
    private:

        inline void getScreenSizeAPI(int &width, int &height)
        {
#if defined COBE_PLATFORM_WIN32

            ::CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
            if (! ::GetConsoleScreenBufferInfo(hStdOut, &csbiInfo) )
                cobe_err("Unable to retrieve screen buffer info");

            width = csbiInfo.srWindow.Right - csbiInfo.srWindow.Left + 1;
            height = csbiInfo.srWindow.Bottom - csbiInfo.srWindow.Top + 1;

#elif defined COBE_PLATFORM_LINUX

            struct ::winsize wsize;
            ::ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);
            width = wsize.ws_col;
            height = wsize.ws_row;

#endif

            cobe_check_err(width <= 0 || height <= 0, "Cannot get console terminal screen size");
        }


#if defined COBE_PLATFORM_WIN32

        inline void setConioTerminalMode(int enableMode)
        {
            if (enableMode) {
                ::SetConsoleMode(hStdIn, fdwCurrentConsoleMode);
            } else {
                ::SetConsoleMode(hStdIn, fdwOldConsoleMode);
            }
        }

        inline void setUserManualInputMode(int enableMode)
        {
            if (enableMode)
                fdwCurrentConsoleMode = fdwEnabledInputNewConsoleMode;
            else
                fdwCurrentConsoleMode = fdwDisabledInputNewConsoleMode;
            
            ::SetConsoleMode(hStdIn, fdwCurrentConsoleMode);
        }

#elif defined COBE_PLATFORM_LINUX

        inline void setConioTerminalMode(int enableMode)
        {
            if (enableMode) {
                ::tcsetattr(STDIN_FILENO, TCSANOW, &termiosNewSettings);
                setNonblockFlag(1);
#if defined COBE_LINUX_SUPPORT_MOUSE_EVENTS
                setMouseTracking(1);
#endif
            } else {
                ::tcsetattr(STDIN_FILENO, TCSANOW, &termiosOldSettings);
                setNonblockFlag(0);
#if defined COBE_LINUX_SUPPORT_MOUSE_EVENTS
                setMouseTracking(0);
#endif
            }
        }

        // return 1 on success, return 0 on error
        inline int setNonblockFlag(int nonBlock)
        {
            int flags = ::fcntl(STDIN_FILENO, F_GETFL);
            if (flags == -1)
                return 0;
            
            if (nonBlock)
                flags |= O_NONBLOCK;
            else
                flags &= ~O_NONBLOCK;
                
            if (::fcntl(STDIN_FILENO, F_SETFL, flags) == 0)
                return 1;

            return 0;
        }

        inline void setMouseTracking(int enableMode)
        {
            if (enableMode)
                ::write(STDOUT_FILENO, cobe_esc_seq "?1003;1006;1015h", 18);
	        else
                ::write(STDOUT_FILENO, cobe_esc_seq "?1003;1006;1015l", 18);
        }

#endif
    // END METHODS ----------------------------------------
    };
}








///////////////////////////////////////////////////////////
//              GLOBAL FUNCTION DEFINITIONS              //
///////////////////////////////////////////////////////////

namespace libcobe
{
    inline static CobeManager& initcobe(int cursorVisibility = 0)
    {
        return CobeManager::getInstance(1, cursorVisibility);
    }


    inline static int cobe_random(int minValue, int maxValue)
    {
        return CoUtils::random(minValue, maxValue);
    }
}


#endif // _COBE_HEADER_INCLUDED_
