/*
 * example.cpp
 *
 *  Created on: 16 juil. 2022
 *      Author: msiala
 */





#include "mistral_scheduler.hpp"


using namespace Mistral;

//#include "mistral_solver.hpp"
//#include "mistral_variable.hpp"
//#include "mistral_search.hpp"


using namespace std;
//using namespace Mistral;




int main(int argc, char * argv[]) {



	VarArray scope;
	Solver s;
	Outcome result;

	int L=3;

	//U is a lower bound for the accuracy
	int U = 10;

	scope.add(Variable(L, U));
	scope.add(Variable(L, U));
	scope.add(Variable(L, U));
	scope.add(Variable(L, U));


	result = UNSAT;

	std::vector < int > accuracy_coefficient;
	// accuracy_coefficient represents the coefficients used in the accuracy.
	accuracy_coefficient.push_back(1);
	accuracy_coefficient.push_back(-1);
	accuracy_coefficient.push_back(1);
	accuracy_coefficient.push_back(-1);

    //std::cout <<  " \n c in the CP model, the upper Bound for accuracy constraint: "  << constant	<< std::endl;
    s.add(Sum(scope, accuracy_coefficient) <= 13);



    s.parameters.verbosity = 2;
    //std::cout <<  s << std::endl;
    //s.rewrite();
    s.consolidate();
    result = s.solve();



    s.statistics.print_full(std::cout);


    if (result) {
      std::cout << " \n \n c Solution Found! " << std::endl;

      //for ( unsigned int i= 0 ; i< scope.size ; ++i)
      //	std::cout <<  " c Solution value of scope[" << i <<  "]  is " << scope[i].get_solution_int_value() << std::endl;

      int a = scope[0].get_solution_int_value();
      int b = scope[1].get_solution_int_value();
      int c = scope[2].get_solution_int_value();
      int d = scope[3].get_solution_int_value();

      //int fairness_sum= scope[4].get_solution_int_value();

      std::cout << " c a" << a << std::endl;
      std::cout << " c b" << b << std::endl;
      std::cout << " c c" << c << std::endl;
      std::cout << " c d" << d << std::endl;


      assert( (a + b + d + c) <=  13);


      //int discrete_fairness= (nb_unprotected * (sp_plus+sp_minus)) - (nb_protected * (su_plus +su_minus) )  ;
      //std::cout <<  " c Fairness (discrete constraint) is "  << discrete_fairness << std::endl;
      std::cout << " c Solution Verified" << std::endl;

    } else
      std::cout << " c No Solution! " << std::endl;
}



