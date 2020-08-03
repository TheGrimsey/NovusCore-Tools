#include "MOMT.h"
#include "../../ChunkHeader.h"
#include "../../../Wrappers/WMO_ROOT.h"

bool MOMT::Read(std::shared_ptr<Bytebuffer>& buffer, const ChunkHeader& header, WMO_ROOT& wmo)
{
    size_t num = header.size / sizeof(MOMT);
    if (num == 0)
        return true;

    wmo.momts.reserve(num);
    for (size_t i = 0; i < num; i++)
    {
        MOMT& mddf = wmo.momts.emplace_back();
        if (!buffer->Get(mddf))
        {
            assert(false);
            return false;
        }
    }

    return true;
}