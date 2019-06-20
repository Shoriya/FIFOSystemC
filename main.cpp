#include"ProdCons.h"



int sc_main(int argc, char* argv[])
{
	sc_clock Clock("Clock", 2, SC_SEC,true);
	consumer* cons_inst = new consumer("cons_inst");
	Producer* prod_inst = new Producer("prod_inst");

	fifo_channel<int,10>fifo_inst ("fifo_inst");

	prod_inst->out(fifo_inst);
	prod_inst->clk(Clock);

	cons_inst->clk(Clock);
	cons_inst->in(fifo_inst);
	sc_start(8000,SC_MS);

	return 0;
}
