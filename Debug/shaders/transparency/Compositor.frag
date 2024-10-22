#version 420
vec4 Evaluate ();

layout (early_fragment_tests) in;

in vec2 TextureCoordinate;

#include "shaders/transparency/Functions.hglsl"

vec4 Evaluate ();

out vec4 Output;

void AddFrag (vec4 color, float depth)
{
	if (color.a < 0.00001)
	{
		discard;
	}

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