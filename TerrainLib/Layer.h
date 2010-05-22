#ifndef TERRAIN_LAYERS_H
#define TERRAIN_LAYERS_H

#include <vector>
#include "IFF.h"

namespace TerrainLib
{

	enum LAYER_TYPE
	{
		LAYER_NONE = 0,
		LAYER_CONTAINER,
		LAYER_BREC, //Boundry Rectangle
		LAYER_BCIR, //Boundry Circle
		LAYER_BPOL, //Boundry Polygon
		LAYER_BPLN, //Boundry Polyline
		LAYER_FDIR, //Filter Direction
		LAYER_FFRA, //Filter Fractal
		LAYER_FHGT, //Filter Height
		LAYER_FSLP, //Filter Slope
		LAYER_ASCN, //Affector Shader Constant
		LAYER_ASCR, //Affector Shader Replace
		LAYER_ACCN, //Affector Color Constant
		LAYER_FSHD, //Filter Shader
		LAYER_AHCN, //Affector Height Constant
		LAYER_AHFR, //Affector Height Fractal
		LAYER_AHFT, //Affector Height Terrace
		LAYER_AFSC, //Affector Flora Static Collidable
		LAYER_AFSN, //Affector Flora Static Non-Collidable
		LAYER_AFDN, //Affector Flora Dynamic Near
		LAYER_AFDF, //Affector Flora Dynamic Far
		LAYER_AENV, //Environment
		LAYER_AEXC, //Affector Exclude
		LAYER_AROA, //Affector Road
		LAYER_ARIV, //Affector River
		LAYER_ACRF, //Affector Color Ramp Fractal
		LAYER_ACRH, //Affector Color Ramp Height
		LAYER_AHTR, //UNK - I suspect this has to do with height.
		LAYER_ASRP, //UNK - I suspect this has to do with shaders.
	};

	class LAYER
	{
	public:
		static LAYER* LOAD(IFFLib::IFF::NODE* node);

		LAYER_TYPE type;
		bool enabled;

		unsigned char* customName;
	};

	class CONTAINER_LAYER : public LAYER
	{
	public:

		CONTAINER_LAYER()
		{
			type = LAYER_CONTAINER;
		}

		int enabled;
		unsigned char* name;
	
		int unk2;
		int unk3; //type unknown
		int unk4;
		unsigned char* description;
	
		std::vector<LAYER*> children;
	};
};

#endif