#pragma once
#include <Tocs/Core/FreeList.h>
#include <vector>
#include <Tocs/Math/BoundingBox.h>
#include "Job.h"
#include <cmath>

namespace Tocs {
namespace Rendering {

template <class T>
class JobOctree
{
public:
	class Node;
	friend class Node;

	typedef FreeList <Node>::Id NodeId;

	class NodeReference
	{
		JobOctree *Tree;
		NodeId Id;
		unsigned int Index;
	public:
		friend class Node;

		NodeReference (JobOctree *tree, NodeId id, unsigned int index)
			: Tree(tree), Id(id), Index(index)
		{}

		NodeReference (Node *node,unsigned int index)
			: Tree (node->Tree), Id(node->ThisId), Index(index)
		{
		}

		Node &Get () { return Tree->Nodes.Get(Id); }
	};

	friend class NodeReference;

	class Node
	{
		NodeId ThisId;
		NodeId ParentId;
		int Octant;
		NodeId ChildrenIds[8];
		int ChildCount;
		JobOctree *Tree;
	public:
		std::vector<T *> Elements;

		Node (Node &&moveme)
			: ChildrenIds(std::move(moveme.ChildrenIds)),
			  Tree(std::move(moveme.Tree)),
			  Bounds(std::move(moveme.Bounds)),
			  Elements(std::move(moveme.Elements)),
			  ChildCount(moveme.ChildCount),
			  Octant(moveme.Octant)
		{
			moveme.Tree = nullptr;
		}

		Node (JobOctree *tree, Math::BoundingBox bounds)
			: Tree(tree),
			  Bounds(bounds),
			  ChildCount(0),
			  Octant(-1)
		{
		}

		Node (JobOctree *tree, Math::BoundingBox bounds, Node *parent, int octant)
			: Tree(tree),
			  Bounds(bounds),
			  ParentId(parent->ThisId),
			  ChildCount(0),
			  Octant(octant)
		{
		}

		Math::BoundingBox Bounds;

		bool HasChild (int index)
		{
			return ChildrenIds[index].IsValid ();
		}

		bool HasChildren ()
		{
			return ChildCount > 0;
		}

		Node *Child (int index)
		{
			return &Tree->Nodes.Get(ChildrenIds[index]);
		}
		const Node *Child (int index) const
		{
			return &Tree->Nodes.Get(ChildrenIds[index]);
		}

		void NullChild (int index)
		{
			if (HasChild(index))
			{
				ChildrenIds[index] = NodeId ();
				--ChildCount;
			}
		}

		Node *Parent ()
		{
			return &Tree->Nodes.Get(ParentId);
		}
		const Node *Parent () const
		{
			return &Tree->Nodes.Get(ParentId);
		}

		Math::BoundingBox ChildBounds (int index) const
		{
			return Math::BoundingBox::MinMax (Bounds.Center (), Bounds.Corner(index));
		}

		bool Insert (T *job)
		{
			if (!Bounds.CompletelyContains (job->GeometryComponent().Bounds ()))
				return false;

			for (int i = 0; i < 8; ++i)
			{
				if (HasChild(i))
				{
					if (Insert (Child(i)))
					{
						return true;
					}
				}

			}

			Elements.push_back (job);
			job->NodeRef = NodeReference(this, Elements.size () - 1); //give it a reference back
			
			Subdivide ();

			return true;
		}

		void SelfDestruct ()
		{
			Parent->NullChild(Octant);
			Tree->Nodes.Remove(ThisId);
		}

		void UpwardsEmptyCheck ()
		{
			if (!HasChildren ())
			{
				//Remove from parent's children.
				Parent()->NullChild(Octant);
				Parent()->EmptyCheck();

				SelfDestruct();
				return true;
			}
		}

		NodeId DownwardsEmptyCheck ()
		{
			if (Elements.size () != 0 || ChildCount > 1)
			{ return ThisId; }

			if (ChildCount == 1)
			{
				NodeId onlychild;

				for (int i = 0; i < 8; ++i)
				{
					if (ChildrenIds[i].IsValid ())
					{ onlychild = ChildrenIds[i]; break; }
				}

				NodeId deeproot = Tree->Nodes.Get(onlychild).DownardsEmptyCheck();
				Tree->RootId = deeproot;
				SelfDestruct();
				return deeproot;
			}

			return NodeId ();
		}

		bool EmptyCheck ()
		{
			if (Elements.size () != 0)
			{ return false; }

			if (!HasChildren())
			{
				UpwardsEmptyCheck ();
			}
			else if (ChildCount == 1 && Tree->RootId == ThisId)
			{
				DownwardsEmptyCheck ();
			}
			return false;
		}

