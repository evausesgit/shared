#ifndef _BOWLING_GAME_H_
#define _BOWLING_GAME_H_

#include "Settings.h"
#include "Frame.h"
#include <vector>
#include <string>
#include <assert.h>

class BowlingGame
{
 public:
  BowlingGame();
  ~BowlingGame(){}

  //to sort player according to their totalScore
  bool operator<( const BowlingGame & b) const { return this->getTotalScore() < b.getTotalScore(); }

  //playerName
  void setPlayerName(const std::string& name) { playerName_ = name; }
  const std::string& getPlayerName() const { return playerName_; }

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
  std::string        playerName_;
};
typedef std::vector<BowlingGame>       BowlingGames;
typedef BowlingGames::iterator         BowlingGamesIt;
typedef BowlingGames::reverse_iterator BowlingGamesReverseIt;
#endif
