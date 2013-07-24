#pragma once

template<typename T>
struct PointerGuard
{
	PointerGuard(T** ptr) : Pointer(ptr) {};
	~PointerGuard(){ delete (*Pointer); };
	T** Pointer;
};