#pragma once
#ifndef GAME_LOGIC_H_
#define GAME_LOGIC_H_

#include <array>
#include <string>

namespace GameLogicLibrary
{
   using std::array;

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
      void makeMove( unsigned id );
      std::wstring& getCurrentFigure() { return m_currentFigure; }
      EGameStatus getGameStatus();
      void startNewGame();
   
   private:
      array< wchar_t, 9 > m_moves{ L' ', L' ', L' ', L' ', L' ', L' ', L' ', L' ', L' ' };
      std::wstring m_currentFigure{ L"X" };
   };
}

#endif // GAME_LOGIC_H_