		void Remove (T *job)
		{
			if (job->NodeRef.Id != ThisId && job->NodeRef.Tree != Tree)
				return;

			Elements.erase(Elements.begin() + job->NodeRef.Index);
			EmptyCheck();
			
		}

		void CreateChild (int i)
		{
			if (HasChild(i))
				return;

			ChildrenIds[i] = Tree->Nodes.Add(Node(Tree,ChildBounds(i),this));
			Tree->Nodes.Get(ChildrenIds[i]).ThisId = ChildrenIds[i];
			++ChildCount;
		}

		void Subdivide ()
		{
			static int ElementThreshold = 15;
			if (Elements.size () <= 15)
				return;

			
			for (int i = 0; i < 8; ++i)
			{
				Math::BoundingBox bounds = ChildBounds(i);
			
				for (int e = Elements.size () - 1; e >= 0; --e)
				{
					if (ChildBoundings[i].CompletelyContains(job->GeometryComponent().Bounds ()))
					{
						CreateChild(i);
						Child(i)->Insert(e);
						Elements.erase(Elements.begin() + e);
					}
				}
			}
		}

		//returns > 0 if positive direction in axis has largest distance to encompass otherbox or < 0 if the negative direction in axis has largest distance to encompass otherbox
		static int MaxBoundingBoxAxisDifference (Math::BoundingBox rootbox, Math::BoundingBox otherbox, int axis)
		{
			float pos = rootbox.Max()[axis] - otherbox.Max()[axis];
			float neg = rootbox.Min()[axis] - otherbox.Min()[axis];
			return (pos > neg ? 1 : -1);
		}

		NodeId CreateParentNode (T *job)
		{
			Math::Vector3 minbounds;
			Math::Vector3 maxbounds;

			int xdir = MaxBoundingBoxAxisDifference (Bounds,job->GeometryComponent().Bounds(),0);
			int ydir = MaxBoundingBoxAxisDifference (Bounds,job->GeometryComponent().Bounds(),1);
			int zdir = MaxBoundingBoxAxisDifference (Bounds,job->GeometryComponent().Bounds(),2);

			minbounds.X = (xdir > 0 ? Bounds.Min().X : Bounds.Min().X - Bounds.Width());
			minbounds.Y = (ydir > 0 ? Bounds.Min().Y : Bounds.Min().Y - Bounds.Height());
			minbounds.Z = (zdir > 0 ? Bounds.Min().Z : Bounds.Min().Z - Bounds.Length());

			maxbounds.X = (xdir < 0 ? Bounds.Max().X : Bounds.Max().X + Bounds.Width());
			maxbounds.Y = (ydir < 0 ? Bounds.Max().Y : Bounds.Max().Y + Bounds.Height());
			maxbounds.Z = (zdir < 0 ? Bounds.Max().Z : Bounds.Max().Z + Bounds.Length());

			ParentId = Tree->Nodes.Add(Node (Tree,Math::BoundingBox::MinMax(minbounds,maxbounds)));
			return ParentId;
		}
	};
	
private:
	FreeList <Node> Nodes;
	NodeId RootId;

	bool HasRoot () const
	{
		return RootId.IsValid ();
	}

	Node &Root ()
	{ return Nodes.Get(RootId); }

	const Node &Root () const
	{ return Nodes.Get(RootId); }

public:
	void Update (T *object)
	{

	}

	void Insert (T *object)
	{
		const Math::BoundingBox &objectbounds = object->GeometryComponent().Bounds ();
		if (!HasRoot ())
		{
			//Create a root node containing the object.
			float maxdim = std::max(std::max(objectbounds.Width(),objectbounds.Height()),objectbounds.Length());

			RootId = Nodes.Add(Node(this,Math::BoundingBox(objectbounds.Center(),Math::Vector3(maxdim*4,maxdim*4,maxdim*4))));
			Nodes.Get(RootId).ThisId = RootId;
		}
		else if (!Root ().Bounds.CompletelyContains (objectbounds))
		{
			//Expand root to contain object
			while (!Root ().Bounds.CompletelyContains (objectbounds))
			{
				RootId = Root().CreateParentNode(object);
			}
			//add object to root
			Root().Insert(object);
			return;
		}
		else
		{
			Root().Insert(object);
		}
	}

	void Remove (T *object)
	{
		object->NodeRef.Get().Remove(object);
	}
};

}}