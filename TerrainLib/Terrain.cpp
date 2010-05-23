#include "Terrain.h"
#include "Layer.h"

using namespace TerrainLib;
using namespace IFFLib;

Trn::Trn(std::string trnFile)
{
	try
	{
		IFFLib::IFF* mObject = new IFFLib::IFF();
		IFF::retVal ret = mObject->readFile(trnFile);

		//Load Basic Map Info
		std::list<IFF::NODE*> ptats = mObject->mHeads[0]->searchTree("PTATFORM");
	
		std::list<IFF::NODE*>::iterator it = ptats.begin();
		std::list<IFF::NODE*>::iterator end = ptats.end();
		while(it != end)
		{
			_handleBasicData((*it)->children.at(0)->data, (*it)->children.at(0)->size);
			it++;
		}

		if(ret == IFF::READ_FILE_OK)
		{
			//Load the Shader Families
			for(unsigned int i=0; i < mObject->mHeads.size(); i++)
			{
				std::list<IFF::NODE*> shaderFamilies = mObject->mHeads[i]->searchTree("SGRPFORM");

				std::list<IFF::NODE*>::iterator it = shaderFamilies.begin();
				std::list<IFF::NODE*>::iterator end = shaderFamilies.end();
				while(it != end)
				{
					for(unsigned int i=0; i < (*it)->children.size(); i++)
						this->ShaderFamilies.push_back(new SFAM((*it)->children.at(i)->data));
					it++;
				}
			}

			//Load the Flora Families
			for(unsigned int i=0; i < mObject->mHeads.size(); i++)
			{
				std::list<IFF::NODE*> floraFamilies = mObject->mHeads[i]->searchTree("FGRPFORM");
	
				std::list<IFF::NODE*>::iterator it = floraFamilies.begin();
				std::list<IFF::NODE*>::iterator end = floraFamilies.end();

				while(it != end)
				{
					for(unsigned int i=0; i < (*it)->children.size(); i++)
						this->FloraFamilies.push_back(new FFAM((*it)->children.at(i)->data));
					it++;
				}
			}

			//Load Radial Flora Families
			for(unsigned int i=0; i < mObject->mHeads.size(); i++)
			{
			std::list<IFF::NODE*> radfloraFamilies = mObject->mHeads[i]->searchTree("RFAM");
	
				std::list<IFF::NODE*>::iterator it = radfloraFamilies.begin();
				std::list<IFF::NODE*>::iterator end = radfloraFamilies.end();

				while(it != end)
				{
					for(unsigned int i=0; i < (*it)->children.size(); i++)
						this->RadialFloraFamilies.push_back(new RFAM((*it)->children.at(i)->data));
					it++;
				}
			}

			//Load Environment Families
			for(unsigned int i=0; i < mObject->mHeads.size(); i++)
			{
				std::list<IFF::NODE*> floraFamilies = mObject->mHeads[i]->searchTree("EFAMDATA");

				std::list<IFF::NODE*>::iterator it = floraFamilies.begin();
				std::list<IFF::NODE*>::iterator end = floraFamilies.end();

				while(it != end)
				{
					if((*it)->data)
						this->EnvironmentFamilies.push_back(new EFAM((*it)->data));
					++it;
				}
			}

			//Load Fractal Families
			for(unsigned int i=0; i < mObject->mHeads.size(); i++)
			{
				std::list<IFF::NODE*> fractalFamilies = mObject->mHeads[i]->searchTree("MFAMDATA");

				std::list<IFF::NODE*>::iterator it = fractalFamilies.begin();
				std::list<IFF::NODE*>::iterator end = fractalFamilies.end();

				while(it != end)
				{
					IFF::NODE* parent = (*it)->parent;
					this->FractalFamilies.push_back(new MFAM((*it)->data, parent->children.at(1)->children.at(0)->children.at(0)->data));
					it++;
				}
			}

			//Now for the Layers
			for(unsigned int i=0; i < mObject->mHeads.size(); i++)
			{
				std::list<IFF::NODE*> layerlist = mObject->mHeads[i]->searchTree("LYRSFORM");

				std::list<IFF::NODE*>::iterator it = layerlist.begin();
				std::list<IFF::NODE*>::iterator end = layerlist.end();

				while(it != end)
				{
					IFF::NODE* parent = (*it)->parent;

					std::vector<IFF::NODE*>::iterator jt = parent->children.begin();
					std::vector<IFF::NODE*>::iterator jend = parent->children.end();
	
					while(jt != jend)
					{
						layers.push_back(_loadLayer((*jt)->children[0]));
						jt++;
					}
					it++;
				}		
			}

			delete mObject;

			error = 0;
		}
		else if(ret == IFF::READ_FILE_BAD_FILE)
			error = 1;
		else if(ret == IFF::READ_FILE_BAD_FORMAT)
			 error = 2;
		else
			error = -1;
	}
	catch(...)
	{
		error = IFF::READ_FILE_BAD_FORMAT;
	}
}

