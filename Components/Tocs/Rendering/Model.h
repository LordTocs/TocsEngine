#pragma once
#include "Pipeline.h"
#include "RenderObject.h"
#include "Mesh.h"
#include "Material.h"
#include "MeshJob.h"
namespace Tocs {
namespace Rendering {


class Model : public RenderObject
{
	Mesh &ModelMesh;
	GeometryHandler &Handler;
	class MaterialJobs
	{
		Material *ModelMaterial;
		std::vector<std::unique_ptr<MeshJob>> Jobs;
		Model *ThisModel;
		int Index;
	public:
		MaterialJobs ()
			: ModelMaterial(nullptr),
			  ThisModel(nullptr)
		{

		}

		void SetModel (Model *model)
		{
			ThisModel = model;
		}

		void SetMaterial (Material &material)
		{
			ModelMaterial = &material;
			if (ThisModel->HasSystem ())
			{
				CreateJobs(ThisModel->GetSystem ().GetPipes());
			}
		}

		void CreateJobs (Pipeline &pipeline);

		void Show ();
		void Hide ();


		void Update (float dt) {}

	};
	std::unique_ptr<MaterialJobs[]> Materials;
	
public:
	Model(Mesh& mesh);
	Model(Mesh& mesh, GeometryHandler &geometryhandler);
	~Model();

	void Show ();
	void Hide ();


};

}}

