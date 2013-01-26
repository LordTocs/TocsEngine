#pragma once
#include <string>
#include <initializer_list>
#include <map>
class SpecialTokenSet
{
	class CharacterNode
	{
		char Character;
		std::map <char, CharacterNode *> Children;
	public:
		CharacterNode (char c)
			: Character (c)	{}

		char GetCharacter () const { return Character; }
		CharacterNode *AddChildChar (char c);
		bool HasChild (char c) const { return Children.find (c) != Children.end (); }
		CharacterNode *GetChild (char c);
	};

	std::map <char, CharacterNode *> BaseNodes;
	CharacterNode *GetBaseNode (char c);
	bool HasBaseNode (char c) const { return BaseNodes.find (c) != BaseNodes.end (); }

	
public:
	void AddString (std::string string);
	class TokenTester
	{
		CharacterNode *Current;
		SpecialTokenSet *Set;
	public:
		TokenTester (SpecialTokenSet &set) : Set (&set), Current (nullptr) {}
		bool TestChar (char c);
	};
	SpecialTokenSet();
	~SpecialTokenSet(void);
};

