// smartPointer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>

class packet
{
public:
	int _iVal;

	packet() {
		_iVal = 10;
	}
	~packet()
	{

	}
};

class smartptr
{
public:
	ULONG * refCount;
	packet * pk;

	// 처음 생성 할때 
	smartptr(packet * ptr)
	{
		pk = ptr;
		refCount = new ULONG;
		*refCount = 1;
	}
	// 만약 복사 생성자 라면
	smartptr(const smartptr & smpt)
	{
		pk = smpt.pk;
		// 기존의 레퍼런스 카운트 증가.
		InterlockedIncrement(smpt.refCount);
		// 현재 레퍼런스 카운트 
		refCount = smpt.refCount;
	}
	~smartptr()
	{
		InterlockedDecrement(&*refCount);
		if (*refCount <= 0)
		{
			delete refCount;
			// 얼록 프리 pk
		}
	}
};

void test(smartptr pk)
{
	if (*pk.refCount == 1)
		test(pk);
}

int main()
{
	smartptr smpt = new packet;
	test(smpt);
	test(smpt);
	int a = 0;
}
