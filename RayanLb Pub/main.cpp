#include <Windows.h>
#include "Menu/render.h"
#include "protection/xorst.h"
#include <ntstatus.h>
#include <tchar.h>
#include <Shlobj.h>
#include <iostream>
#include <sapi.h>
#include "auth.hpp"

#pragma comment(lib, "ntdll.lib")


using namespace KeyAuth;

auto name = skCrypt(""); // application name. right above the blurred text aka the secret on the licenses tab among other tabs
auto ownerid = skCrypt(""); // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
auto secret = skCrypt(""); // app secret, the blurred text on licenses tab and other tabs
auto version = skCrypt("1.0"); // leave alone unless you've changed version on website
auto url = skCrypt("https://keyauth.win/api/1.2/"); // change if you're self-hosting

api KeyAuthApp(name.decrypt(), ownerid.decrypt(), secret.decrypt(), version.decrypt(), url.decrypt());



HWND windows = NULL;
#define debug false
#define driver false




namespace gay {
	int choice;
}


// Speak Driver loaded
void SpeakText(const wchar_t* text) {
	CoInitialize(NULL);
	ISpVoice* pVoice = NULL;
	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
	if (SUCCEEDED(hr)) {
		hr = pVoice->Speak(text, 0, NULL);
		pVoice->Release();
		pVoice = NULL;
	}
	CoUninitialize();
}



auto main() -> int {
	LI_FN(SetConsoleTitleA)(skCrypt(("RayanLB Public")));
	mouse_interface();
	input->initialize();

	name.clear(); ownerid.clear(); secret.clear(); version.clear(); url.clear();
	KeyAuthApp.init();

	if (!KeyAuthApp.data.success) {
		std::cout << skCrypt("[!] Error: ") << KeyAuthApp.data.message;
		Sleep(1500);
		exit(1);
	}

	int option;
	std::string key;
	std::cout << skCrypt("[+] Key: ");
	std::cin >> key;


	key = (key.c_str());

	KeyAuthApp.license(key);

	if (!KeyAuthApp.data.success) {
		std::cout << skCrypt("[!] Error: ") << KeyAuthApp.data.message;
		Sleep(1500);
		exit(1);
	}
	std::system("cls");


	std::cout << "Choose an overlay: \n";
	std::cout << "1. Medal Overlay\n"; // Medal
	std::cout << "2. Nvidia GeForce Overlay\n"; // Nvidia
	std::cout << "3. FPSMonitor Overlay\n"; // Monitor
	std::cout << "4. OBS Overlay\n"; // obs
	std::cout << "5. Visual Studio Overlay\n"; // visual studio
	std::cout << "Enter your choice: ";
	std::cin >> gay::choice;

	switch (gay::choice) {
	case 1:
		window_handle = FindWindowA_Spoofed(E("MedalOverlayClass"), E("MedalOverlay")); // Medal
		break;
	case 2:
		window_handle = FindWindowA_Spoofed(E("CEF-OSC-WIDGET"), E("NVIDIA Geforce Overlay")); // Nvidia
		break;
	case 3:
		window_handle = FindWindowA_Spoofed(E("GDI+ Hook Class"), E("GDI+ Window (FPSMonitor)")); // Monitor
		break;
	case 4:
		window_handle = FindWindowA_Spoofed(E("GDI+ Hook Window Class"), E("GDI+ Window (obs64.exe)")); // obs
		break;
	case 5:
		window_handle = FindWindowA_Spoofed(E("CiceroUIWndFrame"), E("CiceroUIWndFrame")); // visual studio
		break;
	default:
		std::cout << "Invalid choice." << std::endl;
		return false;
	}

	if (!window_handle)
	{
		MessageBoxA(0, skCrypt("{!} Overlay Failed -> Make A Ticket."), skCrypt(""), MB_ICONINFORMATION);
		return false;
	}

	

	std::system("cls");
	


	
		
	screen_width = GetSystemMetrics(SM_CXSCREEN), screen_height = GetSystemMetrics(SM_CYSCREEN);



	

	io::find_driver();

	while (windows == NULL)
	{

		XorS(wind, "Fortnite  ");
		windows = FindWindowA_Spoofed(0, wind.decrypt());
	}

	io::find_process(E("FortniteClient-Win64-Shipping.exe"));
	base_address = io::get_base_address();


	// Loaded

	std::cout << E(" base_address -> ") << io::get_base_address << std::endl;
	//SpeakText(L"Anis Private Cheat Loaded!");


	

	//LI_FN(system)(E("curl https://cdn.discordapp.com/attachments/1217428145993682997/1217445997962072064/fortnite.otf --silent -o C:\\fortnite.otf"));


	// Kill exe`
	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL) {
	ShowWindow(hwnd, SW_HIDE);
	}
	
	
	



	std::thread([&]()
		{
			while (true)
			{
				loop_game->cache_entities();
				loop_game->weapon_loop();
			}
		}).detach();
		


		render->hijack();
		render->imgui();
		render->render();
		return 0;
}