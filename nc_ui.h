#if !defined(__NC_UI_H__)
#define __NC_UI_H__

// @defines____________________________________________________________________
#if !defined(NCUI_DEF)
    #if defined(NCUI_STATIC)
        #define NCUI_DEF static
    #else
        #define NCUI_DEF extern
    #endif
#endif

#if !defined(NCUI_ATTR)
    #define NCUI_ATTR
#endif

#if !defined(NCUI_NO_STDLIB)
    #include <stdint.h>

    typedef uint8_t  u8;
    typedef uint16_t u16;
    typedef uint32_t u32;
    typedef uint64_t u64;
    typedef int8_t   i8;
    typedef int16_t  i16;
    typedef int32_t  i32;
    typedef int64_t  i64;
    typedef uint32_t b32;
    typedef uint8_t  b8;
    typedef float    f32;
    typedef double   f64;
#else
    typedef unsigned char      u8;
    typedef unsigned short     u16;
    typedef unsigned int       u32;
    typedef unsigned long long u64;
    typedef signed char        i8;
    typedef signed short       i16;
    typedef signed int         i32;
    typedef signed long long   i64;
    typedef u32                b32;
    typedef u8                 b8;
    typedef float              f32;
    typedef double             f64;
#endif

#if !defined(NCUI_MEMSET)
    #if !defined(NCUI_NO_STDLIB)
        #include <string.h>

        #define NCUI_MEMSET(X, Y, Z) memset(X, Y, Z)
    #else
        // TODO(nathan): at least iterate over more than a byte at a time
        static inline void*
        MemSet(void* _Dst, u8 Value, u32 Count)
        {
            u8* Dst = (u8*) _Dst;
        
            while (Count--)
                *Dst++ = Value;

            return _Dst;
        }

        #define NCUI_MEMSET(X, Y, Z) MemSet(X, Y, Z)
    #endif
#endif

#if !defined(NCUI_MAX)
    #define NCUI_MAX(A, B) (((A) > (B)) ? (A) : (B))
#endif

#if !defined(NCUI_MIN)
    #define NCUI_MIN(A, B) (((A) < (B)) ? (A) : (B))
#endif

#if !defined(NCUI_SWAP)
    #define NCUI_SWAP(T, A, B) do { T _Tmp = (A); (A) = (B); (B) = _Tmp; } while (FALSE)
#endif

#if !defined(NCUI_CLAMP_TOP)
    #define NCUI_CLAMP_TOP(X, Y) NCUI_MIN(X, Y)
#endif

#if !defined(NCUI_DEFER)
    #define NCUI_DEFER(X, Y) for (u32 __I = ((X), 0); !__I; ++__I, (Y))
#endif

#if !defined(FALSE)
    #define FALSE 0
#endif

#if !defined(TRUE)
    #define TRUE 1
#endif

#if !defined(NULL)
    #define NULL 0
#endif

typedef i8 SideKind;
enum { 
    SIDE_INVALID = -1, 
    SIDE_MIN, 
    SIDE_MAX, 
    SIDE_COUNT 
};

#define FLIP_SIDE(X) ((SideKind) (!(X)))

typedef i8 Axis2D;
enum { 
    AXIS_2D_INVALID = -1, 
    AXIS_2D_X, 
    AXIS_2D_Y, 
    AXIS_2D_COUNT 
};

#define FLIP_AXIS(X) ((Axis2D) (!(X)))

// NOTE: Override these limits to suit your specific project needs
#if !defined(NCUI_MAX_BOXES)
    #define NCUI_MAX_BOXES 32
#endif

#if !defined(NCUI_MAX_EVENTS)
    #define NCUI_MAX_EVENTS 8
#endif

#if !defined(NCUI_BOX_HASH_SLOTS)
    #define NCUI_BOX_HASH_SLOTS 16
#endif

#if !defined(NCUI_STALE_FRAMES)
    #define NCUI_STALE_FRAMES 2
#endif

#if !defined(NCUI_MAX_STACK_DEPTH)
    #define NCUI_MAX_STACK_DEPTH 8
#endif

#if !defined(NCUI_MAX_ANIMATIONS)
    #define NCUI_MAX_ANIMATIONS 32
#endif

#if !defined(NCUI_ANIMATION_HASH_SLOTS)
    #define NCUI_ANIMATION_HASH_SLOTS 16
#endif

#define NCUI_FONT_GLYPH_WIDTH   5
#define NCUI_FONT_GLYPH_HEIGHT  7
#define NCUI_FONT_ADVANCE       6
#define NCUI_FONT_LINE_HEIGHT   8
#define NCUI_FONT_FIRST_CHAR   32
#define NCUI_FONT_LAST_CHAR   126
#define NCUI_FONT_MAX_COLS     14
#define NCUI_FONT_GLYPH_COUNT  (NCUI_FONT_LAST_CHAR - NCUI_FONT_FIRST_CHAR + 1)

// NOTE: Controls UIBox behavior, layout, and rendering
typedef u16 UIBoxFlags;
enum {
    UI_BOX_FLAG_CLICKABLE    = (1 <<  0),
    UI_BOX_FLAG_DISABLED     = (1 <<  1),
    UI_BOX_FLAG_DRAW_TEXT    = (1 <<  2),
    UI_BOX_FLAG_DRAW_BORDER  = (1 <<  3),
    UI_BOX_FLAG_DRAW_FILL    = (1 <<  4),
    UI_BOX_FLAG_INVERTED     = (1 <<  5),
    UI_BOX_FLAG_FIXED_WIDTH  = (1 <<  6),
    UI_BOX_FLAG_FIXED_HEIGHT = (1 <<  7),
    UI_BOX_FLAG_CLIP         = (1 <<  8),
    UI_BOX_FLAG_FLOATING     = (1 <<  9),
    UI_BOX_FLAG_NAV_SKIP     = (1 << 10),
    UI_BOX_FLAG_DRAW_DIVIDER = (1 << 11)
    
    // NOTE: add more variants here if needed
};

// NOTE: UIBox interaction kinds
typedef u8 UISignalKind;
enum {
    UI_SIGNAL_PRESSED  = (1 << 0),
    UI_SIGNAL_RELEASED = (1 << 1),
    UI_SIGNAL_CLICKED  = (1 << 2),
    UI_SIGNAL_HELD     = (1 << 3),
    UI_SIGNAL_HOT      = (1 << 4),
    UI_SIGNAL_ACTIVE   = (1 << 5)
};

#define UI_PRESSED(S)  (!!((S).Kind & UI_SIGNAL_PRESSED))
#define UI_RELEASED(S) (!!((S).Kind & UI_SIGNAL_RELEASED))
#define UI_CLICKED(S)  (!!((S).Kind & UI_SIGNAL_CLICKED))
#define UI_HELD(S)     (!!((S).Kind & UI_SIGNAL_HELD))
#define UI_HOT(S)      (!!((S).Kind & UI_SIGNAL_HOT))
#define UI_ACTIVE(S)   (!!((S).Kind & UI_SIGNAL_ACTIVE))

// NOTE: Represent types of user input to a single UIBox
// WARN: If expanding these, be mindful of current u8 constraint
typedef u8 UIInputKind;
enum { 
    UI_INPUT_NONE, 
    UI_INPUT_UP, 
    UI_INPUT_DOWN, 
    UI_INPUT_LEFT, 
    UI_INPUT_RIGHT, 
    UI_INPUT_SELECT, 
    UI_INPUT_BACK, 
    UI_INPUT_COUNT 
};

// NOTE: Represent kinds of events that will be propagated and can be handled
// WARN: If expanding these, be mindful of current u8 constraint
typedef u8 UIEventKind;
enum { 
    UI_EVENT_NONE, 
    UI_EVENT_PRESS, 
    UI_EVENT_RELEASE, 
    UI_EVENT_COUNT 
};

typedef u8 UITextAlign;
enum { 
    UI_TEXT_ALIGN_LEFT, 
    UI_TEXT_ALIGN_CENTRE, 
    UI_TEXT_ALIGN_RIGHT, 
    UI_TEXT_ALIGN_COUNT 
};

typedef u8 UISizeKind;
enum { 
    UI_SIZE_KIND_NULL,
    UI_SIZE_KIND_PIXELS,                                                        // NOTE: static pixel sizing
    UI_SIZE_KIND_TEXT_CONTENT,                                                  // NOTE: size box to fit text content
    UI_SIZE_KIND_PERCENT_OF_PARENT,                                             // NOTE: size box to fill % of parent
    UI_SIZE_KIND_SUM_OF_CHILDREN                                                // NOTE: size box to fit all children
};

#define UI_PX(X)      (UISize){ (f32) (X), UI_SIZE_KIND_PIXELS }
#define UI_TEXT()     (UISize){ 0.0f, UI_SIZE_KIND_TEXT_CONTENT }
#define UI_PCT(X)     (UISize){ (f32) (X), UI_SIZE_KIND_PERCENT_OF_PARENT }
#define UI_CHILDREN() (UISize){ 0.0f, UI_SIZE_KIND_SUM_OF_CHILDREN }

#define UI_BUILD_SCOPE(S)       NCUI_DEFER(UIBeginBuild(S), UIEndBuild(S))
#define UIPreferedWidth(S, X)   NCUI_DEFER(UIPushPreferredWidth(S, X), UIPopPreferredWidth(S))
#define UIPreferedHeight(S, X)  NCUI_DEFER(UIPushPreferredHeight(S, X), UIPopPreferredHeight(S))
#define UIChildLayoutAxis(S, X) NCUI_DEFER(UIPushChildLayoutAxis(S, X), UIPopChildLayoutAxis(S))
#define UIParent(S, X)          NCUI_DEFER(UIPushParent(S, X), UIPopParent(S))

#define UIRectIsValid(X) (((X).X0 <= (X).X1) && ((X).Y0 <= (X).Y1))

// @types______________________________________________________________________
struct UIKey { 
    u32 V; 
};

// NOTE: Represents queued input event
struct UIEvent { 
    UIEventKind Kind; 
    UIInputKind Input; 
};

// NOTE: Result of building a UIBox, stores its current interaction state
struct UISignal { 
    UISignalKind Kind; 
};

// WARN: These co-ordinates are constrained to unsigned 8 bit limits.
//     : change these if you wish to use a larger display
struct UIRect { 
    u8 X0; 
    u8 Y0; 
    u8 X1; 
    u8 Y1; 
};

struct UISize { 
    f32        Value; 
    UISizeKind Kind; 
};

// NOTE: Retained node representing a square area in the UI tree
struct UIBox {
    char const* String;
    UISize      PreferredSize[AXIS_2D_COUNT];
    UIKey       Key;
    UIRect      Rect;
    UIRect      ClipRect;
    u16         HeadBuildIndex;
    u16         TailBuildIndex;
    UIBoxFlags  Flags;
    u8          FixedSize[AXIS_2D_COUNT];
    u8          FixedPosition[AXIS_2D_COUNT];
    u8          StringLength;
    u8          HashNext;
    u8          HashPrev;
    u8          Parent;
    u8          Head;
    u8          Tail;
    u8          Next;
    u8          Prev;
    UITextAlign TextAlign;
    u8          IsHot;
    u8          IsActive;
    Axis2D      ChildLayoutAxis;
};

struct UIHashSlot { 
    u8 Head; 
    u8 Tail; 
};

