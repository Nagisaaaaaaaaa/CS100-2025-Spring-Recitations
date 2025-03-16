//! `assert` will save you 95% of your debugging time.
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

//! We have to use macros to define constants before C23 or C++11.
//! In order to make it safer, please use a consistent naming style,
//! such as `cSomeName`, `c_some_name`, `PREFIX_SOME_NAME`, etc.
#define cN 15  // N = Number.
#define cB 'X' // B = Black.
#define cW 'O' // W = White.
#define cE '.' // E = Empty.

//
//
//
//* For 2D problems, define `Vec` to make life easier.
typedef struct {
  int x, y;
} Vec;

Vec Add(Vec a, Vec b) {
  return (Vec){a.x + b.x, a.y + b.y};
}

Vec Mul(Vec a, int b) {
  return (Vec){a.x * b, a.y * b};
}

//
//
//
//! It is not bad to use global variables for homework, but
//! please always use `static`.
static char flags[cN][cN];

bool IsValid(Vec pos) {
  return pos.x >= 0 && pos.x < cN && pos.y >= 0 && pos.y < cN;
}

char At(Vec pos) {
  assert(IsValid(pos)); //! `assert` will find the index-out-of-range bug.
  return flags[pos.y][pos.x];
}

char *AtPtr(Vec pos) {
  assert(IsValid(pos)); //! `assert` will find the index-out-of-range bug.
  return &flags[pos.y][pos.x];
}

//
//
//
//* I personally prefer to name help functions with a suffix, such as `_AtDir`.
bool IsAlreadyWin_AtDir(Vec pos, Vec dir) {
  assert(IsValid(pos)); //! `assert` will find the index-out-of-range bug.

  bool res = true;

  //! It's better to use a loop, instead of making duplicates.
  //! Copy-paste is usually error prone.
  for (int i = 0; i < 5; ++i) {
    //* I personally use the suffix `1`, `2`, etc. to name the temporary variables in loops.
    //* You will never forget that `pos` has some relationships with `pos1`.
    Vec pos1 = Add(pos, Mul(dir, i));
    if (IsValid(pos1)) {
      // ...
    }
  }

  return res;
}

bool IsAlreadyWin(Vec pos) {
  assert(IsValid(pos)); //! `assert` will find the index-out-of-range bug.

  //! There will be too many duplicates without the help function, `IsAlreadyWin_AtDir`.
  //! Copy-paste is usually error prone.
  return IsAlreadyWin_AtDir(pos, (Vec){-1, -1}) && //
         IsAlreadyWin_AtDir(pos, (Vec){0, -1}) &&  //
         IsAlreadyWin_AtDir(pos, (Vec){1, -1}) &&  //

         IsAlreadyWin_AtDir(pos, (Vec){-1, 0}) && //
         IsAlreadyWin_AtDir(pos, (Vec){1, 0}) &&  //

         IsAlreadyWin_AtDir(pos, (Vec){-1, 1}) && //
         IsAlreadyWin_AtDir(pos, (Vec){0, 1}) &&  //
         IsAlreadyWin_AtDir(pos, (Vec){1, 1});
}

//
//
//
void SwapInts(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

//
//
//
//! Always compile with `gcc -Wall -Wextra -Wpedantic main.c` for homework.
int main(void) {
  //! I personally prefer the following naming style.
  //! `nBs` means number of blacks, where
  //!   `n`: number of,
  //!   `B`: black,
  //!   `s`: the plural.
  int nBs = 0;
  //! `nWs` means number of whites.
  int nWs = 0;

  //! Never use `i, j`    for 2D loops, always use `y, x`    instead.
  //! Never use `i, j, k` for 3D loops, always use `z, y, x` instead.
  //! When you accidentally type "j" as "i," you'll never notice it!
  for (int y = 0; y < cN; ++y)
    for (int x = 0; x < cN; ++x) {
      Vec pos = {x, y};
      scanf(" %c", AtPtr(pos));
      //! `assert` will find the bug if you failed to write the correct `scanf`.
      assert(At(pos) == cB || At(pos) == cW || At(pos) == cE);

      if (At(pos) == cB)
        ++nBs;
      else if (At(pos) == cW)
        ++nWs;
    }
  //! `assert` will find the bug if you failed to correctly compute `nBs` and `nWs`.
  assert(nBs == nWs || nBs == nWs + 1);
  bool isRoundBlack = nBs == nWs;

  //! Swap black and white if this is white's round.
  //! This will save your 50% codes.
  if (!isRoundBlack) {
    //! Again, always use `y, x` for 2D loops.
    for (int y = 0; y < cN; ++y)
      for (int x = 0; x < cN; ++x) {
        Vec pos = {x, y};

        // Swap flags.
        if (At(pos) == cB)
          *AtPtr(pos) = cW;
        else if (At(pos) == cW)
          *AtPtr(pos) = cB;

        // Swap numbers.
        SwapInts(&nBs, &nWs);
      }
  }

  return 0;
}
