/**
 * OMTProtocol.h - OMT Protocol Structures
 * Port of libomtnet frame header structures
 */

#ifndef OMT_PROTOCOL_H
#define OMT_PROTOCOL_H

#include <cstdint>

namespace omt {

#pragma pack(push, 1)

/**
 * Frame header - 16 bytes
 * Port of OMTFrame header structure
 */
struct FrameHeader {
    uint8_t version;           // Always 1
    uint8_t frameType;         // 1=Metadata, 2=Video, 4=Audio (per official spec)
    int64_t timestamp;         // Timestamp in 100ns ticks
    uint16_t metadataLength;   // Length of metadata
    int32_t dataLength;        // Includes extended header + payload
    
    static constexpr int SIZE = 16;
};

/**
 * Video extended header - 32 bytes
 * Contains video-specific information
 */
struct VideoExtHeader {
    int32_t codec;             // Codec fourCC (e.g., VMX1 = 0x31584D56)
    int32_t width;
    int32_t height;
    int32_t frameRateN;        // Numerator
    int32_t frameRateD;        // Denominator
    float aspectRatio;
    int32_t flags;             // OMTVideoFlags
    int32_t colorSpace;        // OMTColorSpace
    
    static constexpr int SIZE = 32;
};

/**
 * Audio extended header - 24 bytes
 * Field order per official OMT PROTOCOL.md:
 * Codec, SampleRate, SamplesPerChannel, Channels, ActiveChannels, Reserved1
 */
struct AudioExtHeader {
    int32_t codec;             // Codec fourCC ('FPA1')
    int32_t sampleRate;        // e.g. 48000
    int32_t samplesPerChannel; // Samples per channel in this frame
    int32_t channels;          // Total channel count
    uint32_t activeChannels;   // Bit field of channels actually stored
    int32_t reserved1;         // Reserved, must be 0
    
    static constexpr int SIZE = 24;
};

#pragma pack(pop)

// Codec FourCC values
namespace Codec {
    constexpr int32_t VMX1 = 0x31584D56;  // "VMX1"
    constexpr int32_t UYVY = 0x59565955;  // "UYVY"
    constexpr int32_t YUY2 = 0x32595559;  // "YUY2"
    constexpr int32_t NV12 = 0x3231564E;  // "NV12"
    constexpr int32_t BGRA = 0x41524742;  // "BGRA"
    constexpr int32_t PCM_F32 = 0x32334650; // "FP32" (legacy, incorrect - do not use)
    constexpr int32_t FPA1 = 0x31415046;    // "FPA1" 32-bit float planar audio (official OMT)
}

// Video flags
namespace VideoFlags {
    constexpr int32_t None = 0;
    constexpr int32_t Interlaced = 1;
    constexpr int32_t Alpha = 2;
    constexpr int32_t HighBitDepth = 4;
    constexpr int32_t Preview = 8;
}

// Color space
namespace ColorSpace {
    constexpr int32_t Unknown = 0;
    constexpr int32_t BT601 = 1;
    constexpr int32_t BT709 = 2;
    constexpr int32_t BT2020 = 3;
}

} // namespace omt

#endif // OMT_PROTOCOL_H
