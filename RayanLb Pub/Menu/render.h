#include "Cheat info/loop.h"
#include "icons.h"
#include <D3D11.h>
#include "ImGui/imgui_impl_dx11.h"
#include "icon.h"
#include "ImGui/imgui_internal.h"
#include "imgui_notify.h"
#include "animation.h"
#include <D3DX11core.h>
#include "fonts.h"
#include "image.h"
#include <D3DX11.h>
#include <D3DX11tex.h>

ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.f);
HWND window_handle;
ID3D11Device* d3d_device;
ID3D11DeviceContext* d3d_device_ctx;
IDXGISwapChain* d3d_swap_chain;
ID3D11RenderTargetView* d3d_render_target;
D3DPRESENT_PARAMETERS d3d_present_params;
ID3D11ShaderResourceView* Logo = nullptr;


static int tabs = 0;
static int weaponconfigsubs = 0;
static int visualsubs = 0;
static int aimbotsubs = 0;
static int ColorsMisc = 0;

ImVec2 pos;
ImFont* icons;
ImFont* colorpicker;
ImFont* tabfont;


namespace render1 {
    class c_render {
    public:

        auto imgui() -> bool {
            SPOOF_FUNC

                DXGI_SWAP_CHAIN_DESC swap_chain_description;
            ZeroMemory(&swap_chain_description, sizeof(swap_chain_description));
            swap_chain_description.BufferCount = 2;
            swap_chain_description.BufferDesc.Width = 0;
            swap_chain_description.BufferDesc.Height = 0;
            swap_chain_description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            swap_chain_description.BufferDesc.RefreshRate.Numerator = 60;
            swap_chain_description.BufferDesc.RefreshRate.Denominator = 1;
            swap_chain_description.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
            swap_chain_description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swap_chain_description.OutputWindow = window_handle;
            swap_chain_description.SampleDesc.Count = 1;
            swap_chain_description.SampleDesc.Quality = 0;
            swap_chain_description.Windowed = 1;
            swap_chain_description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

            D3D_FEATURE_LEVEL d3d_feature_lvl;

            const D3D_FEATURE_LEVEL d3d_feature_array[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };

            D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, d3d_feature_array, 2, D3D11_SDK_VERSION, &swap_chain_description, &d3d_swap_chain, &d3d_device, &d3d_feature_lvl, &d3d_device_ctx);

            ID3D11Texture2D* pBackBuffer;
            D3DX11_IMAGE_LOAD_INFO info;
            ID3DX11ThreadPump* pump{ nullptr };
           

            d3d_swap_chain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

            d3d_device->CreateRenderTargetView(pBackBuffer, NULL, &d3d_render_target);

            pBackBuffer->Release();

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

            static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
            ImFontConfig icons_config;

            ImFontConfig CustomFont;
            CustomFont.FontDataOwnedByAtlas = false;

            icons_config.MergeMode = true;
            icons_config.PixelSnapH = true;
            icons_config.OversampleH = 2.5;
            icons_config.OversampleV = 2.5;

            ImGui_ImplWin32_Init(window_handle);
            ImGui_ImplDX11_Init(d3d_device, d3d_device_ctx);


            ImFontConfig font_config;
            font_config.OversampleH = 1;
            font_config.OversampleV = 1;
            font_config.PixelSnapH = 1;


            static const ImWchar ranges[] =
            {
                0x0020, 0x00FF,
                0x0400, 0x044F,
                0,
            };

           


            tabfont = io.Fonts->AddFontFromMemoryTTF(&mainfonthxd, sizeof mainfonthxd, 16, NULL, io.Fonts->GetGlyphRangesCyrillic());
            icons = io.Fonts->AddFontFromMemoryTTF(iconshxd, sizeof(iconshxd), 14.0f, &font_config, ranges);
            colorpicker = io.Fonts->AddFontFromMemoryTTF(iconshxd, sizeof(iconshxd), 28.0f, &font_config, ranges);

     

            MenuFont = io.Fonts->AddFontFromFileTTF(E("C:\\fortnite.otf"), 18.f);

