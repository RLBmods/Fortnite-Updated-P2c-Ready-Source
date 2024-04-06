#include "Functions/keybind.h"

namespace camera1
{
	fvector location, rotation;
	float fov;
}

struct camera_position_s {
	fvector location{};
	fvector rotation{};
	float fov{};
};
inline camera_position_s camera_postion{};

#define deg2Rad(angleDegrees) ((angleDegrees) * M_PI / 180.0)
#define rad2Deg(angleRadians) ((angleRadians) * 180.0 / M_PI)
struct FMinimalViewInfo
{
	FMinimalViewInfo() : Location(), Rotation(), FOV(FOV) {}
	FMinimalViewInfo(fvector Location, fvector Rotation, float FOV) : Location(Location), Rotation(Rotation), FOV(FOV) {}

	fvector Location, Rotation;
	float FOV;
};

inline FMinimalViewInfo m_camera_information{};


typedef struct _D3DMATRIX1 {
	union {
		struct {
			double _11, _12, _13, _14;
			double _21, _22, _23, _24;
			double _31, _32, _33, _34;
			double _41, _42, _43, _44;

		};
		double m[4][4];
	};
} D3DMATRIX1;

typedef struct D3DXMATRIX1 {
	DOUBLE _ij;
} D3DXMATRIX1, * LPD3DXMATRIX1;

struct FPlane : public fvector
{
	double W;
};

struct FMatrix
{
	FPlane XPlane, YPlane, ZPlane, WPlane;

	FMatrix MatrixMultiplication(FMatrix Other)
	{
		FMatrix Copy = {};

		Copy.WPlane.x = this->WPlane.x * Other.XPlane.x + this->WPlane.y * Other.YPlane.x + this->WPlane.z * Other.ZPlane.x + this->WPlane.W * Other.WPlane.x;
		Copy.WPlane.y = this->WPlane.x * Other.XPlane.y + this->WPlane.y * Other.YPlane.y + this->WPlane.z * Other.ZPlane.y + this->WPlane.W * Other.WPlane.y;
		Copy.WPlane.z = this->WPlane.x * Other.XPlane.z + this->WPlane.y * Other.YPlane.z + this->WPlane.z * Other.ZPlane.z + this->WPlane.W * Other.WPlane.z;
		Copy.WPlane.W = this->WPlane.x * Other.XPlane.W + this->WPlane.y * Other.YPlane.W + this->WPlane.z * Other.ZPlane.W + this->WPlane.W * Other.WPlane.W;

		return Copy;
	}

	static FMatrix RotatorToMatrix(fvector Rotation)
	{
		auto ReturnValue = FMatrix();

		auto Pitch = (Rotation.x * 3.14159265358979323846 / 180);
		auto Yaw = (Rotation.y * 3.14159265358979323846 / 180);
		auto Roll = (Rotation.z * 3.14159265358979323846 / 180);

		auto sp = sin(Pitch);
		auto cp = cos(Pitch);
		auto sy = sin(Yaw);
		auto cy = cos(Yaw);
		auto sr = sin(Roll);
		auto cr = cos(Roll);

		ReturnValue.XPlane.x = cp * cy;
		ReturnValue.XPlane.y = cp * sy;
		ReturnValue.XPlane.z = sp;

		ReturnValue.YPlane.x = sr * sp * cy - cr * sy;
		ReturnValue.YPlane.y = sr * sp * sy + cr * cy;
		ReturnValue.YPlane.z = -sr * cp;

		ReturnValue.ZPlane.x = -(cr * sp * cy + sr * sy);
		ReturnValue.ZPlane.y = cy * sr - cr * sp * sy;
		ReturnValue.ZPlane.z = cr * cp;

		ReturnValue.WPlane.W = 0x1;

		return ReturnValue;
	}
};

uintptr_t viewStates;
uintptr_t viewMatrices;
D3DMATRIX1 invProjMatrix;

class Camera
{
public:

	void normalize(fvector& in)
	{
		SPOOF_FUNC
			while (in.x > 180.0f)
				in.x -= 360.0f;

		while (in.x < -180.0f)
			in.x += 360.0f;

		while (in.y > 180.0f)
			in.y -= 360.0f;

		while (in.y < -180.0f)
			in.y += 360.0f;

		in.z = 0;
	}

	auto calc_angle(fvector LocalPos, fvector WorldPos) -> fvector {
		SPOOF_FUNC
		fvector RelativePos = WorldPos - LocalPos;
		float yaw = atan2(RelativePos.y, RelativePos.x) * 180.0f / M_PI;
		float pitch = -((acos(RelativePos.z / LocalPos.distance(WorldPos)) * 180.0f / M_PI) - 90.0f);

		return fvector(pitch, yaw, 0);
	}




	auto in_screen(fvector2d screen_location) -> bool {
		SPOOF_FUNC

			if (screen_location.x > 0 && screen_location.x < screen_width && screen_location.y > 0 && screen_location.y < screen_height) return true;
			else return false;
	}

}; inline Camera* camera;


inline std::wstring MBytesToWString(const char* lpcszString)
{
	SPOOF_FUNC

		int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring wString = (wchar_t*)pUnicode;
	delete[] pUnicode;
	return wString;
}
inline std::string WStringToUTF8(const wchar_t* lpwcszWString)
{
	SPOOF_FUNC

		char* pElementText;
	int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}

