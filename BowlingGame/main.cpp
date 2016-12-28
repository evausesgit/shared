#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <time.h>
#include "Frame.h"
#include "BowlingGame.h"	

#define ASSERT_EQUAL(a, b) { if(!(a == b)) { std::cerr << "ASSERT FAILED: " << a << " != " << b << " @ " << __PRETTY_FUNCTION__ << " (" << __LINE__ << ")" << std::endl; } else std::cout << std::left << std::setw(30) << " OK" << std::endl; }

int current_time_nanoseconds(){
    struct timespec tm;
    clock_gettime(CLOCK_REALTIME, &tm);
    return tm.tv_nsec;
}
void testStrike()
{
  std::cout << std::left << std::setw(30) << __PRETTY_FUNCTION__ << std::endl;
  BowlingGame game;
  game.roll(10);
  game.score();
  ASSERT_EQUAL( game.getTotalScore(), 10 );

  game.roll(1);
  game.roll(1);
  game.score();

  ASSERT_EQUAL( game.getTotalScore(), 14 );
}

void testAllStrike()
{
  std::cout << std::left << std::setw(30) << __PRETTY_FUNCTION__ << std::endl;
  BowlingGame game;
  for(int i = 0; i < MAX_FRAMES+2; ++i)
  {
    game.roll(10);
    game.score();
  }
  ASSERT_EQUAL( game.getTotalScore(), MAX_SCORE );
}

void testSpare()
{
  std::cout << std::left << std::setw(30) << __PRETTY_FUNCTION__ << std::endl;
  BowlingGame game;
  game.roll(9);
  game.roll(1);
  ASSERT_EQUAL(game.score(), 10);
  game.roll(1);
  game.roll(1);
  ASSERT_EQUAL( game.score(), 3 );
  ASSERT_EQUAL( game.getTotalScore(), 13 );
}

void testBonusStrike()
{
  std::cout << std::left << std::setw(30) << __PRETTY_FUNCTION__ << std::endl;
  BowlingGame game;
  for (int i=0; i<MAX_FRAMES-1; ++i)
  {
    game.roll(5);
    game.roll(1);
    game.score();
  }
  //(5+1)*9
  ASSERT_EQUAL( game.getTotalScore(), 54 );

  //strike
  game.roll(10);
  game.score();
  ASSERT_EQUAL( game.getTotalScore(), 64 );

  game.roll(1);
  game.roll(1);
  game.score();
  ASSERT_EQUAL( game.getTotalScore(), 66 );
}

void testBonusSpare()
{
  std::cout << std::left << std::setw(30) << __PRETTY_FUNCTION__ << std::endl;
  BowlingGame game;
  for (int i=0; i<MAX_FRAMES-1; ++i)
  {
    game.roll(5);
    game.roll(1);
    game.score();
  }
  //(5+1)*9
  ASSERT_EQUAL( game.getTotalScore(), 54 );

  //spare
  game.roll(9);
  game.roll(1);
  game.score();
  ASSERT_EQUAL( game.getTotalScore(), 64 );

  //1 bonus
  game.roll(3);
  game.score();
  ASSERT_EQUAL( game.getTotalScore(), 67 );
}

//kind of bowling pyramid ;)
void drawBowling()
{
  int rows = 3;
  for(int i=rows;i>=1;--i)
  {
    for(int space=0;space<rows-i;++space)
      std::cout<<"  ";
    for(int j=i;j<=2*i-1;++j)
      std::cout<<"0 ";
    for(int j=0;j<i-1;++j)
      std::cout<<"0 ";
    std::cout<<std::endl;
  }
}

int main()
{
  std::string message = "Do you want to TEST (1) or to PLAY (2) Bowling Game or QUIT (3)?";

  while (true)
  { 
    drawBowling();
    std::cout << message << std::endl;
    int choice =-1;
    std::cin >> choice;

    //CTRL + D
    if(std::cin.eof())
      goto Finish;

    switch ( choice )
    {
    case 1:
      {
        //tests
        std::cout << "Test my bowling game" << std::endl;
        testStrike();
        testAllStrike();
        testSpare();
        testBonusStrike();
        testBonusSpare();
      }
      break;
    case 2:
      {
        //Bowling game
        std::cout << "Game is simulated by random roll" << std::endl;

        BowlingGame game;

        //First, 10 FRAMES
        for(int i = 0; i < MAX_FRAMES; ++i)
        {
          std::cout << "FRAME " << i+1 << std::endl;

          int maxScore = MAX_PINS;
          for(int j = 0; j < MAX_ATTEMPTS_PER_FRAME && maxScore != 0; ++j)
          {
            //use time nano to get diff seed for srand 
            srand(current_time_nanoseconds());

            //number between 0 to MAX_PINS and sum = MAX_PINS
            int nbOfPins = rand() % maxScore + 1;
            maxScore -= nbOfPins;
            game.roll(nbOfPins);

            std::cout << "attempt " << j << " nbOfPins " << nbOfPins << std::endl;
          }

          std::cout << "intermediaire score " << std::left << std::setw(5) << game.score()
                    << " getTotalScore " << std::left << std::setw(5) << game.getTotalScore() << std::endl;
        }

        //Then, Bonus?
        int nbBonus = 2;
        if(!game.isOver() && nbBonus)
        {
          --nbBonus;
          srand(current_time_nanoseconds());
          int nbOfPins = rand() % MAX_PINS + 1;
          game.roll(nbOfPins);

          std::cout << "BONUS nbOfPins " << nbOfPins << std::endl;

          std::cout << "intermediaire score " << std::left << std::setw(5) << game.score()
                    << " getTotalScore " << std::left << std::setw(5) << game.getTotalScore() << std::endl;
        }

        std::cout << "GAME is OVER " << std::endl;
        std::cout << "Congratulations! your score is " << game.getTotalScore() << std::endl;
      }
      break;
    case 3:
      {
        std::cout << "Bye!" << std::endl;
        goto Finish;
      }
      break;
    default:
      {
        std::cout << "invalid choice " << std::endl;
      }
      break;
    }
  }

 Finish:
  return 0;
}