            GameFont = io.Fonts->AddFontFromFileTTF(E("C:\\Windows\\Fonts\\Arial.ttf"), 15.f); // C:\\Windows\\Fonts\\Arial.ttf


            
      
        
           
            
            DistanceFont = io.Fonts->AddFontFromFileTTF(E("C:\\Windows\\Fonts\\Verdana.ttf"), 15.0f);



            UsernamePlatformFont = io.Fonts->AddFontFromFileTTF(E("C:\\Windows\\Fonts\\Arial.ttf"), 15.0f);
            WeaponFont = io.Fonts->AddFontFromFileTTF(E("C:\\fortnite.otf"), 15.0f);

            FpsFont = io.Fonts->AddFontFromFileTTF(E("C:\\fortnite.otf"), 20.0f);




            d3d_device->Release();
            return true;
        }





        auto hijack() -> bool
        {
            SPOOF_FUNC;

            // window_handle = FindWindowA_Spoofed(E("CiceroUIWndFrame"), E("CiceroUIWndFrame")); // visual studio
           //  window_handle = FindWindowA_Spoofed ( E ("MedalOverlayClass" ), E ( "MedalOverlay" ) ); // Medal
           // window_handle = FindWindowA_Spoofed(E("CEF-OSC-WIDGET"), E("NVIDIA Geforce Overlay")); // Nvidia
            //  window_handle = FindWindowA_Spoofed(E("GDI+ Hook Class"), E("GDI+ Window (FPSMonitor)")); // Monitor
             // window_handle = FindWindowA_Spoofed(E("GDI+ Hook Window Class"), E("GDI+ Window (obs64.exe)")); // obs

                
                
     

            if (!window_handle)
            {
                MessageBoxA(0, skCrypt("{!} Overlay Failed -> Contact Anis."), skCrypt(""), MB_ICONINFORMATION);
                return false;
            }

            int WindowWidth = GetSystemMetrics(SM_CXSCREEN);
            int WindowHeight = GetSystemMetrics(SM_CYSCREEN);

            if (!SetWindowPos_Spoofed(window_handle, HWND_TOPMOST, 0, 0, WindowWidth, WindowHeight, SWP_SHOWWINDOW))
            {
                return false;
            }

            if (!SetLayeredWindowAttributes_Spoofed(window_handle, RGB(0, 0, 0), 255, LWA_ALPHA))
            {
                return false;
            }

            if (!SetWindowLongA_Spoofed(window_handle, GWL_EXSTYLE, GetWindowLong(window_handle, GWL_EXSTYLE) | WS_EX_TRANSPARENT))
            {
                return false;
            }

            MARGINS Margin = { -1 };
            if (FAILED(DwmExtendFrameIntoClientArea(window_handle, &Margin)))
            {
                return false;
            }

            ShowWindow_Spoofed(window_handle, SW_SHOW);

            UpdateWindow_Spoofed(window_handle);

            ShowWindow_Spoofed(window_handle, SW_HIDE);

            return true;
        }

      
       


       // Menu 


