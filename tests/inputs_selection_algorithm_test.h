/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   I N P U T   S E L E C T I O N   A L G O R I T H M   T E S T   C L A S S   H E A D E R                      */
/*                                                                                                              */
/*   Fernando Gomez                                                                                             */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   fernandogomez@artelnics.com                                                                                */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __INPUTSELECTIONALGORITHMTEST_H__
#define __INPUTSELECTIONALGORITHMTEST_H__

// Unit testing includes

#include "unit_testing.h"

using namespace OpenNN;


class InputsSelectionAlgorithmTest : public UnitTesting
{

#define	STRING(x) #x
#define TOSTRING(x) STRING(x)
#define LOG __FILE__ ":" TOSTRING(__LINE__)"\n"

public:

   // CONSTRUCTOR

   explicit InputsSelectionAlgorithmTest(void);


   // DESTRUCTOR

   virtual ~InputsSelectionAlgorithmTest(void);


   // METHODS

   // Constructor and destructor methods

   void test_constructor(void);
   void test_destructor(void);

   // Get methods

   void test_get_training_strategy_pointer(void);


   void test_get_performance_calculation_method(void);

   void test_write_performance_calculation_method(void) ;

   // Set methods

   void test_set_training_strategy_pointer(void);

   void test_set_default(void);

   void test_set_performance_calculation_method(void);

   // Performances calculation methods

   void test_set_neural_inputs(void);

   void test_calculate_minimum_final_performances(void);
   void test_calculate_maximum_final_performances(void);
   void test_calculate_mean_final_performances(void);

   void test_get_final_performances(void);

   void test_calculate_performances(void);

   void test_get_parameters_order(void);

   // Unit testing methods

   void run_test_case(void);

};


#endif
