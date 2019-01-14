#ifdef _WIN32

#include "App/app_io.h"

int initialize_memory(Memory * memory, size_t size, const char * location) {
    
	MemoryImpl * impl = &memory->impl;

	DWORD dwAttrib = GetFileAttributes(location);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));

	DWORD open_mode = ((dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_NORMAL)) ?
		OPEN_EXISTING : CREATE_ALWAYS;

	impl->file = CreateFile(
		memory->location,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		open_mode,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
		NULL
	);

	if (impl->file == INVALID_HANDLE_VALUE) {
		return INIT_FAIL;
	}

	impl->mapping = CreateFileMapping(
		impl->file,
		PAGE_READWRITE,
		NULL,
		HIWORD(size),
		LOWORD(size),
		location
	);

	if (impl->mapping == NULL) {
		CloseHandle(impl->file);
		return INIT_FAIL;
	}

	memory->ptr = MapViewOfFile(
		impl->mapping,
		FILE_MAP_ALL_ACCESS,
		0, 0, 0
	);

	if (memory->ptr == NULL) {
		CloseHandle(impl->file);
		CloseHandle(impl->mapping);
		return INIT_FAIL;
	}

	return INIT_OK;
}

int resize(Memory * memory, size_t new_size) {
    deinitialize(memory);
    
    return initialize_memory(memory, new_size, memory->location);
}

int deinitialize(Memory * memory) {

	MemoryImpl * impl = &memory->impl;

	CloseHandle(impl->file);
	CloseHandle(impl->mapping);

	UnmapViewOfFile(memory->ptr);

	return INIT_OK;
}

#endif
