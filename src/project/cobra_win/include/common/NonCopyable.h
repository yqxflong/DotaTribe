#ifndef  _LC_COBRA_WIN_NONCOPYABLE_H
#define  _LC_COBRA_WIN_NONCOPYABLE_H


namespace  cobra_win
{


class  NonCopyable
{
protected:
	NonCopyable()  { }
	~NonCopyable() { }

private:
	NonCopyable(const NonCopyable& obj) { }
	NonCopyable& operator=(const NonCopyable& obj) { return *this; }
};


}


#endif