struct UIAnimationNode { 
    UIKey Key; 
    u16   LastTouchedBuildIndex; 
    u8    Current; 
    u8    HashNext; 
    u8    HashPrev; 
};

// NOTE: Holds current library state:
//     :  - UIBox tree
//     :  - Events
//     :  - Layout stacks
//     :  - Display dimensions
struct UIState {
    UIBox           Boxes[NCUI_MAX_BOXES];
    UIEvent         Events[NCUI_MAX_EVENTS];
    UIAnimationNode AnimationNodes[NCUI_MAX_ANIMATIONS];
    UIHashSlot      HashSlots[NCUI_BOX_HASH_SLOTS];
    UIHashSlot      AnimationHashSlots[NCUI_ANIMATION_HASH_SLOTS];
    UISize          PreferredWidthStack[NCUI_MAX_STACK_DEPTH];
    UISize          PreferredHeightStack[NCUI_MAX_STACK_DEPTH];
    UIKey           HotKey;
    UIKey           ActiveKey;
    u16             Width;
    u16             Height;
    u16             Banks;
    u16             BufferSize;
    u16             BuildIndex;
    u8              ParentStack[NCUI_MAX_STACK_DEPTH];
    Axis2D          ChildLayoutAxisStack[NCUI_MAX_STACK_DEPTH];
    u8              BoxesCount;
    u8              HeadFreeBox;
    u8              ParentStackDepth;
    u8              PreferredWidthStackDepth;
    u8              PreferredHeightStackDepth;
    u8              ChildLayoutAxisStackDepth;
    u8              EventsCount;
    u8              HeadEvent;
    u8              TailEvent;
    u8              HeadFreeAnimation;
    u8              AnimationCount;
};

// @runtime____________________________________________________________________
#define EMPTY_UI_INDEX_VALUE 0xFF

constexpr UIKey EMPTY_UI_KEY_VALUE = {};

static inline b32 
operator==(UIKey KeyA, UIKey KeyB) 
{ 
    return KeyA.V == KeyB.V; 
}

static inline b32 
operator!=(UIKey KeyA, UIKey KeyB) 
{ 
    return !(KeyA == KeyB); 
}

static inline UIRect 
UIRectAlloc(u8 X0, u8 Y0, u8 X1, u8 Y1) 
{
    UIRect Result = { 
        X0, 
        Y0, 
        X1, 
        Y1 
    };

    return Result;
}

static inline UIRect 
UIRectBank(u8 X0, u8 Bank0, u8 X1, u8 Bank1) 
{
    return UIRectAlloc(
        X0, 
        (u8) (Bank0 * 8), 
        X1,
        (u8) (Bank1 * 8 - 1)
    );
}

// @functions__________________________________________________________________
NCUI_DEF UIKey UIKeyFromStr(UIKey Seed, char const* String, u8 StringLength);
NCUI_DEF UIKey UIKeyFromStr(char const* String);

// NOTE: Initialises the given UIState for given display dimensions
NCUI_DEF void UIInit(UIState* State, u16 Width, u16 Height);

// NOTE: Begin a UI declaration scope. Resets layout stacks in UIState
NCUI_DEF void UIBeginBuild(UIState* State);

// NOTE: End a UI declaration scope. Processes events, computes layout, and
//     : garbage-collect stale boxes
NCUI_DEF void UIEndBuild(UIState* State);

// NOTE: Queue an input event to be processed in UIEndBuild
NCUI_DEF void UIPushEvent(UIState* State, UIEventKind Kind, UIInputKind Input);
NCUI_DEF void UIPopEvent(UIState* State, u8 Index);

NCUI_DEF UIBox* UIBoxFromKey(UIState* State, UIKey Key);

// NOTE: Allocate and insert a box into the current parent and return its
//     : current interaction state
NCUI_DEF UISignal UIBuildBox(UIState* State, UIBoxFlags Flags, UIKey Key);
NCUI_DEF UISignal UIBuildBoxFromStr(UIState* State, UIBoxFlags Flags, char const* String);

// NOTE: Manage parent stack for UI hierarchy
NCUI_DEF void UIPushParent(UIState* State, UIBox* Box);
NCUI_DEF void UIPopParent(UIState* State);
NCUI_DEF UIBox* UIHeadParent(UIState* State);

// NOTE: Framerate independent interpolation keyed by given UIKey
NCUI_DEF u8 UIAnimate(UIState* State, UIKey Key, u8 Target, u8 Initial, u8 RateShift);

// NOTE: Manage layout property stack
NCUI_DEF void UIPushPreferredWidth(UIState* State, UISize Size);
NCUI_DEF void UIPopPreferredWidth(UIState* State);
NCUI_DEF void UIPushPreferredHeight(UIState* State, UISize Size);
NCUI_DEF void UIPopPreferredHeight(UIState* State);
NCUI_DEF void UIPushChildLayoutAxis(UIState* State, Axis2D Axis);
NCUI_DEF void UIPopChildLayoutAxis(UIState* State);

// NOTE: Some high-level UI components
NCUI_DEF UISignal UILabel(UIState* State, char const* String);
NCUI_DEF UISignal UIButton(UIState* State, char const* String);
NCUI_DEF UISignal UICheckBox(UIState* State, char const* String, b32* Value);
NCUI_DEF UISignal UIMenuEntry(UIState* State, char const* String, b32 IsSelected);
NCUI_DEF UISignal UIDivider(UIState* State, char const* String);
NCUI_DEF UISignal UIProgressBar(UIState* State, char const* String, u8 ProgressPCT);
NCUI_DEF UISignal UISlider(UIState* State, char const* String, u8* ValuePCT, u8 Step);

// NOTE: Render computed box tree to given Buffer
NCUI_DEF void DrawUI(UIState* State, u8* Buffer);

// NOTE: Draw directly to Buffer, independent of box tree
NCUI_DEF void DrawStr(UIState* State, u8* Buffer, u8 X, u8 Y, char const* String);
NCUI_DEF void DrawStrInverted(UIState* State, u8* Buffer, u8 X, u8 Y, char const* String);
NCUI_DEF void DrawStrClipped(UIState* State, u8* Buffer, u8 X, u8 Y, char const* String, UIRect Clip);
NCUI_DEF void DrawStrInvertedClipped(UIState* State, u8* Buffer, u8 X, u8 Y, char const* String, UIRect Clip);
NCUI_DEF void DrawStrAligned(UIState* State, u8* Buffer, u8 X0, u8 X1, u8 Y, char const* String, u8 Align);
NCUI_DEF void DrawPixelSet(UIState* State, u8* Buffer, u8 X, u8 Y);
NCUI_DEF void DrawPixelClear(UIState* State, u8* Buffer, u8 X, u8 Y);
NCUI_DEF void DrawPixelToggle(UIState* State, u8* Buffer, u8 X, u8 Y);
NCUI_DEF void DrawFilledRect(UIState* State, u8* Buffer, u8 X0, u8 Y0, u8 X1, u8 Y1);
NCUI_DEF void DrawChar(UIState* State, u8* Buffer, u8 X, u8 Y, char Char);
NCUI_DEF void DrawCharClipped(UIState* State, u8* Buffer, u8 X, u8 Y, char Char, UIRect Clip);
NCUI_DEF void DrawCharInverted(UIState* State, u8* Buffer, u8 X, u8 Y, char Char);
NCUI_DEF void DrawCharInvertedClipped(UIState* State, u8* Buffer, u8 X, u8 Y, char Char, UIRect Clip);
NCUI_DEF void ClearDisplay(UIState* State, u8* Buffer);
NCUI_DEF void FillDisplay(UIState* State, u8* Buffer);
NCUI_DEF void DrawHorzLine(UIState* State, u8* Buffer, u8 X0, u8 X1, u8 Y);
NCUI_DEF void ClearHorzLine(UIState* State, u8* Buffer, u8 X0, u8 X1, u8 Y);
NCUI_DEF void DrawVertLine(UIState* State, u8* Buffer, u8 X, u8 Y0, u8 Y1);
NCUI_DEF void ClearVertLine(UIState* State, u8* Buffer, u8 X, u8 Y0, u8 Y1);
NCUI_DEF void DrawLine(UIState* State, u8* Buffer, u8 X0, u8 Y0, u8 X1, u8 Y1);
NCUI_DEF void ClearLine(UIState* State, u8* Buffer, u8 X0, u8 Y0, u8 X1, u8 Y1);
NCUI_DEF void DrawClearRect(UIState* State, u8* Buffer, u8 X0, u8 Y0, u8 X1, u8 Y1);
NCUI_DEF void DrawInvertRect(UIState* State, u8* Buffer, u8 X0, u8 Y0, u8 X1, u8 Y1);
NCUI_DEF void DrawBorderRect(UIState* State, u8* Buffer, u8 X0, u8 Y0, u8 X1, u8 Y1);
NCUI_DEF void DrawBMP(UIState* State, u8* Buffer, u8 X, u8 Y, u8 Width, u8 Height, u8 const* Data);

#endif // __NC_UI_H__

#if defined(NCUI_IMPLEMENTATION)

