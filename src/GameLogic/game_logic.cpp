#include "game_logic.h"

using namespace GameLogicLibrary;

void GameLogic::makeMove( unsigned id )
{
   m_moves.at( id ) = m_currentFigure.at( 0 );

   m_currentFigure = m_currentFigure == L"O" ? L"X" : L"O";
}

EGameStatus GameLogic::getGameStatus()
{
   if ( ( m_moves.at( 0 ) == m_moves.at( 1 ) && m_moves.at( 1 ) == m_moves.at( 2 ) && m_moves.at( 0 ) != L' ' ) ||
        ( m_moves.at( 3 ) == m_moves.at( 4 ) && m_moves.at( 4 ) == m_moves.at( 5 ) && m_moves.at( 3 ) != L' ' ) ||
        ( m_moves.at( 6 ) == m_moves.at( 7 ) && m_moves.at( 7 ) == m_moves.at( 8 ) && m_moves.at( 8 ) != L' ' ) ||
        ( m_moves.at( 0 ) == m_moves.at( 3 ) && m_moves.at( 3 ) == m_moves.at( 6 ) && m_moves.at( 0 ) != L' ' ) ||
        ( m_moves.at( 1 ) == m_moves.at( 4 ) && m_moves.at( 4 ) == m_moves.at( 7 ) && m_moves.at( 1 ) != L' ' ) ||
        ( m_moves.at( 2 ) == m_moves.at( 5 ) && m_moves.at( 5 ) == m_moves.at( 8 ) && m_moves.at( 8 ) != L' ' ) ||
        ( m_moves.at( 0 ) == m_moves.at( 4 ) && m_moves.at( 4 ) == m_moves.at( 8 ) && m_moves.at( 0 ) != L' ' ) ||
        ( m_moves.at( 2 ) == m_moves.at( 4 ) && m_moves.at( 4 ) == m_moves.at( 6 ) && m_moves.at( 2 ) != L' ' ) )
   {
      if ( m_currentFigure == L"X" )
         return EGameStatus::eGS_OWin;
      else
         return EGameStatus::eGS_XWin;
   }

   for ( const auto& elem : m_moves )
   {
      if ( elem == L' ' )
         return EGameStatus::eGS_GameContinue;
   }

   return EGameStatus::eGS_Draw;
}

void GameLogic::startNewGame()
{
   for ( auto& elem : m_moves )
   {
      elem = L' ';
   }

   m_currentFigure = L"X";
}
