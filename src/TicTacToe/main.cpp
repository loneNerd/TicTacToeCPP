#include <windows.h>

#include "windows/main_window.h"

int APIENTRY wWinMain( _In_     HINSTANCE hInstance,
                       _In_opt_ HINSTANCE hPrevInstance,
                       _In_     LPWSTR    lpCmdLine,
                       _In_     int       nCmdShow)
{
   Windows::MainWindow mainWindow( hInstance, nCmdShow );

   MSG msg;

   while ( GetMessage( &msg, nullptr, 0, 0 ) )
   {
      TranslateMessage( &msg );
      DispatchMessage( &msg );
   }

   return static_cast<int>( msg.wParam );
}