// NOTE: 5 * 7 font data, each byte represents a vertical column of 8 pixels.
//     : bottom bit of each byte is unused (as the font is only 7 pixels tall)
static const u8 FONT_BYTES[NCUI_FONT_GLYPH_COUNT][NCUI_FONT_GLYPH_WIDTH] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00 },                                           // ' '
    { 0x00, 0x00, 0x5F, 0x00, 0x00 },                                           // '!'
    { 0x00, 0x07, 0x00, 0x07, 0x00 },                                           // '"'
    { 0x14, 0x7F, 0x14, 0x7F, 0x14 },                                           // '#'
    { 0x24, 0x2A, 0x7F, 0x2A, 0x12 },                                           // '$'
    { 0x23, 0x13, 0x08, 0x64, 0x62 },                                           // '%'
    { 0x36, 0x49, 0x55, 0x22, 0x50 },                                           // '&'
    { 0x00, 0x05, 0x03, 0x00, 0x00 },                                           // '''
    { 0x00, 0x1C, 0x22, 0x41, 0x00 },                                           // '('
    { 0x00, 0x41, 0x22, 0x1C, 0x00 },                                           // ')'
    { 0x08, 0x2A, 0x1C, 0x2A, 0x08 },                                           // '*'
    { 0x08, 0x08, 0x3E, 0x08, 0x08 },                                           // '+'
    { 0x00, 0x50, 0x30, 0x00, 0x00 },                                           // ','
    { 0x08, 0x08, 0x08, 0x08, 0x08 },                                           // '-'
    { 0x00, 0x60, 0x60, 0x00, 0x00 },                                           // '.'
    { 0x20, 0x10, 0x08, 0x04, 0x02 },                                           // '/'
    { 0x3E, 0x51, 0x49, 0x45, 0x3E },                                           // '0'
    { 0x00, 0x42, 0x7F, 0x40, 0x00 },                                           // '1'
    { 0x42, 0x61, 0x51, 0x49, 0x46 },                                           // '2'
    { 0x21, 0x41, 0x45, 0x4B, 0x31 },                                           // '3'
    { 0x18, 0x14, 0x12, 0x7F, 0x10 },                                           // '4'
    { 0x27, 0x45, 0x45, 0x45, 0x39 },                                           // '5'
    { 0x3C, 0x4A, 0x49, 0x49, 0x30 },                                           // '6'
    { 0x01, 0x71, 0x09, 0x05, 0x03 },                                           // '7'
    { 0x36, 0x49, 0x49, 0x49, 0x36 },                                           // '8'
    { 0x06, 0x49, 0x49, 0x29, 0x1E },                                           // '9'
    { 0x00, 0x36, 0x36, 0x00, 0x00 },                                           // ':'
    { 0x00, 0x56, 0x36, 0x00, 0x00 },                                           // ';'
    { 0x00, 0x08, 0x14, 0x22, 0x41 },                                           // '<'
    { 0x14, 0x14, 0x14, 0x14, 0x14 },                                           // '='
    { 0x41, 0x22, 0x14, 0x08, 0x00 },                                           // '>'
    { 0x02, 0x01, 0x51, 0x09, 0x06 },                                           // '?'
    { 0x32, 0x49, 0x79, 0x41, 0x3E },                                           // '@'
    { 0x7E, 0x11, 0x11, 0x11, 0x7E },                                           // 'A'
    { 0x7F, 0x49, 0x49, 0x49, 0x36 },                                           // 'B'
    { 0x3E, 0x41, 0x41, 0x41, 0x22 },                                           // 'C'
    { 0x7F, 0x41, 0x41, 0x22, 0x1C },                                           // 'D'
    { 0x7F, 0x49, 0x49, 0x49, 0x41 },                                           // 'E'
    { 0x7F, 0x09, 0x09, 0x01, 0x01 },                                           // 'F'
    { 0x3E, 0x41, 0x41, 0x51, 0x32 },                                           // 'G'
    { 0x7F, 0x08, 0x08, 0x08, 0x7F },                                           // 'H'
    { 0x00, 0x41, 0x7F, 0x41, 0x00 },                                           // 'I'
    { 0x20, 0x40, 0x41, 0x3F, 0x01 },                                           // 'J'
    { 0x7F, 0x08, 0x14, 0x22, 0x41 },                                           // 'K'
    { 0x7F, 0x40, 0x40, 0x40, 0x40 },                                           // 'L'
    { 0x7F, 0x02, 0x04, 0x02, 0x7F },                                           // 'M'
    { 0x7F, 0x04, 0x08, 0x10, 0x7F },                                           // 'N'
    { 0x3E, 0x41, 0x41, 0x41, 0x3E },                                           // 'O'
    { 0x7F, 0x09, 0x09, 0x09, 0x06 },                                           // 'P'
    { 0x3E, 0x41, 0x51, 0x21, 0x5E },                                           // 'Q'
    { 0x7F, 0x09, 0x19, 0x29, 0x46 },                                           // 'R'
    { 0x46, 0x49, 0x49, 0x49, 0x31 },                                           // 'S'
    { 0x01, 0x01, 0x7F, 0x01, 0x01 },                                           // 'T'
    { 0x3F, 0x40, 0x40, 0x40, 0x3F },                                           // 'U'
    { 0x1F, 0x20, 0x40, 0x20, 0x1F },                                           // 'V'
    { 0x7F, 0x20, 0x18, 0x20, 0x7F },                                           // 'W'
    { 0x63, 0x14, 0x08, 0x14, 0x63 },                                           // 'X'
    { 0x03, 0x04, 0x78, 0x04, 0x03 },                                           // 'Y'
    { 0x61, 0x51, 0x49, 0x45, 0x43 },                                           // 'Z'
    { 0x00, 0x00, 0x7F, 0x41, 0x41 },                                           // '['
    { 0x02, 0x04, 0x08, 0x10, 0x20 },                                           // '\'
    { 0x41, 0x41, 0x7F, 0x00, 0x00 },                                           // ']'
    { 0x04, 0x02, 0x01, 0x02, 0x04 },                                           // '^'
    { 0x40, 0x40, 0x40, 0x40, 0x40 },                                           // '_'
    { 0x00, 0x01, 0x02, 0x04, 0x00 },                                           // '`'
    { 0x20, 0x54, 0x54, 0x54, 0x78 },                                           // 'a'
    { 0x7F, 0x48, 0x44, 0x44, 0x38 },                                           // 'b'
    { 0x38, 0x44, 0x44, 0x44, 0x20 },                                           // 'c'
    { 0x38, 0x44, 0x44, 0x48, 0x7F },                                           // 'd'
    { 0x38, 0x54, 0x54, 0x54, 0x18 },                                           // 'e'
    { 0x08, 0x7E, 0x09, 0x01, 0x02 },                                           // 'f'
    { 0x08, 0x14, 0x54, 0x54, 0x3C },                                           // 'g'
    { 0x7F, 0x08, 0x04, 0x04, 0x78 },                                           // 'h'
    { 0x00, 0x44, 0x7D, 0x40, 0x00 },                                           // 'i'
    { 0x20, 0x40, 0x44, 0x3D, 0x00 },                                           // 'j'
    { 0x00, 0x7F, 0x10, 0x28, 0x44 },                                           // 'k'
    { 0x00, 0x41, 0x7F, 0x40, 0x00 },                                           // 'l'
    { 0x7C, 0x04, 0x18, 0x04, 0x78 },                                           // 'm'
    { 0x7C, 0x08, 0x04, 0x04, 0x78 },                                           // 'n'
    { 0x38, 0x44, 0x44, 0x44, 0x38 },                                           // 'o'
    { 0x7C, 0x14, 0x14, 0x14, 0x08 },                                           // 'p'
    { 0x08, 0x14, 0x14, 0x18, 0x7C },                                           // 'q'
    { 0x7C, 0x08, 0x04, 0x04, 0x08 },                                           // 'r'
    { 0x48, 0x54, 0x54, 0x54, 0x20 },                                           // 's'
    { 0x04, 0x3F, 0x44, 0x40, 0x20 },                                           // 't'
    { 0x3C, 0x40, 0x40, 0x20, 0x7C },                                           // 'u'
    { 0x1C, 0x20, 0x40, 0x20, 0x1C },                                           // 'v'
    { 0x3C, 0x40, 0x30, 0x40, 0x3C },                                           // 'w'
    { 0x44, 0x28, 0x10, 0x28, 0x44 },                                           // 'x'
    { 0x0C, 0x50, 0x50, 0x50, 0x3C },                                           // 'y'
    { 0x44, 0x64, 0x54, 0x4C, 0x44 },                                           // 'z'
    { 0x00, 0x08, 0x36, 0x41, 0x00 },                                           // '{'
    { 0x00, 0x00, 0x7F, 0x00, 0x00 },                                           // '|'
    { 0x00, 0x41, 0x36, 0x08, 0x00 },                                           // '}'
    { 0x08, 0x04, 0x08, 0x10, 0x08 }                                            // '~'
};

static u8 
FontStrLen(char const* String) 
{
    u16 Result = 0;

    if (!String)
        return Result;

    char const* StringPtr = String;

    for ( ; *StringPtr; ++StringPtr);

    Result = (u16) (StringPtr - String);

    return NCUI_CLAMP_TOP(Result, 0xFF);
}

static u8 
FontStrWidth(char const* String) 
{
    u8 StringLength = FontStrLen(String);

    return StringLength 
        ? (u8) (StringLength * NCUI_FONT_ADVANCE - 1) 
        : 0;
}

// NOTE: FNV-1A hashing strategy
//     : See https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
static u32
Hash(u32 Seed, char const* String, u8 StringLength) 
{
    u32 Result = 2166136261U ^ Seed;

    if (!String)
        return Result;

    for (u8 Index = 0; Index < StringLength; ++Index) {
        Result ^= (u32) String[Index];
        Result *= 16777619U;
    }

    return Result;
}

static UIRect 
UIRectIntersect(UIRect RectA, UIRect RectB) 
{
    UIRect Result = {
        NCUI_MAX(RectA.X0, RectB.X0),
        NCUI_MAX(RectA.Y0, RectB.Y0),
        NCUI_MIN(RectA.X1, RectB.X1),
        NCUI_MIN(RectA.Y1, RectB.Y1)
    };

    return Result;
}

// NOTE: Given a UIState and a UIKey, allocate a UIBox into the UI tree
static UIBox* 
UIBoxAlloc(UIState* State, UIKey Key) 
{
    UIBox* Result = UIBoxFromKey(State, Key);

    if (Result) {
        Result->TailBuildIndex = State->BuildIndex;
        Result->Parent = EMPTY_UI_INDEX_VALUE;
        Result->Head = EMPTY_UI_INDEX_VALUE;
        Result->Tail = EMPTY_UI_INDEX_VALUE;
        Result->Next = EMPTY_UI_INDEX_VALUE;
        Result->Prev = EMPTY_UI_INDEX_VALUE;

        return Result;
    }

    if (State->HeadFreeBox == EMPTY_UI_INDEX_VALUE)
        return NULL;

    u8 NewIndex = State->HeadFreeBox;

    Result = &State->Boxes[NewIndex];
    State->HeadFreeBox = Result->HashNext;
    NCUI_MEMSET(Result, 0, sizeof(*Result));
    Result->HashNext = EMPTY_UI_INDEX_VALUE;
    Result->HashPrev = EMPTY_UI_INDEX_VALUE;
    Result->Parent = EMPTY_UI_INDEX_VALUE;
    Result->Head = EMPTY_UI_INDEX_VALUE;
    Result->Tail = EMPTY_UI_INDEX_VALUE;
    Result->Next = EMPTY_UI_INDEX_VALUE;
    Result->Prev = EMPTY_UI_INDEX_VALUE;
    Result->Key = Key;
    Result->HeadBuildIndex = State->BuildIndex;
    Result->TailBuildIndex = State->BuildIndex;

    u8 SlotIndex = (u8) (Key.V % NCUI_BOX_HASH_SLOTS);
    UIHashSlot* Slot = &State->HashSlots[SlotIndex];

    Result->HashPrev = Slot->Tail;

    if (Slot->Tail != EMPTY_UI_INDEX_VALUE)
        State->Boxes[Slot->Tail].HashNext = NewIndex;
    else
        Slot->Head = NewIndex;

    Slot->Tail = NewIndex;
    ++State->BoxesCount;

    return Result;
}

// NOTE: Given a UIState release the UIBox at position Index from the UI tree.
static void 
UIBoxRelease(UIState* State, u8 Index) 
{
    UIBox* Box = &State->Boxes[Index];
    u8 SlotIndex = (u8) (Box->Key.V % NCUI_BOX_HASH_SLOTS);
    UIHashSlot* Slot = &State->HashSlots[SlotIndex];

    if (Box->HashPrev != EMPTY_UI_INDEX_VALUE)
        State->Boxes[Box->HashPrev].HashNext = Box->HashNext;
    else
        Slot->Head = Box->HashNext;

    if (Box->HashNext != EMPTY_UI_INDEX_VALUE)
        State->Boxes[Box->HashNext].HashPrev = Box->HashPrev;
    else
        Slot->Tail = Box->HashPrev;

    Box->Key = EMPTY_UI_KEY_VALUE;
    Box->HashNext = State->HeadFreeBox;
    Box->HashPrev = EMPTY_UI_INDEX_VALUE;
    State->HeadFreeBox = Index;
    --State->BoxesCount;
}

