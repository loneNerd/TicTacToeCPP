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
      eGS_XWin,
      eGS_OWin,
      eGS_Draw,
      eGS_GameContinue
   };

   class __declspec(dllexport) GameLogic
   {
   public:
      GameLogic() { m_moves.fill(L' '); }

      GameLogic( const GameLogic& other )            = delete;
      GameLogic( GameLogic&& other )                 = delete;
      GameLogic& operator=( const GameLogic& other ) = delete;
      GameLogic& operator=( GameLogic&& other )      = delete;

      ~GameLogic() {}
      unsigned makeAIMove();
      void makeMove( unsigned id );
      EGameStatus getGameStatus();
      wstring getGameStatusString();
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
   };
}

#endif // GAME_LOGIC_H_
