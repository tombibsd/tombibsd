// $NetBSD$

// generate references to exception handling runtime code

extern "C" void ccexc(void);

void
ccexc(void)
{
	try {
		throw "mist";
	} catch (char *e) {
	}
}
