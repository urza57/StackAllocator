#include "StackAllocator.h"

int	StackAllocator::initFrameMemorySystem(int sizeInBytes, int bytesAlignment)
{
	// Make sure sizeInBytes is amultiple of bytesAlignment
	sizeInBytes = ALIGNUP( sizeInBytes, bytesAlignment );

	m_pMemoryBlock = (u8*)malloc(sizeInBytes + bytesAlignment);

	if ( m_pMemoryBlock == 0 )
	{
		return 1;
	}

	m_iBytesAlignment = bytesAlignment;

	// Set up base pointer
	m_pBaseandCap[0] = (u8*)ALIGNUP( m_pMemoryBlock, bytesAlignment );

	m_pBaseandCap[1] = (u8*)ALIGNUP( m_pMemoryBlock + sizeInBytes, bytesAlignment );

	// Init lower and upped frame pointer

	m_pFrame[0] = m_pBaseandCap[0];
	m_pFrame[1] = m_pBaseandCap[1];

	return 0;
}


void StackAllocator::shutdownFrameMemorySystem()
{
	free(m_pMemoryBlock);
}


void* StackAllocator::allocateFrameMemory(int bytes, int heapNum)
{
	u8*	mem;

	// Align the request size
	bytes = ALIGNUP( bytes, m_iBytesAlignment);

	// Check for available memory
	if (m_pFrame[0] + bytes > m_pFrame[1])
	{
		// insufficient memory
		return 0;
	}

	if (heapNum)
	{
		// Allocate form upped heap, down
		m_pFrame[1] -= bytes;
		mem = m_pFrame[1];
	}
	else
	{
		// Allocate form lower heap, up
		mem = m_pFrame[0];
		m_pFrame[0] += bytes;
	}

	return (void*)mem;
}


Frame_Allocator	StackAllocator::getFrame(int heapNum)
{
	Frame_Allocator frame;

	frame.frame = m_pFrame[heapNum];
	frame.heapNum = heapNum;

	return frame;
}


void StackAllocator::releaseFrame(Frame_Allocator frame)
{
	m_pFrame[frame.heapNum] = frame.frame;
}
