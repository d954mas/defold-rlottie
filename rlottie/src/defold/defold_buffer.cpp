#include "defold_buffer.h"

#include <dmsdk/sdk.h>
#include <defold_buffer.h>

Buffer BufferCreate(int width, int height, int channels, dmScript::LuaHBuffer* luaBuffer){
    Buffer buffer;
	buffer.width = width;
	buffer.height = height;
	buffer.channels = channels;
	dmBuffer::HBuffer hBuffer = luaBuffer->m_Buffer;
	uint32_t size_ignored = 0;
	dmBuffer::Result r = dmBuffer::GetBytes(hBuffer, (void**)&buffer.stream, &size_ignored);
    return buffer;
}

void BufferClear(Buffer &buffer){
	int size = buffer.width * buffer.height * buffer.channels;
	for(int i=0; i< size; i++){
		buffer.stream[i] = 0;
	}
}