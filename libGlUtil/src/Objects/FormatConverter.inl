// #include "Objects.hpp"

// template <>
// void *glutil::Texture::FormatConverter<1>::operator()(uint8_t *target, uint32_t value) const
// {
//     *target = value & 0x000000ff;

//     return target + 1;
// }

// template <>
// void *glutil::Texture::FormatConverter<2>::operator()(uint8_t *target, uint32_t value) const
// {
//     *(reinterpret_cast<uint16_t *>(target)) = static_cast<uint16_t>(value & 0x0000ffff);

//     return target + 2;
// }

// template <>
// void *glutil::Texture::FormatConverter<3>::operator()(uint8_t *target, uint32_t value) const
// {
//     target[0] = static_cast<uint8_t>(value & 0x000000ff);
//     target[1] = static_cast<uint8_t>(value & 0x0000ff00);
//     target[2] = static_cast<uint8_t>(value & 0x00ff0000);

//     return target + 3;
// }

// template <>
// void *glutil::Texture::FormatConverter<4>::operator()(uint8_t *target, uint32_t value) const
// {
//     *(reinterpret_cast<uint32_t *>(target)) = value;

//     return target + 4;
// }

// // template <uint PChannels>
// // void *glutil::Texture::FormatConverter<PChannels>::operator()(uint8_t *target, uint32_t value) const
// // {
// //     *(reinterpret_cast<uint32_t *>(target)) = value;

// //     return target + PChannels;
// // }