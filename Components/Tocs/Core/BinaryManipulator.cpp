#include "TocsLib.h"
#include "BinaryManipulator.h"

using namespace Tocs;

BinaryManipulator::BinaryManipulator(DataSource &source)
	: Source (&source),
	  Location (0)
{
}


BinaryManipulator::~BinaryManipulator(void)
{
}
