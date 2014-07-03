#include <atomic>

namespace Tocs {
namespace Threads
{

template <class T>
class AtomicShared
{
	class DataNode
	{
	public:
		T Data;
		std::atomic<unsigned int> ReferenceCount;
		std::atomic_flag DeleteFlag;
		public DataNode(T &&data)
			: Data(std::forward(data)), ReferenceCount(0) {}
		public DataNode(const T &data)
			: Data(data), ReferenceCount(0) {}

		void DecRef()
		{
			int count = ReferenceCount.fetch_sub(-1);
			if (count > 1)
				return;
			bool remove = DeleteFlag.test_and_set();
			if (remove)
				return;
			delete *this;
		}
	};
	std::atomic<DataNode *> Data;

	void IncRef()
	{
		while (true)
		{
			DataNode *node = Data.load();
			if (node == nullptr)
				return;
			++(node->ReferenceCount);
			if (node == Data.load())
			{
				return;
			}
			else
			{
				node->DecRef();
			}

		}
	}
public:
	AtomicShared(T &&data)
		: Data(new DataNode(std::forward(data)))
	{
		++(Data->ReferenceCount);
	}

	AtomicShared(const AtomicShared<T> &copyme)
	: Data(copyme.Data.load())
	{
		if (Data != nullptr)
			++(Data->ReferenceCount);
	}

	AtomicShared(AtomicShared<T> &&moveme)
	: Data(moveme.Data.load())
	{
		moveme.Data.store(nullptr);
	}

	AtomicShared &operator= (const AtomicShared<T> &copyme)
	{
		DataNode *oldnode = Data.exchange(nullptr);
		do
		{
			if (oldnode)
				oldnode->DecRef();
			oldnode = nullptr;
		} while (Data.compare_exchange_weak(oldnode, copyme.Data.load()));

		IncRef();
	}

	AtomicShared &operator= (AtomicShared<T> &&moveme)
	{
		DataNode *newnode = moveme.Data.load(); //This stays the same because its an r-value... I think.
		DataNode *oldnode = Data.exchange(nullptr); 
		do
		{
			if (oldnode)
				oldnode->DecRef();
			oldnode = nullptr;
		} while (Data.compare_exchange_weak(oldnode, newnode));
	}

	T &operator *()
	{
		return Data->Data;
	}

	const T &operator *() const
	{
		return Data->Data;
	}
};

}}