#include "main_window.h"

using namespace Windows;

MainWindow::MainWindow( HINSTANCE hInstance, int nCmdShow )
{
   m_windowClass.cbSize        = sizeof( WNDCLASSEX );
   m_windowClass.style         = CS_HREDRAW | CS_VREDRAW;
   m_windowClass.lpfnWndProc   = s_processes;
   m_windowClass.hInstance     = hInstance;
   m_windowClass.hCursor       = LoadCursor( nullptr, IDC_ARROW );
   m_windowClass.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
   m_windowClass.lpszClassName = L"Main Window";

   RegisterClassExW( &m_windowClass );

   m_windowHandler = CreateWindow( L"Main Window", 
                                   L"TicTacToe", 
                                   WS_OVERLAPPEDWINDOW,
                                   CW_USEDEFAULT, 0, 510, 530, 
                                   nullptr, 
                                   nullptr, 
                                   hInstance, 
                                   this );

   ShowWindow( m_windowHandler, nCmdShow );
   UpdateWindow( m_windowHandler );

   m_playButtons.emplace_back( CreateWindow( WC_BUTTON,
                                             L"",
                                             WS_CHILD | WS_VISIBLE,
                                             10, 10, 150, 150,
                                             m_windowHandler,
                                             ( HMENU )eWEID_PlayButton1ID,
                                             hInstance,
                                             this ) );

   m_font = CreateFont( 132, 72, 0, 0, 
                        FW_BOLD, 
                        FALSE, FALSE, FALSE, 
                        ANSI_CHARSET, 
                        OUT_DEFAULT_PRECIS, 
                        CLIP_DEFAULT_PRECIS, 
                        ANTIALIASED_QUALITY, 
                        DEFAULT_PITCH, 
                        NULL );

   SendMessage( m_playButtons[0], WM_SETFONT, ( WPARAM )m_font, ( LPARAM )TRUE );

   m_playButtons.emplace_back( CreateWindow( WC_BUTTON,
                                             L"",
                                             WS_CHILD | WS_VISIBLE,
                                             170, 10, 150, 150,
                                             m_windowHandler,
                                             ( HMENU )eWEID_PlayButton2ID,
                                             hInstance,
                                             this ) );
   SendMessage( m_playButtons[1], WM_SETFONT, ( WPARAM )m_font, ( LPARAM )TRUE );

   m_playButtons.emplace_back( CreateWindow( WC_BUTTON,
                                             L"",
                                             WS_CHILD | WS_VISIBLE,
                                             330, 10, 150, 150,
                                             m_windowHandler,
                                             ( HMENU )eWEID_PlayButton3ID,
                                             hInstance,
                                             this ) );
   SendMessage( m_playButtons[2], WM_SETFONT, ( WPARAM )m_font, ( LPARAM )TRUE );

   m_playButtons.emplace_back( CreateWindow( WC_BUTTON,
                                             L"",
                                             WS_CHILD | WS_VISIBLE,
                                             10, 170, 150, 150,
                                             m_windowHandler,
                                             ( HMENU )eWEID_PlayButton4ID,
                                             hInstance,
                                             this ) );
   SendMessage( m_playButtons[3], WM_SETFONT, ( WPARAM )m_font, ( LPARAM )TRUE );

   m_playButtons.emplace_back( CreateWindow( WC_BUTTON,
                                             L"",
                                             WS_CHILD | WS_VISIBLE,
                                             170, 170, 150, 150,
                                             m_windowHandler,
                                             ( HMENU )eWEID_PlayButton5ID,
                                             hInstance,
                                             this ) );
   SendMessage( m_playButtons[4], WM_SETFONT, ( WPARAM )m_font, ( LPARAM )TRUE );

   m_playButtons.emplace_back( CreateWindow( WC_BUTTON,
                                             L"",
                                             WS_CHILD | WS_VISIBLE,
                                             330, 170, 150, 150,
                                             m_windowHandler,
                                             ( HMENU )eWEID_PlayButton6ID,
                                             hInstance,
                                             this ) );
   SendMessage( m_playButtons[5], WM_SETFONT, ( WPARAM )m_font, ( LPARAM )TRUE );

   m_playButtons.emplace_back( CreateWindow( WC_BUTTON,
                                             L"",
                                             WS_CHILD | WS_VISIBLE,
                                             10, 330, 150, 150,
                                             m_windowHandler,
                                             ( HMENU )eWEID_PlayButton7ID,
                                             hInstance,
                                             this ) );
   SendMessage( m_playButtons[6], WM_SETFONT, ( WPARAM )m_font, ( LPARAM )TRUE );

   m_playButtons.emplace_back( CreateWindow( WC_BUTTON,
                                             L"",
                                             WS_CHILD | WS_VISIBLE,
                                             170, 330, 150, 150,
                                             m_windowHandler,
                                             ( HMENU )eWEID_PlayButton8ID,
                                             hInstance,
                                             this ) );
   SendMessage( m_playButtons[7], WM_SETFONT, ( WPARAM )m_font, ( LPARAM )TRUE );

   m_playButtons.emplace_back( CreateWindow( WC_BUTTON,
                                             L"",
                                             WS_CHILD | WS_VISIBLE,
                                             330, 330, 150, 150,
                                             m_windowHandler,
                                             ( HMENU )eWEID_PlayButton9ID,
                                             hInstance,
                                             this ) );
   SendMessage( m_playButtons[8], WM_SETFONT, ( WPARAM )m_font, ( LPARAM )TRUE );
}