inline void DrawString(float fontSize, int x, int y, ImColor color, bool bCenter, bool stroke, const char* pText, ...)
{
	va_list va_alist;
	char buf[128] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x = x - textSize.x / 4;
		y = y - textSize.y;
	}
	//if (stroke)
	//{
	//	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
	//	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
	//	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
	//	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
	//}
	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), ImColor(color), text.c_str());
}


inline void DrawFilledRect(int x, int y, int w, int h, ImU32 color, bool round = false)
{

	if (round)
		ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, ImDrawCornerFlags_All, 30);
	else
		ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
}

std::string string_To_UTF8(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}




void FovCircle(float r, bool filled, bool rainbow, bool toMouse) {
	auto& io = ImGui::GetIO();

	ImVec2 center = toMouse ? ImVec2(io.MousePos.x, io.MousePos.y) : ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);
	auto drawList = ImGui::GetBackgroundDrawList();
	int sides = 100;
	for (int i = 0; i < sides; ++i) {
		auto pos = center;
		float angle = (i / static_cast<float>(sides)) * 2 * M_PI;
		auto lastPos = ImVec2(pos.x + cos(angle) * r, pos.y + sin(angle) * r);
		auto nextPos = ImVec2(pos.x + cos(angle + 2 * M_PI / sides) * r, pos.y + sin(angle + 2 * M_PI / sides) * r);

		ImU32 currentColor = rainbow ? ImGui::ColorConvertFloat4ToU32(ImColor::HSV((fmod(ImGui::GetTime(), 5.0f) / 5.0f - i / static_cast<float>(sides)) + 1.0f, 0.5f, 1.0f)) : IM_COL32(255, 255, 255, 255);

		ImU32 fillCol = filled ? ImGui::ColorConvertFloat4ToU32({ ImGui::ColorConvertU32ToFloat4(currentColor).x, ImGui::ColorConvertU32ToFloat4(currentColor).y, ImGui::ColorConvertU32ToFloat4(currentColor).z, 0.2f }) : 0; // 0.2f = fill opacity

		if (Aimbot::FovFilled) 
		{
			ImVec2 triangle[3] = { lastPos, nextPos, center };
			drawList->AddConvexPolyFilled(triangle, 3, fillCol); // fill
		}
		if (Visuals::outline)
		{
			drawList->AddLine(lastPos, nextPos, IM_COL32(0, 0, 0, 255), 4.f); // outline 
		}
			drawList->AddLine(lastPos, nextPos, currentColor, 2.f); // main 
	}
}







void colorbox(int x, int y, int w, int h, int thickness, int borderPx, bool rainbow) {
	auto& io = ImGui::GetIO();

	//ImVec2 center = toMouse ? ImVec2(io.MousePos.x, io.MousePos.y) : ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);
	auto drawList = ImGui::GetBackgroundDrawList();
	int sides = 100;
	for (int i = 0; i < sides; ++i) {
		//auto pos = center;
		float angle = (i / static_cast<float>(sides)) * 2 * M_PI;
		//auto lastPos = ImVec2(pos.x + cos(angle) * r, pos.y + sin(angle) * r);
		//auto nextPos = ImVec2(pos.x + cos(angle + 2 * M_PI / sides) * r, pos.y + sin(angle + 2 * M_PI / sides) * r);

		ImU32 currentColor = rainbow ? ImGui::ColorConvertFloat4ToU32(ImColor::HSV((fmod(ImGui::GetTime(), 5.0f) / 5.0f - i / static_cast<float>(sides)) + 1.0f, 0.5f, 1.0f)) : IM_COL32(255, 255, 255, 255);


		//drawList->AddLine(lastPos, nextPos, currentColor, 2.f); // main 
		int cornerBoxLength = w / 3;
		int cornerBoxHeight = h / 5;
		DrawFilledRect(x + borderPx, y, w, borderPx, ImColor(10, 10, 10, 180));


		ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + cornerBoxLength, y), ImVec2(x, y), currentColor, thickness);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(x, y + cornerBoxHeight), ImVec2(x, y), currentColor, thickness);


		ImGui::GetForegroundDrawList()->AddLine(ImVec2((x + w) - cornerBoxLength, y), ImVec2(x + w, y), currentColor, thickness);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2((x + w), y + cornerBoxHeight), ImVec2(x + w, y), currentColor, thickness);


		ImGui::GetForegroundDrawList()->AddLine(ImVec2(x + cornerBoxLength, (y + h)), ImVec2(x, y + h), currentColor, thickness);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(x, (y + h) - cornerBoxHeight), ImVec2(x, y + h), currentColor, thickness);


		ImGui::GetForegroundDrawList()->AddLine(ImVec2((x + w) - cornerBoxLength, (y + h)), ImVec2(x + w, y + h), currentColor, thickness);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2((x + w), (y + h) - cornerBoxHeight), ImVec2(x + w, y + h), currentColor, thickness);

	}
}

char* wchar_to_char(const wchar_t* pwchar)
{
	int currentCharIndex = 0;
	char currentChar = pwchar[currentCharIndex];

	while (currentChar != '\0')
	{
		currentCharIndex++;
		currentChar = pwchar[currentCharIndex];
	}

	const int charCount = currentCharIndex + 1;

	char* filePathC = (char*)malloc(sizeof(char) * charCount);

	for (int i = 0; i < charCount; i++)
	{
		char character = pwchar[i];

		*filePathC = character;

		filePathC += sizeof(char);

	}
	filePathC += '\0';

	filePathC -= (sizeof(char) * charCount);

	return filePathC;
}
typedef struct _LootEntity {
	std::string GNames;
	uintptr_t ACurrentItem;
}LootEntity;

static std::vector<LootEntity> LootEntityList;