// NOTE: Check through queued UIEvents and get UISignal for any pertaining to
//     : a given UIBox
static UISignal 
SignalFromBox(UIState* State, UIBox* Box) 
{
    UISignal Sig = {0};

    if (!(Box->Flags & UI_BOX_FLAG_CLICKABLE))
        return Sig;

    b32 IsHot = (Box->Key.V == State->HotKey.V);
    b32 IsActive = (Box->Key.V == State->ActiveKey.V);

    if (IsHot) 
        Sig.Kind |= UI_SIGNAL_HOT;

    if (IsActive) 
        Sig.Kind |= UI_SIGNAL_ACTIVE;

    for (u8 Index = 0; Index < NCUI_MAX_EVENTS; ++Index) {
        UIEvent* Event = &State->Events[Index];

        if (Event->Kind == UI_EVENT_NONE) 
            continue;

        if (
            Event->Kind == UI_EVENT_PRESS && 
            Event->Input == UI_INPUT_SELECT && 
            IsHot
        ) {
            Sig.Kind |= UI_SIGNAL_PRESSED;
            Box->IsActive = TRUE;
        }

        if (
            Event->Kind == UI_EVENT_RELEASE && 
            Event->Input == UI_INPUT_SELECT && 
            IsActive
        ) {
            Sig.Kind |= (UI_SIGNAL_RELEASED | UI_SIGNAL_CLICKED);
            Box->IsActive = FALSE;
        }
    }

    Box->IsHot = IsHot;

    return Sig;
}

// NOTE: Pre-order tree traversal
//     : non-recursive to avoid deep call stacks
static u8 
UIGetNextNode(UIState* State, u8 NodeIndex, u8 RootIndex) 
{
    UIBox* Node = &State->Boxes[NodeIndex];

    if (Node->Head != EMPTY_UI_INDEX_VALUE)
        return Node->Head;

    for (
        u8 Current = NodeIndex; 
        Current != EMPTY_UI_INDEX_VALUE && Current != RootIndex; 
        Current = State->Boxes[Current].Parent
    ) {
        if (State->Boxes[Current].Next != EMPTY_UI_INDEX_VALUE)
            return State->Boxes[Current].Next;
    }

    return EMPTY_UI_INDEX_VALUE;
}

static u8 
UIGetFirstNodePostOrder(UIState* State, u8 RootIndex) 
{
    u8 Current = RootIndex;

    while (State->Boxes[Current].Head != EMPTY_UI_INDEX_VALUE)
        Current = State->Boxes[Current].Head;

    return Current;
}

// NOTE: Post-order tree traversal
//     : non-recursive to avoid deep call stacks
//     : used for layout pass where parent's size depends on size of its children
static u8 
UIGetNextNodePostOrder(UIState* State, u8 NodeIndex, u8 RootIndex) 
{
    if (NodeIndex == RootIndex) 
        return EMPTY_UI_INDEX_VALUE;

    u8 NextSibling = State->Boxes[NodeIndex].Next;

    if (NextSibling != EMPTY_UI_INDEX_VALUE)
        return UIGetFirstNodePostOrder(State, NextSibling);

    return State->Boxes[NodeIndex].Parent;
}

static void 
UILayoutRoot(UIState* State, u8 RootIndex) 
{
    if (RootIndex == EMPTY_UI_INDEX_VALUE) 
        return;

    // NOTE: Resolve static sizes
    for (
        u8 Node = RootIndex; 
        Node != EMPTY_UI_INDEX_VALUE; 
        Node = UIGetNextNode(State, Node, RootIndex)
    ) {
        UIBox* Box = &State->Boxes[Node];

        if (Box->Flags & UI_BOX_FLAG_FLOATING) 
            continue;

        for (Axis2D Axis = 0; Axis < AXIS_2D_COUNT; ++Axis) {
            if (Box->PreferredSize[Axis].Kind == UI_SIZE_KIND_PIXELS) {
                Box->FixedSize[Axis] = (u8) Box->PreferredSize[Axis].Value;
            } else if (Box->PreferredSize[Axis].Kind == UI_SIZE_KIND_TEXT_CONTENT) {
                Box->FixedSize[Axis] = (Axis == AXIS_2D_X) 
                    ? (Box->StringLength * NCUI_FONT_ADVANCE) 
                    : NCUI_FONT_LINE_HEIGHT;
            }
        }
    }

    // NOTE: Resolve upwards-dependent sizes
    for (
        u8 Node = RootIndex; 
        Node != EMPTY_UI_INDEX_VALUE; 
        Node = UIGetNextNode(State, Node, RootIndex)
    ) {
        UIBox* Box = &State->Boxes[Node];

        if (Box->Flags & UI_BOX_FLAG_FLOATING) 
            continue;

        for (Axis2D Axis = 0; Axis < AXIS_2D_COUNT; ++Axis) {
            if (Box->PreferredSize[Axis].Kind == UI_SIZE_KIND_PERCENT_OF_PARENT) {
                if (Box->Parent != EMPTY_UI_INDEX_VALUE) {
                    Box->FixedSize[Axis] = (u8) (
                        State->Boxes[Box->Parent].FixedSize[Axis] * Box->PreferredSize[Axis].Value
                    );
                }
            }
        }
    }

    // NOTE: Resolve downwards-dependent sizes
    for (
        u8 Node = UIGetFirstNodePostOrder(State, RootIndex); 
        Node != EMPTY_UI_INDEX_VALUE; 
        Node = UIGetNextNodePostOrder(State, Node, RootIndex)
    ) {
        UIBox* Box = &State->Boxes[Node];

        if (Box->Flags & UI_BOX_FLAG_FLOATING) 
            continue;

        for (Axis2D Axis = 0; Axis < AXIS_2D_COUNT; ++Axis) {
            if (Box->PreferredSize[Axis].Kind == UI_SIZE_KIND_SUM_OF_CHILDREN) {
                u8 Sum = 0;

                for (
                    u8 Child = Box->Head; 
                    Child != EMPTY_UI_INDEX_VALUE; 
                    Child = State->Boxes[Child].Next
                ) {
                    if (Box->ChildLayoutAxis == Axis)
                        Sum += State->Boxes[Child].FixedSize[Axis];
                    else
                        Sum = NCUI_MAX(Sum, State->Boxes[Child].FixedSize[Axis]);
                }

                Box->FixedSize[Axis] = Sum;
            }
        }
    }

    // NOTE: Compute final positions and clip rectangles
    UIRect ScreenRect = UIRectAlloc(0, 0, State->Width - 1, State->Height - 1);

    {
        UIBox* Root = &State->Boxes[RootIndex];

        Root->Rect.X0 = Root->FixedPosition[AXIS_2D_X];
        Root->Rect.Y0 = Root->FixedPosition[AXIS_2D_Y];
        Root->Rect.X1 = Root->Rect.X0 + Root->FixedSize[AXIS_2D_X] - 1;
        Root->Rect.Y1 = Root->Rect.Y0 + Root->FixedSize[AXIS_2D_Y] - 1;
        Root->ClipRect = ScreenRect;
    }

    for (
        u8 Node = RootIndex; 
        Node != EMPTY_UI_INDEX_VALUE; 
        Node = UIGetNextNode(State, Node, RootIndex)
    ) {
        UIBox* Box = &State->Boxes[Node];
        u8 LayoutPosition[AXIS_2D_COUNT] = { 
            Box->FixedPosition[AXIS_2D_X], 
            Box->FixedPosition[AXIS_2D_Y] 
        };
        UIRect ChildClipRect = Box->ClipRect;

        if (Box->Flags & UI_BOX_FLAG_CLIP)
            ChildClipRect = UIRectIntersect(ChildClipRect, Box->Rect);

        for (
            u8 Child = Box->Head; 
            Child != EMPTY_UI_INDEX_VALUE; 
            Child = State->Boxes[Child].Next
        ) {
            UIBox* ChildBox = &State->Boxes[Child];

            if (ChildBox->Flags & UI_BOX_FLAG_FLOATING) {
                ChildBox->Rect.X0 = ChildBox->FixedPosition[AXIS_2D_X];
                ChildBox->Rect.Y0 = ChildBox->FixedPosition[AXIS_2D_Y];
                ChildBox->Rect.X1 = ChildBox->Rect.X0 + ChildBox->FixedSize[AXIS_2D_X] - 1;
                ChildBox->Rect.Y1 = ChildBox->Rect.Y0 + ChildBox->FixedSize[AXIS_2D_Y] - 1;
                ChildBox->ClipRect = ChildClipRect;
                continue;
            }

            ChildBox->FixedPosition[AXIS_2D_X] = LayoutPosition[AXIS_2D_X];
            ChildBox->FixedPosition[AXIS_2D_Y] = LayoutPosition[AXIS_2D_Y];
            LayoutPosition[Box->ChildLayoutAxis] += ChildBox->FixedSize[Box->ChildLayoutAxis];
            ChildBox->Rect.X0 = ChildBox->FixedPosition[AXIS_2D_X];
            ChildBox->Rect.Y0 = ChildBox->FixedPosition[AXIS_2D_Y];
            ChildBox->Rect.X1 = ChildBox->Rect.X0 + ChildBox->FixedSize[AXIS_2D_X] - 1;
            ChildBox->Rect.Y1 = ChildBox->Rect.Y0 + ChildBox->FixedSize[AXIS_2D_Y] - 1;
            ChildBox->ClipRect = ChildClipRect;
        }
    }
}

NCUI_DEF UIKey 
UIKeyFromStr(UIKey Seed, char const* String, u8 StringLength) 
{
    UIKey Result = {0};

    if (StringLength)
        Result.V = Hash(Seed.V, String, StringLength);

    return Result;
}

NCUI_DEF UIKey 
UIKeyFromStr(char const* String) 
{
    return UIKeyFromStr(EMPTY_UI_KEY_VALUE, String, FontStrLen(String));
}

NCUI_DEF void 
UIInit(UIState* State, u16 Width, u16 Height) 
{
    NCUI_MEMSET(State, 0, sizeof(*State));
    State->Width = Width;
    State->Height = Height;
    State->Banks = (Height + 7) / 8;
    State->BufferSize = Width * State->Banks;

    for (u8 Index = 0; Index < NCUI_BOX_HASH_SLOTS; ++Index) {
        State->HashSlots[Index].Head = EMPTY_UI_INDEX_VALUE;
        State->HashSlots[Index].Tail = EMPTY_UI_INDEX_VALUE;
    }

    for (u8 Index = 0; Index < NCUI_MAX_BOXES; ++Index) {
        State->Boxes[Index].HashNext = (Index + 1 < NCUI_MAX_BOXES) 
            ? (Index + 1) 
            : EMPTY_UI_INDEX_VALUE;
        State->Boxes[Index].HashPrev = EMPTY_UI_INDEX_VALUE;
        State->Boxes[Index].Parent = EMPTY_UI_INDEX_VALUE;
        State->Boxes[Index].Head = EMPTY_UI_INDEX_VALUE;
        State->Boxes[Index].Tail = EMPTY_UI_INDEX_VALUE;
        State->Boxes[Index].Next = EMPTY_UI_INDEX_VALUE;
        State->Boxes[Index].Prev = EMPTY_UI_INDEX_VALUE;
        State->Boxes[Index].Key = EMPTY_UI_KEY_VALUE;
    }

    for (u8 Index = 0; Index < NCUI_ANIMATION_HASH_SLOTS; ++Index) {
        State->AnimationHashSlots[Index].Head = EMPTY_UI_INDEX_VALUE;
        State->AnimationHashSlots[Index].Tail = EMPTY_UI_INDEX_VALUE;
    }

    for (u8 Index = 0; Index < NCUI_MAX_ANIMATIONS; ++Index) {
        State->AnimationNodes[Index].HashNext = (Index + 1 < NCUI_MAX_ANIMATIONS) 
            ? (Index + 1) 
            : EMPTY_UI_INDEX_VALUE;
        State->AnimationNodes[Index].HashPrev = EMPTY_UI_INDEX_VALUE;
        State->AnimationNodes[Index].Key = EMPTY_UI_KEY_VALUE;
    }

    State->HeadFreeAnimation = 0;
    State->AnimationCount = 0;
    State->HeadFreeBox = 0;
    State->BoxesCount = 0;
    State->BuildIndex = 0;
    State->HotKey = EMPTY_UI_KEY_VALUE;
    State->ActiveKey = EMPTY_UI_KEY_VALUE;
    State->ParentStackDepth = 0;
    State->HeadEvent = 0;
    State->TailEvent = 0;
    State->EventsCount = 0;
}

