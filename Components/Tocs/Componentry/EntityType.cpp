#include "EntityType.h"
#include <iostream>
#include <Tocs/Core/Tokenizer.h>
#include <Tocs/Scripting/Callback.h>
#include <sstream>
#include "Entity.h"

using namespace std;
using namespace Tocs::Lexing;

namespace Tocs {
namespace Componentry {

EntityType::EntityType(std::string entity_file,Scripting::Engine &engine)
{
	Parse(entity_file,engine);
}


EntityType::~EntityType(void)
{
}

void EntityType::Parse (std::string entity_file, Scripting::Engine &engine)
{
	StringSource filesource (StringSource::FromFile(entity_file));

	Tokenizer tokens (filesource);

	if (!tokens.Is("entity"))
	{ return; }

	Name = tokens.GetToken ();

	Module = engine.GetEnginePtr ()->GetModule ((Name+"_module").c_str(),asGM_ALWAYS_CREATE);


	if (!tokens.Is(":"))
	{ return; }

	if (!tokens.Is("{"))
	{ return; }

	vector<pair<string,string>> ComponentScripts;

	//Parse Components
	while (tokens.Is("component"))
	{
		string componenttype = tokens.GetToken ();
		if (!tokens.Is(":"))
		{ return; }
		if (!tokens.Is("{"))
		{ return; }
		int scriptstart = filesource.GetIndex () - tokens.PeekToken().length();
		tokens.FindClose("{","}");
		int scriptend = filesource.GetIndex () - 3;

		string scriptstring = filesource.GetString().substr(scriptstart,scriptend - scriptstart);
		//Angelscript the code inbetween...
		//Module->AddScriptSection (componenttype.c_str(),scriptstring.c_str(),scriptstring.length ());
		ComponentScripts.push_back(make_pair(componenttype,scriptstring));
	}

	if (!tokens.Is("}"))
	{ return; }


	for (auto i = ComponentScripts.begin(); i != ComponentScripts.end(); ++i)
	{
		Components.push_back(ComponentRegistry::GetRegistry().GetFactory((*i).first));
	}

	stringstream genscript;

	genscript << "class " << Name << "\
				 {\
					" << Name << "_Cpp @self; \
					" << Name << "(" << Name << "_Cpp @selfptr)\
					{\
						@self = @selfptr;\
					}\
				 ";

	for (auto i = ComponentScripts.begin(); i != ComponentScripts.end(); ++i)
	{
		genscript << (*i).second;
	}
	
	genscript << "}";
	string genscriptstr= genscript.str();
	cout << genscriptstr << endl;

	RegisterScriptType (engine);


	Module->AddScriptSection ("Generated Code", genscriptstr.c_str());
	Module->Build ();

	ScriptType = Module->GetObjectTypeByName(Name.c_str());
	for (auto i = Components.begin(); i != Components.end(); ++i)
	{
		(*i)->ProcessCompiledObject(ScriptType);
	}

	//Get points to callbacks

}

void EntityType::RegisterScriptType (Scripting::Engine &engine)
{
	string angelname = Name + "_Cpp";
	engine.GetEnginePtr ()->RegisterObjectType (angelname.c_str(),0,asOBJ_REF | asOBJ_NOCOUNT);

	int index = 0;
	for (auto i = Components.begin (); i != Components.end (); ++i)
	{
		(*i)->RegisterToEngine (angelname,index,engine);
	}
}

asIScriptObject *EntityType::ConstructScriptObject(Entity *ent)
{
	Scripting::Context *context = ent->GetWorld ().GetEngine().Pool.GetContext ();
	cout << "Context: " << context << endl;
	cout << "ContextPtr: " << context->GetContextPtr () << endl;
	Scripting::Callback<asIScriptObject *(Entity *)> constructor;
	cout << "Factory: " << ScriptType->GetFactoryByIndex(0);
	constructor.SetFunction(ScriptType->GetFactoryByIndex(0));
	asIScriptObject *obj = constructor.Invoke(context,ent);
	ent->GetWorld().GetEngine().Pool.ReturnContext(context);
	return obj;
}


}}
  