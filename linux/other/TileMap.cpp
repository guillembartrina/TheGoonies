#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"


using namespace std;


TileMap *TileMap::createTileMap(const std::string &levelFile, const glm::vec2 &minCoords, Program &program)
{
	TileMap *map = new TileMap(levelFile, minCoords, program);
	
	return map;
}


TileMap::TileMap(const std::string &levelFile, const glm::vec2 &minCoords, Program &program)
{
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
}

TileMap::~TileMap()
{
	if(map != NULL)
		delete map;
}


void TileMap::render() const
{
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6 * mapSize.x * mapSize.y);
	glDisable(GL_TEXTURE_2D);
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}

bool TileMap::loadLevel(const std::string &levelFile)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char tile;
	
	fin.open(levelFile.c_str());
	if(!fin.is_open())
		return false;
	getline(fin, line);
	if(line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	//Ancho y alto del mapa en caracteres
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	//tileSize: �cu�nto estar�n separados los tiles en x e y? (el ancho/alto de la baldosa). Sirve para
	//   generar el v�rtice superior izquierdo de cada quad (su origen)
	//blockSize: tama�o real de la imagen del tile (podr�a pensarse que es justo el tileSize,
	//pero esto no tiene porqu� ser as�: si, por ejemplo, las im�genes tienen "sombra" que queremos que solo se vea en los
	//tiles de los bordes). Normalmente tileSize < blockSize
	sstream >> tileSize >> blockSize;
	getline(fin, line);
	sstream.str(line);
	//Fichero de la imagen del spritesheet con los tiles
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	//No permite repetici�n si nos pasamos de uv's en las coordenadas de textura
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);

	getline(fin, line);
	sstream.str(line);
	//N�mero de im�genes (tiles) del spritesheel de tiles (filas y columnas)
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	//Lo que guardamos es el inverso, porque es lo que hemos de incrementar las uv
	//del spritesheet para saltar de imagen en imagen
	//Por ejemplo, si hay 2x2 im�genes, guardamos un vector(0.5, 0.5)
	//ya que las uv iniciales de la primera imagen ser�n (0,0), las de la segunda, (0.5, 0)
	//las de la tercera (0, 0.5) y las de la cuarta (0.5, 0.5)

	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);
	
	//Lee el mapa de tiles como caracteres
	//Los caracteres son n�meros '1', '2', '3'...
	//que hacen referencia al n�mero de imagen del spritesheet (de izquierda a derecha, arriba a abajo, empezando por el cero)
	//en map se almacenan como su integer correspondiente '1' => 1 '2' => 2 ...
	map = new int[mapSize.x * mapSize.y];
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			fin.get(tile);
			if(tile == ' ')
				map[j*mapSize.x+i] = 0;
			else
				map[j*mapSize.x+i] = tile - int('0');
		}
		fin.get(tile);
#ifndef _WIN32
		fin.get(tile);
#endif
	}
	fin.close();
	
	return true;
}

void TileMap::prepareArrays(const glm::vec2 &minCoords, Program &program)
{
	int tile, nTiles = 0;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;
	
	//halfTexel: Ancho normalizado de medio texel: (un texel es un "pixel" de informaci�n en el archivo
	//de la imagen que luego puede convertirse en uno o varios pixeles en pantalla -si se escala la imagen o se reduce-)
	//El ancho de un texel "normalizado" (respecto a su textura) ser�a 1/Anchura_imagen
	//Aqu� calculamos el ancho de medio texel respecto a tu textura �por qu�?
	//Pues porque cuando indiquemos las coordenadas uv de cada tile, le vamos a restar medio texel al final
	//para evitar que nos interpole el color de la imagen vecina en el spritesheet

	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i];
			if(tile != 0)
			{
				// Non-empty tile
				nTiles++;

				//posTile es la coordenada superior izquierda de cada tile (su origen)
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);

				//Lo siguiente sirve para indicar, en el VBO, las coordenadas de textura (UV) de
				//este tile en concreto.
				//Funcionamiento: si en la imagen hay, por ejemplo, 4 texturas (2x2)
				//las coordenadas de textura de la primera imagen deber�an ir de (0,0) -> (0.5, 0.5)
				//Vemos el n�mero de imagen del spritesheet "tile", que tiene este tile
				//y calculamos en texCoordTile[0] sus uv's iniciales
				//OJO!!! Esta expresi�n sirve solo para spritesheets de 2x2 im�genes
				//HAY QUE MODIFICARLAS PARA EL CASO GEN�RICO DE N X M IM�GENES
				texCoordTile[0] = glm::vec2(float((tile-1)%tilesheetSize.x) / tilesheetSize.x, float((tile-1)/tilesheetSize.x) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				//texCoordTile[0] += halfTexel;
				//Le restamos medio texel a las uv's finales para que el rasterizador, a la hora
				//de interpolar las uv's para pas�rselas al fragment desde los vertex shader, no coja
				//pixeles de la imagen vecina del spritesheet
				texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//OJO!!! Este VBO tiene es buffer que tiene informaci�n de v�rtices y de uv's intercaladas!

	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.getAttributeLocation("position");
	texCoordLocation = program.getAttributeLocation("texCoord");

	glVertexAttribPointer(posLocation, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
	glEnableVertexAttribArray(posLocation);
	glVertexAttribPointer(texCoordLocation, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void *)(2*sizeof(float)));
	glEnableVertexAttribArray(texCoordLocation);
}






























