#include <string>
#include <memory>




class AsyncPort 
{
public:

	AsyncPort();


private:

	class impl;
	typedef std::auto_ptr<impl> impl_ptr;
	impl_ptr pimpl;
};