        auto menu() -> void {

            SPOOF_FUNC;

            if (GetAsyncKeyState_Spoofed(VK_INSERT) & 1)
                Misc::enable_menu = !Misc::enable_menu;

            


            if (Misc::enable_menu) {

                ImGui::Begin(E("RayanLB Public"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

               // ImGui::GetStyle().Colors[ImGuiCol_Border] = ImVec4(0.282f, 0.067f, 0.392f, 0.5f); // Purple color
                ImGui::GetStyle().WindowRounding = 8.0f; 
               



                ImGuiStyle* style = &ImGui::GetStyle();

              

                style->FrameBorderSize = 1.0f; // outline
                style->Colors[ImGuiCol_Border] = ImColor(0, 0, 0); // Outline tabs

                style->Colors[ImGuiCol_FrameBg] = ImVec4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 1.0f); // color pickers background
                style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 1.0f); // color pickers background
                style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 1.0f); // color pickers background
                 
                style->Colors[ImGuiCol_Header] = ImVec4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 1.0f); // background color box bones
                style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.282f, 0.067f, 0.392f, 1.0f); // background color box bones
                style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.1568627506494522f, 0.1568627506494522f, 0.1568627506494522f, 1.0f); // background color box bones
       
                
              
              
              
              


                   
                ImGui::SetWindowSize(ImVec2(800, 400));

                ImGui::PushFont(MenuFont);
               
                pos = ImGui::GetWindowPos();


                ImGui::SetCursorPos(ImVec2(50, 15));
       
                ImGui::SetCursorPos(ImVec2(40, 100));


               



           //   ImGui::PushFont(icons);
                ImGui::PopFont();

                ImGui::PushFont(MenuFont);




                // Aimbot + Configs

                if (tabs == 0)
                {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
                    ImGui::SetCursorPos(ImVec2(15, 5));
                    if (ImGui::Button("Aimbot + Configs", ImVec2(170, 30)))
                        tabs = 0;
                    ImGui::PopStyleColor(3);
                }
                else
                {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
                    ImGui::SetCursorPos(ImVec2(15, 5));
                    if (ImGui::Button("Aimbot + Configs", ImVec2(170, 30)))
                        tabs = 0;
                }

              // Visuals

                if (tabs == 1)
                {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
                    ImGui::SetCursorPos(ImVec2(15, 40));
                    if (ImGui::Button("Visuals", ImVec2(170, 30)))
                        tabs = 1;
                    ImGui::PopStyleColor(3);
                }
                else
                {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
                    ImGui::SetCursorPos(ImVec2(15, 40));
                    if (ImGui::Button("Visuals", ImVec2(170, 30)))
                        tabs = 1;
                }






                if (tabs == 2)
                {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
                    ImGui::SetCursorPos(ImVec2(15, 75));
                    if (ImGui::Button("Colors + Size", ImVec2(170, 30)))
                        tabs = 2;
                    ImGui::PopStyleColor(3);
                }
                else
                {
                    ImGui::SetCursorPos(ImVec2(15, 75));
                    if (ImGui::Button("Colors + Size", ImVec2(170, 30)))
                        tabs = 2;
                }
                

               


                ImGui::PopFont();


               // ImGui::GetForegroundDrawList()->AddLine(ImVec2(pos.x + 15, pos.y + 210), ImVec2(pos.x + 185, pos.y + 210), ImColor(71, 60, 68, 150), 2.f);

              //  ImGui::GetForegroundDrawList()->AddLine(ImVec2(pos.x + 15, pos.y + 300), ImVec2(pos.x + 185, pos.y + 300), ImColor(71, 60, 68, 150), 2.f);


          // Aimbot + Configs
      
                int tab0alpha = Animate("Tab0", "Tab0", tabs == 0, 255, 40.f, INTERP);
                tab0alpha = ImClamp(tab0alpha, 0, 255);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab0alpha / 255.f);
                if (tabs == 0)
                {
                    ImGui::SetCursorPos(ImVec2(200, 0));
                    ImGui::BeginChild("Child0", ImVec2(570, 495), false, ImGuiWindowFlags_NoMove);
                    ImGui::BeginChild("Child0", ImVec2(570, 495), false, ImGuiWindowFlags_NoScrollbar);

                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
                    ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));

                   // ImGui::GetForegroundDrawList()->AddRect(ImVec2(pos.x + 200, pos.y + 55), ImVec2(pos.x + 770, pos.y + 350), ImColor(255, 255, 255, 255), 1);

                    ImGui::SetCursorPos(ImVec2(20, 5));
                    if (ImGui::Button("Aimbot", ImVec2(260, 25)))
                        aimbotsubs = 0;

                    ImGui::SetCursorPos(ImVec2(290, 5));
                    if (ImGui::Button("Aimbot Configs", ImVec2(260, 25)))
                        aimbotsubs = 1;


                    ImGui::PopStyleColor(3);

                    // Aimbot

                    if (aimbotsubs == 0)
                    {
                        ImGui::SetCursorPos(ImVec2(20, 35));
                        ImGui::BeginGroup();

                        ImGui::Checkbox("Enable", &Aimbot::aimbot);
                        ImGui::Spacing();
                        ImGui::Checkbox("Visible Check", &Aimbot::visible_check);
                        ImGui::Spacing();
                        ImGui::Checkbox("Fov Normal", &Aimbot::fov_circle);
                        ImGui::Spacing();
                        ImGui::Checkbox("FOV Filled", &Aimbot::FovFilled);
                        ImGui::Spacing();
                        ImGui::Checkbox("FOV LGBTQ", &Aimbot::FOVlgbtq);
                        ImGui::Spacing();
                        ImGui::Checkbox("FOV Dynamic", &Aimbot::FOVdynamic);
                        ImGui::Spacing();
                        ImGui::Checkbox("Target Text", &Aimbot::target_text);
                        ImGui::Spacing();
                        ImGui::Checkbox("Target Line", &Aimbot::target_line);
                    }

                    // Aimbot configs 

                    if (aimbotsubs == 1)
                    {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.5f, 0.0f, 1.0f));
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.5f, 0.0f, 1.0f));
                        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.5f, 0.0f, 1.0f));
                        ImGui::SetCursorPos(ImVec2(20, 35));
                        ImGui::BeginGroup();


                        ImGui::SetCursorPos(ImVec2(20, 35));
                        if (ImGui::Button("Rifle", ImVec2(125, 25)))
                            weaponconfigsubs = 0;

                        ImGui::SetCursorPos(ImVec2(155, 35));
                        if (ImGui::Button("Shotgun", ImVec2(125, 25)))
                            weaponconfigsubs = 1;

                        ImGui::SetCursorPos(ImVec2(290, 35));
                        if (ImGui::Button("SMG/Pistol", ImVec2(125, 25)))
                            weaponconfigsubs = 2;

                        ImGui::SetCursorPos(ImVec2(425, 35));
                        if (ImGui::Button("Sniper", ImVec2(125, 25)))
                            weaponconfigsubs = 3;

                        ImGui::PopStyleColor(3);


                        // Rifle

                        if (weaponconfigsubs == 0)
                        {
                            ImGui::SetCursorPos(ImVec2(20, 60));
                            ImGui::Text("Rifle");

                            ImGui::SetCursorPos(ImVec2(20, 60));
                            ImGui::Combo(E("Rifle Bone"), &Rifle::hitbox, E("Head\0\Neck\0\Chest\0\Pelvis"));

                            ImGui::SetCursorPos(ImVec2(450, 130));
                            ImGui::SliderFloat("Rifle Smooth", &Rifle::smooth, 1.f, 20.f);

                            ImGui::SetCursorPos(ImVec2(450, 150));
                            ImGui::SliderFloat("Rifle FOV", &Rifle::aim_fov, 50.f, 300.f);

                            ImGui::SetCursorPos(ImVec2(20, 170));
                            ImGui::Text("Rifle AimKey");

                            ImGui::SetCursorPos(ImVec2(20, 190));
                            HotkeyButton(Rifle::aimkey, ChangeKey1, keystatus1);
                        }

                        // Shotgun

                        if (weaponconfigsubs == 1)
                        {
                            ImGui::SetCursorPos(ImVec2(20, 60));
                            ImGui::Text("Shotgun");

                            ImGui::SetCursorPos(ImVec2(20, 60));
                            ImGui::Combo(E("Shotgun Bone"), &Shotgun::hitbox, E("Head\0\Neck\0\Chest\0\Pelvis"));

                            ImGui::SetCursorPos(ImVec2(450, 130));
                            ImGui::SliderFloat("Shotgun Smooth", &Shotgun::smooth, 1.f, 20.f);

                            ImGui::SetCursorPos(ImVec2(450, 150));
                            ImGui::SliderFloat("Shotgun FOV", &Shotgun::aim_fov, 50.f, 300.f);

                            ImGui::SetCursorPos(ImVec2(20, 170));
                            ImGui::Text("Shotgun AimKey");

                            ImGui::SetCursorPos(ImVec2(20, 190));
                            HotkeyButton(Shotgun::aimkey, ChangeKey2, keystatus2);

                        }

                        // Smg

                        if (weaponconfigsubs == 2)
                        {
                            ImGui::SetCursorPos(ImVec2(20, 60));
                            ImGui::Text("Smg");

                            ImGui::SetCursorPos(ImVec2(20, 60));
                            ImGui::Combo(E("SMG/Pistol Bone"), &Smg::hitbox, E("Head\0\Neck\0\Chest\0\Pelvis"));

                            ImGui::SetCursorPos(ImVec2(450, 130));
                            ImGui::SliderFloat("SMG/Pistol Smooth", &Smg::smooth, 1.f, 20.f);

                            ImGui::SetCursorPos(ImVec2(450, 150));
                            ImGui::SliderFloat("SMG/Pistol FOV", &Smg::aim_fov, 50.f, 300.f);

                            ImGui::SetCursorPos(ImVec2(20, 170));
                            ImGui::Text("SMG/Pistol AimKey");

                            ImGui::SetCursorPos(ImVec2(20, 190));
                            HotkeyButton(Smg::aimkey, ChangeKey3, keystatus3);
                        }

                        // Sniper

                        if (weaponconfigsubs == 3)
                        {
                            ImGui::SetCursorPos(ImVec2(20, 60));
                            ImGui::Text("Sniper");

                            ImGui::SetCursorPos(ImVec2(20, 60));
                            ImGui::Combo(E("Sniper Bone"), &Sniper::hitbox, E("Head\0\Neck\0\Chest\0\Pelvis"));

                            ImGui::SetCursorPos(ImVec2(450, 130));
                            ImGui::SliderFloat("Sniper Smooth", &Sniper::smooth, 1.f, 20.f);

                            ImGui::SetCursorPos(ImVec2(450, 150));
                            ImGui::SliderFloat("Sniper FOV", &Sniper::aim_fov, 50.f, 800.f);

                            ImGui::SetCursorPos(ImVec2(20, 170));
                            ImGui::Text("Sniper AimKey");

                            ImGui::SetCursorPos(ImVec2(20, 190));
                            HotkeyButton(Sniper::aimkey, ChangeKey4, keystatus4);

                            ImGui::Checkbox("Sniper Prediction", &Sniper::prediction); 
                        }
                    }
                        ImGui::EndChild();
                        ImGui::EndGroup();
                }

                ImGui::PopStyleVar();

                // Visuals

                int tab1alpha = Animate("Tab1", "Tab1", tabs == 1, 255, 40.f, INTERP);
                tab1alpha = ImClamp(tab1alpha, 0, 255);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab1alpha / 255.f);

                if (tabs == 1)
                {
                    ImGui::SetCursorPos(ImVec2(200, 0));
                    ImGui::BeginChild("Child2", ImVec2(570, 495), false, ImGuiWindowFlags_NoMove);


                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
                    

                    ImGui::SetCursorPos(ImVec2(20, 5));
                    if (ImGui::Button("Visuals", ImVec2(260, 25)))
                        visualsubs = 0;

                    ImGui::SetCursorPos(ImVec2(290, 5));
                    if (ImGui::Button("Misc", ImVec2(260, 25)))
                        visualsubs = 1;

                    ImGui::PopStyleColor(3);

                    if (visualsubs == 0)
                    {
                        ImGui::SetCursorPos(ImVec2(20, 35));
                        ImGui::BeginGroup();

                        ImGui::Checkbox("Enable ESP", &Visuals::enable_esp);
                        ImGui::Spacing();
                        ImGui::Checkbox("Box", &Visuals::Box_ESP); // need add 3 func
                        ImGui::Spacing();
                        ImGui::Checkbox("Skeleton", &Visuals::skeleton);
                        ImGui::Spacing();
                        ImGui::Checkbox("Snaplines", &Visuals::snapline); // need add 3func
                        ImGui::Spacing();
                        ImGui::Checkbox("Username", &Visuals::username);
                        ImGui::Spacing();
                        ImGui::Checkbox("Platform", &Visuals::platform);
                        ImGui::Spacing();
                        ImGui::Checkbox("Weapon", &Visuals::weapon);
                        ImGui::Spacing();
                        ImGui::Checkbox("Outline", &Visuals::outline);
                        ImGui::Spacing();
                        ImGui::Checkbox("HeadEsp", &Visuals::HeadEsp);
                        ImGui::Spacing();
                        ImGui::Checkbox("Distance", &Visuals::distance);
                        ImGui::Spacing();

                        ImGui::SetCursorPos(ImVec2(450, 330));
                        ImGui::SliderFloat("Distance render", &Visuals::render_distance, 0.f, 275.f);

                        ImGui::SetCursorPos(ImVec2(20, 340));
                        ImGui::Combo(E("BoxType"), &Visuals::box_types, E("2D\0\Rounded\0\Cornered\0\FilledBox\0"));

                        ImGui::SetCursorPos(ImVec2(20, 380));
                        ImGui::Combo(E("LineType"), &Visuals::line_type, E("Top\0\Bottom\0"));

                    }

                    // Misc 


                    if (visualsubs == 1)
                    {

                        ImGui::SetCursorPos(ImVec2(20, 35));
                        ImGui::BeginGroup();

                        ImGui::Checkbox("Fps", &Misc::fps);
                        ImGui::Checkbox("Crosshair", &Misc::Crosshair);
                        ImGui::Checkbox("AmmoCount", &Visuals::AmmoCount);
                        ImGui::Checkbox("Teamcheck", &Misc::Teamcheck);
                        ImGui::Checkbox("Vsync", &Misc::VSYNC);
                        ImGui::Checkbox("Kill Count", &Misc::KillCount);
                        ImGui::Checkbox("Player ID", &Misc::playerid);
                        ImGui::Checkbox("Render Count", &Misc::playercount);



            

                    }

                    ImGui::EndGroup();
                    ImGui::EndChild();
                        
                    }
                    ImGui::PopStyleVar();
                    
                    int tab2alpha = Animate("Tab2", "Tab2", tabs == 2, 255, 40.f, INTERP);
                    tab2alpha = ImClamp(tab2alpha, 0, 255);
                    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab2alpha / 255.f);
                    if (tabs == 2)
                    {
                        ImGui::SetCursorPos(ImVec2(200, 0));
                        ImGui::BeginChild("Child2", ImVec2(570, 495), false, ImGuiWindowFlags_NoMove);
                        ImGui::BeginChild("Child2", ImVec2(570, 495), false, ImGuiWindowFlags_NoScrollbar);

                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
                        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));

                        ImGui::SetCursorPos(ImVec2(20, 5));
                        if (ImGui::Button("Colors", ImVec2(260, 25)))
                            ColorsMisc = 0;

                        ImGui::SetCursorPos(ImVec2(290, 5));
                        if (ImGui::Button("Size", ImVec2(260, 25)))
                            ColorsMisc = 1;

                            ImGui::PopStyleColor(3);

                            if (ColorsMisc == 0)
                            {
                                ImGui::SetCursorPos(ImVec2(20, 35));
                                ImGui::BeginGroup();


                                



                                ImGui::Text("Visible");
                                ImGui::SameLine(0, 278);
                                ImGui::Text("InVisible");


                                ImGui::SetNextItemWidth(180);
                                ImGui::ColorEdit3("Box", Misc::box_visible);
                                ImGui::SameLine(0, 112);
                                ImGui::SetNextItemWidth(180);
                                ImGui::ColorEdit3("Box ", Misc::box_invisible);


                                ImGui::SetNextItemWidth(180);
                                ImGui::ColorEdit3("Box Fill", Misc::box_filled_visible);
                                ImGui::SameLine(0, 90);
                                ImGui::SetNextItemWidth(180);
                                ImGui::ColorEdit3("Box Fill ", Misc::box_filled_invisible);


                                ImGui::SetNextItemWidth(180);
                                ImGui::ColorEdit3("Skeleton", Misc::skeleton_visible);
                                ImGui::SameLine(0, 79);
                                ImGui::SetNextItemWidth(180);
                                ImGui::ColorEdit3("Skeleton ", Misc::skeleton_invisible);


                                ImGui::SetNextItemWidth(180);
                                ImGui::ColorEdit3("Text", Misc::text_visible);
                                ImGui::SameLine(0, 107);
                                ImGui::SetNextItemWidth(180);
                                ImGui::ColorEdit3("Text ", Misc::text_invisible);


                                ImGui::SetNextItemWidth(180);
                                ImGui::ColorEdit3("Line", Misc::snaplines_visible);
                                ImGui::SameLine(0, 110);
                                ImGui::SetNextItemWidth(180);
                                ImGui::ColorEdit3("Line ", Misc::snaplines_invisible);
                            }

                        

                            if (ColorsMisc == 1)
                            {
                                ImGui::SetCursorPos(ImVec2(20, 35));
                                ImGui::BeginGroup();

                               
                                ImGui::Text("Thickness");



                                ImGui::SetCursorPos(ImVec2(450, 60));
                                ImGui::SliderInt(E("Skeleton Thickness"), &Misc::skeleton_thick, 1.f, 5);
                                ImGui::SetCursorPos(ImVec2(450, 80));
                                ImGui::SliderInt(E("Boxs Thickness"), &Misc::box_thick, 1.f, 5);
                                ImGui::SetCursorPos(ImVec2(450, 100));
                                ImGui::SliderInt(E("Line Thickness"), &Misc::line_thick, 1.f, 5);
                                ImGui::SetCursorPos(ImVec2(450, 120));
                                ImGui::SliderInt(E("Head Circle Size"), &Misc::HeadSized, 1.f, 50);
                                ImGui::SetCursorPos(ImVec2(450, 140));
                                ImGui::SliderFloat("font size", &Misc::fontsize, 10.f, 15.0f);






                            }

                    ImGui::EndGroup();

                    ImGui::PopStyleColor(3);

                    ImGui::EndChild();
                }        
                ImGui::PopStyleVar();





                ImGui::End();

            }
        }

 



        auto draw() -> void
        {
            SPOOF_FUNC;

            ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.f);

            ImGui::StyleColorsDark();


            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            loop_game->actor_loop();

            menu();

            ImGui::Render();
            const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
            d3d_device_ctx->OMSetRenderTargets(1, &d3d_render_target, nullptr);
            d3d_device_ctx->ClearRenderTargetView(d3d_render_target, clear_color_with_alpha);
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());



            if (Misc::VSYNC) 
                {
                d3d_swap_chain->Present(0, 0);
                }
            else
            {
                d3d_swap_chain->Present(1, 0);
            }
            
            
               
        

        }

        auto render() -> bool {
            SPOOF_FUNC

                static RECT rect_og;
            MSG msg = { NULL };
            ZeroMemory(&msg, sizeof(MSG));

            while (msg.message != WM_QUIT)
            {

                UpdateWindow_Spoofed(window_handle);
                ShowWindow_Spoofed(window_handle, SW_SHOW);

                if (PeekMessageA_Spoofed(&msg, window_handle, 0, 0, PM_REMOVE))
                {
                    TranslateMessage_Spoofed(&msg);
                    DispatchMessage(&msg);
                }

                ImGuiIO& io = ImGui::GetIO();
                io.ImeWindowHandle = window_handle;
                io.DeltaTime = 1.0f / 60.0f;


                POINT p_cursor;
                GetCursorPos(&p_cursor);
                io.MousePos.x = p_cursor.x;
                io.MousePos.y = p_cursor.y;

                if (GetAsyncKeyState_Spoofed(VK_LBUTTON)) {
                    io.MouseDown[0] = true;
                    io.MouseClicked[0] = true;
                    io.MouseClickedPos[0].x = io.MousePos.x;
                    io.MouseClickedPos[0].x = io.MousePos.y;
                }
                else
                    io.MouseDown[0] = false;

                draw();

            }
            ImGui_ImplDX11_Shutdown();
            ImGui_ImplWin32_Shutdown();
            ImGui::DestroyContext();

            DestroyWindow(window_handle);

            return true;

        }

    };
} static render1::c_render* render = new render1::c_render();