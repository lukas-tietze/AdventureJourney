#include "Objects.hpp"

template <uint PChannels>
void *glutil::Texture::FormatConverter<PChannels>::operator()(uint8_t *target, uint32_t value) const
{
    *(reinterpret_cast<uint32_t *>(target)) = value;

    return target + PChannels;
}