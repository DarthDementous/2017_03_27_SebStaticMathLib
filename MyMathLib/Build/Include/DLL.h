#pragma once

// FYI this would be required if you were creating a dll rather than a lib file. LIBRARY_API needs to be in front of every function and constructor!
#ifdef MYMATHLIB_EXPORTS
#define LIBRARY_API   __declspec(dllexport)
//Explicit instantiation to make template classes work with DLL exporting
//template<class T>
//class Vector2 {
//	class template Vector2<int>;
//	class template Vector2<float>;
//	class template Vector2<double>;
//	class template Vector2<short>;
//};
//
//template<class T>
//class Vector3 {
//	class template Vector3<int>;
//	class template Vector3<float>;
//	class template Vector3<double>;
//	class template Vector3<short>;
//};
//
//template<class T>
//class Vector4 {
//	class template Vector4<int>;
//	class template Vector4<float>;
//	class template Vector4<double>;
//	class template Vector4<short>;
//};
//
//template<class T>
//class Matrix2 {
//	class template Matrix2<int>;
//	class template Matrix2<float>;
//	class template Matrix2<double>;
//	class template Matrix2<short>;
//};
//
//template<class T>
//class Matrix3 {
//	class template Matrix3<int>;
//	class template Matrix3<float>;
//	class template Matrix3<double>;
//	class template Matrix3<short>;
//};
//
//template<class T>
//class Matrix4 {
//	class template Matrix4<int>;
//	class template Matrix4<float>;
//	class template Matrix4<double>;
//	class template Matrix4<short>;
//};

#else 
#define LIBRARY_API   __declspec(dllimport) 
#endif