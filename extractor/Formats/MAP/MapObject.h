/*
# MIT License
# Copyright(c) 2018-2020 NovusCore
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files(the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions :
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
*/
#pragma once
#include <NovusTypes.h>

#pragma pack(push, 1)
struct MapObjectHeader
{
    u32 token = 7236975; // UTF8 -> Binary -> Decimal for "nmo"
    u32 version = 4;
};

struct MapObjectVertex
{
    hvec3 position = hvec3(static_cast<f16>(0.0f));
    u8 octNormal[2] = { 0, 0 };
    hvec4 uv = hvec4(static_cast<f16>(0.0f));
}; // 16 bytes

struct RenderBatch
{
    u32 startIndex;
    u16 indexCount;
    u8 materialID;
};

struct CullingData
{
    hvec3 minBoundingBox = hvec3(static_cast<f16>(100000.0f));
    hvec3 maxBoundingBox = hvec3(static_cast<f16>(-100000.0f));
    f32 boundingSphereRadius = 0.0f;
}; // 16 bytes

struct MapObject
{
    MapObjectHeader header;

    std::vector<MapObjectVertex> vertices;
    std::vector<RenderBatch> renderBatches;
    std::vector<CullingData> cullingData;
};
#pragma pack(pop)