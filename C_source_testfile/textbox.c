#include <windows.h> // Include the Windows API header

// Window Procedure function
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Create a brush for the box background
            HBRUSH hBrush = CreateSolidBrush(RGB(200, 200, 200)); // Light grey
            RECT rect = {50, 50, 250, 150}; // Define the box dimensions

            FillRect(hdc, &rect, hBrush); // Fill the rectangle with the brush
            DeleteObject(hBrush); // Clean up the brush

            // Set text color and background mode
            SetTextColor(hdc, RGB(0, 0, 0)); // Black text
            SetBkMode(hdc, TRANSPARENT); // Transparent background for text

            // Draw the text
            DrawText(hdc, TEXT("Hello from C!"), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

// Entry point for the Windows application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "SimpleGUIBoxClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles
        CLASS_NAME,                     // Window class name
        TEXT("Graphical Box"),          // Window title
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,

        NULL,                           // Parent window
        NULL,                           // Menu
        hInstance,                      // Instance handle
        NULL                            // Additional application data
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
