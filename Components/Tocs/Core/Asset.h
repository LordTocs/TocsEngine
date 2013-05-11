#pragma once
#include <map>
#include <string>
#include <memory>

namespace Tocs {


template <class T>
class Asset
{
	class AssetInfo
	{
		T *AssetPtr;
		int Count;
		std::string File;
		bool Registered;
	public:
		T *GetAsset () { return AssetPtr; }
		const T *GetAsset () const { return AssetPtr; }
		int GetCount () { return Count; }
		void DecreaseCount () { --Count; }
		void IncreaseCount () { ++Count; }
		bool IsRegistered () const { return Registered; }
		std::string GetFile () { return File; }

		AssetInfo (T *asset, std::string file)
			: AssetPtr (asset),
			  Count (0),
			  File (file),
			  Registered(true)
		{
		}

		AssetInfo (T *asset)
			: AssetPtr(asset), 
			  Count(0),
			  Registered(false)
		{
		}

		~AssetInfo ()
		{
			if (Registered && AssetPtr != nullptr)
				delete AssetPtr;
		}
	};


	static std::map <std::string, std::unique_ptr<AssetInfo>> Assets;

	AssetInfo *Info;


	void RemoveReference ()
	{
		if (Info == nullptr)
			return;
		Info->DecreaseCount ();

		if (Info->GetCount () == 0)
		{
			//KILL
			if (Info->IsRegistered())
				Assets.erase (Info->GetFile ());
			else
				delete Info;
		}

	}
	void AddReference ()
	{
		if (Info == nullptr)
			return;
		Info->IncreaseCount ();
	}

	Asset (AssetInfo *info)
		: Info (info)
	{
		AddReference ();
	}
public:
	Asset (const Asset <T> &copyme)
		: Info (copyme.Info)
	{ 
		AddReference ();
	}

	Asset (Asset <T> &&moveme)
		: Info (moveme.Info)
	{
		moveme.Info = nullptr;
	}

	~Asset ()
	{ 
		RemoveReference ();
	}
	
	
	T &operator  *()
	{ 
		return *Info->GetAsset ();
	}

	T *operator-> ()
	{ 
		return Info->GetAsset ();
	}

	T &Get ()
	{
		return *Info->GetAsset ();
	}

	const T &Get () const
	{
		return *Info->GetAsset ();
	}

	Asset <T> &operator= (const Asset <T> &op2)
	{
		RemoveReference ();
		Info = op2.Info;
		AddReference ();
		return *this;
	}

	Asset<T> &operator= (Asset<T> &&moveme)
	{
		Info = moveme.Info;
		moveme.Info = nullptr;
		return *this;
	}

	//static void PreLoad (const std::string &Filename)
	//{
	//	auto i =  Assets.find (Filename);
	//	if (i == Assets.end ())
	//	{
	//		AssetInfo *info = new AssetInfo (new T (std::move(T::LoadFromFile (Filename))),Filename);
	//		info->IncreaseCount ();
	//		Assets[Filename] = std::unique_ptr<AssetInfo>(info);
	//	}
	//}

	static Asset <T> Load (const std::string &Filename)
	{
		auto i =  Assets.find (Filename);
		if (i != Assets.end ())
		{
			return Asset <T> ((*i).second.get());
		}
		else
		{
			AssetInfo *info = new AssetInfo (new T (std::move(T::LoadFromFile (Filename))),Filename);
			Assets[Filename] = std::unique_ptr<AssetInfo>(info);
			return Asset <T> (info);
		}
	}

	static Asset <T> Manage (const std::string &filename, T* asset)
	{
		auto i = Assets.find (Filename);
		if (i != Assets.end ())
		{
			throw "Asset already exists."; //make better
		}
		AssetInfo *info = new AssetInfo (asset,filename);
		Assets[filename] = std::unique_ptr<T>(info);
		return Asset<T> (info);
	}

	static Asset<T> Wrap (T &asset)
	{
		AssetInfo *info = new AssetInfo (&asset);
		return Asset<T> (info);
	}

	bool operator == (const Asset <T> &op2)
	{
		if (op2.Info == nullptr)
		{
			if (Info == nullptr)
				return true;
			return false;
		}

		if (Info == nullptr)
			return false;

		return op2.Info->GetAsset () == Info->GetAsset ();
	}

	bool operator != (const Asset <T> &op2)
	{
		return !operator== (op2);
	}

	bool operator < (const Asset <T> &op2)
	{
		if (op2.Info == nullptr)
			return false;

		if (Info == nullptr)
			return false;

		return op2.Info->GetAsset () <= Info->GetAsset ();
	}

};

template <class T>
std::map <std::string, std::unique_ptr<typename Asset<T>::AssetInfo>> Asset<T>::Assets;

}