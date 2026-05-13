
//##################################################################
//                    Platform Globals
//##################################################################
static bool running = true;


//##################################################################
//                    Platform Functions
//##################################################################
bool platform_create_window(int width, int height, char* title);
void platform_update_window();

//##################################################################
//                    Window Platform
//##################################################################
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <windows.h>

//##################################################################
//                    Window Globals
//##################################################################
static HWND window;


//##################################################################
//                    Platform Implementation
//##################################################################
LRESULT CALLBACK windows_window_callback(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{
  LRESULT result = 0;

  switch (msg)
  {
    case WM_CLOSE:
    {
      running = false;
      break;
    }
    


    default:
    {
      result = DefWindowProcA(window, msg, wParam, lParam);
      break;
    }    
  }

  return result;
}


bool platform_create_window(int width, int height, char* title)
{
    HINSTANCE instance = GetModuleHandleA(0);
    WNDCLASSA wc = {};
    wc.hInstance = instance;
    wc.hIcon = LoadIcon(instance, IDI_APPLICATION); 
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);       // The look of the cursor.
    wc.lpszClassName = title;                       // This is NOT the title of the window, just an ID to OS can identify our window
    wc.lpfnWndProc = windows_window_callback;       // Callback for Input Handling from our window

    if(!RegisterClassA(&wc))
       return false;

    // WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX
    int dwStyle = WS_OVERLAPPEDWINDOW;
    
    window = CreateWindowExA(0, title,     // This reference lpszClassName from wc
                                     title,      // This is the real actual title of the screen
                                    dwStyle,
                                    100,
                                    100,
                                    width,
                                    height,
                                    NULL,       // Parent
                                    NULL,       // Menu
                                    instance,
                                    NULL        //lpParam
                                  );
                                  
  if(window == NULL)
    return false;
                                      
  ShowWindow(window, SW_SHOW);

  return true;
}

void platform_update_window()
{
  MSG msg;
  while(PeekMessageA(&msg, window, 0, 0, PM_REMOVE))
  {
      TranslateMessage(&msg);
      DispatchMessageA(&msg); // Call the specific CALLBACK when we created the window
  }
}



#endif

int main()
{
  platform_create_window(1280,720,"Celeste");

  while (running)
  {
    platform_update_window();
  } 
  
  return 0;
}