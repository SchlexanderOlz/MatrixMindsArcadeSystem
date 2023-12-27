#ifndef MOVESTATEITER 
#define MOVESTATEITER

#define N_STATES 4

#include <vector>
#include <array>

#include "Block.hpp"
#include "MoveState.hpp"

using namespace std;

namespace tetris {
  class MoveStateIterator {
    private:
      size_t idx;
      vector<MoveState> blocks;
    public:
      MoveStateIterator(vector<MoveState> states) : idx(0), blocks(states) {}

      MoveState& operator *() {
        return this->blocks[this->idx];
      }
      
      const MoveState& current() const {
        return this->blocks[this->idx];
      }

      MoveStateIterator& operator++() {
        this->idx = (this->idx + 1) % blocks.size();
        return *this;
      }

      MoveStateIterator& operator--() {
        if ((int)(this->idx) - 1 < 0) this->idx = blocks.size() - 1;
        else this->idx -= 1;
        return *this;
      }
  };
}

#endif