MainWindow::~MainWindow()
{
   DestroyWindow( m_windowHandler );

   for ( HWND button : m_playButtons )
   {
      DestroyWindow( button );
   }

   DeleteObject( m_font );
}

LRESULT MainWindow::s_processes(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   MainWindow* pThis;

   if ( uMsg == WM_NCCREATE )
   {
      pThis = static_cast< MainWindow* >( reinterpret_cast< CREATESTRUCT* >( lParam )->lpCreateParams );

      SetLastError( 0 );
      if ( !SetWindowLongPtr( hWnd, GWLP_USERDATA, reinterpret_cast< LONG_PTR >( pThis ) ) )
      {
         if ( GetLastError() != 0 )
            return FALSE;
      }
   }
   else
   {
      pThis = reinterpret_cast< MainWindow* >( GetWindowLongPtr( hWnd, GWLP_USERDATA ) );
   }

   if ( pThis )
   {
      return pThis->processes( hWnd, uMsg, wParam, lParam );
   }

   return FALSE;
}

LRESULT CALLBACK MainWindow::processes( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
   switch ( message )
   {
      case WM_COMMAND:
      {
         switch ( LOWORD( wParam ) )
         {
            case eWEID_PlayButton1ID:
            case eWEID_PlayButton2ID:
            case eWEID_PlayButton3ID:
            case eWEID_PlayButton4ID:
            case eWEID_PlayButton5ID:
            case eWEID_PlayButton6ID:
            case eWEID_PlayButton7ID:
            case eWEID_PlayButton8ID:
            case eWEID_PlayButton9ID:
            {
               SendMessage( m_playButtons[ LOWORD( wParam ) ], WM_SETTEXT, 0, ( LPARAM )L"X" );
               EnableWindow( m_playButtons[ LOWORD( wParam ) ], FALSE );
               m_gameLogic.makeMove( LOWORD( wParam ) );

               if ( m_gameLogic.getGameStatus() == EGameStatus::eGS_GameContinue )
               {
                  unsigned temp = m_gameLogic.makeAIMove();
                  SendMessage( m_playButtons[ temp ], WM_SETTEXT, 0, ( LPARAM )L"O" );
                  EnableWindow( m_playButtons[ temp ], FALSE);

                  if ( m_gameLogic.getGameStatus() == EGameStatus::eGS_GameContinue )
                     break;
               }

               MessageBox( m_windowHandler, m_gameLogic.getGameStatusString().c_str(), L"Game Over", MB_OK );
               MessageBox( m_windowHandler, m_gameLogic.getGameStatisticString().c_str(), L"Statistic", MB_OK );

               for ( const auto& elem : m_playButtons )
               {
                  SendMessage( elem, WM_SETTEXT, 0, ( LPARAM )L"" );
                  EnableWindow( elem, TRUE );
               }

               m_gameLogic.startNewGame();

               break;
            }
         }

         break;
      }
      case WM_DESTROY:
      {
         PostQuitMessage( 0 );
         break;
      }
   }

   return DefWindowProc( hWnd, message, wParam, lParam );
}
