#pragma once

#include <cstdint>
#include <basetsd.h>
#include <WTypesbase.h>
#include <TlHelp32.h>





uint64_t base_address;





#define find_base_address CTL_CODE(FILE_DEVICE_UNKNOWN, 0x1588, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define read_process_memory CTL_CODE(FILE_DEVICE_UNKNOWN, 0x1589, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define write_process_memory CTL_CODE(FILE_DEVICE_UNKNOWN, 0x1590, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define code_security 0x85b3e12



typedef struct _rw {
	INT32 security;
	INT32 process_id;
	ULONGLONG address;
	ULONGLONG buffer;
	ULONGLONG size;
	BOOLEAN write;
} rw, * prw;

typedef struct _ba {
	INT32 security;
	INT32 process_id;
	ULONGLONG* address;
} ba, * pba;

typedef struct _ga {
	INT32 security;
	ULONGLONG* address;
} ga, * pga;







enum REQUEST_TYPE : int
{
	NONE,
	BASE,
	WRITE,
	READ
};
typedef struct _DRIVER_REQUEST
{
	REQUEST_TYPE type;
	HANDLE pid;
	PVOID address;
	PVOID buffer;
	SIZE_T size;
	PVOID base;
} DRIVER_REQUEST, * PDRIVER_REQUEST;


namespace io {
	HANDLE driver_handle;
	INT32 process_id;

	bool find_driver()
	{
		driver_handle = CreateFileA(("\\\\.\\genericdrv"), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (!driver_handle || (driver_handle == INVALID_HANDLE_VALUE))
			return false;

		return true;
	}







	void readm(PVOID address, PVOID buffer, DWORD size)
	{
		DRIVER_REQUEST out{};
		out.type = READ;
		out.pid = (HANDLE)process_id;
		out.address = address;
		out.buffer = buffer;
		out.size = size;
		DeviceIoControl(driver_handle, read_process_memory, &out, sizeof(out), &out, sizeof(out), nullptr, nullptr);
	}






	inline bool read1(const std::uintptr_t address, void* buffer, const std::size_t size)
	{
		if (buffer == nullptr || size == 0) {
			return false;
		}
		readm(reinterpret_cast<PVOID>(address), buffer, static_cast<DWORD>(size));
	}



	void writem(PVOID address, PVOID buffer, DWORD size)
	{
		DRIVER_REQUEST out{};
		out.type = WRITE;
		out.pid = (HANDLE)process_id;
		out.address = address;
		out.buffer = buffer;
		out.size = size;
		DeviceIoControl(driver_handle, write_process_memory, &out, sizeof(out), &out, sizeof(out), nullptr, nullptr);
	}


	uintptr_t get_base_address()
	{
		DRIVER_REQUEST io_info{};
		io_info.type = BASE;
		io_info.pid = (HANDLE)process_id;

		DeviceIoControl(driver_handle, find_base_address, &io_info, sizeof(io_info), &io_info, sizeof(io_info), nullptr, nullptr);
		return (uintptr_t)io_info.base;
	}

	INT32 find_process(LPCTSTR process_name)
	{
		PROCESSENTRY32 pt;
		HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pt.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hsnap, &pt)) {
			do {
				if (!lstrcmpi(pt.szExeFile, process_name)) {
					CloseHandle(hsnap);
					process_id = pt.th32ProcessID;
					return pt.th32ProcessID;
				}
			} while (Process32Next(hsnap, &pt));
		}
		CloseHandle(hsnap);

		return { NULL };
	}
}




template <typename T>
T read(uint64_t address) {
	T buffer{ };
	io::readm((PVOID)address, &buffer, sizeof(T));
	return buffer;
}


template<typename T>
bool read_array(uintptr_t address, T out[], size_t len)
{
	for (size_t i = 0; i < len; ++i)
	{
		out[i] = read<T>(address + i * sizeof(T));
	}
	return true; // you can add additional checks to verify successful reads
}




template <typename T>
T write(uint64_t address, T buffer) {

	io::writem((PVOID)address, &buffer, sizeof(T));
	return buffer;
}


bool is_valid(const uint64_t adress)
{
	if (adress <= 0x400000 || adress == 0xCCCCCCCCCCCCCCCC || reinterpret_cast<void*>(adress) == nullptr || adress >
		0x7FFFFFFFFFFFFFFF) {
		return false;
	}
	return true;
}

























