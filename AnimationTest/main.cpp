#include <iostream>
#include <utility>
#include "Game.h"

#include <Tocs/Math/Dual.h>
#include <Tocs/Math/DualQuaternionTransform.h>
#include <Tocs/Math/Quaternion.h>
#include <Tocs/Math/Matrix4.h>



using namespace Tocs;
using namespace Tocs::Math;
using namespace Tocs::Rendering;
using namespace std;


int main()
{
	Game game;
	game.Start();

	//Dual<Quaternion> trans = DualQuaternionTransform::ToDualQuaternion(Vector3(0, 1, 0), Quaternion::FromEuler(Constants::Pi<float>() / 2, 0, 0));
	//Dual<Quaternion> trans2 = DualQuaternionTransform::ToDualQuaternion(Vector3(0, 2, 0), Quaternion::Identity);
	//std::cout << trans << std::endl;
	//std::cout << trans2 << std::endl;
	//std::cout << trans * trans2 << std::endl;
	//std::cout << DualQuaternionTransform::ExtractPosition(trans * trans2) << std::endl;
	
	
	std::cin.ignore(1);
}