#version 420
uniform uvec2 ScreenSize;

coherent uniform layout(r32ui) uimage2D ABufferIndex;
coherent uniform layout(r32ui) uimage2D ABufferCounts;

coherent uniform layout(r32ui) uimageBuffer PageLinks;
coherent uniform layout(rgba8)  imageBuffer ColorPages;
coherent uniform layout(r32f) imageBuffer DepthPages;

#define PageSize 8

uint GetFragCounter(ivec2 coords)
{
	return imageLoad(ABufferCounts, coords).x;
}
uint GetCurrentPage(ivec2 coords)
{
	return imageLoad(ABufferIndex, coords).x;
}
uint GetPageLink (uint page)
{
	return imageLoad(PageLinks, int(page)).x;
}
vec4 GetColor(uint index)
{
	return imageLoad(ColorPages, int(index));
}
vec4 GetDepth(uint index)
{
	return imageLoad(DepthPages, int(index));
}


#define BlendBufferSize 32

vec4  BlendBufferColors [BlendBufferSize];
float BlendBufferDepths [BlendBufferSize];

//Iterates through pages populating the blendbuffer
void FillBlendBuffer (uint page, uint count)
{
	//Load fragments into a local memory array for sorting
	uint CurrentPage = page;
	int ip=0;
	int fi=0;
	while(CurrentPage !=0 && ip < 20)
	{
		uint elementcount;
		if(ip==0)
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
			if (fi < BlendBufferSize)
			{
				BlendBufferColors[fi]=GetColor(PagePointer+fi);
				BlendBufferDepths[fi]=GetDepth(PagePointer+fi);
			}
			else
			{
				return;
			}
			fi++;
		}
		
		CurrentPage = GetPageLink(CurrentPage);
		ip++;
	}
}
//Swaps two blend buffer indices
void SwapBlendBuffer(int a, int b)
{
	vec4 tempcolor = BlendBufferColors[a];
	float tempdepth = BlendBufferDepths[a];
	
	BlendBufferDepths[a] = BlendBufferDepths[b];
	BlendBufferColors[a] = BlendBufferColors[b];
	
	BlendBufferDepths[b] = tempdepth;
	BlendBufferColors[b] = tempcolor;
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
vec4 AlphaBlend (uint count)
{
	vec4 result = vec4(0.0);
	
	for (int i = 0; i < count; ++i)
	{
		vec4 color = BlendBufferColors[i];
		color.rgb = color.rgb * color.a;
		
		result = result + color * (1.0 - result.a);
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
	
	FragCount = min(FragCount,BlendBufferSize);

	
	FillBlendBuffer (PageIndex, FragCount);
	SortBlendBuffer (int(FragCount));
	
	Color = AlphaBlend(FragCount);
}
