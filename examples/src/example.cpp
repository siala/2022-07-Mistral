/*
 * example.cpp
 *
 *  Created on: 16 juil. 2022
 *      Author: msiala
 */




#include<iostream>

#include "mistral_scheduler.hpp"


using namespace Mistral;

//#include "mistral_solver.hpp"
//#include "mistral_variable.hpp"
//#include "mistral_search.hpp"


using namespace std;
//using namespace Mistral;


class SolListener : public SolutionListener {

public:

	
	Mistral::Solver *solver_;
	Variable var; 

	SolListener(Mistral::Solver *s , Variable v)
	{
		solver_ = s ; 
		var = v ; 
	} ; 
	//virtual ~SolutionPrinter()

	virtual void notify_solution() 
	{

		for (int i = 0 ; i< solver_->variables.size ;  ++i) {
					std::cout  << " " << solver_->variables[i].get_solution_min()	; 
		}
					std::cout  << "  OPT  " << var.get_solution_min()	<< std::endl;
	} ;

	} ;



int main(int argc, char * argv[]) {



	VarArray scope;
	Solver s;
	Outcome result;

	int L=-100;

	//U is a lower bound for the accuracy
	int U = 100;

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
	s.add(Sum(scope, accuracy_coefficient) <= 200);




	s.parameters.verbosity = 2;
	
	


	Goal* goal = new Goal(Goal::MAXIMIZATION, scope[1]);
	
	SolListener sol(&s,scope[1] ) ; 

	//result = s.solve();
	//result =
	s.add(& sol) ; 
	std::string _variable_ordering = "lexicographic" ; 
	std::string _value_ordering = "min" ; 
	int _randomization = 2; 
	BranchingHeuristic * _option_heuristic = s.heuristic_factory( _variable_ordering, _value_ordering, _randomization);
	RestartPolicy * gg = new Geometric() ; 


	//std::cout <<  s << std::endl;
	//s.rewrite();
	s.consolidate();


	result = s.depth_first_search(s.variables, _option_heuristic, gg , goal);

	//s.minimize(scope[1] + scope[2]) ;



	//s.statistics.print_full(std::cout);


		std::cout << " \n \n c Solution Found! " << std::endl;

		//for ( unsigned int i= 0 ; i< scope.size ; ++i)
		//	std::cout <<  " c Solution value of scope[" << i <<  "]  is " << scope[i].get_solution_int_value() << std::endl;

		int a = scope[0].get_solution_int_value();
		int b = scope[1].get_solution_int_value();
		int c = scope[2].get_solution_int_value();
		int d = scope[3].get_solution_int_value();

		//int fairness_sum= scope[4].get_solution_int_value();

//      std::cout << " c a" << a << std::endl;
//      std::cout << " c b" << b << std::endl;
//      std::cout << " c c" << c << std::endl;
//      std::cout << " c d" << d << std::endl;


      assert( (a - b + d - c) <=  13);


		//int discrete_fairness= (nb_unprotected * (sp_plus+sp_minus)) - (nb_protected * (su_plus +su_minus) )  ;
		//std::cout <<  " c Fairness (discrete constraint) is "  << discrete_fairness << std::endl;
//		std::cout << " c Solution Verified" << std::endl;

//	} else
//		std::cout << " c No Solution! " << std::endl;


}



