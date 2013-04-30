#pragma once
#include <Tocs/Core/StaticInitializer.h>
#include <Tocs/Core/Asset.h>
#include "RenderObject.h"
#include "Mesh.h"
#include "MaterialInstance.h"
#include "StaticGeometry.h"
#include <memory>
namespace Tocs {
namespace Rendering {

class Model : public RenderObject
{
public:
	class MaterialSlot
	{
		Model *ModelInstance;
		std::shared_ptr<MaterialInstance> Mat;
		std::vector<Job> Jobs;
		unsigned int Index;
	public:
		MaterialSlot (Model *model, unsigned int index);
		void QueueJobs ();
		void DequeueJobs ();

		void SetMaterial (const Material &mat);
	};
private:
	Asset<Mesh> ModelMesh;
	std::vector<MaterialSlot> Materials;
	Asset<StaticGeometryType> ModelGeometryType;
	StaticGeometry ModelGeometry;
	
	explicit Model (const Model &);
protected:
	void QueueJobs ();
	void DequeueJobs ();
public:
	Model(const Asset<Mesh> &mesh, RenderSystem &system);
	const Asset<Mesh> &GetMesh() const { return ModelMesh; }

	StaticGeometry &GetGeometry () { return ModelGeometry; }

};

}}