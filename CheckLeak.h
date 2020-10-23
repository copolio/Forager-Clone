#if defined(_DEBUG)
# include <crtdbg.h>
# if defined(malloc)
# undef malloc
# endif
# define malloc(s) (_malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__ ))
# if defined(calloc)
# undef calloc
# endif
# define calloc(c, s) (_calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__ ))
# if defined(realloc)
# undef realloc
# endif
# define realloc(p, s) (_realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__ ))
# if defined(_expand)
# undef _expand
# endif
# define _expand(p, s) (_expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__  ))
# if defined(free)
# undef free
# endif
# define free(p) (_free_dbg(p, _NORMAL_BLOCK))
# if defined(_msize)
# undef _msize
# endif
# define _msize(p) (_msize_dbg(p, _NORMAL_BLOCK))
# define new new( _NORMAL_BLOCK, __FILE__, __LINE__ )
class CheckMemoryLeakForWin32 {
public:
	CheckMemoryLeakForWin32() {
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		// 중단점 트리거
		//_CrtSetBreakAlloc(2774);
	}
	~CheckMemoryLeakForWin32() {}
}CheckMemoryLeakForWin32;
#endif