#pragma once

#include <cstdint>
#include <vector> 

class buffer_t
{
  public:
    buffer_t() = default;

  public:
    void Resize( uint32_t rows, uint32_t columns );

  private:
    uint32_t _rows{ 0 };
    uint32_t _columns{ 0 };

    std::vector<uint32_t> _data{};
};