NCUI_DEF void 
UIBeginBuild(UIState* State) 
{
    State->ParentStackDepth = 0;
}

NCUI_DEF void 
UIEndBuild(UIState* State) 
{
    // NOTE: Garbage-collect stale boxes
    //     : if a box has not been touched within NCUI_STALE_FRAMES,
    //     : it is considered dead and its memory is reclaimed
    for (u8 SlotIndex = 0; SlotIndex < NCUI_BOX_HASH_SLOTS; ++SlotIndex) {
        u8 BoxIndex = State->HashSlots[SlotIndex].Head;

        while (BoxIndex != EMPTY_UI_INDEX_VALUE) {
            UIBox* Box = &State->Boxes[BoxIndex];
            u8 NextIndex = Box->HashNext;

            if (
                Box->TailBuildIndex + NCUI_STALE_FRAMES < State->BuildIndex || 
                Box->Key.V == EMPTY_UI_KEY_VALUE.V
            ) {
                UIBoxRelease(State, BoxIndex);
            }

            BoxIndex = NextIndex;
        }
    }

    // NOTE: Garbage-collect stale animations
    //     : if an animation has not been touched within NCUI_STALE_FRAMES,
    //     : it is considered dead and its memory is reclaimed
    for (
        u8 SlotIndex = 0; 
        SlotIndex < NCUI_ANIMATION_HASH_SLOTS; 
        ++SlotIndex
    ) {
        for (
            u8 NodeIndex = State->AnimationHashSlots[SlotIndex].Head, Next = 0; 
            NodeIndex != EMPTY_UI_INDEX_VALUE; 
            NodeIndex = Next
        ) {
            UIAnimationNode* Node = &State->AnimationNodes[NodeIndex];

            Next = Node->HashNext;

            if (
                Node->LastTouchedBuildIndex + NCUI_STALE_FRAMES < State->BuildIndex || 
                Node->Key.V == EMPTY_UI_KEY_VALUE.V
            ) {
                if (Node->HashPrev != EMPTY_UI_INDEX_VALUE)
                    State->AnimationNodes[Node->HashPrev].HashNext = Node->HashNext;
                else
                    State->AnimationHashSlots[SlotIndex].Head = Node->HashNext;

                if (Node->HashNext != EMPTY_UI_INDEX_VALUE)
                    State->AnimationNodes[Node->HashNext].HashPrev = Node->HashPrev;
                else
                    State->AnimationHashSlots[SlotIndex].Tail = Node->HashPrev;

                Node->Key = EMPTY_UI_KEY_VALUE;
                Node->HashNext = State->HeadFreeAnimation;
                Node->HashPrev = EMPTY_UI_INDEX_VALUE;
                State->HeadFreeAnimation = NodeIndex;
                --State->AnimationCount;
            }
        }
    }

    // NOTE: Handle selection and movement events
    for (u8 EventIndex = 0; EventIndex < NCUI_MAX_EVENTS; ++EventIndex) {
        UIEvent* Event = &State->Events[EventIndex];

        if (Event->Kind == UI_EVENT_NONE) 
            continue;

        if (Event->Kind == UI_EVENT_PRESS && Event->Input == UI_INPUT_SELECT) {
            if (State->HotKey.V != EMPTY_UI_KEY_VALUE.V)
                State->ActiveKey = State->HotKey;
        }

        if (
            Event->Kind == UI_EVENT_RELEASE && 
            Event->Input == UI_INPUT_SELECT
        ) {
            State->ActiveKey = EMPTY_UI_KEY_VALUE;
        }
    }

    u8 RootIndex = EMPTY_UI_INDEX_VALUE;

    for (u8 Index = 0; Index < NCUI_MAX_BOXES; ++Index) {
        if (
            State->Boxes[Index].Key.V != EMPTY_UI_KEY_VALUE.V && 
            State->Boxes[Index].Parent == EMPTY_UI_INDEX_VALUE
        ) {
            RootIndex = Index;
            break;
        }
    }

    if (RootIndex != EMPTY_UI_INDEX_VALUE) {
        State->Boxes[RootIndex].FixedPosition[AXIS_2D_X] = 0;
        State->Boxes[RootIndex].FixedPosition[AXIS_2D_Y] = 0;
        State->Boxes[RootIndex].FixedSize[AXIS_2D_X] = State->Width;
        State->Boxes[RootIndex].FixedSize[AXIS_2D_Y] = State->Height;
        UILayoutRoot(State, RootIndex);
    }

    State->HeadEvent = 0;
    State->TailEvent = 0;
    State->EventsCount = 0;
    ++State->BuildIndex;
}

NCUI_DEF u8 
UIAnimate(UIState *State, UIKey Key, u8 Target, u8 Initial, u8 RateShift) 
{
    if (Key.V == EMPTY_UI_KEY_VALUE.V) 
        return Target;

    u8 SlotIndex = (u8) (Key.V % NCUI_ANIMATION_HASH_SLOTS);
    UIHashSlot* Slot = &State->AnimationHashSlots[SlotIndex];
    u8 NodeIndex = Slot->Head;
    UIAnimationNode* Node = NULL;

    while (NodeIndex != EMPTY_UI_INDEX_VALUE) {
        if (State->AnimationNodes[NodeIndex].Key.V == Key.V) {
            Node = &State->AnimationNodes[NodeIndex];
            break;
        }

        NodeIndex = State->AnimationNodes[NodeIndex].HashNext;
    }

    if (!Node) {
        if (State->HeadFreeAnimation == EMPTY_UI_INDEX_VALUE) 
            return Target;

        NodeIndex = State->HeadFreeAnimation;
        Node = &State->AnimationNodes[NodeIndex];
        State->HeadFreeAnimation = Node->HashNext;
        Node->Key = Key;
        Node->Current = Initial;
        Node->HashPrev = Slot->Tail;
        Node->HashNext = EMPTY_UI_INDEX_VALUE;

        if (Slot->Tail != EMPTY_UI_INDEX_VALUE)
            State->AnimationNodes[Slot->Tail].HashNext = NodeIndex;
        else
            Slot->Head = NodeIndex;

        Slot->Tail = NodeIndex;
        ++State->AnimationCount;
    }

    Node->LastTouchedBuildIndex = State->BuildIndex;

    i16 Diff = (i16) Target - (i16) Node->Current;

    if (Diff != 0) {
        i16 Step = Diff >> RateShift;

        // NOTE: Snap to target when remaining distance is smaller than shift
        if (Step == 0) 
            Step = (Diff > 0) ? 1 : -1;

        Node->Current += Step;
    }

    return Node->Current;
}

NCUI_DEF void 
UIPushEvent(UIState* State, UIEventKind Kind, UIInputKind Input) 
{
    if (State->EventsCount >= NCUI_MAX_EVENTS) 
        return;

    UIEvent* Event = &State->Events[State->TailEvent];

    Event->Kind = Kind;
    Event->Input = Input;
    State->TailEvent = (State->TailEvent + 1) % NCUI_MAX_EVENTS;
    ++State->EventsCount;
}

NCUI_DEF void 
UIPopEvent(UIState* State, u8 Index) 
{
    State->Events[Index].Kind = UI_EVENT_NONE;
}

NCUI_DEF UIBox* 
UIBoxFromKey(UIState* State, UIKey Key) 
{
    UIBox* Result = NULL;

    if (Key.V == EMPTY_UI_KEY_VALUE.V) 
        return Result;

    u8 SlotIndex = (u8) (Key.V % NCUI_BOX_HASH_SLOTS);
    u8 BoxIndex = State->HashSlots[SlotIndex].Head;

    while (BoxIndex != EMPTY_UI_INDEX_VALUE) {
        UIBox* Box = &State->Boxes[BoxIndex];

        if (Box->Key.V == Key.V) {
            Result = Box;
            break;
        }

        BoxIndex = Box->HashNext;
    }

    return Result;
}

NCUI_DEF UISignal 
UIBuildBox(UIState* State, UIBoxFlags Flags, UIKey Key) 
{
    UISignal Result = {0};
    UIBox* Box = UIBoxAlloc(State, Key);

    if (!Box) 
        return Result;

    Box->Flags = Flags;
    Box->TailBuildIndex = State->BuildIndex;
    Box->PreferredSize[AXIS_2D_X] = State->PreferredWidthStackDepth 
        ? State->PreferredWidthStack[State->PreferredWidthStackDepth - 1] 
        : UI_PX(0);
    Box->PreferredSize[AXIS_2D_Y] = State->PreferredHeightStackDepth 
        ? State->PreferredHeightStack[State->PreferredHeightStackDepth - 1] 
        : UI_PX(0);
    Box->ChildLayoutAxis = State->ChildLayoutAxisStackDepth 
        ? State->ChildLayoutAxisStack[State->ChildLayoutAxisStackDepth - 1]
        : AXIS_2D_Y;

    UIBox* Parent = UIHeadParent(State);

    if (Parent) {
        u8 Index = (u8) (Box - State->Boxes);

        Box->Parent = (u8) (Parent - State->Boxes);

        if (Parent->Tail != EMPTY_UI_INDEX_VALUE) {
            State->Boxes[Parent->Tail].Next = Index;
            Box->Prev = Parent->Tail;
        } else {
            Parent->Head = Index;
        }

        Parent->Tail = Index;
    }

    return SignalFromBox(State, Box);
}

NCUI_DEF UISignal 
UIBuildBoxFromStr(UIState* State, UIBoxFlags Flags, char const* String) 
{
    UIKey Key = UIKeyFromStr(String);
    UISignal Sig = UIBuildBox(State, Flags, Key);
    UIBox* Box = UIBoxFromKey(State, Key);

    if (Box) {
        Box->String = String;
        Box->StringLength = FontStrLen(String);
    }

    return Sig;
}

NCUI_DEF void 
UIPushParent(UIState* State, UIBox* Box) 
{
    if (State->ParentStackDepth < NCUI_MAX_STACK_DEPTH)
        State->ParentStack[State->ParentStackDepth++] = (u8) (Box - State->Boxes);
}

NCUI_DEF void 
UIPopParent(UIState* State) 
{
    if (State->ParentStackDepth) 
        --State->ParentStackDepth;
}

NCUI_DEF UIBox* 
UIHeadParent(UIState* State) 
{
    if (!State->ParentStackDepth) 
        return NULL;

    return &State->Boxes[State->ParentStack[State->ParentStackDepth - 1]];
}

NCUI_DEF void 
UIPushPreferredWidth(UIState* State, UISize Size) 
{
    if (State->PreferredWidthStackDepth < NCUI_MAX_STACK_DEPTH)
        State->PreferredWidthStack[State->PreferredWidthStackDepth++] = Size;
}

