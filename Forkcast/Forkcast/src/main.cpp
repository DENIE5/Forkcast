#include <iostream>
#include <ctime>
#include <windows.h>
#include <cstdlib>
#include <limits>
#include <d3d11.h>
#include "..\ext\imgui\imgui.h"
#include "..\ext\imgui\imgui_impl_win32.h"
#include "..\ext\imgui\imgui_impl_dx11.h"
#include <tchar.h>
#include "mainFunctions.h"
#include <thread>

// Global variables for console integration
extern std::string consoleOutput;  // This will hold the output from chooseMeal and customRand
extern bool needsReroll;  // Define it here in the main.cpp
extern char userChoice;   // Define it here in the main.cpp

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

// DirectX init
ID3D11Device* g_Device = nullptr;
ID3D11DeviceContext* g_DeviceContext = nullptr;
IDXGISwapChain* g_SwapChain = nullptr;
HWND g_Hwnd = nullptr;
ID3D11RenderTargetView* g_RenderTargetView = nullptr;

// Define userChoice and needsReroll here
char userChoice = '\0';  // Initialize userChoice
bool needsReroll = false; // Initialize needsReroll

void InitializeImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(g_Hwnd);
    ImGui_ImplDX11_Init(g_Device, g_DeviceContext);
}

void CleanupImGui()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void RenderImGui()
{
    static const float clear_color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    g_DeviceContext->ClearRenderTargetView(g_RenderTargetView, clear_color);

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Forkcast");
    ImGui::Text("Please choose a randomization mode to continue.");

    if (ImGui::Button("Basic Randomization")) {
        std::thread([]() { chooseMeal(); }).detach();
    }
    if (ImGui::Button("Custom Randomization")) {
        std::thread([] { customRand(); }).detach();
    }

    // Console output window
    ImGui::BeginChild("Console Output", ImVec2(0, 300), true);
    ImGui::TextWrapped("%s", consoleOutput.c_str());  // Display consoleOutput in ImGui window
    ImGui::EndChild();

    // Reroll buttons
    if (needsReroll) {
        if (ImGui::Button("Reroll (Y)")) {
            userChoice = 'y';
            needsReroll = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Accept (N)")) {
            userChoice = 'n';
            needsReroll = false;
        }
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
        return true;

    switch (uMsg)
    {
    case WM_SIZE:
        if (g_Device != nullptr && wParam != SIZE_MINIMIZED)
        {
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) 
            return 0;
        break;
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool InitializeWindowAndDX(HINSTANCE hInstance, int nCmdShow)
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WindowProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("MealPicker"), NULL };
    RegisterClassEx(&wc);

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    g_Hwnd = CreateWindowExW(
        WS_EX_LAYERED,
        wc.lpszClassName,
        _T("Forkcast"),
        WS_POPUP,
        0,
        0,
        screenWidth,
        screenHeight,
        NULL,
        NULL,
        wc.hInstance,
        NULL
    );
    SetLayeredWindowAttributes(g_Hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

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
    HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, NULL, 0, D3D11_SDK_VERSION,
        &swapChainDesc, &g_SwapChain, &g_Device, &featureLevel, &g_DeviceContext);

    if (FAILED(hr))
    {
        std::cerr << "Failed to create Direct3D device and swap chain." << std::endl;
        return false;
    }

    ID3D11Texture2D* pBackBuffer = nullptr;
    g_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
    g_Device->CreateRenderTargetView(pBackBuffer, NULL, &g_RenderTargetView);
    pBackBuffer->Release();

    g_DeviceContext->OMSetRenderTargets(1, &g_RenderTargetView, NULL);

    ShowWindow(g_Hwnd, nCmdShow);
    UpdateWindow(g_Hwnd);
    return true;
}

int main()
{
    if (!InitializeWindowAndDX(GetModuleHandle(NULL), SW_SHOW))
        return -1;

    InitializeImGui();

    bool running = true;
    MSG msg;
    while (running)
    {
        while (PeekMessage(&msg, g_Hwnd, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                running = false;
        }

        RenderImGui();
        g_SwapChain->Present(1, 0);
    }

    CleanupImGui();
    return 0;
}
