
#include <iostream>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

void MYFUNC(void *user_data)
{

	std::cout << std::endl <<"MYFUNC: running" << std::endl;
	std::cout << (char *)user_data << std::endl;
	boost::posix_time::seconds workTime(3);
	boost::this_thread::sleep(workTime);
	std::cout << "MYFUNC: finished" << std::endl;
}

class PCWorkerThread
{
public:
	void Create(void(*Worker_thread)(void *), void *data);
	boost::thread *workerThread;
};

void PCWorkerThread::Create(void(*Worker_thread)(void *),void *data)
{
	workerThread = new boost::thread(Worker_thread, data);
}


int main(int argc, char* argv[])
{
	std::cout << "main: startup" << std::endl;
	char *a = new char;
	a = "this is a  string";
	PCWorkerThread obj;
	obj.Create(MYFUNC,(void *)a);
	std::cout << " main: waiting for thread " <<std::endl;
	obj.workerThread->join();
	std::cout << "main: done" << std::endl;
	fflush(stdin);
	getchar();
	return 0;
}
