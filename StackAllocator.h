#ifndef _ALLOCATOR_STACKALLOCATOR_
#define _ALLOCATOR_STACKALLOCATOR_

#include <cstdlib>

#define ALIGNUP( nAddress, nBytes ) ( (((uint)nAddress) + (nBytes)-1) & (~((nBytes)-1)) )

typedef	unsigned char	u8;
typedef	unsigned int	uint;

// Frame Allocator structure
struct	Frame_Allocator
{
	u8*	frame;
	int	heapNum;
};


class StackAllocator
{
public:

	//	Init and Shutdown
	int	initFrameMemorySystem(int sizeInBytes, int bytesAlignment);
	void    shutdownFrameMemorySystem();

	//	Assign Memory
	void*	allocateFrameMemory(int bytes, int heapNum);

	//	FramePointer
	Frame_Allocator	getFrame(int heapNum);
	void	releaseFrame(Frame_Allocator frame);

private:
	int	m_iBytesAlignment;	// Memory Alignement in bytes
	u8*	m_pMemoryBlock;		// Value returned by malloc
	u8*	m_pBaseandCap[2];	// [0]=Base pointer, [1]=Cap Pointer
	u8*	m_pFrame[2];		// [0]=Lower frame pointer, [1]=Upped frame pointer
};


#endif // _ALLOCATOR_STACKALLOCATOR_
