#include "game_logic.h"

using namespace GameLogicLibrary;

void GameLogic::makeMove( unsigned id )
{
   m_moves.at( id ) = L'X';
}

EGameStatus GameLogic::getGameStatus()
{
   if ( checkWin( m_moves, L'X' ) )
      return EGameStatus::eGS_XWin;
   else if ( checkWin( m_moves, L'O' ) )
      return EGameStatus::eGS_OWin;

   if ( checkDraw( m_moves ) )
      return EGameStatus::eGS_Draw;

   return EGameStatus::eGS_GameContinue;
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

   switch ( getGameStatus() )
   {
      case EGameStatus::eGS_XWin:
      {
         return L"You Win";
      }
      case EGameStatus::eGS_OWin:
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

void GameLogic::startNewGame()
{
   m_moves.fill( L' ' );
}

unsigned GameLogic::makeAIMove()
{
   ZonePoints temp = checkZonePoints( m_moves, L'O', 0 ).zone;
   m_moves.at( temp.zone ) = L'O';
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
