#include "SpecialTokenSet.h"

using namespace std;

SpecialTokenSet::CharacterNode *SpecialTokenSet::CharacterNode::AddChildChar(char c)
{
	if (!HasChild (c))
	{
		CharacterNode * result = new CharacterNode (c);
		Children[c] = result;
		return result;
	}
	return Children[c];
}

SpecialTokenSet::CharacterNode *SpecialTokenSet::CharacterNode::GetChild (char c)
{
	map <char, CharacterNode *>::iterator i = Children.find (c);
	if (i != Children.end ())
		return (*i).second;
	return nullptr;
}

SpecialTokenSet::CharacterNode *SpecialTokenSet::GetBaseNode (char c)
{
	map <char, CharacterNode *>::iterator i = BaseNodes.find (c);
	if (i != BaseNodes.end ())
		return (*i).second;
	return nullptr;
}


void SpecialTokenSet::AddString (string str)
{
	CharacterNode *node = GetBaseNode (str[0]);
	if (node == nullptr)
	{
		node = new CharacterNode (str[0]);
		BaseNodes[str[0]] = node;
	}
	for (string::iterator i = str.begin () + 1; i != str.end (); ++i)
	{
		node = node->AddChildChar (*i);
	}
}

SpecialTokenSet::SpecialTokenSet()
{
}

bool SpecialTokenSet::TokenTester::TestChar (char c)
{
	if (Current == nullptr)
	{
		Current = Set->GetBaseNode (c);
	}
	else
	{
		Current = Current->GetChild (c);
	}

	return Current != nullptr;
}


SpecialTokenSet::~SpecialTokenSet(void)
{
}
