#pragma once

#include <cereal/archives/binary.hpp>
#include <cereal/cereal.hpp>
#include <fstream>

using input_archive = cereal::BinaryInputArchive;
using output_archive = cereal::BinaryOutputArchive;

template <typename T>
inline void serialize_save(const char* file, T&& object)
{
  std::ofstream stream{file, std::ios::binary};
  output_archive archive{stream};

  archive(object);
}

template <typename T>
inline auto serialize_create(const char* file) -> T
{
  std::ifstream stream{file, std::ios::binary};
  input_archive archive{stream};

  T object;
  archive(object);

  return object;
}