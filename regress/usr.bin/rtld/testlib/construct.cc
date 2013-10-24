// $NetBSD$

// check constructor / destructor calls

#include <iostream>

using namespace std;

class mist {
public:
	mist(void);
	~mist();
};

mist::mist(void)
{
	cout << "constructor" << endl;
}

mist::~mist()
{
	cout << "destructor" << endl;
}

static mist construct;