void Trn::_handleBasicData(unsigned char* data, unsigned int dataSize)
{
	unsigned int i=0;
	//Read filename;
	unsigned int strLen = strlen(const_cast<const char*>((char*)&data[i])) + 1;
	filename = new unsigned char[strLen];
	memcpy(filename, &data[i], strLen); i+= strLen;
	//Read map_width;
	memcpy(&map_width, &data[i], 4); i+=4;
	//Read chunk_width;
	memcpy(&chunk_width, &data[i], 4); i+=4;
	//Read tiles_per_chunk;
	memcpy(&tiles_per_chunk, &data[i], 4); i+=4;
	//Read use_global_water_table;
	memcpy(&header_type, &data[i], 4); i+=4;
	//Read global_water_height;
	memcpy(&global_water_height, &data[i], 4); i+=4;
	//Read water_shader_size;
	memcpy(&water_shader_size, &data[i], 4); i+=4;
	//Read water_shader_name;
	strLen = strlen(const_cast<const char*>((char*)&data[i])) + 1;
	water_shader_name = new unsigned char[strLen];
	memcpy(water_shader_name, &data[i], strLen); i+= strLen;
	//Read seconds_per_world_cycle;
	memcpy(&seconds_per_world_cycle, &data[i], 4); i+=4;
}

LAYER* Trn::_loadLayer(IFF::NODE* parent)
{
	if(strcmp(parent->name, "LAYRFORM") == 0)
	{
		CONTAINER_LAYER* result = new CONTAINER_LAYER();

		std::vector<IFF::NODE*>::iterator it = parent->children.begin();
		std::vector<IFF::NODE*>::iterator end = parent->children.end();

		while( it != end )
		{
			if(strcmp((*it)->name, "0003FORM") == 0)
			{
				//Load Custom Name
				unsigned char* tempData = (*it)->children[0]->children[0]->data;

				memcpy(&result->enabled, &tempData[0], 4);

				unsigned int strLen = strlen(const_cast<const char*>((char*)&tempData[4])) + 1;
				result->customName = new unsigned char[strLen];
				memcpy(water_shader_name, &tempData[4], strLen);
				
			}
			else if(strcmp((*it)->name, "ADTA") == 0)
			{
				unsigned char* tempData = (*it)->data;

				//Load Unknowns and description
				memcpy(&result->unk2, &tempData[0], 4);
				memcpy(&result->unk3, &tempData[4], 4);
				memcpy(&result->unk4, &tempData[8], 4);

				unsigned int strLen = strlen(const_cast<const char*>((char*)&tempData[9])) + 1;
				result->description = new unsigned char[strLen];
				memcpy(result->description, &tempData[9], strLen);
			}
			else
			{
				LAYER* temp = _loadLayer((*it)->children[0]);
				if(temp)
					result->children.push_back(temp);
				else
					printf("Unknown Layer Found : %s\n", ((*it)->children[0]->name));
			}

			it++;
		}

		return result;
	}
	else
	{
		LAYER* tempResult = LAYER::LOAD(parent);
		return tempResult;
	}
}

void SaveTerrain(std::string outputFile)
{

}