NCUI_DEF void 
UIPopPreferredWidth(UIState* State) 
{
    if (State->PreferredWidthStackDepth) 
        --State->PreferredWidthStackDepth;
}

NCUI_DEF void 
UIPushPreferredHeight(UIState* State, UISize Size) 
{
    if (State->PreferredHeightStackDepth < NCUI_MAX_STACK_DEPTH)
        State->PreferredHeightStack[State->PreferredHeightStackDepth++] = Size;
}

NCUI_DEF void 
UIPopPreferredHeight(UIState* State) 
{
    if (State->PreferredHeightStackDepth) 
        --State->PreferredHeightStackDepth;
}

NCUI_DEF void 
UIPushChildLayoutAxis(UIState* State, Axis2D Axis) 
{
    if (State->ChildLayoutAxisStackDepth < NCUI_MAX_STACK_DEPTH)
        State->ChildLayoutAxisStack[State->ChildLayoutAxisStackDepth++] = Axis;
}

NCUI_DEF void 
UIPopChildLayoutAxis(UIState* State) 
{
    if (State->ChildLayoutAxisStackDepth) 
        --State->ChildLayoutAxisStackDepth;
}

NCUI_DEF UISignal 
UILabel(UIState* State, char const* String) 
{
    return UIBuildBoxFromStr(State, UI_BOX_FLAG_DRAW_TEXT, String);
}

NCUI_DEF UISignal 
UIButton(UIState* State, char const* String) 
{
    return UIBuildBoxFromStr(
        State, 
        UI_BOX_FLAG_DRAW_TEXT | UI_BOX_FLAG_DRAW_BORDER | UI_BOX_FLAG_CLICKABLE, 
        String
    );
}

NCUI_DEF UISignal 
UICheckBox(UIState* State, char const* String, b32* Value) 
{
    UISignal Sig = UIBuildBoxFromStr(
        State, 
        UI_BOX_FLAG_DRAW_TEXT | UI_BOX_FLAG_DRAW_BORDER | UI_BOX_FLAG_CLICKABLE, 
        String
    );

    if (UI_CLICKED(Sig)) 
        *Value = !(*Value);

    UIBox* Box = UIBoxFromKey(State, UIKeyFromStr(String));

    if (Box && *Value) 
        Box->Flags |= UI_BOX_FLAG_INVERTED;

    return Sig;
}

NCUI_DEF UISignal 
UIMenuEntry(UIState* State, char const* String, b32 IsSelected) 
{
    UISignal Sig = {0};

    UIPreferedWidth(State, UI_PCT(1.0f)) {
        UIPreferedHeight(State, UI_PX(8)) {
            Sig = UIBuildBoxFromStr(
                State, 
                UI_BOX_FLAG_DRAW_TEXT | UI_BOX_FLAG_CLICKABLE | ((IsSelected) ? UI_BOX_FLAG_INVERTED : 0), 
                String
            );
        }
    }

    return Sig;
}

NCUI_DEF UISignal
UIDivider(UIState *State, const char *String)
{
    UIBoxFlags Flags = UI_BOX_FLAG_NAV_SKIP | UI_BOX_FLAG_DRAW_DIVIDER;

    if (String)
        Flags |= UI_BOX_FLAG_DRAW_TEXT;

    return UIBuildBoxFromStr(State, Flags, String);
}


NCUI_DEF UISignal 
UIProgressBar(UIState* State, char const* String, u8 ProgressPCT)
{
    UIKey BaseKey = UIKeyFromStr(String);
    UISignal Sig = UIBuildBox(State, UI_BOX_FLAG_DRAW_BORDER, BaseKey);
    UIBox* ParentBox = UIBoxFromKey(State, BaseKey);

    ProgressPCT = NCUI_CLAMP_TOP(ProgressPCT, 100);

    if (ParentBox && ProgressPCT) {
        UIParent(State, ParentBox) {
            UIPreferedWidth(State, UI_PCT((f32) ProgressPCT / 100.0f)) {        // FIXME: RIP ISAs with no hardware float div op
                UIPreferedHeight(State, UI_PCT(1.0f)) {
                    UIKey FillKey = UIKeyFromStr(BaseKey, "fill", 4);

                    UIBuildBox(
                        State,
                        UI_BOX_FLAG_DRAW_FILL | UI_BOX_FLAG_NAV_SKIP,
                        FillKey
                    );
                }
            }
        }
    }

    return Sig;
}

NCUI_DEF UISignal 
UISlider(UIState* State, char const* String, u8* ValuePCT, u8 Step)
{
    UIKey BaseKey = UIKeyFromStr(String);
    UISignal Sig = UIBuildBox(
        State,
        UI_BOX_FLAG_DRAW_BORDER | UI_BOX_FLAG_CLICKABLE,
        BaseKey
    );
    UIBox* ParentBox = UIBoxFromKey(State, BaseKey);

    if (UI_HOT(Sig) || UI_ACTIVE(Sig)) {
        for (u8 Index = 0; Index < NCUI_MAX_EVENTS; ++Index) {
            UIEvent* Event = &State->Events[Index];

            if (Event->Kind == UI_EVENT_PRESS) {
                if (Event->Input == UI_INPUT_LEFT) {
                    if (*ValuePCT >= Step)
                        *ValuePCT -= Step;
                    else
                        *ValuePCT = 0;

                    UIPopEvent(State, Index);
                } else if (Event->Input == UI_INPUT_RIGHT) {
                    if (*ValuePCT <= 100 - Step)
                        *ValuePCT += Step;
                    else
                        *ValuePCT = 100;

                    UIPopEvent(State, Index);
                }
            }
        }
    }

    *ValuePCT = NCUI_CLAMP_TOP(*ValuePCT, 100);

    if (ParentBox && *ValuePCT) {
        UIParent(State, ParentBox) {
            UIPreferedWidth(State, UI_PCT((f32) *ValuePCT / 100.0f)) {
                UIPreferedHeight(State, UI_PCT(1.0f)) {
                    UIKey FillKey = UIKeyFromStr(BaseKey, "fill", 4);
                    UIBoxFlags Flags = UI_BOX_FLAG_DRAW_FILL | UI_BOX_FLAG_NAV_SKIP;

                    if (UI_ACTIVE(Sig))
                        Flags = UI_BOX_FLAG_DRAW_BORDER | UI_BOX_FLAG_NAV_SKIP;

                    UIBuildBox(State, Flags, FillKey);
                }
            }
        }
    }

    return Sig;
}

NCUI_DEF NCUI_ATTR 
void DrawPixelSet(UIState* State, u8* Buffer, u8 X, u8 Y) 
{
    if (X >= State->Width || Y >= State->Height) 
        return;

    // NOTE: Bank index = Y >> 3
    //     : Bit within Bank index = Y & 7
    Buffer[(Y >> 3) * State->Width + X] |= (1 << (Y & 7));
}

NCUI_DEF NCUI_ATTR void 
DrawPixelClear(UIState* State, u8* Buffer, u8 X, u8 Y) 
{
    if (X >= State->Width || Y >= State->Height) 
        return;

    Buffer[(Y >> 3) * State->Width + X] &= ~(1 << (Y & 7));
}

NCUI_DEF NCUI_ATTR void 
DrawPixelToggle(UIState* State, u8* Buffer, u8 X, u8 Y) 
{
    if (X >= State->Width || Y >= State->Height) 
        return;

    Buffer[(Y >> 3) * State->Width + X] ^= (1 << (Y & 7));
}

NCUI_DEF NCUI_ATTR void 
ClearDisplay(UIState* State, u8* Buffer) 
{
    NCUI_MEMSET(Buffer, 0, State->BufferSize);
}

NCUI_DEF NCUI_ATTR void 
FillDisplay(UIState* State, u8* Buffer) 
{
    NCUI_MEMSET(Buffer, 0xFF, State->BufferSize);
}

NCUI_DEF NCUI_ATTR void 
DrawHorzLine(UIState* State, u8* Buffer, u8 X0, u8 X1, u8 Y) 
{
    if (Y >= State->Height) 
        return;

    if (X0 > X1) 
        NCUI_SWAP(u8, X0, X1);

    if (X0 >= State->Width) 
        return;

    if (X1 >= State->Width) 
        X1 = State->Width - 1;

    u8 Bank = Y >> 3;
    u8 Mask = 1 << (Y & 7);
    u8* Row = Buffer + Bank * State->Width;

    for (u8 X = X0; X <= X1; ++X) 
        Row[X] |= Mask;
}

NCUI_DEF NCUI_ATTR void 
ClearHorzLine(UIState* State, u8* Buffer, u8 X0, u8 X1, u8 Y) 
{
    if (Y >= State->Height) 
        return;

    if (X0 > X1) 
        NCUI_SWAP(u8, X0, X1);

    if (X0 >= State->Width) 
        return;

    if (X1 >= State->Width) 
        X1 = State->Width - 1;

    u8 Bank = Y >> 3;
    u8 Mask = ~(1 << (Y & 7));
    u8* Row = Buffer + Bank * State->Width;

    for (u8 X = X0; X <= X1; ++X) 
        Row[X] &= Mask;
}

NCUI_DEF NCUI_ATTR void 
DrawVertLine(UIState* State, u8* Buffer, u8 X, u8 Y0, u8 Y1) 
{
    if (X >= State->Width) 
        return;

    if (Y0 > Y1) 
        NCUI_SWAP(u8, Y0, Y1);

    if (Y0 >= State->Height) 
        return;

    if (Y1 >= State->Height) 
        Y1 = State->Height - 1;

    u8 Bank0 = Y0 >> 3;
    u8 Bank1 = Y1 >> 3;
    u8 Bit0 = Y0 & 7;
    u8 Bit1 = Y1 & 7;

    if (Bank0 == Bank1) {                                                       // NOTE: Line starts and ends within same display bank
        u8 Mask = ((0xFF << Bit0) & (0xFF >> (7 - Bit1)));

        Buffer[Bank0 * State->Width + X] |= Mask;
    } else {                                                                    // NOTE: Line spans multiple display banks
        Buffer[Bank0 * State->Width + X] |= (0xFF << Bit0);

        for (u8 Bank = Bank0 + 1; Bank < Bank1; ++Bank)
            Buffer[Bank * State->Width + X] = 0xFF;

        Buffer[Bank1 * State->Width + X] |= (0xFF >> (7 - Bit1));
    }
}

NCUI_DEF NCUI_ATTR void 
ClearVertLine(UIState* State, u8* Buffer, u8 X, u8 Y0, u8 Y1) 
{
    if (X >= State->Width) 
        return;

    if (Y0 > Y1) 
        NCUI_SWAP(u8, Y0, Y1);

    if (Y0 >= State->Height) 
        return;

    if (Y1 >= State->Height) 
        Y1 = State->Height - 1;

    u8 Bank0 = Y0 >> 3;
    u8 Bank1 = Y1 >> 3;
    u8 Bit0 = Y0 & 7;
    u8 Bit1 = Y1 & 7;

    if (Bank0 == Bank1) {                                                       // NOTE: Line starts and ends within same display bank
        u8 Mask = ~((0xFF << Bit0) & (0xFF >> (7 - Bit1)));

        Buffer[Bank0 * State->Width + X] &= Mask;
    } else {                                                                    // NOTE: Line spans multiple display banks
        Buffer[Bank0 * State->Width + X] &= (0xFF << Bit0);

        for (u8 Bank = Bank0 + 1; Bank < Bank1; ++Bank)
            Buffer[Bank * State->Width + X] = 0;

        Buffer[Bank1 * State->Width + X] &= ~(0xFF >> (7 - Bit1));
    }
}

