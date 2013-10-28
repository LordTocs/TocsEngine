#pragma once
#include <Tocs/Core/StaticInitializer.h>
#include <Tocs/Core/Asset.h>

#include <memory>
namespace Tocs {
namespace Rendering {
/*
class Model : public RenderObject
{
public:
	class MaterialSlot
	{
		Model *ModelInstance;
		std::unique_ptr<MaterialInstance> Mat;
		std::vector<Job> Jobs;
		unsigned int Index;
		MaterialSlot (const MaterialSlot &);
		MaterialSlot &operator=(const MaterialSlot &);
	public:
		MaterialSlot (MaterialSlot &&moveme);
		MaterialSlot (Model *model, unsigned int index);
		void QueueJobs ();
		void DequeueJobs ();

		void SetMaterial (const Asset<Material> &material);
	};
private:
	Asset<Mesh> ModelMesh;
	
	Asset<StaticGeometryType> ModelGeometryType;
	StaticGeometry ModelGeometry;
	
	explicit Model (const Model &);
protected:
	void QueueJobs ();
	void DequeueJobs ();
public:
	std::vector<MaterialSlot> Materials;

	Model(const Asset<Mesh> &mesh, RenderSystem &system);
	const Asset<Mesh> &GetMesh() const { return ModelMesh; }

	StaticGeometry &GetGeometry () { return ModelGeometry; }


};*/

}}