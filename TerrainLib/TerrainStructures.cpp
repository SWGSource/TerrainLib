#include "TerrainStructures.h"
#include <string>

using namespace TerrainLib;

SFAM::SFAM(unsigned char* data)
{
	unsigned int i = 0;
	
	//Read family_id
	memcpy(&family_id, &data[i], 4); i += 4;

	//Read family_name
	family_name = &data[i];
	while(data[i] != 0) ++i;
	i++;

	//Read file_name
	file_name = &data[i];
	while(data[i] != 0) ++i;
	i++;

	//Read unk1
	memcpy(&unk1, &data[i], 1); ++i;
	//Read unk2
	memcpy(&unk2, &data[i], 1); ++i;
	//Read unk3
	memcpy(&unk3, &data[i], 1); ++i;
	//Read unk4
	memcpy(&unk4, &data[i], 4); i+=4;
	//Read unk5
	memcpy(&unk5, &data[i], 4); i+=4;

	unsigned int child_count;
	memcpy(&child_count, &data[i], 4); i+=4;

	for(unsigned int j=0; j < child_count; ++j)
	{
		SFAM_CHILD* pChild = new SFAM_CHILD();

		//Read shader_name
		pChild->shader_name = &data[i];
		while(data[i] != 0) ++i;
		++i;

		//Read unk1
		memcpy(&pChild->unk1, &data[i], 4); i+=4;

		children.push_back(pChild);
	}
}

FFAM::FFAM(unsigned char* data)
{
	unsigned int i=0;

	//Read family_id
	memcpy(&family_id, &data[i], 4); i += 4;

	//Read family_name
	family_name = &data[i];
	while(data[i] != 0) ++i;
	i++;

	//Read unk1
	memcpy(&unk1, &data[i], 1); ++i;
	//Read unk2
	memcpy(&unk2, &data[i], 1); ++i;
	//Read unk3
	memcpy(&unk3, &data[i], 1); ++i;
	//Read unk4
	memcpy(&unk4, &data[i], 4); i+=4;
	//Read unk5
	memcpy(&unk5, &data[i], 4); i+=4;

	unsigned int child_count;
	memcpy(&child_count, &data[i], 4); i+=4;

	for(unsigned int j=0; j < child_count; ++j)
	{
		FFAM_CHILD* pChild = new FFAM_CHILD();

		pChild->appearance_name = &data[i];
		while(data[i] != 0) ++i;
		i++;

		//Read unk1;
		memcpy(&pChild->unk1, &data[i], 4); i+=4;
		//Read unk2; //Type unknown!
		memcpy(&pChild->unk2, &data[i], 4); i+=4;
		//Read unk3;
		memcpy(&pChild->unk3, &data[i], 4); i+=4;
		//Read unk4;
		memcpy(&pChild->unk4, &data[i], 4); i+=4;
		//Read unk5;
		memcpy(&pChild->unk5, &data[i], 4); i+=4;
		//Read unk6;
		memcpy(&pChild->unk6, &data[i], 4); i+=4;
		//Read unk7;
		memcpy(&pChild->unk7, &data[i], 4); i+=4;
		//Read unk8;
		memcpy(&pChild->unk8, &data[i], 4); i+=4;

		children.push_back(pChild);
	}
}

RFAM::RFAM(unsigned char* data)
{
	unsigned int i=0;

	//Read family_id
	memcpy(&family_id, &data[i], 4); i += 4;

	//Read family_name
	family_name = &data[i];
	while(data[i] != 0) ++i;
	i++;

	//Read unk1
	memcpy(&unk1, &data[i], 1); ++i;
	//Read unk2
	memcpy(&unk2, &data[i], 1); ++i;
	//Read unk3
	memcpy(&unk3, &data[i], 1); ++i;
	//Read unk4
	memcpy(&unk4, &data[i], 4); i+=4;

	unsigned int child_count;
	memcpy(&child_count, &data[i], 4); i+=4;

	for(unsigned int j=0; j < child_count; ++j)
	{
		RFAM_CHILD* pChild = new RFAM_CHILD();

		pChild->shader_name = &data[i];
		while(data[i] != 0) ++i;
		i++;

		//Read unk1;
		memcpy(&pChild->unk1, &data[i], 4); i+=4;
		//Read unk2; //Type unknown!
		memcpy(&pChild->unk2, &data[i], 4); i+=4;
		//Read unk3;
		memcpy(&pChild->unk3, &data[i], 4); i+=4;
		//Read unk4;
		memcpy(&pChild->unk4, &data[i], 4); i+=4;
		//Read unk5;
		memcpy(&pChild->unk5, &data[i], 4); i+=4;
		//Read unk6;
		memcpy(&pChild->unk6, &data[i], 4); i+=4;
		//Read unk7;
		memcpy(&pChild->unk7, &data[i], 4); i+=4;
		//Read unk8;
		memcpy(&pChild->unk8, &data[i], 4); i+=4;
		//Read unk9;
		memcpy(&pChild->unk9, &data[i], 4); i+=4;

		children.push_back(pChild);
	}
}

EFAM::EFAM(unsigned char* data)
{
	unsigned int i=0;

	//Read family_id;
	memcpy(&family_id, &data[i], 4); i+=4;
	//Read family_name;
	family_name = &data[i];
	while(data[i] != 0) ++i;
	i++;

	//Read unk1;
	memcpy(&unk1, &data[i], 1); ++i;
	//Read unk2;
	memcpy(&unk1, &data[i], 1); ++i;
	//Read unk3;
	memcpy(&unk1, &data[i], 1); ++i;
	//Read unk4;
	memcpy(&unk1, &data[i], 4); i+=4;
}

MFAM::MFAM(unsigned char* data, unsigned char* data2)
{
	unsigned int i = 0;

	//First Part
	//Read fractal_id;
	memcpy(&fractal_id, &data[i], 4); i+=4;
	//Read fractal_label;
	fractal_label = &data[i];
	while(data[i] != 0) ++i;
	i++;

	//Reset the counter
	i=0;

	//Second Part
	//Read unk1;
	memcpy(&unk1 , &data2[i], 4); i+=4;
	//Read unk2;
	memcpy(&unk2 , &data2[i], 4); i+=4;
	//Read unk3;
	memcpy(&unk3 , &data2[i], 4); i+=4;
	//Read unk4;
	memcpy(&unk4 , &data2[i], 4); i+=4;
	//Read unk5;
	memcpy(&unk5 , &data2[i], 4); i+=4;
	//Read unk6;
	memcpy(&unk6 , &data2[i], 4); i+=4;
	//Read unk7;
	memcpy(&unk7 , &data2[i], 4); i+=4;
	//Read unk8;
	memcpy(&unk8 , &data2[i], 4); i+=4;
	//Read unk9;
	memcpy(&unk9 , &data2[i], 4); i+=4;
	//Read unk10;
	memcpy(&unk10, &data2[i], 4); i+=4;
	//Read unk11;
	memcpy(&unk11, &data2[i], 4); i+=4;
	//Read unk12; //type unknown
	memcpy(&unk12, &data2[i], 4); i+=4;
	//Read unk13;
	memcpy(&unk13, &data2[i], 4); i+=4;
}