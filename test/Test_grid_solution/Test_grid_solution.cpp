# include <iostream>
# include <fstream>
# include <sstream>
using namespace std;
# include "../../scr/liton_ordered_tec/ordered_tec.h"
using namespace liton_ot;

# define DATATYPE double
int main(int argc,char **argv)
{
	DATATYPE *x, *y, *z, *w;
	size_t NI = 1000, NJ = 2000;
	try
	{
		x = new DATATYPE[NI*NJ];
		y = new DATATYPE[NI*NJ];
		z = new DATATYPE[NI*NJ];
		w = new DATATYPE[NI*NJ];
	}
	catch (...)
	{
		cerr << "runtime_error: out of memery" << endl;
		return 0;
	}
	for (int j = 0; j != NJ; ++j)
	{
		for (int i = 0; i != NI; ++i)
		{
			x[i + j*NI] = j;
			y[i + j*NI] = i;
			z[i + j*NI] = 1 + i / 2 + j;
			w[i + j*NI] = i + j;
		}
	}

	TEC_FILE tecfile_grid("test_03_g", ".", "test_03_grid");
	tecfile_grid.FileType=1;
	tecfile_grid.Variables.push_back("x");
	tecfile_grid.Variables.push_back("y");
	tecfile_grid.Zones.push_back(TEC_ZONE("grid"));
	tecfile_grid.Zones[0].Max[0]=NI;
	tecfile_grid.Zones[0].Max[1]=NJ;
	tecfile_grid.Zones[0].Data.push_back(TEC_DATA(x));
	tecfile_grid.Zones[0].Data.push_back(TEC_DATA(y));
	tecfile_grid.Zones[0].Skip[0]=2;
	tecfile_grid.Zones[0].Skip[1]=3;
	tecfile_grid.Zones[0].Begin[0]=50;
	tecfile_grid.Zones[0].End[0]=50;
	tecfile_grid.Zones[0].Begin[1]=10;
	tecfile_grid.Zones[0].End[1]=10;
	tecfile_grid.set_echo_mode("full", "full");
	try
	{
		tecfile_grid.write_plt(false);
		tecfile_grid.last_log.write_echo();
	}
	catch(runtime_error err)
	{
		cerr<<"runtime_error: "<<err.what()<<endl;
	}

	TEC_FILE tecfile_solution("test_03_s", ".", "test_03_solution");
	tecfile_solution.FileType=2;
	tecfile_solution.Variables.push_back("z");
	tecfile_solution.Variables.push_back("w");
	tecfile_solution.Zones.push_back(tecfile_grid.Zones[0]);
	tecfile_solution.Zones[0].ZoneName="solution";
	tecfile_solution.Zones[0].Data.clear();
	tecfile_solution.Zones[0].Data.push_back(TEC_DATA(z));
	tecfile_solution.Zones[0].Data.push_back(TEC_DATA(w));
	tecfile_solution.set_echo_mode("full", "full");
	try
	{
		tecfile_solution.write_plt(false);
		tecfile_solution.last_log.write_echo();
	}
	catch(runtime_error err)
	{
		cerr<<"runtime_error: "<<err.what()<<endl;
	}

	delete [] x;
	delete [] y;
	delete [] z;
	delete [] w;
	return 0;
}