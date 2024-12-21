#include <iostream>
#include <ctime>
#include <windows.h>
#include <cstdlib>
#include <limits>
#include <d3d11.h>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <tchar.h>
#include "mainFunctions.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

// Global variables for DirectX initialization
ID3D11Device* g_Device = nullptr;
ID3D11DeviceContext* g_DeviceContext = nullptr;
IDXGISwapChain* g_SwapChain = nullptr;
HWND g_Hwnd = nullptr;

//back buffer
ID3D11RenderTargetView* g_RenderTargetView = nullptr;

// Function to initialize ImGui
void InitializeImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplWin32_Init(g_Hwnd);  // Initialize Win32 backend
    ImGui_ImplDX11_Init(g_Device, g_DeviceContext);  // Initialize DirectX 11 backend
}

// Function to clean up ImGui
void CleanupImGui()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

// Function to render ImGui UI
void RenderImGui()
{
    //clear the back buffer otherwise u get an glitchy background as the screen is never cleared
    static const float clear_color[4] = { 0.0f, 0.0f, 0.0f, 0.0f }; //clear so no background
    g_DeviceContext->ClearRenderTargetView(g_RenderTargetView, clear_color);

    // Start a new ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // Example ImGui UI
    ImGui::Begin("Forkcast");
    ImGui::Text("This is a simple ImGui window.");
    if (ImGui::Button("Basic Randomization")) {
        chooseMeal();
    }
    if (ImGui::Button("Custom Randomization")) {
        customRand();
    }
    ImGui::End();

    // Render the ImGui frame
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

// Window procedure function to handle messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
        return true;

    switch (uMsg)
    {
    case WM_SIZE:
        if (g_Device != nullptr && wParam != SIZE_MINIMIZED)
        {
            // Resize swap chain when the window size changes
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Function to create the window and initialize DirectX
bool InitializeWindowAndDX(HINSTANCE hInstance, int nCmdShow)
{
    // Register the window class
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WindowProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("MealPicker"), NULL };
    RegisterClassEx(&wc);

    int screenWidth = GetSystemMetrics(SM_CXSCREEN); // X (width)
    int screenHeight = GetSystemMetrics(SM_CYSCREEN); // Y (height)

    //make the dx window insiable
    g_Hwnd = CreateWindowExW(
        WS_EX_LAYERED,  // Layered, Always on top, Transparent to mouse
        wc.lpszClassName,
        _T("Forkcast"),
        WS_POPUP,  // No border or title bar
        0,
        0,
        screenWidth,  //screen x
        screenHeight,   //screen y
        NULL,
        NULL,
        wc.hInstance,
        NULL
    );
    SetLayeredWindowAttributes(g_Hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

    // Initialize DirectX
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = screenWidth;
    swapChainDesc.BufferDesc.Height = screenHeight;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = g_Hwnd;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.Windowed = TRUE;

    D3D_FEATURE_LEVEL featureLevel;
    HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, NULL, 0, D3D11_SDK_VERSION, &swapChainDesc, &g_SwapChain, &g_Device, &featureLevel, &g_DeviceContext);

    if (FAILED(hr))
    {
        std::cerr << "Failed to create Direct3D device and swap chain." << std::endl;
        return false;
    }

    // u need an back buffer otherwise imgui wont show
    ID3D11Texture2D* pBackBuffer = nullptr;
    g_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
    g_Device->CreateRenderTargetView(pBackBuffer, NULL, &g_RenderTargetView);
    pBackBuffer->Release();

    g_DeviceContext->OMSetRenderTargets(1, &g_RenderTargetView, NULL);

    ShowWindow(g_Hwnd, nCmdShow);
    UpdateWindow(g_Hwnd);
    return true;
}



// Main function
int main()
{
    // Initialize window and DirectX
    if (!InitializeWindowAndDX(GetModuleHandle(NULL), SW_SHOW))
        return -1;

    // Initialize ImGui
    InitializeImGui();

    // Main loop
    bool running = true;
    MSG msg;
    while (running)
    {
        // Handle messages and events
        while (PeekMessage(&msg, g_Hwnd, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                running = false;
        }

        // Render ImGui UI
        RenderImGui();

        // Render your DirectX 11 frame (swap buffers or present)
        g_SwapChain->Present(1, 0);  // DirectX 11 present call
    }

    // Clean up ImGui resources before exiting
    CleanupImGui();

    return 0;
}
