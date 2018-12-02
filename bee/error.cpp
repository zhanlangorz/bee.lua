#include <bee/error.h>
#if defined(_WIN32)
#include <Windows.h>
#include <bee/error/windows_category.h>
#else
#include <errno.h>
#endif

namespace bee {
	int last_syserror() {
#if defined(_WIN32)
		return ::GetLastError();
#else
		return errno;
#endif
	}

	int last_neterror() {
#if defined(_WIN32)
		return ::WSAGetLastError();
#else
		return errno;
#endif
	}

	static std::error_code make_error_code(int err) {
#if defined(_WIN32)
		return std::error_code(err, windows_category());
#else
		return std::error_code(err, std::generic_category());
#endif
	}

	std::system_error make_syserror(const char* message) {
		return std::system_error(make_error_code(last_syserror()), message ? message : "");
	}

	std::system_error make_neterror(const char* message) {
		return std::system_error(make_error_code(last_neterror()), message ? message : "");
	}

	std::system_error make_error(int err, const char* message) {
		return std::system_error(make_error_code(err), message ? message : "");
	}
}