NCUI_DEF NCUI_ATTR void
DrawLine(UIState *State, u8 *Buffer, u8 X0, u8 Y0, u8 X1, u8 Y1)
{
    i16 DX = X1 > X0 ? X1 - X0 : X0 - X1;
    i16 DY = Y1 > Y0 ? Y1 - Y0 : Y0 - Y1;
    i8 SX = X0 < X1 ? 1 : -1;
    i8 SY = Y0 < Y1 ? 1 : -1;
    i16 Threshold = DX + DY;
    i16 DoubleThreshold;

    for (;;) {
        DrawPixelSet(State, Buffer, X0, Y0);

        if (X0 == X1 && Y0 == Y1)
            break;

        DoubleThreshold = 2 * Threshold;

        if (DoubleThreshold >= DY) {
            Threshold += DY;
            X0 += SX;
        }

        if (DoubleThreshold <= DX) {
            Threshold += DX;
            Y0 += SY;
        }
    }
}

NCUI_DEF NCUI_ATTR void
ClearLine(UIState *State, u8 *Buffer, u8 X0, u8 Y0, u8 X1, u8 Y1)
{
    i16 DX = X1 > X0 ? X1 - X0 : X0 - X1;
    i16 DY = Y1 > Y0 ? Y1 - Y0 : Y0 - Y1;
    i8 SX = X0 < X1 ? 1 : -1;
    i8 SY = Y0 < Y1 ? 1 : -1;
    i16 Threshold = DX + DY;
    i16 DoubleThreshold;

    for (;;) {
        DrawPixelClear(State, Buffer, X0, Y0);

        if (X0 == X1 && Y0 == Y1)
            break;

        DoubleThreshold = 2 * Threshold;

        if (DoubleThreshold >= DY) {
            Threshold += DY;
            X0 += SX;
        }

        if (DoubleThreshold <= DX) {
            Threshold += DX;
            Y0 += SY;
        }
    }
}

NCUI_DEF NCUI_ATTR void 
DrawFilledRect(UIState* State, u8* Buffer, u8 X0, u8 Y0, u8 X1, u8 Y1) 
{
    if (X0 > X1) 
        NCUI_SWAP(u8, X0, X1);

    if (Y0 > Y1) 
        NCUI_SWAP(u8, Y0, Y1);

    if (X0 >= State->Width || Y0 >= State->Height) 
        return;

    if (X1 >= State->Width) 
        X1 = State->Width - 1;

    if (Y1 >= State->Height) 
        Y1 = State->Height - 1;

    u8 Bank0 = Y0 >> 3;
    u8 Bank1 = Y1 >> 3;
    u8 Bit0 = Y0 & 7;
    u8 Bit1 = Y1 & 7;

    if (Bank0 == Bank1) {
        u8 Mask = ((0xFF << Bit0) & (0xFF >> (7 - Bit1)));
        u8* Row = Buffer + Bank0 * State->Width;

        for (u8 X = X0; X <= X1; ++X) 
            Row[X] |= Mask;
    } else {
        u8 Mask0 = 0xFF << Bit0;
        u8* Row0 = Buffer + Bank0 * State->Width;

        for (u8 X = X0; X <= X1; ++X) 
            Row0[X] |= Mask0;

        for (u8 Bank = Bank0 + 1; Bank < Bank1; ++Bank) {
            u8* Row = Buffer + Bank * State->Width;

            for (u8 X = X0; X <= X1; ++X) 
                Row[X] = 0xFF;
        }

        u8 Mask1 = 0xFF >> (7 - Bit1);
        u8* Row1 = Buffer + Bank1 * State->Width;

        for (u8 X = X0; X <= X1; ++X) 
            Row1[X] |= Mask1;
    }
}

NCUI_DEF NCUI_ATTR void 
DrawClearRect(UIState* State, u8* Buffer, u8 X0, u8 Y0, u8 X1, u8 Y1) 
{
    if (X0 > X1) 
        NCUI_SWAP(u8, X0, X1);

    if (Y0 > Y1) 
        NCUI_SWAP(u8, Y0, Y1);

    if (X0 >= State->Width || Y0 >= State->Height) 
        return;

    if (X1 >= State->Width) 
        X1 = State->Width - 1;

    if (Y1 >= State->Height) 
        Y1 = State->Height - 1;

    u8 Bank0 = Y0 >> 3;
    u8 Bank1 = Y1 >> 3;
    u8 Bit0 = Y0 & 7;
    u8 Bit1 = Y1 & 7;

    if (Bank0 == Bank1) {
        u8 Mask = ~((0xFF << Bit0) & (0xFF >> (7 - Bit1)));
        u8* Row = Buffer + Bank0 * State->Width;

        for (u8 X = X0; X <= X1; ++X) 
            Row[X] &= Mask;
    } else {
        u8 Mask0 = ~(0xFF << Bit0);
        u8* Row0 = Buffer + Bank0 * State->Width;

        for (u8 X = X0; X <= X1; ++X) 
            Row0[X] &= Mask0;

        for (u8 Bank = Bank0 + 1; Bank < Bank1; ++Bank) {
            u8* Row = Buffer + Bank * State->Width;

            for (u8 X = X0; X <= X1; ++X) 
                Row[X] = 0;
        }

        u8 Mask1 = ~(0xFF >> (7 - Bit1));
        u8* Row1 = Buffer + Bank1 * State->Width;

        for (u8 X = X0; X <= X1; ++X) 
            Row1[X] &= Mask1;
    }
}

NCUI_DEF NCUI_ATTR void 
DrawInvertRect(UIState* State, u8* Buffer, u8 X0, u8 Y0, u8 X1, u8 Y1) 
{
    if (X0 > X1) 
        NCUI_SWAP(u8, X0, X1);

    if (Y0 > Y1) 
        NCUI_SWAP(u8, Y0, Y1);

    if (X0 >= State->Width || Y0 >= State->Height) 
        return;

    if (X1 >= State->Width) 
        X1 = State->Width - 1;

    if (Y1 >= State->Height) 
        Y1 = State->Height - 1;

    u8 Bank0 = Y0 >> 3;
    u8 Bank1 = Y1 >> 3;
    u8 Bit0 = Y0 & 7;
    u8 Bit1 = Y1 & 7;

    if (Bank0 == Bank1) {
        u8 Mask = (0xFF << Bit0) & (0xFF >> (7 - Bit1));
        u8* Row = Buffer + Bank0 * State->Width;

        for (u8 X = X0; X <= X1; ++X) 
            Row[X] ^= Mask;
    } else {
        u8 Mask0 = 0xFF << Bit0;
        u8* Row0 = Buffer + Bank0 * State->Width;

        for (u8 X = X0; X <= X1; ++X) 
            Row0[X] ^= Mask0;

        for (u8 Bank = Bank0 + 1; Bank < Bank1; ++Bank) {
            u8* Row = Buffer + Bank * State->Width;

            for (u8 X = X0; X <= X1; ++X) 
                Row[X] ^= 0xFF;
        }

        u8 Mask1 = 0xFF >> (7 - Bit1);
        u8* Row1 = Buffer + Bank1 * State->Width;

        for (u8 X = X0; X <= X1; ++X) 
            Row1[X] ^= Mask1;
    }
}

NCUI_DEF NCUI_ATTR void 
DrawBorderRect(UIState* State, u8* Buffer, u8 X0, u8 Y0, u8 X1, u8 Y1) 
{
    DrawHorzLine(State, Buffer, X0, X1, Y0);
    DrawHorzLine(State, Buffer, X0, X1, Y1);
    DrawVertLine(State, Buffer, X0, Y0, Y1);
    DrawVertLine(State, Buffer, X1, Y0, Y1);
}

NCUI_DEF NCUI_ATTR void 
DrawChar(UIState* State, u8* Buffer, u8 X, u8 Y, char Char) 
{
    if (Char < NCUI_FONT_FIRST_CHAR || Char > NCUI_FONT_LAST_CHAR) 
        return;

    u8 const* Glyph = FONT_BYTES[Char - NCUI_FONT_FIRST_CHAR];
    u8 Bank = Y >> 3;
    u8 Bit = Y & 7;

    if (!Bit) {                                                                 // NOTE: Fast-path for bank-boundary aligned chars
        u8* Row = Buffer + Bank * State->Width + X;

        for (u8 Column = 0; Column < NCUI_FONT_GLYPH_WIDTH; ++Column) {
            if (X + Column >= State->Width) 
                break;

            Row[Column] |= Glyph[Column];
        }
    } else {                                                                    // NOTE: Character spans multiple display banks
        u8* TopRow = Buffer + Bank * State->Width + X;

        if (Bank + 1 < State->Banks) {
            u8* BottomRow = Buffer + (Bank + 1) * State->Width + X;

            for (u8 Column = 0; Column < NCUI_FONT_GLYPH_WIDTH; ++Column) {
                if (X + Column >= State->Width) 
                    break;

                TopRow[Column] |= (Glyph[Column] << Bit);
                BottomRow[Column] |= (Glyph[Column] >> (8 - Bit));
            }
        } else {
            for (u8 Column = 0; Column < NCUI_FONT_GLYPH_WIDTH; ++Column) {
                if (X + Column >= State->Width) 
                    break;

                TopRow[Column] |= (Glyph[Column] << Bit);
            }
        }
    }
}

NCUI_DEF NCUI_ATTR void 
DrawCharClipped(UIState* State, u8* Buffer, u8 X, u8 Y, char Char, UIRect Clip) 
{
    if (Char < NCUI_FONT_FIRST_CHAR || Char > NCUI_FONT_LAST_CHAR) 
        return;

    u8 const* Glyph = FONT_BYTES[Char - NCUI_FONT_FIRST_CHAR];
    u8 Bank = Y >> 3;
    u8 Bit = Y & 7;

    if (!Bit) {
        u8* Row = Buffer + Bank * State->Width + X;

        for (u8 Column = 0; Column < NCUI_FONT_GLYPH_WIDTH; ++Column) {
            u8 PX = X + Column;

            if (PX < Clip.X0 || PX > Clip.X1) 
                continue;

            if (PX >= State->Width) 
                break;

            Row[Column] |= Glyph[Column];
        }
    } else {
        u8* TopRow = Buffer + Bank * State->Width + X;

        if (Bank + 1 < State->Banks) {
            u8* BottomRow = Buffer + (Bank + 1) * State->Width + X;

            for (u8 Column = 0; Column < NCUI_FONT_GLYPH_WIDTH; ++Column) {
                u8 PX = X + Column;

                if (PX < Clip.X0 || PX > Clip.X1) 
                    continue;

                if (PX >= State->Width) 
                    break;

                TopRow[Column] |= (Glyph[Column] << Bit);
                BottomRow[Column] |= (Glyph[Column] >> (8 - Bit));
            }
        } else {
            for (u8 Column = 0; Column < NCUI_FONT_GLYPH_WIDTH; ++Column) {
                u8 PX = X + Column;

                if (PX < Clip.X0 || PX > Clip.X1) 
                    continue;

                if (PX >= State->Width) 
                    break;

                TopRow[Column] |= (Glyph[Column] << Bit);
            }
        }
    }
}

