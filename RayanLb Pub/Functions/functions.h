#include <string.h>
#include <list>
#include <string>
#include "Functions/ue.h"

namespace Important1
{
	class func 
	{
	public:

		
		// Platform

		__forceinline auto platform(uintptr_t PlayerState) -> std::string
		{
			SPOOF_FUNC;

			uintptr_t test_platform = read<uintptr_t>(PlayerState + 0x438);
			wchar_t platform[64]{ 0 };
			io::readm(reinterpret_cast<PVOID>(test_platform), reinterpret_cast<uint8_t*>(platform), sizeof(platform));
			std::wstring platform_wstr(platform);
			std::string platform_str(platform_wstr.begin(), platform_wstr.end());
			return platform_str;
		}


		// Player Name

		auto get_player_name( __int64 player_state) -> std::string
		{
			SPOOF_FUNC;

			int pNameLength;
			_WORD* pNameBufferPointer;
			int i;
			char v25;
			int v26;
			int v29;

			char16_t* pNameBuffer;

			uintptr_t pNameStructure = read<uintptr_t> (player_state + 0xAF0);
			if (is_valid(pNameStructure)) {
				pNameLength = read<int>(pNameStructure + 0x10);
				if (pNameLength <= 0)
					return "AI";

				pNameBuffer = new char16_t[pNameLength];
				uintptr_t pNameEncryptedBuffer = read <uintptr_t>(pNameStructure + 0x8);
				if (is_valid(pNameEncryptedBuffer)) {
					read_array(pNameEncryptedBuffer, pNameBuffer, pNameLength);

					v25 = pNameLength - 1;
					v26 = 0;
					pNameBufferPointer = (_WORD*)pNameBuffer;

					for (i = (v25) & 3;; *pNameBufferPointer++ += i & 7) {
						v29 = pNameLength - 1;
						if (!(_DWORD)pNameLength)
							v29 = 0;

						if (v26 >= v29)
							break;

						i += 3;
						++v26;
					}

					std::u16string temp_wstring(pNameBuffer);
					delete[] pNameBuffer;
					return std::string(temp_wstring.begin(), temp_wstring.end());
				}
			}
		}




		auto in_screen(fvector2d screen_location) -> bool {
			SPOOF_FUNC;

			if (screen_location.x > 0 && screen_location.x < screen_width && screen_location.y > 0 && screen_location.y < screen_height) return true;
			else return false;
		}



		camera_position_s get_camera()
		{
			SPOOF_FUNC;

			camera_position_s camera;

			auto location_pointer = read <uintptr_t>(Undetected->uworld + 0x110);
			auto rotation_pointer = read <uintptr_t>(Undetected->uworld + 0x120);

			struct FNRot
			{
				double a; //0x0000
				char pad_0008[24]; //0x0008
				double b; //0x0020
				char pad_0028[424]; //0x0028
				double c; //0x01D0
			} fnRot;

			fnRot.a = read <double>(rotation_pointer);
			fnRot.b = read <double>(rotation_pointer + 0x20);
			fnRot.c = read <double>(rotation_pointer + 0x1D0); // gameinstance /0x1D8

			camera.location = read <fvector>(location_pointer);
			camera.rotation.x = asin(fnRot.c) * (180.0 / M_PI);
			camera.rotation.y = ((atan2(fnRot.a * -1, fnRot.b) * (180.0 / M_PI)) * -1) * -1;
			camera.fov = read <float>((uintptr_t)Undetected->player_controller + 0x394) * 90.f;
			return camera;
		}



		int dynamicFOV;


		inline fvector2d w2s(fvector WorldLocation)
		{
			SPOOF_FUNC;

			camera_postion = get_camera();

			if (WorldLocation.x == 0)
				return fvector2d(0, 0);

			_MATRIX tempMatrix = Matrix(camera_postion.rotation);
			fvector vAxisX = fvector(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
			fvector vAxisY = fvector(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
			fvector vAxisZ = fvector(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);
			fvector vDelta = WorldLocation - camera_postion.location;
			dynamicFOV = camera_postion.fov;
			fvector vTransformed = fvector(vDelta.dot(vAxisY), vDelta.dot(vAxisZ), vDelta.dot(vAxisX));
			if (vTransformed.z < 1.f)
				vTransformed.z = 1.f;
			return fvector2d((screen_width / 2.0f) + vTransformed.x * (((screen_width / 2.0f) / tanf(camera_postion.fov * (float)M_PI / 360.f))) / vTransformed.z, (screen_height / 2.0f) - vTransformed.y * (((screen_width / 2.0f) / tanf(camera_postion.fov * (float)M_PI / 360.f))) / vTransformed.z);
		}




		// prediction

		fvector Anis_Target_Prediction(fvector target, fvector targetVelocity, float projectileSpeed, float projectileGravityScale, float distance)
		{
			SPOOF_FUNC;

			float horizontalTime = distance / projectileSpeed;
			float verticalTime = distance / projectileSpeed;

			target.x += targetVelocity.x * horizontalTime;
			target.y += targetVelocity.y * horizontalTime;
			target.z += targetVelocity.z * verticalTime + abs(-980 * projectileGravityScale) * 0.5f * (verticalTime * verticalTime);

			return target;
		}




		fvector get_bone_3d(uint64_t Mesh, int32_t Bone)
		{
			uint64_t boneArray = read<uint64_t>(Mesh + 0x5B0 + (read<int>(Mesh + 0x5F8) * 0x10));
			FTransform bone = read<FTransform>(boneArray + (Bone * 0x60));
			FTransform componentToWorld = read<FTransform>(Mesh + 0x1C0);
			D3DMATRIX matrix = MatrixMultiplication(bone.ToMatrixWithScale(), componentToWorld.ToMatrixWithScale());
			return fvector(matrix._41, matrix._42, matrix._43);
		}



		static auto is_visible(uintptr_t skeletal_mesh) -> bool 
		{
			SPOOF_FUNC;

			auto last_submit = read <float>(skeletal_mesh + 0x2E8);
			auto last_render = read <float>(skeletal_mesh + 0x2F0);
			return (bool)(last_render + 0.06f >= last_submit);

		}

	
	};  static Important1::func* Important = new Important1::func();
}

int HeldWeaponType;

enum EFortWeaponType : int
{
	rifle = 0,
	shotgun = 1,
	smg = 2,
	sniper = 3
};

