#pragma once
#ifndef GAME_LOGIC_H_
#define GAME_LOGIC_H_

#include <array>
#include <string>
#include <vector>

namespace GameLogicLibrary
{
   using std::array;
   using std::wstring;
   using std::vector;

   enum class EGameStatus
   {
      eGS_PlayerWin,
      eGS_PlayerLose,
      eGS_Draw,
      eGS_GameContinue
   };

   class __declspec(dllexport) GameLogic
   {
   public:
      GameLogic() : m_currentStatus{ EGameStatus::eGS_GameContinue }, 
                    m_round{ 0 }, 
                    m_wins{ 0 }, 
                    m_loses{ 0 }, 
                    m_draws{ 0 } { m_moves.fill( L' ' ); }

      GameLogic( const GameLogic& other )            = delete;
      GameLogic( GameLogic&& other )                 = delete;
      GameLogic& operator=( const GameLogic& other ) = delete;
      GameLogic& operator=( GameLogic&& other )      = delete;

      ~GameLogic() {}

      EGameStatus getGameStatus() { return m_currentStatus; }

      unsigned makeAIMove();
      void makeMove( unsigned id );
      wstring getGameStatusString();
      wstring getGameStatisticString();
      void startNewGame();
   
   private:
      struct ZonePoints
      {
         ZonePoints( int zone )
         {
            this->zone = zone;
            points = 0;
         }
         int zone;
         int points;
      };

      vector< ZonePoints > getEmptyIndexes( array< wchar_t, 9 > zones );
      ZonePoints checkZonePoints( array< wchar_t, 9 >& playField, wchar_t symbol, int depthLevel );
      bool checkWin( array< wchar_t, 9 >& playField, wchar_t symbol );
      bool checkDraw( array< wchar_t, 9 >& playField );

      array< wchar_t, 9 > m_moves;

      EGameStatus m_currentStatus;
      unsigned    m_round;
      unsigned    m_wins;
      unsigned    m_loses;
      unsigned    m_draws;
   };
}

#endif // GAME_LOGIC_H_
