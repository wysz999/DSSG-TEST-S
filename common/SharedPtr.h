#ifndef __SharedPtr_H__
#define __SharedPtr_H__

#include "Common.h"

//#define BOOST_NOEXCEPT
#include <boost/thread.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/shared_mutex.hpp>


#define WGS_AUTO_MUTEX_NAME mutex
#define WGS_AUTO_MUTEX mutable 	boost::mutex WGS_AUTO_MUTEX_NAME;
#define WGS_LOCK_AUTO_MUTEX 	boost::lock_guard<boost::mutex> wgsAutoMutexLock(WGS_AUTO_MUTEX_NAME);

#define WGS_AUTO_READ_WRITE_MUTEX_NAME      read_write_shared_mutex
#define WGS_AUTO_READ_WRITE_MUTEX   mutable boost::mutex WGS_AUTO_READ_WRITE_MUTEX_NAME;
#define WGS_AUTO_READ_LOCK             boost::lock_guard<boost::mutex>  wgsAutoSharedMutexLock(WGS_AUTO_READ_WRITE_MUTEX_NAME);
#define WGS_AUTO_WRITE_LOCK 		boost::lock_guard<boost::mutex>  wgsAutoWriteMutexLock(WGS_AUTO_READ_WRITE_MUTEX_NAME); 
//#define WGS_AUTO_UPGRADE_LOCK                 boost::upgrade_lock<boost::shared_mutex>  wgsAutoUpgardMutexLock(WGS_AUTO_READ_WRITE_MUTEX_NAME); 
#define WGS_AUTO_UPGRADE_LOCK           boost::lock_guard<boost::mutex>  wgsAutoUpgardMutexLock(WGS_AUTO_READ_WRITE_MUTEX_NAME); 

//#define WGS_AUTO_READ_WRITE_MUTEX_NAME      read_write_shared_mutex
//#define WGS_AUTO_READ_WRITE_MUTEX   mutable boost::shared_mutex WGS_AUTO_READ_WRITE_MUTEX_NAME;
//#define WGS_AUTO_READ_LOCK             boost::shared_lock<boost::shared_mutex>  wgsAutoSharedMutexLock(WGS_AUTO_READ_WRITE_MUTEX_NAME);
//#define WGS_AUTO_WRITE_LOCK 		boost::unique_lock<boost::shared_mutex>  wgsAutoWriteMutexLock(WGS_AUTO_READ_WRITE_MUTEX_NAME); 
//#define WGS_AUTO_UPGRADE_LOCK                 boost::upgrade_lock<boost::shared_mutex>  wgsAutoUpgardMutexLock(WGS_AUTO_READ_WRITE_MUTEX_NAME); 
//#define WGS_AUTO_UPGRADE_LOCK           boost::unique_lock<boost::shared_mutex>  wgsAutoUpgardMutexLock(WGS_AUTO_READ_WRITE_MUTEX_NAME); 


#define WGS_MUTEX(name) mutable boost::mutex name;
#define WGS_STATIC_MUTEX(name) static boost::mutex name;
#define WGS_STATIC_MUTEX_INSTANCE(name) boost::mutex name;
#define WGS_LOCK_MUTEX(name) boost::lock_guard<boost::mutex> wgsnameLock(name);
#define WGS_LOCK_MUTEX_NAMED(mutexName, lockName) boost::lock_guard<boost::mutex> lockName(mutexName);
// like WGS_AUTO_MUTEX but mutex held by pointer
#define WGS_AUTO_SHARED_MUTEX mutable boost::mutex *WGS_AUTO_MUTEX_NAME;
#define WGS_LOCK_AUTO_SHARED_MUTEX assert(WGS_AUTO_MUTEX_NAME); boost::lock_guard<boost::mutex>  \
		wgsAutoMutexLock(*WGS_AUTO_MUTEX_NAME);
#define WGS_NEW_AUTO_SHARED_MUTEX assert(!WGS_AUTO_MUTEX_NAME); \
		WGS_AUTO_MUTEX_NAME = new boost::mutex();

#define WGS_DELETE_AUTO_SHARED_MUTEX assert(WGS_AUTO_MUTEX_NAME); delete WGS_AUTO_MUTEX_NAME;

#define WGS_COPY_AUTO_SHARED_MUTEX(from) assert(!WGS_AUTO_MUTEX_NAME); WGS_AUTO_MUTEX_NAME = from;
#define WGS_SET_AUTO_SHARED_MUTEX_NULL WGS_AUTO_MUTEX_NAME = 0;
#define WGS_MUTEX_CONDITIONAL(mutex) if (mutex)
#define WGS_THREAD_SYNCHRONISER(sync) boost::condition sync;
#define WGS_THREAD_WAIT(sync, lock) sync.wait(lock);
#define WGS_THREAD_NOTIFY_ONE(sync) sync.notify_one(); 
#define WGS_THREAD_NOTIFY_ALL(sync) sync.notify_all(); 
// Thread-local pointer
#define WGS_THREAD_POINTER(T, var) boost::thread_specific_ptr<T> var
#define WGS_THREAD_POINTER_SET(var, expr) var.reset(expr)
#define WGS_THREAD_POINTER_DELETE(var) var.reset(0)
#define WGS_THREAD_POINTER_GET(var) var.get()