NCUI_DEF NCUI_ATTR void 
DrawCharInverted(UIState* State, u8* Buffer, u8 X, u8 Y, char Char) 
{
    if (Char < NCUI_FONT_FIRST_CHAR || Char > NCUI_FONT_LAST_CHAR) 
        return;

    u8 const* Glyph = FONT_BYTES[Char - NCUI_FONT_FIRST_CHAR];
    u8 Bank = Y >> 3;
    u8 Bit = Y & 7;

    if (!Bit) {
        u8* Row = Buffer + Bank * State->Width + X;

        for (u8 Column = 0; Column < NCUI_FONT_GLYPH_WIDTH; ++Column) {
            if (X + Column >= State->Width) 
                break;

            Row[Column] &= ~Glyph[Column];
        }
    } else {
        u8* TopRow = Buffer + Bank * State->Width + X;

        if (Bank + 1 < State->Banks) {
            u8* BottomRow = Buffer + (Bank + 1) * State->Width + X;

            for (u8 Column = 0; Column < NCUI_FONT_GLYPH_WIDTH; ++Column) {
                if (X + Column >= State->Width) 
                    break;

                TopRow[Column] &= ~(Glyph[Column] << Bit);
                BottomRow[Column] &= ~(Glyph[Column] >> (8 - Bit));
            }
        } else {
            for (u8 Column = 0; Column < NCUI_FONT_GLYPH_WIDTH; ++Column) {
                if (X + Column >= State->Width) 
                    break;

                TopRow[Column] &= ~(Glyph[Column] << Bit);
            }
        }
    }
}

NCUI_DEF NCUI_ATTR void 
DrawCharInvertedClipped(UIState* State, u8* Buffer, u8 X, u8 Y, char Char, UIRect Clip) 
{
    if (Char < NCUI_FONT_FIRST_CHAR || Char > NCUI_FONT_LAST_CHAR) 
        return;

    u8 const* Glyph = FONT_BYTES[Char - NCUI_FONT_FIRST_CHAR];
    u8 Bank = Y >> 3;
    u8 Bit = Y & 7;

    if (!Bit) {
        u8* Row = Buffer + Bank * State->Width + X;

        for (u8 Column = 0; Column < NCUI_FONT_GLYPH_WIDTH; ++Column) {
            u8 PX = X + Column;

            if (PX < Clip.X0 || PX > Clip.X1) 
                continue;

            if (PX >= State->Width) 
                break;

            Row[Column] &= ~Glyph[Column];
        }
    } else {
        u8* TopRow = Buffer + Bank * State->Width + X;

        if (Bank + 1 < State->Banks) {
            u8* BottomRow = Buffer + (Bank + 1) * State->Width + X;

            for (u8 Column = 0; Column < NCUI_FONT_GLYPH_WIDTH; ++Column) {
                u8 PX = X + Column;

                if (PX < Clip.X0 || PX > Clip.X1) 
                    continue;

                if (PX >= State->Width) 
                    break;

                TopRow[Column] &= ~(Glyph[Column] << Bit);
                BottomRow[Column] &= ~(Glyph[Column] >> (8 - Bit));
            }
        } else {
            for (u8 Column = 0; Column < NCUI_FONT_GLYPH_WIDTH; ++Column) {
                u8 PX = X + Column;

                if (PX < Clip.X0 || PX > Clip.X1) 
                    continue;

                if (PX >= State->Width) 
                    break;

                TopRow[Column] &= ~(Glyph[Column] << Bit);
            }
        }
    }
}

NCUI_DEF NCUI_ATTR void 
DrawStr(UIState* State, u8* Buffer, u8 X, u8 Y, char const* String) 
{
    if (!String)
        return;

    for (
        u8 Index = 0; 
        String[Index] && X < State->Width; 
        ++Index, X += NCUI_FONT_ADVANCE
    ) {
        DrawChar(State, Buffer, X, Y, String[Index]);
    }
}

NCUI_DEF NCUI_ATTR void 
DrawStrClipped(
    UIState* State, 
    u8* Buffer, 
    u8 X, 
    u8 Y, 
    char const* String, 
    UIRect Clip
) {
    if (!String)
        return;

    for (
        u8 Index = 0; 
        String[Index] && X < State->Width; 
        ++Index, X += NCUI_FONT_ADVANCE
    ) {
        if (X + NCUI_FONT_GLYPH_WIDTH <= Clip.X0) 
            continue;

        if (X > Clip.X1) 
            break;

        DrawCharClipped(State, Buffer, X, Y, String[Index], Clip);
    }
}

NCUI_DEF NCUI_ATTR void 
DrawStrInverted(UIState* State, u8* Buffer, u8 X, u8 Y, char const* String) 
{
    if (!String)
        return;

    for (
        u8 Index = 0; 
        String[Index] && X < State->Width; 
        ++Index, X += NCUI_FONT_ADVANCE
    ) {
        DrawCharInverted(State, Buffer, X, Y, String[Index]);
    }
}

NCUI_DEF NCUI_ATTR void 
DrawStrInvertedClipped(
    UIState* State, 
    u8* Buffer, 
    u8 X, 
    u8 Y, 
    char const* String, 
    UIRect Clip
) {
    if (!String)
        return;

    for (
        u8 Index = 0; 
        String[Index] && X < State->Width; 
        ++Index, X += NCUI_FONT_ADVANCE
    ) {
        if (X + NCUI_FONT_GLYPH_WIDTH <= Clip.X0) 
            continue;

        if (X > Clip.X1) 
            break;

        DrawCharInvertedClipped(State, Buffer, X, Y, String[Index], Clip);
    }
}

NCUI_DEF NCUI_ATTR void 
DrawStrAligned(
    UIState* State, 
    u8* Buffer, 
    u8 X0, 
    u8 X1, 
    u8 Y, 
    char const* String, 
    u8 Align
) {
    if (!String)
        return;

    u8 Width = FontStrWidth(String);
    u8 X;

    switch (Align) {
        default:
        case 0: {
            X = X0; 
        } break;

        case 1: {
            X = X0 + (((X1 - X0) - Width) >> 1);
        } break;

        case 2: {
            X = X1 - Width; 
        } break;
    }

    DrawStr(State, Buffer, X, Y, String);
}

NCUI_DEF NCUI_ATTR void 
DrawBMP(
    UIState* State, 
    u8* Buffer, 
    u8 X, 
    u8 Y, 
    u8 Width, 
    u8 Height, 
    u8 const* Data
) {
    u8 Banks = (Height + 7) >> 3;
    u8 Bit = Y & 7;
    u8 Bank = Y >> 3;

    for (u8 B = 0; B < Banks && (Bank + B) < State->Banks; ++B) {
        u8* Dst = Buffer + (Bank + B) * State->Width + X;
        u8 const* Src = Data + B * Width;

        if (!Bit) {
            for (
                u8 Column = 0; 
                Column < Width && (X + Column) < State->Width; 
                ++Column
            ) {
                Dst[Column] |= Src[Column];
            }
        } else {
            for (
                u8 Column = 0; 
                Column < Width && (X + Column) < State->Width; 
                ++Column
            ) {
                Dst[Column] |= Src[Column];

                if ((Bank + B + 1) < State->Banks) {
                    Buffer[
                        (Bank + B + 1) * State->Width + X + Column
                    ] |= (Src[Column] >> (8 - Bit));
                }
            }
        }
    }
}

NCUI_DEF void 
DrawUI(UIState* State, u8* Buffer) 
{
    ClearDisplay(State, Buffer);

    for (u8 SlotIndex = 0; SlotIndex < NCUI_BOX_HASH_SLOTS; ++SlotIndex) {
        u8 BoxIndex = State->HashSlots[SlotIndex].Head;

        while (BoxIndex != EMPTY_UI_INDEX_VALUE) {
            UIBox* Box = &State->Boxes[BoxIndex];

            if (Box->TailBuildIndex + NCUI_STALE_FRAMES >= State->BuildIndex) {
                UIRect Clip = Box->ClipRect;

                if (!UIRectIsValid(Clip)) {
                    BoxIndex = Box->HashNext;
                    continue;
                }

                UIRect Rect = Box->Rect;
                u8 X0 = NCUI_MAX(Rect.X0, Clip.X0);
                u8 Y0 = NCUI_MAX(Rect.Y0, Clip.Y0);
                u8 X1 = NCUI_MIN(Rect.X1, Clip.X1);
                u8 Y1 = NCUI_MIN(Rect.Y1, Clip.Y1);

                if (X0 > X1 || Y0 > Y1) {
                    BoxIndex = Box->HashNext;
                    continue;
                }

                if (
                    Box->Flags & UI_BOX_FLAG_INVERTED || 
                    Box->Flags & UI_BOX_FLAG_DRAW_FILL
                ) {
                    DrawFilledRect(State, Buffer, X0, Y0, X1, Y1);
                }

                if (Box->Flags & UI_BOX_FLAG_DRAW_BORDER) {
                    DrawBorderRect(State, Buffer, X0, Y0, X1, Y1);
                }

                if (Box->Flags & UI_BOX_FLAG_DRAW_DIVIDER) {
                    Axis2D ParentAxis = AXIS_2D_Y;

                    if (Box->Parent != EMPTY_UI_INDEX_VALUE)
                        ParentAxis = State->Boxes[Box->Parent].ChildLayoutAxis;

                    if (ParentAxis == AXIS_2D_Y) {
                        u8 MidY = Y0 + ((Y1 - Y0) >> 1);

                        if ((Box->Flags & UI_BOX_FLAG_DRAW_TEXT) && Box->String) {
                            u8 TextWidth = FontStrWidth(Box->String);

                            if (X0 + TextWidth + 2 <= X1) {
                                if (Box->Flags & UI_BOX_FLAG_INVERTED)
                                    ClearHorzLine(State, Buffer, X0 + TextWidth + 2, X1, MidY);
                                else
                                    DrawHorzLine(State, Buffer, X0 + TextWidth + 2, X1, MidY);
                            }
                        } else {
                            if (Box->Flags & UI_BOX_FLAG_INVERTED)
                                ClearHorzLine(State, Buffer, X0, X1, MidY);
                            else
                                DrawHorzLine(State, Buffer, X0, X1, MidY);
                        }
                    } else {
                        u8 MidX = X0 + ((X1 - X0) >> 1);

                        if (Box->Flags & UI_BOX_FLAG_INVERTED)
                            ClearVertLine(State, Buffer, MidX, Y0, Y1);
                        else
                            DrawVertLine(State, Buffer, MidX, Y0, Y1);
                    }
                }

                if ((Box->Flags & UI_BOX_FLAG_DRAW_TEXT) && Box->String) {
                    u8 BoxHeight = Rect.Y1 - Rect.Y0 + 1;
                    u8 TextY = Rect.Y0;

                    if (BoxHeight > NCUI_FONT_GLYPH_HEIGHT)
                        TextY += (BoxHeight - NCUI_FONT_GLYPH_HEIGHT) >> 1;

                    u8 TextX = Rect.X0 + 1;

                    if (Box->Flags & UI_BOX_FLAG_INVERTED)
                        DrawStrInvertedClipped(State, Buffer, TextX, TextY, Box->String, Clip);
                    else
                        DrawStrClipped(State, Buffer, TextX, TextY, Box->String, Clip);
                }
            }

            BoxIndex = Box->HashNext;
        }
    }
}
#endif // NCUI_IMPLEMENTATION
