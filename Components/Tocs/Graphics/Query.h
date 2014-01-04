#pragma once

namespace Tocs {
namespace Graphics {

class QueryTarget
{
	unsigned int Internal;

	QueryTarget(unsigned int value)
		: Internal(value)
	{}

public:
	const static QueryTarget SamplesPassed;
	const static QueryTarget AnySamplesPassed;
	const static QueryTarget AnySamplesPassedConservative;
	const static QueryTarget Time;
	const static QueryTarget None;

	unsigned int GetGLEnum() const { return Internal; }

	bool operator ==  (const QueryTarget &op2) const { return Internal == op2.Internal; }
	bool operator !=  (const QueryTarget &op2) const { return Internal != op2.Internal; }
};

class Query
{
	unsigned int ID;
	QueryTarget Target;
public:
	Query();
	~Query();

	unsigned int GetID() const { return ID; }

	void Begin(QueryTarget target);
	void End();

	bool Ready() const;

	unsigned int Result() const;
	unsigned long long Result64() const;
};

}}