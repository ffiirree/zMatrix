#ifndef ALCHEMY_CORE_DEFS_H
#define ALCHEMY_CORE_DEFS_H

namespace alchemy {

// Type value
#define TYPE_DEFAULT    (-1)
#define TYPE_UINT8      0
#define TYPE_INT8       1
#define TYPE_UINT16     2
#define TYPE_INT16      3
#define TYPE_UINT32     4
#define TYPE_INT32      5
#define TYPE_UINT64     6
#define TYPE_INT64      7
#define TYPE_FLOAT      8
#define TYPE_DOUBLE     9

#define TYPE_COMPLEX    10
#define TYPE_POINT      11
#define TYPE_POINT3     12
#define TYPE_RECT       13
#define TYPE_VEC        14
#define TYPE_SIZE       15
#define TYPE_MATRIX     16
#define TYPE_SCALAR     17

// Type of boundary processing.
enum BorderTypes {
    BORDER_CONSTANT,                        //!< `iiiiii|abcdefgh|iiiiiii`  with some specified `i`
    BORDER_REPLICATE,                       //!< `aaaaaa|abcdefgh|hhhhhhh`
    BORDER_REFLECT,                         //!< `fedcba|abcdefgh|hgfedcb`
    BORDER_WRAP,                            //!< `cdefgh|abcdefgh|abcdefg`
    BORDER_REFLECT_101,                     //!< `gfedcb|abcdefgh|gfedcba`
    BORDER_TRANSPARENT,                     //!< `uvwxyz|absdefgh|ijklmno`
    BORDER_DEFAULT = BORDER_REFLECT_101,    //!< same as BORDER_REFLECT_101
};

enum ImageFormat {
    JPEG = 0x01, GIF, PNG, WEBP
};

// Method of boundary processing.
#define BORDER_REPLICATE_CALLBACK(src)  [&](int &_i, int &_j) { \
        _i < 0 ? _i = 0 : _i >= (src).rows_ ? _i = (src).rows_ - 1 : 0;   \
        _j < 0 ? _j = 0 : _j >= (src).cols_ ? _j = (src).cols_ - 1 : 0;   \
    }

#define BORDER_REFLECT_CALLBACK(src) [&](int &_i, int &_j) {\
        _i < 0 ? _i = -_i - 1 : _i >= (src).rows_ ? _i = (src).rows_ - 1 - (_i - (src).rows_) : 0;\
        _j < 0 ? _j = -_j - 1 : _j >= (src).cols_ ? _j = (src).cols_ - 1 - (_j - (src).cols_) : 0;\
    }

#define BORDER_WRAP_CALLBACK(src) [&](int &_i, int &_j) {\
        _i < 0 ? _i = (src).rows_ + _i : _i >= (src).rows_ ? _i = _i - (src).rows_ : 0;\
        _j < 0 ? _j = (src).cols_ + _j : _j >= (src).cols_ ? _j = _j - (src).cols_ : 0;\
    }

#define BORDER_DEFAULT_CALLBACK(src) [&](int &_i, int &_j) {\
        _i < 0 ? _i = -_i : _i >= (src).rows_ ? _i = (src).rows_ - 2 - (_i - (src).rows_) : 0;\
        _j < 0 ? _j = -_j : _j >= (src).cols_ ? _j = (src).cols_ - 2 - (_j - (src).cols_) : 0;\
    }

/**
 * \ 颜色空间转换
 */
enum
{
    BGR2GRAY = 0,
    BGR2RGB,
    BGR2HSV,
    BGR2HSI,
};

/**
 * \ 形态学滤波方式
 */
enum {
    MORP_ERODE = 0,
    MORP_DILATE,
    MORP_OPEN,
    MORP_CLOSE,
    MORP_TOPHAT,
    MORP_BLACKHAT,
    MORP_GRADIENT
};

/**
 * \ 单通道固定阈值方式
 */
enum {
    THRESH_BINARY,
    THRESH_BINARY_INV,
    THRESH_TRUNC,
    THRESH_TOZERO,
    THRESH_TOZERO_INV,
};

};

#endif //! ALCHEMY_CORE_DEFS_H
