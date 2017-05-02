#pragma once

// FYI this would be required if you were creating a dll rather than a lib file. LIBRARY_API needs to be in front of every class name and separate functions!
#ifdef DLLTEST_EXPORTS
///DLL
#define LIBRARY_API   __declspec(dllexport)         
#else
///LIB
#define LIBRARY_API   __declspec(dllimport)         
#endif