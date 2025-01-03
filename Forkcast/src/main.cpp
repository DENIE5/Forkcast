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

// Global variables
extern std::string consoleOutput;

// DirectX initialization variables
ID3D11Device* g_Device = nullptr;
ID3D11DeviceContext* g_DeviceContext = nullptr;
IDXGISwapChain* g_SwapChain = nullptr;
HWND g_Hwnd = nullptr;
ID3D11RenderTargetView* g_RenderTargetView = nullptr;

// This function should be included in your project as part of the ImGui impl files.
// You don't need to manually define this, but it must be available in your project setup.
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

// Global flag to control application exit
bool exitRequested = false;

void InitializeImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(g_Hwnd);
    ImGui_ImplDX11_Init(g_Device, g_DeviceContext);

    ImGuiStyle& style = ImGui::GetStyle();

    // Dark red button colors
    style.Colors[ImGuiCol_Button] = ImColor(139, 0, 0);         
    style.Colors[ImGuiCol_ButtonHovered] = ImColor(178, 34, 34); 
    style.Colors[ImGuiCol_ButtonActive] = ImColor(220, 20, 60);

    //titlebar color 

    style.Colors[ImGuiCol_TitleBg] = ImColor(139, 0, 0);       
    style.Colors[ImGuiCol_TitleBgActive] = ImColor(178, 34, 34); 
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(139, 0, 0);
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

    enum RandomizationMode { None, Basic, Custom };
    static RandomizationMode selectedMode = None;

    ImGui::Begin("Forkcast");

    // Exit Button (Will Close the Program)
    if (ImGui::Button("Exit"))
    {
        exitRequested = true;  // Set the flag to true when the button is clicked
    }

    ImGui::BeginChild("Console Output", ImVec2(0, 300), true);
    ImGui::TextWrapped("%s", consoleOutput.c_str());
    ImGui::EndChild();

    ImGui::Spacing();
    ImGui::Text("Meal Plan for the Week:");

    ImGui::BeginChild("Meal Plan", ImVec2(0, 0), true);

    std::string days[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
    std::string categories[7] = { "Beef", "Chicken", "Pork", "Lamb", "Fish", "Pasta", "Soup" };

    // Category to meals mapping (you can expand this with more meals)
    std::string meals[7][7] = {
        { "Beef Stew", "Steak", "Burger", "Roast Beef", "Meatballs", "Lasagna", "Beef Wellington" },
        { "Chicken Stir-fry", "Chicken Soup", "Chicken Salad", "Chicken Casserole", "Chicken Wrap", "Grilled Chicken", "Chicken Tacos" },
        { "Pork Roast", "Pulled Pork", "Sausage", "Pork Chops", "Pork Belly", "Bacon", "Pork Ribs" },
        { "Lamb Curry", "Grilled Lamb", "Lamb Stew", "Lamb Chop", "Lamb Kebabs", "Lamb Shank", "Roast Lamb" },
        { "Salmon", "Tuna", "Shrimp", "Cod", "Mackerel", "Tilapia", "Sardines" },
        { "Spaghetti", "Lasagna", "Fettucine", "Pasta Primavera", "Mac and Cheese", "Pasta Puttanesca", "Pasta Carbonara" },
        { "Tomato Soup", "Minestrone", "Lentil Soup", "Chicken Soup", "Vegetable Soup", "Clam Chowder", "Pea Soup" }
    };

    // Loop over days and categories to render buttons
    for (int i = 0; i < 7; ++i) {
        ImGui::PushID(i);
        ImGui::Text("%s", days[i].c_str());
        ImGui::BeginGroup();

        for (int j = 0; j < 7; ++j) {
            // Make buttons smaller by setting the size here
            if (ImGui::Button(categories[j].c_str(), ImVec2(70, 22))) {  // Adjusted size of buttons
                // Randomly select a meal from the chosen category
                int mealIndex = std::rand() % 7; // Randomly pick an index from 0 to 6
                std::string selectedMeal = meals[j][mealIndex];
                consoleOutput += days[i] + ": " +  selectedMeal + "\n";
            }
            if (j < 6) ImGui::SameLine();
        }

        ImGui::EndGroup();
        ImGui::Separator();
        ImGui::PopID();
    }

    ImGui::EndChild();
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
        if (g_Device != nullptr && wParam != SIZE_MINIMIZED) {}
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

    HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, NULL, 0, D3D11_SDK_VERSION,
        &swapChainDesc, &g_SwapChain, &g_Device, NULL, &g_DeviceContext);

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
    HWND consoleWindow = GetConsoleWindow();  // Get the console window handle
    if (consoleWindow != NULL)
    {
        ShowWindow(consoleWindow, SW_HIDE);  // Hide the console window
    }
    
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

        // Check if the exit button was clicked
        if (exitRequested)
        {
            running = false;  // Stop the loop and close the application
        }
    }

    CleanupImGui();
    return 0;
}
