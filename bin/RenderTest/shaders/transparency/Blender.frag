#version 420
uniform uvec2 ScreenSize;

#include "shaders/transparency/Functions.hglsl"

#define BlendBufferSize 64

vec4  BlendBufferColors [BlendBufferSize];
float BlendBufferDepths [BlendBufferSize];
uint   BlendBufferModes  [BlendBufferSize];

//Iterates through pages populating the blendbuffer
void FillBlendBuffer (uint page, uint count)
{
	//Load fragments into a local memory array for sorting
	uint CurrentPage = page;
	int pageindex=0;
	int fragindex=0;
	uint fragmax = min(count,BlendBufferSize);
	while(CurrentPage !=0)
	{
		uint elementcount;
		if(pageindex==0)
		{
			elementcount = count % (PageSize);
			if (elementcount==0)
				elementcount=PageSize;
		}
		else
		{
			elementcount = PageSize;
		}

		uint PagePointer = CurrentPage * PageSize;
		
		for (int i=0; i < elementcount; i++)
		{
			if (fragindex < fragmax)
			{
				BlendBufferColors[fragindex]=GetColor(PagePointer+i);
				BlendBufferDepths[fragindex]=GetDepth(PagePointer+i);
				BlendBufferModes [fragindex]=GetMode (PagePointer+i);
			}
			else
			{
				return;
			}
			fragindex++;
		}
		
		CurrentPage = GetPageLink(CurrentPage);
		pageindex++;
	}
}

vec4 BlendPages (uint page, uint count)
{
	vec4 result = vec4(0.0);

	//Load fragments into a local memory array for sorting
	uint CurrentPage = page;
	int pageindex=0;
	int fragindex=0;
	
	while(fragindex < count)
	{
		uint elementcount;
		if(pageindex==0)
		{
			elementcount = count % (PageSize);
			if (elementcount==0)
				elementcount=PageSize;
		}
		else
		{
			elementcount = PageSize;
		}

		uint PagePointer = CurrentPage * PageSize;
		
		for (int i=0; i < elementcount; i++)
		{
			vec4 color = GetColor(PagePointer+i);
			color.rgb = color.rgb * color.a;
	
			result = color + result * (1.0 - color.a);
			//result = result + vec4 (color.a,color.a,color.a,1);
			fragindex++;
		}
		
		CurrentPage = GetPageLink(CurrentPage);
		pageindex++;
	}
	
	return result;
}

//Swaps two blend buffer indices
void SwapBlendBuffer(int a, int b)
{
	uint tempmode = BlendBufferModes[a];
	vec4 tempcolor = BlendBufferColors[a];
	float tempdepth = BlendBufferDepths[a];
	
	BlendBufferDepths[a] = BlendBufferDepths[b];
	BlendBufferColors[a] = BlendBufferColors[b];
	BlendBufferModes[a] = BlendBufferModes[b];
	
	BlendBufferDepths[b] = tempdepth;
	BlendBufferColors[b] = tempcolor;
	BlendBufferModes[b] = tempmode;
}

//Bubble sorts the blend buffer
void SortBlendBuffer(int count)
{
	for (int i = (count - 2); i >= 0; --i) 
	{
		for (int j = 0; j <= i; ++j) 
		{
			if (BlendBufferDepths[j] > BlendBufferDepths[j+1]) 
			{
				SwapBlendBuffer(j,j+1);
			}
		}
	}	
}

//Iterates the list, blending via alpha
vec4 Blend (uint count)
{
	vec4 result = vec4(0.0);
	
	for (int i = 0; i < count; ++i)
	{
		if (BlendBufferModes[i] == 0)
		{
			vec4 color = BlendBufferColors[i];
			color.rgb = color.rgb * color.a;
			
			//result = color + result * (1.0 - color.a);
			result = result + color * (1.0 - result.a);
		}
		else
		{
			vec4 color = BlendBufferColors[i];
			result = result + color;
		}
	}
	
	return result;
}

out vec4 Color;

void main ()
{
	ivec2 icoords = ivec2(gl_FragCoord.xy);
	
	if(!(icoords.x >= 0 && icoords.y >= 0 
	&& icoords.x < ScreenSize.x && icoords.y < ScreenSize.y))
	{ return; }
	
	uint PageIndex = GetCurrentPage(icoords);
	
	if (PageIndex <= 0)
	{ discard; }
	
	uint FragCount = GetFragCounter(icoords);
	
	if (FragCount <= 0)
	{ discard; }
	
	FillBlendBuffer (PageIndex, FragCount);
	
	FragCount = min(FragCount,BlendBufferSize);
	//FragCount = FragCount % (PageSize);
	//if (FragCount==0)
	//	FragCount=PageSize;
	
	SortBlendBuffer (int(FragCount));
	
	//Color = BlendPages(PageIndex, FragCount); 
	Color = Blend(FragCount);
	//Color = vec4 (FragCount / float (100),FragCount / float (100),FragCount / float (100),1);
}
