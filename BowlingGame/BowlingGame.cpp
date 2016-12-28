#include "BowlingGame.h"

//get number of pins per frame
//count progressively score  
void BowlingGame::roll(int nbOfPins)
{
  assert(nbOfPins <= MAX_PINS);

  Frame& frame = getFrame();

  frame.setScore(nbOfPins);

  if(isBonusFrame())
  {
    const Frame& previousFrame = getPreviousFrame();
    if(previousFrame.isSpare())
    {
      frame.limitToOneAttempt();
    }
  }
}

//need to be called to compute score and add it to totalScore
int BowlingGame::score()
{
  int score = 0 ;
  if(frameCounter_ == 0)
  {
    score = frames_[0].score();
  }
  else
  {
    const Frame& prev = getPreviousFrame();
    const Frame& curr = getCurrentFrame();

    score = curr.score();
    if(isBonusFrame())
    {
      //no extra points
    }
    else if(prev.isSpare() && curr.getFirstScore())
    {
      score += curr.getFirstScore();
    }
    else if(prev.isStrike())
    {
      score += curr.getFirstScore() + curr.getSecondScore();
    }

    //check if it is the third strike, score will be triple
    if(isThirdConsecutiveStrike())
    {
      score += curr.score();
    }
  }

  totalScore_ += score;

  return score;
}


bool BowlingGame::isOver() const
{
  const Frame& curr = getCurrentFrame();
  if( !curr.isStrike() && !curr.isSpare() && frameCounter_ >= MAX_FRAMES -1 )
    return true;

return false;
}

Frame& BowlingGame::getFrame()
{
  //can get maximum MAX_FRAMES + 2 frames (in case of strikes)
  assert( frameCounter_ < MAX_FRAMES + 2 );
  
const Frame& frame = getCurrentFrame();
  if( frame.isDone() )
  {
    frameCounter_++;
  }
  return frames_[frameCounter_];
}

bool BowlingGame::isThirdConsecutiveStrike() const
{
  if( frameCounter_ < 2)
    return false;

  const Frame& curr    = getCurrentFrame();
  const Frame& prev    = getPreviousFrame();
  const Frame& twoPrev = getTwoPreviousFrame();

  if( curr.isStrike() &&
      prev.isStrike() &&
      twoPrev.isStrike() &&
      ( !curr.isBonus() || isLastBonusFrame()) )
    return true;

  return false;
}