/// The method to use to free memory on destruction
enum SharedPtrFreeMethod
{
	/// Use DELETE to free the memory
	SPFM_DELETE,
	/// Use DELETE_T to free (only MEMCATEGORY_GENERAL supported)
	SPFM_DELETE_T,
	/// Use FREE to free (only MEMCATEGORY_GENERAL supported)
	SPFM_FREE
};

/** Reference-counted shared pointer, used for objects where implicit destruction is 
required. 
@remarks
This is a standard shared pointer implementation which uses a reference 
count to work out when to delete the object. 
@par
	If WGS_THREAD_SUPPORT is defined to be 1, use of this class is thread-safe.
*/
template<class T> class SharedPtr
{
protected:
	T* pRep;
	unsigned int* pUseCount;
	SharedPtrFreeMethod useFreeMethod; // if we should use WGS_FREE instead of WGS_DELETE
public:
	WGS_AUTO_SHARED_MUTEX // public to allow external locking
	/** Constructor, does not initialise the SharedPtr.
		@remarks
			<b>Dangerous!</b> You have to call bind() before using the SharedPtr.
	*/
	SharedPtr() : pRep(0), pUseCount(0), useFreeMethod(SPFM_DELETE)
	{
    		WGS_SET_AUTO_SHARED_MUTEX_NULL
	}

	/** Constructor.
	@param rep The pointer to take ownership of
	@param freeMode The mechanism to use to free the pointer
	*/
	template< class Y> explicit SharedPtr(Y* rep, SharedPtrFreeMethod freeMethod = SPFM_DELETE) 
		: pRep(rep)
		, pUseCount(rep ? new unsigned int: 0)
		, useFreeMethod(freeMethod)
	{
    		WGS_SET_AUTO_SHARED_MUTEX_NULL
		WGS_NEW_AUTO_SHARED_MUTEX
		
		if(pUseCount)
		   *pUseCount = 1;
	}

	 explicit SharedPtr(const T & rep, SharedPtrFreeMethod freeMethod = SPFM_DELETE)
		:pUseCount(new unsigned int)
		,useFreeMethod(freeMethod)
	{
		WGS_SET_AUTO_SHARED_MUTEX_NULL
		WGS_NEW_AUTO_SHARED_MUTEX

		pRep = new T;
	
		*pRep = rep;

		*pUseCount = 1;
	}

		

	SharedPtr(const SharedPtr& r) : pRep(0), pUseCount(0), useFreeMethod(SPFM_DELETE)
	{
		// lock & copy other mutex pointer
    
    		WGS_SET_AUTO_SHARED_MUTEX_NULL
    		WGS_MUTEX_CONDITIONAL(r.WGS_AUTO_MUTEX_NAME)
    		{
		    	WGS_LOCK_MUTEX(*r.WGS_AUTO_MUTEX_NAME)
		    	WGS_COPY_AUTO_SHARED_MUTEX(r.WGS_AUTO_MUTEX_NAME)
		    	pRep = r.pRep;
		    	pUseCount = r.pUseCount; 
			useFreeMethod = r.useFreeMethod;
		    	// Handle zero pointer gracefully to manage STL containers
		    	if(pUseCount)
		    	{
			    ++(*pUseCount); 
		    	}
    		}
	}

	SharedPtr& operator=(const SharedPtr& r) {
		if (pRep == r.pRep)
			return *this;
		// Swap current data into a local copy
		// this ensures we deal with rhs and this being dependent
		SharedPtr<T> tmp(r);
		swap(tmp);
		return *this;
	}

	SharedPtr& operator=(const T & r) {

		WGS_MUTEX_CONDITIONAL(WGS_AUTO_MUTEX_NAME)
		{
			WGS_LOCK_AUTO_SHARED_MUTEX 
			assert(pRep);
			*pRep = r;

			return *this;
		}
		
		SharedPtr<T> tmp(r);
		swap(tmp);
		return *this;
	}
	
	template< class Y> SharedPtr(const SharedPtr<Y>& r) : pRep(0), pUseCount(0), useFreeMethod(SPFM_DELETE)
	{
		// lock & copy other mutex pointer

    		WGS_SET_AUTO_SHARED_MUTEX_NULL
    		WGS_MUTEX_CONDITIONAL(r.WGS_AUTO_MUTEX_NAME)
    		{
		    WGS_LOCK_MUTEX(*r.WGS_AUTO_MUTEX_NAME)
		    WGS_COPY_AUTO_SHARED_MUTEX(r.WGS_AUTO_MUTEX_NAME)
		    pRep = r.getPointer();
		    pUseCount = r.useCountPointer();
		    useFreeMethod = r.freeMethod();
		    // Handle zero pointer gracefully to manage STL containers
		    if(pUseCount)
		    {
			    ++(*pUseCount);
		    }
    		}
	}

	template< class Y> SharedPtr& operator=(const SharedPtr<Y>& r) {
		if (pRep == r.pRep)
			return *this;
		// Swap current data into a local copy
		// this ensures we deal with rhs and this being dependent
		SharedPtr<T> tmp(r);
		swap(tmp);
		return *this;
	}
	virtual ~SharedPtr() {
    		release();
	}


	inline T& operator*() const { assert(pRep); return *pRep; }
	inline T* operator->() const { assert(pRep); return pRep; }
	inline T* get() const { return pRep; }

	/** Binds rep to the SharedPtr.
		@remarks
			Assumes that the SharedPtr is uninitialised!
	*/
	void bind(T* rep, SharedPtrFreeMethod freeMethod = SPFM_DELETE) {
		assert(!pRep && !pUseCount);
    		WGS_NEW_AUTO_SHARED_MUTEX
		WGS_LOCK_AUTO_SHARED_MUTEX
		pUseCount = new unsigned int;
		*pUseCount = 1;
		pRep = rep;
		useFreeMethod = freeMethod;
	}

	inline bool unique() const { WGS_LOCK_AUTO_SHARED_MUTEX assert(pUseCount); return *pUseCount == 1; }
	inline unsigned int useCount() const { WGS_LOCK_AUTO_SHARED_MUTEX assert(pUseCount); return *pUseCount; }
	inline unsigned int* useCountPointer() const { return pUseCount; }

	inline T* getPointer() const { return pRep; }
	inline SharedPtrFreeMethod freeMethod() const { return useFreeMethod; }

	inline bool isNull(void) const { return pRep == 0; }

	inline void setNull(void) { 
		if (pRep)
		{
			// can't scope lock mutex before release in case deleted
			release();
			pRep = 0;
			pUseCount = 0;
		}
	}	

protected:

	inline void release(void)
	{
		bool destroyThis = false;

		/* If the mutex is not initialized to a non-zero value, then
		neither is pUseCount nor pRep.
		*/

		WGS_MUTEX_CONDITIONAL(WGS_AUTO_MUTEX_NAME)
		{
			// lock own mutex in limited scope (must unlock before destroy)
			WGS_LOCK_AUTO_SHARED_MUTEX
			if (pUseCount)
			{
				if (--(*pUseCount) == 0) 
				{
					destroyThis = true;
				}
			}
		}
		if (destroyThis)
			destroy();

		WGS_SET_AUTO_SHARED_MUTEX_NULL
	}

	virtual void destroy(void)
	{
	    // IF YOU GET A CRASH HERE, YOU FORGOT TO FREE UP POINTERS
	    // BEFORE SHUTTING WGS DOWN
	    // Use setNull() before shutdown or make sure your pointer goes
	    // out of scope before WGS shuts down to avoid this.
		switch(useFreeMethod)
		{
		case SPFM_DELETE:
			delete pRep;
			break;
		case SPFM_DELETE_T:
			delete [] pRep;
			break;
		case SPFM_FREE:
			free(pRep);
			break;
		};
			// use WGS_FREE instead of WGS_DELETE_T since 'unsigned int' isn't a destructor
			// we only used WGS_NEW_T to be able to use constructor
	    	delete pUseCount;
		WGS_DELETE_AUTO_SHARED_MUTEX
	}

	virtual void swap(SharedPtr<T> &other) 
	{
		std::swap(pRep, other.pRep);
		std::swap(pUseCount, other.pUseCount);
		std::swap(useFreeMethod, other.useFreeMethod);
		std::swap(WGS_AUTO_MUTEX_NAME, other.WGS_AUTO_MUTEX_NAME);
	}
};

template<class T, class U> inline bool operator==(SharedPtr<T> const& a, SharedPtr<U> const& b)
{
	return a.get() == b.get();
}

template<class T, class U> inline bool operator!=(SharedPtr<T> const& a, SharedPtr<U> const& b)
{
	return a.get() != b.get();
}

template<class T, class U> inline bool operator<(SharedPtr<T> const& a, SharedPtr<U> const& b)
{
	

	return std::less<T>()(*a, *b);
}


typedef		SharedPtr<bool>			BoolPtr;
typedef		SharedPtr<unsigned int>		UInt32Ptr;
typedef		SharedPtr<int>			Int32Ptr;
typedef		SharedPtr<float>		FloatPtr;

#endif
