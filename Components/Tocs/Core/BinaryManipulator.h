#include "TocsAPI.h"
#include "DataSource.h"

namespace Tocs {

TocsAPI
class BinaryManipulator
{
	DataSource *Source;
protected:
	int Location;
public:
	BinaryManipulator(DataSource &data);
	~BinaryManipulator(void);

	void SetLocation (int index)
	{
		Location = index;
	}

	template <class T>
	T Read ()
	{
		if (Source == nullptr)
			return T ();

		if (!Source->CanRead (Location,sizeof (T)))
			return T ();

		T item;
		Source->Read (Location,(char *)&item,sizeof (T));
		Location += sizeof (T);
		return item;
	}

	template <class T>
	void Write (const T &value)
	{
		if (Source == nullptr)
			return;
		if (!Source->CanWrite (Location,sizeof (T)))
			return;
		Source->Write (Location,(char *)&value,sizeof (T));
		Location += sizeof (T);
	}
};

}

