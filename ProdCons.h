#include"Channel.h"

SC_MODULE(Producer)
{
	sc_port<fifo_write_inf<int> > out;
	sc_in<bool>clk;
	void do_send()
	{
		while(true)
		{
		int var=25;
		out->write_nb(var);
		cout<<"\n"<<sc_time_stamp()<<"\t Producer Function 1"<<endl;
		cout<<"written value"<<var<<endl;

		var= 100;
		out->write_b(var);
		cout<<"\n"<<sc_time_stamp()<<"\t Producer Function 2"<<endl;
		cout<<"written value"<<var<<endl;

		for(int i=0;i<10;i++)
		{
			out->write_b(var);
			cout<<"\n"<<sc_time_stamp()<<"\t Producer Function 3"<<endl;
			cout<<"Written value"<<var<<endl;
		}
		wait(1);


		}
    }

	SC_CTOR(Producer)
	{
		cout<<sc_time_stamp()<<"\t Producer Constructor"<<endl;
		SC_CTHREAD(do_send,clk.pos());
		//sensitive<<clk.pos();
	}
};

SC_MODULE(consumer)
{
	sc_port<fifo_read_inf<int> >in;
	sc_in<bool>clk;

	void do_read()
	{
		while(true)
		{
		int b;
		cout<<"\n"<<sc_time_stamp()<<"\t Consumer Function 1"<<endl;
		in->read_nb(b);
		cout <<"value read"<<b<<endl;

		int data;
		data= in->get_ndata();
		cout<<"\n"<<sc_time_stamp()<<"Number of data"<<endl;
		cout<<"Data: "<<data;

		in->read_b(b);
		cout<<"\n"<<sc_time_stamp()<<"\t "<<endl;
		cout<<"value read"<<b<<endl;



		wait(1);
		}

	}

	SC_CTOR(consumer)
	{
		cout<<sc_time_stamp()<<"\t Consumer Constructor 2"<<endl;
		SC_CTHREAD(do_read,clk.neg());
	}
};

