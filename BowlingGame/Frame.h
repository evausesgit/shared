#ifndef _BOWLING_GAME_FRAME_H_
#define _BOWLING_GAME_FRAME_H_
#include "Settings.h"
#include <vector>
#include <numeric>
#include <assert.h>

class Frame
{
 public:
  Frame():
    nbOfAttemps_(0)
    , scores_()
    , isBonus_(false)
  {
    scores_[0] = 0;
    scores_[01] = 0;
  }
  ~Frame(){}

  void setScore(int nbOfPins) { assert(nbOfAttemps_ < MAX_ATTEMPTS_PER_FRAME); scores_[nbOfAttemps_++] = nbOfPins; };

  bool isDone()   const { return nbOfAttemps_ == MAX_ATTEMPTS_PER_FRAME || score() == MAX_PINS; }

  bool isSpare()  const { return scores_[0] + scores_[1] == MAX_PINS && 
                                 scores_[0] != MAX_PINS &&
                                 scores_[1] != MAX_PINS; }
  bool isStrike() const { return scores_[0] + scores_[1] == MAX_PINS && 
                                (scores_[0] == MAX_PINS ||
                                 scores_[1] == MAX_PINS); }

  bool isBonus() const { return isBonus_; }
  void setIsBonus(bool isBonus) { isBonus_ = isBonus; }

  int score()          const { return scores_[0] + scores_[1]; }
  int getFirstScore()  const { return scores_[0]; }
  int getSecondScore() const { return scores_[1]; }

  void limitToOneAttempt() { assert(nbOfAttemps_ < MAX_ATTEMPTS_PER_FRAME); nbOfAttemps_++; scores_[1] = 0;}

 private:
  int  nbOfAttemps_;
  int  scores_[MAX_ATTEMPTS_PER_FRAME];
  bool isBonus_;
};

#endif 
