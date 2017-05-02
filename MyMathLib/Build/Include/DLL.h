#pragma once

// FYI this would be required if you were creating a dll rather than a lib file. LIBRARY_API needs to be in front of every function and constructor!
#ifdef MYMATHLIB_EXPORTS
#define LIBRARY_API   __declspec(dllexport) 
#else 
#define LIBRARY_API   __declspec(dllimport) 
#endif