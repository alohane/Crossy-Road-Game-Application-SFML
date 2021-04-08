#ifndef _non_copyable
#define _non_copyable
class no_copy {
public:
	no_copy()							= default;
	no_copy(const no_copy&)				= delete;
	no_copy& operator=(const no_copy&)	= delete;
};
#endif // !_non_copyable
