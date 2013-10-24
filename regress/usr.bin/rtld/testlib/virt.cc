// $NetBSD$

// g++ generates a reference to "__pure_virtual" with this code

class mist {
public:
	virtual void vv(void) = 0;
};

class mast: public mist {
public:
	void vv(void) {};
};

static mast virt;
