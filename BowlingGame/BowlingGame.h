#ifndef _BOWLING_GAME_H_
#define _BOWLING_GAME_H_

#include "Settings.h"
#include "Frame.h"
#include <vector>
#include <assert.h>

class BowlingGame
{
 public:
  BowlingGame():
      frames_(MAX_FRAMES + 2) //2 more for bonus
    , frameCounter_(0)
    , totalScore_(0)
  {
    //mark 2 last frames as bonus frames
    frames_[MAX_FRAMES].setIsBonus(true);
    frames_[MAX_FRAMES + 1].setIsBonus(true);
  }
  ~BowlingGame(){}

  int getTotalScore() const { return totalScore_; }

  void roll(int nbOfPins);
  int  score();

  bool isOver() const;

 private:
  Frame& getFrame();

  const Frame& getTwoPreviousFrame() const { assert(frameCounter_ >= 2); return frames_[frameCounter_ - 2]; }
  const Frame& getPreviousFrame()    const { assert(frameCounter_ >= 1); return frames_[frameCounter_ - 1]; }
  const Frame& getCurrentFrame()     const { assert(frameCounter_ <= MAX_FRAMES + 1); return frames_[frameCounter_]; }

  bool isBonusFrame()     const { return frameCounter_ >= MAX_FRAMES; }
  bool isLastBonusFrame() const { return frameCounter_ == MAX_FRAMES + 1; }
  bool isLastFrame()      const { return frameCounter_ == MAX_FRAMES-1; }

  bool isThirdConsecutiveStrike() const;

 private:
  std::vector<Frame> frames_;
  int                frameCounter_;
  int                totalScore_;
};

#endif
