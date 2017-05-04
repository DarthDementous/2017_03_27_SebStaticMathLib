#pragma once

// FYI this would be required if you were creating a dll rather than a lib file. LIBRARY_API needs to be in front of every class name and separate functions!
#ifdef DLLTEST_EXPORTS
///DLL
#define LIBRARY_API   __declspec(dllexport)
#define EXPIMP_TEMPLATE    // Blank because dllexport isn't compatable with extern
#else
#define EXPIMP_TEMPLATE extern // Necessary for template class instantiation
#ifdef _LIB // Blank because static lib doesn't need it
#define LIBRARY_API
#else 
#define LIBRARY_API   __declspec(dllimport)   
#endif
#endif
