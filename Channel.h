#include <systemc.h>

template <class T>
class fifo_write_inf: virtual public sc_interface
{
public:
	virtual bool write_nb(T)=0;
	virtual void write_b(T)=0;
	virtual void reset()=0;
};

template <class T>
class fifo_read_inf: virtual public sc_interface
{
public:
	virtual bool read_nb(T&)=0;
	virtual void read_b(T&)=0;
	virtual int get_ndata()=0;
};

template <class T, int max_size>
class fifo_channel:
		public fifo_write_inf<T>,
		public fifo_read_inf<T>,
		public sc_module
		{

		protected:

	int size;
	T* buffer;
	int read_next;
	int write_index;
	int n_elements; 	 // no.of elements
	sc_event write_event;
	sc_event read_event;

		public:
	virtual int get_ndata()
	{
		return n_elements;
	}
	virtual bool write_nb(T val)
	{
		if(get_ndata()== size)
		{
			cout<<"Non Blocking mode"<<"bufferfer full, write not possible"<<endl;
			return false;
		}
		else
		{
			buffer[write_index]=val;
			write_index=(write_index+1)%size;
			n_elements++;
			return true;
		}
	}

	virtual void write_b(T val)
	{
		while(get_ndata()== size)
		{
			wait(read_event);

		}

		buffer[write_index]=val;
		write_index=(write_index+1)%size;
		n_elements++;
		write_event.notify();

	}
	virtual bool read_nb(T& val)
	{
		if(get_ndata()==0)
		{
			cout<<"Non Blocking mode"<<"buffer empty, read not possible"<< endl;
			return false;
		}
		else
		{
			val=buffer[read_next];
			read_next=(read_next+1)%size;
			n_elements--;
			return true;
		}
	}

	virtual void read_b(T& val)
	{
		while(get_ndata()== 0)
		{
			wait(write_event);

		}

		val=buffer[read_next];
		read_next=(read_next+1)%size;
		n_elements--;
		read_event.notify();

	}

	virtual void reset()
	{
		read_next=0;
		write_index=0;
		n_elements=0;
	}

	SC_CTOR(fifo_channel)
	{
		size=max_size;
		read_next=0;
		write_index=0;
		n_elements=0;
		buffer = new T[size];
	}
		};

