#include <fstream>
#include <iostream>
#include <stdexcept>

#include "RigidBodyResource.h"

Square::Square(const std::string& _name) : name(_name)
{

}
Square::Square(Square&& sq) : name(std::move(sq.name))
{
	x1 = sq.x1;
	y1 = sq.y1;
	x2 = sq.x2;
	y2 = sq.y2;
}

RigidBodyResource::RigidBodyResource(const std::string& _name, const std::string& path)
: BaseObject(_name)
{
	std::ifstream file;
	std::string buffer;
	file.exceptions(std::istream::failbit | std::istream::badbit);
	try{
		file.open(path);
		//read the title
		file >> frameNumber;

		int frameCount, squareNumber, squareListNumber;
		std::string squareName;
		for(int i = 1; i <= frameNumber; i++){

			file >> frameCount;
			if (frameCount != i) throw std::runtime_error("Error. The rigid body resource format is not valid.");
			//creating the frame
			frameList.push_back( SquareList() );

			file >> squareListNumber;
			for (int k = 0; k < squareListNumber; k++){
				file >> squareNumber;
				file >> squareName;
				for(int j = 0; j < squareNumber; j++){
					//creating the square
					Square sqr(squareName);

					file >> sqr.x1; file >> sqr.y1;
					file >> sqr.x2; file >> sqr.y2;
					frameList.back().push_back( std::move(sqr) );
				}
				squareName.clear();	
			}
		}
	}
	catch (...) {
		//#ifdef _DEBUG
			std::cout << "Error. The resource hasn't been loaded. " << path << std::endl;
		//#endif
		file.close();
		throw;
	}
}

RBR::RigidBodyResource(RigidBodyResource&& rbr) : BaseObject( std::move(static_cast<BaseObject&>(rbr)) ),
frameList( std::move(rbr.frameList) )
{
	frameNumber = rbr.frameNumber;
}