/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2017-2021. All rights reserved.
 * Description:  A helper class of texture image's pixel data bit alignment
 */
#include <cstddef>
#include <cstdint>

#ifndef VMI_PIXEL_DATA_ALIGNMENT_H
#define VMI_PIXEL_DATA_ALIGNMENT_H

enum VmiPixelDataBitAlignment : int32_t {
    BIT_1 = (1 << 0),
    BIT_2 = (1 << 1),
    BIT_3 = (1 << 2),
    BIT_4 = (1 << 3),
};

struct AlignmentTexImgInfo {
    int32_t width = 0;
    int32_t height = 0;
    uint32_t format = 0;
    uint32_t type = 0;
    bool pack = false;
    int32_t depth = 1;
};

class VmiPixelDataAlignment {
public:
    /**
     * @brief: Gets the size of a row
     * @param [in]width: texture image width
     * @param [in]pixelSize: texture image height
     * @param [in]pack: unpack or not
     * @return: the size of a row
    */
    size_t PitchSize(int32_t width, size_t pixelSize, bool pack) const;

    /**
     * @brief: get the memory offset for pack or unpack case
     * @param [in]pitchSize: pitch size
     * @param [in]pixelSize: pixel size
     * @param [in]height: image height
     * @param [in]pack: true for packed
     * @return: memory offset for pack or unpack case
    */
    int32_t OffsetSize(int32_t pitchSize, int32_t pixelSize, int32_t height, bool pack) const;

    /**
     * @brief: get the bit aligned pixel size of 2D texture image
     *         all the parameters are comming from OpenGLES API
     * @param [in]texImgInfo: texture image info
     * @return: bit aligned pixel size
    */
    size_t AlignedSize(AlignmentTexImgInfo &texImgInfo) const;

    bool IsBitSize(int32_t value) const;

    /**
     * @brief: set the bit alignment mode for pack and unpack case
     * @param [in] param: pack or unpack alignment case
     * @param [in] value: bit alignment mode
    */
    void SetAlignment(uint32_t param, int32_t value);

    int32_t GetUnpackRowLen(void) const;
private:
    int32_t m_packAlignment = VmiPixelDataBitAlignment::BIT_3;
    int32_t m_unpackAlignment = VmiPixelDataBitAlignment::BIT_3;
    int32_t m_packRowLength = 0;
    int32_t m_unpackRowLength = 0;
    int32_t m_unpackImageHeight = 0;
    int32_t m_packSkipPixels = 0;
    int32_t m_unpackSkipPixels = 0;
    int32_t m_packSkipRows = 0;
    int32_t m_unpackSkipRows = 0;
    int32_t m_unpackSkipImages = 0;
};

#endif