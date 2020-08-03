#pragma once
#include <NovusTypes.h>
#include <Utils/ByteBuffer.h>

struct WMO_ROOT;
struct ChunkHeader;
struct MODN
{
    u32 size = 0;
    u8* doodadNames = nullptr;

    static bool Read(std::shared_ptr<Bytebuffer>& buffer, const ChunkHeader& header, WMO_ROOT& wmo);
};