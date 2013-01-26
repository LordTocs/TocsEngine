#pragma once

namespace Tocs {

class DataSource
{
public:
	virtual void Write (int location, char *data, int size) = 0;
	virtual void Read  (int location, char *data, int size) = 0;
	virtual bool CanWrite (int location, int size) const = 0;
	virtual bool CanRead  (int location, int size) const = 0;

};

}