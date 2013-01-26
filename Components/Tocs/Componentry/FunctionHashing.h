#include <Tocs/Core/Hashing.h>

namespace Tocs {
namespace Componentry {

template <class T>
class HashOnce
{
	static int Hash;
public:
	static int GetHash (const std::string &str)
	{
		if (Hash != 0)
			return Hash;
		Hash = Hashing::Hash (str);
		return Hash;
	}
};

template <class T> int HashOnce <T>::Hash;

#define HashIdent(token) HashOnce<class q__0##token>::GetHash (#token)

}}