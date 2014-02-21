#version 420
vec4 Evaluate ();

layout (early_fragment_tests) in;

in vec2 TextureCoordinate;

coherent uniform layout(r32ui)  uimage2D ABufferIndex;
coherent uniform layout(r32ui)  uimage2D ABufferCounts;
coherent uniform layout(r32ui)  uimage2D ABufferSemaphore;

coherent uniform layout(r32ui) uimageBuffer PageLinks;
coherent uniform layout(rgba8) imageBuffer ColorPages;
coherent uniform layout(r32f)  imageBuffer DepthPages;

#define PageSize 8
layout(binding = 0) uniform atomic_uint PageCounter;

uniform uint MaxPageCount;

bool AttemptAcquireSemaphore(ivec2 coords)
{
	return (imageAtomicExchange(ABufferSemaphore, coords, 1U)==0U);
}

void ReleaseSemaphore(ivec2 coords)
{
	imageAtomicExchange(ABufferSemaphore, coords, 0U);
}

uint GetCurrentPage(ivec2 coords)
{
	return imageLoad(ABufferIndex, coords).x;
}

void SetCurrentPage(ivec2 coords, uint newpageidx)
{
	imageStore(ABufferIndex, coords, uvec4(newpageidx, 0U, 0U, 0U));
}

uint GetFragCounter(ivec2 coords)
{
	return imageLoad(ABufferCounts, coords).x;
}
void SetFragCounter(ivec2 coords, uint val)
{
	imageStore(ABufferCounts, coords, uvec4(val, 0U, 0U, 0U));
}

void IncrementFragCounter (ivec2 coords, uint value)
{
	imageAtomicAdd(ABufferCounts, coords, value);
}

uint IncrementPageCounter ()
{
	return atomicCounterIncrement(PageCounter);
}

uint GetPageLink (uint page)
{
	return imageLoad(PageLinks, int(page)).x;
}

void SetPageLink (uint page, uint pointer)
{
	imageStore(PageLinks, int(page), uvec4(pointer, 0U, 0U, 0U));
}

vec4 GetColor(uint index)
{
	return imageLoad(ColorPages, int(index));
}
void SetColor(uint index, vec4 val)
{
	imageStore(ColorPages, int(index), val);
}

vec4 GetDepth(uint index)
{
	return imageLoad(DepthPages, int(index));
}
void SetDepth(uint index, float val)
{
	imageStore(DepthPages, int(index), vec4(val,0.0,0.0,0.0));
}


vec4 Evaluate ();

out vec4 Output;

void AddFrag (vec4 color, float depth)
{
	ivec2 icoords=ivec2(gl_FragCoord.xy);
	uint CurrentPage = 0;
	uint FragIndex = 0;
	uint InternalPageIndex = 0;
	
	int ii = 0; //prevents infinite loops
	bool acquired = false;
	while (!acquired && ii++ < 1000)
	{
		if (AttemptAcquireSemaphore (icoords))
		{
			acquired = true;
			CurrentPage = GetCurrentPage(icoords);
			FragIndex   = GetFragCounter(icoords);
			InternalPageIndex = FragIndex % PageSize;
			
			if (InternalPageIndex == 0)
			{
				//First fragment in a page... Allocate
				uint NewPageIndex = IncrementPageCounter ();
				if (NewPageIndex < MaxPageCount)
				{
					//Link the list
					SetPageLink (NewPageIndex, CurrentPage);
					
					//Set the front pointer
					SetCurrentPage(icoords, NewPageIndex);
					CurrentPage = NewPageIndex;
				}
				else
				{
					//There's no space!
					//Nullptr
					CurrentPage = 0;
				}
			}
			
			//Increase the length of the list
			if (CurrentPage != 0)
				IncrementFragCounter(icoords,1); //Increment if there's space
				
			ReleaseSemaphore(icoords);
		}
	}
	
	if (CurrentPage == 0)
	{
		Output = vec4 (1,0,1,1);
		return;
	}
	
	uint pointer = CurrentPage * PageSize + InternalPageIndex;
	
	SetColor (pointer, color);
	SetDepth (pointer, depth);
	
	if (CurrentPage != 0)
	{ discard; }
}

void main ()
{
	AddFrag(Evaluate(),gl_FragCoord.z);
}