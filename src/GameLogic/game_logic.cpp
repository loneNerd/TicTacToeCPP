#include "game_logic.h"

using namespace GameLogicLibrary;

void GameLogic::makeMove( unsigned id )
{
   m_moves.at( id ) = L'X';

   if ( checkWin( m_moves, L'X' ) )
   {
      m_currentStatus = EGameStatus::eGS_PlayerWin;
      m_round += 1;
      m_wins += 1;
   }
   else if ( checkDraw( m_moves ) )
   {
      m_currentStatus = EGameStatus::eGS_Draw;
      m_round += 1;
      m_draws += 1;
   }
}

bool GameLogic::checkWin( array< wchar_t, 9 >& playField, wchar_t symbol )
{
   if ( ( playField.at( 0 ) == playField.at( 1 ) && playField.at( 1 ) == playField.at( 2 ) && playField.at( 0 ) == symbol ) ||
        ( playField.at( 3 ) == playField.at( 4 ) && playField.at( 4 ) == playField.at( 5 ) && playField.at( 3 ) == symbol ) ||
        ( playField.at( 6 ) == playField.at( 7 ) && playField.at( 7 ) == playField.at( 8 ) && playField.at( 8 ) == symbol ) ||
        ( playField.at( 0 ) == playField.at( 3 ) && playField.at( 3 ) == playField.at( 6 ) && playField.at( 0 ) == symbol ) ||
        ( playField.at( 1 ) == playField.at( 4 ) && playField.at( 4 ) == playField.at( 7 ) && playField.at( 1 ) == symbol ) ||
        ( playField.at( 2 ) == playField.at( 5 ) && playField.at( 5 ) == playField.at( 8 ) && playField.at( 8 ) == symbol ) ||
        ( playField.at( 0 ) == playField.at( 4 ) && playField.at( 4 ) == playField.at( 8 ) && playField.at( 0 ) == symbol ) ||
        ( playField.at( 2 ) == playField.at( 4 ) && playField.at( 4 ) == playField.at( 6 ) && playField.at( 2 ) == symbol ) )
   {
      return true;
   }

   return false;
}

bool GameLogic::checkDraw( array< wchar_t, 9 >& playField )
{
   for ( const auto& elem : playField )
   {
      if ( elem == L' ' )
         return false;
   }

   return true;
}

wstring GameLogic::getGameStatusString()
{
   switch ( m_currentStatus )
   {
      case EGameStatus::eGS_PlayerWin:
      {
         return L"You Win";
      }
      case EGameStatus::eGS_PlayerLose:
      {
         return L"You lose";
      }
      case EGameStatus::eGS_Draw:
      {
         return L"Draw";
      }
      case EGameStatus::eGS_GameContinue:
      default:
      {
         return L"";
      }
   }
}

wstring GameLogic::getGameStatisticString()
{
   return L"Round "    + std::to_wstring( m_round ) +
          L"\nWins: "  + std::to_wstring( m_wins ) + 
          L"\nLoses: " + std::to_wstring( m_loses ) + 
          L"\nDraws: " + std::to_wstring( m_draws );
}

void GameLogic::startNewGame()
{
   m_moves.fill( L' ' );
   m_currentStatus = EGameStatus::eGS_GameContinue;
}

unsigned GameLogic::makeAIMove()
{
   ZonePoints temp = checkZonePoints( m_moves, L'O', 0 ).zone;
   m_moves.at( temp.zone ) = L'O';

   if ( checkWin( m_moves, L'O' ) )
   {
      m_currentStatus = EGameStatus::eGS_PlayerLose;
      m_round += 1;
      m_loses += 1;
   }
   else if ( checkDraw( m_moves ) )
   {
      m_currentStatus = EGameStatus::eGS_Draw;
      m_round += 1;
      m_draws += 1;
   }

   return temp.zone;
}

vector< GameLogic::ZonePoints > GameLogic::getEmptyIndexes( array< wchar_t, 9 > zones )
{
   vector< ZonePoints > indexes;

   for ( int i = 0; i < zones.size(); ++i )
   {
      if ( zones[ i ] == L' ' )
         indexes.emplace_back( ZonePoints{ i } );
   }

   return indexes;
}

GameLogic::ZonePoints GameLogic::checkZonePoints( array< wchar_t, 9 >& playField, wchar_t symbol, int depthLevel )
{
   vector<ZonePoints> posibleMoves = getEmptyIndexes( playField );
   ZonePoints bestZone{ -1 };
   depthLevel++;

   for( ZonePoints& zone : posibleMoves )
   {
      array< wchar_t, 9 > newBoard = playField;
      newBoard[ zone.zone ] = symbol;

      ZonePoints newZone = zone;

      if ( checkWin( newBoard, L'O' ) )
         newZone.points = depthLevel;
      else if ( checkWin( newBoard, L'X' ) )
         newZone.points = -depthLevel;
      else if ( !checkDraw( newBoard ) )
         newZone.points = checkZonePoints( newBoard, symbol == L'X' ? L'O' : L'X', depthLevel ).points;

      if ( bestZone.zone == -1 ||
         ( symbol == L'O' && newZone.points > bestZone.points ) ||
         ( symbol == L'X' && newZone.points < bestZone.points ) )
         bestZone = newZone;
   }

   return bestZone;
}
