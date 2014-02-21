#version 420
uniform uvec2 ScreenSize;

coherent uniform layout(size1x32) uimage2D ABufferIndex;
coherent uniform layout(size1x32) uimage2D ABufferCounts;
coherent uniform layout(size1x32) uimage2D ABufferSemaphore;

void SetCurrentPage(ivec2 coords, uint newpageidx)
{
	imageStore(ABufferIndex, coords, uvec4(newpageidx, 0U, 0U, 0U));
}

void SetFragCounter(ivec2 coords, uint val)
{
	imageStore(ABufferCounts, coords, uvec4(val, 0U, 0U, 0U));
}

void ClearSemaphore(ivec2 coords)
{
	imageStore(ABufferSemaphore, coords, uvec4(0U, 0U, 0U, 0U));
}

void main ()
{
	ivec2 coords=ivec2(gl_FragCoord.xy);

	if(coords.x >= 0 
	&& coords.y >= 0 
	&& coords.x < ScreenSize.x
	&& coords.y < ScreenSize.y)
	{
		SetCurrentPage(coords, 0U);
		SetFragCounter(coords, 0U);
		ClearSemaphore(coords);
	}

	//Discard fragment so nothing is writen to the framebuffer
	discard;
}