#pragma once
#ifndef WINDOWS_MAIN_WINDOW_H_
#define WINDOWS_MAIN_WINDOW_H_

#include <thread>
#include <string>
#include <vector>
#include <windows.h>
#include <commctrl.h>

#include "game_logic.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

namespace Windows
{
   using std::thread;
   using std::vector;
   using GameLogicLibrary::GameLogic;
   using GameLogicLibrary::EGameStatus;

   enum EWindowElementID
   {
      eWEID_PlayButton1ID = 0,
      eWEID_PlayButton2ID = 1,
      eWEID_PlayButton3ID = 2,
      eWEID_PlayButton4ID = 3,
      eWEID_PlayButton5ID = 4,
      eWEID_PlayButton6ID = 5,
      eWEID_PlayButton7ID = 6,
      eWEID_PlayButton8ID = 7,
      eWEID_PlayButton9ID = 8
   };

   class MainWindow
   {
   public:
      MainWindow( HINSTANCE hInstance, int nCmdShow );
      ~MainWindow();

      LRESULT CALLBACK processes( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

   private:
      static LRESULT CALLBACK s_processes( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
      void makeMove( unsigned id );

      WNDCLASSEXW      m_windowClass;
      HWND             m_windowHandler;
      HFONT            m_font;
      vector< HWND >   m_playButtons;
      HWND             m_gameStatus;
      GameLogic        m_gameLogic;
      bool             m_isMoveEnable;
   };
}

#endif // WINDOWS_MAIN_WINDOW_H_
