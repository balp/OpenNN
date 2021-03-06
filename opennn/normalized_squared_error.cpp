/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   N O R M A L I Z E D   S Q U A R E D   E R R O R   C L A S S                                                */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "normalized_squared_error.h"

namespace OpenNN
{

// DEFAULT CONSTRUCTOR

/// Default constructor. 
/// It creates a normalized squared error performance term object not associated to any 
/// neural network and not measured on any data set.
/// It also initializes all the rest of class members to their default values.

NormalizedSquaredError::NormalizedSquaredError(void) : PerformanceTerm()
{
}


// NEURAL NETWORK CONSTRUCTOR

/// Neural network constructor. 
/// It creates a normalized squared error performance term associated to a neural network object but not measured on any data set.
/// It also initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.

NormalizedSquaredError::NormalizedSquaredError(NeuralNetwork* new_neural_network_pointer)
: PerformanceTerm(new_neural_network_pointer)
{
}


// DATA SET CONSTRUCTOR

/// Data set constructor. 
/// It creates a normalized squared error performance term not associated to any 
/// neural network but to be measured on a data set object.
/// It also initializes all the rest of class members to their default values.
/// @param new_data_set_pointer Pointer to a data set object.

NormalizedSquaredError::NormalizedSquaredError(DataSet* new_data_set_pointer) 
: PerformanceTerm(new_data_set_pointer)
{
}


// NEURAL NETWORK AND DATA SET CONSTRUCTOR

/// Neural network and data set constructor. 
/// It creates a normalized squared error performance term associated to a neural network and measured on a data set.
/// It also initializes all the rest of class members to their default values.
/// @param new_neural_network_pointer Pointer to a neural network object.
/// @param new_data_set_pointer Pointer to a data set object.

NormalizedSquaredError::NormalizedSquaredError(NeuralNetwork* new_neural_network_pointer, DataSet* new_data_set_pointer)
: PerformanceTerm(new_neural_network_pointer, new_data_set_pointer)
{
}


// XML CONSTRUCTOR

/// XML constructor. 
/// It creates a normalized squared error not associated to any neural network and not measured on any data set.
/// It also sets all the rest of class members from a TinyXML document->
/// @param normalized_squared_error_document XML document with the class members. 

NormalizedSquaredError::NormalizedSquaredError(const tinyxml2::XMLDocument& normalized_squared_error_document)
 : PerformanceTerm(normalized_squared_error_document)
{
}


// DESTRUCTOR

/// Destructor.

NormalizedSquaredError::~NormalizedSquaredError(void)
{
}


// METHODS

// double calculate_training_normalization_coefficient(const Matrix<double>&, const Vector<double>&) const method

/// Returns the normalization coefficient to be used for the performance of the error. 
/// This is measured on the training instances of the data set. 

double NormalizedSquaredError::calculate_normalization_coefficient(const Matrix<double>& target_data, const Vector<double>& target_data_mean) const
{
    std::cout << "Target data:\n" << target_data << std::endl;
    std::cout << "Target data mean:\n" << target_data_mean << std::endl;
    std::cout << "Coeff:\n" << target_data.calculate_sum_squared_error(target_data_mean) << std::endl;


   return(target_data.calculate_sum_squared_error(target_data_mean));
}


// void check(void) const method

/// Checks that there are a neural network and a data set associated to the normalized squared error, 
/// and that the numbers of inputs and outputs in the neural network are equal to the numbers of inputs and targets in the data set. 
/// If some of the above conditions is not hold, the method throws an exception. 

void NormalizedSquaredError::check(void) const
{
   std::ostringstream buffer;

   // Neural network stuff

   if(!neural_network_pointer)
   {
      buffer << "OpenNN Exception: NormalizedquaredError class.\n"
             << "void check(void) const method.\n"
             << "Pointer to neural network is NULL.\n";

      throw std::logic_error(buffer.str());	  
   }

   const MultilayerPerceptron* multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

   if(!multilayer_perceptron_pointer)
   {
      buffer << "OpenNN Exception: NormalizedquaredError class.\n"
             << "void check(void) const method.\n"
             << "Pointer to multilayer perceptron is NULL.\n";

      throw std::logic_error(buffer.str());	  
   }

   const size_t multilayer_perceptron_inputs_number = multilayer_perceptron_pointer->get_inputs_number();
   const size_t multilayer_perceptron_outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   if(multilayer_perceptron_inputs_number == 0)
   {
      buffer << "OpenNN Exception: NormalizedquaredError class.\n"
             << "void check(void) const method.\n"
             << "Number of inputs in multilayer perceptron object is zero.\n";

      throw std::logic_error(buffer.str());	  
   }

   if(multilayer_perceptron_outputs_number == 0)
   {
      buffer << "OpenNN Exception: NormalizedquaredError class.\n"
             << "void check(void) const method.\n"
             << "Number of outputs in multilayer perceptron object is zero.\n";

      throw std::logic_error(buffer.str());	  
   }

   // Data set stuff

   if(!data_set_pointer)
   {
      buffer << "OpenNN Exception: NormalizedquaredError class.\n"
             << "void check(void) const method.\n"
             << "Pointer to data set is NULL.\n";

      throw std::logic_error(buffer.str());	  
   }

   // Sum squared error stuff

   const Variables& variables = data_set_pointer->get_variables();

   const size_t data_set_inputs_number = variables.count_inputs_number();
   const size_t data_set_targets_number = variables.count_targets_number();

   if(multilayer_perceptron_inputs_number != data_set_inputs_number)
   {
      buffer << "OpenNN Exception: NormalizedquaredError class.\n"
             << "void check(void) const method.\n"
             << "Number of inputs in multilayer perceptron (" << multilayer_perceptron_inputs_number << ") must be equal to number of inputs in data set (" << data_set_inputs_number << ").\n";

      throw std::logic_error(buffer.str());	  
   }

   if(multilayer_perceptron_outputs_number != data_set_targets_number)
   {
      buffer << "OpenNN Exception: NormalizedquaredError class.\n"
             << "void check(void) const method.\n"
             << "Number of outputs in multilayer perceptron (" << multilayer_perceptron_outputs_number << ") must be equal to number of targets in data set (" << data_set_targets_number << ").\n";

      throw std::logic_error(buffer.str());
   }
}


// double calculate_performance(void) const method

/// Returns the performance value of a neural network according to the normalized squared error on a data set.

double NormalizedSquaredError::calculate_performance(void) const
{
   // Control sentence

   #ifdef __OPENNN_DEBUG__ 

   check();

   #endif

   // Neural network stuff

   const MultilayerPerceptron* multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

   const size_t inputs_number = multilayer_perceptron_pointer->get_inputs_number();
   const size_t outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   // Data set stuff


   const Instances& instances = data_set_pointer->get_instances();

   const size_t training_instances_number = instances.count_training_instances_number();

   const Vector<size_t> training_indices = instances.arrange_training_indices();

   size_t training_index;

   const Variables& variables = data_set_pointer->get_variables();

   const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();
   const Vector<size_t> targets_indices = variables.arrange_targets_indices();

   const MissingValues& missing_values = data_set_pointer->get_missing_values();

   const Vector<size_t> missing_instances = missing_values.arrange_missing_instances();

   const Vector<double> training_target_data_mean = data_set_pointer->calculate_training_target_data_mean();

   // Normalized squared error stuff 

   Vector<double> inputs(inputs_number);
   Vector<double> outputs(outputs_number);
   Vector<double> targets(outputs_number);

   int i = 0;

   double sum_squared_error = 0.0;
   double normalization_coefficient = 0.0;

   #pragma omp parallel for private(i, training_index, inputs, outputs, targets) reduction(+ : sum_squared_error, normalization_coefficient)

   for(i = 0; i < (int)training_instances_number; i++)
   {
       training_index = training_indices[i];

      // Input vector

      inputs = data_set_pointer->get_instance(training_index, inputs_indices);

      // Output vector

      outputs = multilayer_perceptron_pointer->calculate_outputs(inputs);

      // Target vector

      targets = data_set_pointer->get_instance(training_index, targets_indices);

      // Sum squared error

      sum_squared_error += outputs.calculate_sum_squared_error(targets);

	  // Normalization coefficient

	  normalization_coefficient += targets.calculate_sum_squared_error(training_target_data_mean);
   }

   if(normalization_coefficient < 1.0e-99)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: NormalizedSquaredError class.\n"
		     << "double calculate_performance(void) const method.\n"
             << "Normalization coefficient is zero.\n"
             << "Unuse constant target variables or choose another error functional. ";

      throw std::logic_error(buffer.str());
   }

   return(sum_squared_error/normalization_coefficient);
}


// double calculate_performance(const Vector<double>&) const method

/// Returns which would be the performance of a multilayer perceptron for an hypothetical vector of parameters.
/// It does not set that vector of parameters to the multilayer perceptron. 
/// @param parameters Vector of potential parameters for the multilayer perceptron associated to the performance functional.

double NormalizedSquaredError::calculate_performance(const Vector<double>& parameters) const 
{
   // Control sentence (if debug)

   #ifdef __OPENNN_DEBUG__ 

   check();

   #endif

   #ifdef __OPENNN_DEBUG__ 

   std::ostringstream buffer;

   const size_t size = parameters.size();

   const size_t parameters_number = neural_network_pointer->count_parameters_number();

   if(size != parameters_number)
   {
      buffer << "OpenNN Exception: NormalizedSquaredError class.\n"
             << "double calculate_performance(const Vector<double>&) method.\n"
             << "Size (" << size << ") must be equal to number of parameters (" << parameters_number << ").\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   // Neural network stuff

   const MultilayerPerceptron* multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

   const size_t inputs_number = multilayer_perceptron_pointer->get_inputs_number();
   const size_t outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   // Data set stuff

   const Instances& instances = data_set_pointer->get_instances();

   const size_t training_instances_number = instances.count_training_instances_number();

   const Vector<size_t> training_indices = instances.arrange_training_indices();

   size_t training_index;

   const Variables& variables = data_set_pointer->get_variables();

   const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();
   const Vector<size_t> targets_indices = variables.arrange_targets_indices();

   const Vector<double> training_target_data_mean = data_set_pointer->calculate_training_target_data_mean();

   // Normalized squared error stuff

   Vector<double> inputs(inputs_number);
   Vector<double> outputs(outputs_number);
   Vector<double> targets(outputs_number);

   double sum_squared_error = 0.0;
   double normalization_coefficient = 0.0;

   int i = 0;

   #pragma omp parallel for private(i, training_index, inputs, outputs, targets) reduction(+ : sum_squared_error, normalization_coefficient)

   for(i = 0; i < (int)training_instances_number; i++)
   {
       training_index = training_indices[i];

      // Input vector

      inputs = data_set_pointer->get_instance(training_index, inputs_indices);

      // Output vector

      outputs = multilayer_perceptron_pointer->calculate_outputs(inputs, parameters);

      // Target vector

      targets = data_set_pointer->get_instance(training_index, targets_indices);

      // Sum squared error

      sum_squared_error += outputs.calculate_sum_squared_error(targets);

      // Normalization coefficient

      normalization_coefficient += targets.calculate_sum_squared_error(training_target_data_mean);
   }

   if(normalization_coefficient < 1.0e-99)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: NormalizedSquaredError class.\n"
             << "double calculate_performance(const Vector<double>&) const method.\n"
             << "Normalization coefficient is zero.\n"
             << "Unuse constant target variables or choose another error functional. ";

      throw std::logic_error(buffer.str());
   }

   return(sum_squared_error/normalization_coefficient);
}


// double calculate_selection_performance(void) const method

double NormalizedSquaredError::calculate_selection_performance(void) const
{
   // Control sentence

   #ifdef __OPENNN_DEBUG__ 

   check();

   #endif

   // Neural network stuff

   const MultilayerPerceptron* multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

   const size_t inputs_number = multilayer_perceptron_pointer->get_inputs_number();
   const size_t outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   // Data set stuff

   const Instances& instances = data_set_pointer->get_instances();

   const size_t selection_instances_number = instances.count_selection_instances_number();

   if(selection_instances_number < 2)
   {
      return(0.0);
   }
   
   const Vector<size_t> selection_indices = instances.arrange_selection_indices();

   size_t selection_index;

   const Variables& variables = data_set_pointer->get_variables();

   const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();
   const Vector<size_t> targets_indices = variables.arrange_targets_indices();

   const Vector<double> selection_target_data_mean = data_set_pointer->calculate_selection_target_data_mean();

   Vector<double> inputs(inputs_number);
   Vector<double> outputs(outputs_number);
   Vector<double> targets(outputs_number);

   double sum_squared_error = 0.0;
   double normalization_coefficient = 0.0;

   int i = 0;

   #pragma omp parallel for private(i, selection_index, inputs, outputs, targets) reduction(+ : sum_squared_error, normalization_coefficient)

   for(i = 0; i < (int)selection_instances_number; i++)
   {
       selection_index = selection_indices[i];

      // Input vector

      inputs = data_set_pointer->get_instance(selection_index, inputs_indices);

      // Output vector

      outputs = multilayer_perceptron_pointer->calculate_outputs(inputs);

      // Target vector

      targets = data_set_pointer->get_instance(selection_index, targets_indices);

      // Sum squared error

	  sum_squared_error += outputs.calculate_sum_squared_error(targets);

	  // Normalization coefficient

	  normalization_coefficient += targets.calculate_sum_squared_error(selection_target_data_mean);
   }

   if(normalization_coefficient < 1.0e-99)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: NormalizedSquaredError class.\n"
		     << "double calculate_selection_performance(void) const method.\n"
             << "Normalization coefficient is zero.\n"
             << "Unuse constant target variables or choose another error functional. ";

      throw std::logic_error(buffer.str());
   }

   return(sum_squared_error/normalization_coefficient);
}


// Vector<double> calculate_gradient(void) const method

/// Returns the normalized squared error function gradient of a multilayer perceptron on a data set. 
/// It uses the error back-propagation method.

Vector<double> NormalizedSquaredError::calculate_gradient(void) const
{
   // Control sentence (if debug)

   #ifdef __OPENNN_DEBUG__ 

   check();

   #endif

   // Neural network stuff

   const size_t parameters_number = neural_network_pointer->count_parameters_number();

   const MultilayerPerceptron* multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

   const size_t inputs_number = multilayer_perceptron_pointer->get_inputs_number();
   const size_t outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   const size_t layers_number = multilayer_perceptron_pointer->get_layers_number();

   Vector< Vector< Vector<double> > > first_order_forward_propagation(2); 

   Vector< Vector<double> > layers_inputs(layers_number); 

   Vector< Matrix<double> > layers_combination_parameters_Jacobian; 

   const bool has_conditions_layer = neural_network_pointer->has_conditions_layer();

   const ConditionsLayer* conditions_layer_pointer = has_conditions_layer ? neural_network_pointer->get_conditions_layer_pointer() : NULL;

   Vector<double> particular_solution;
   Vector<double> homogeneous_solution;

   // Data set stuff

   const Instances& instances = data_set_pointer->get_instances();

   const size_t training_instances_number = instances.count_training_instances_number();

   const Vector<size_t> training_indices = instances.arrange_training_indices();

   size_t training_index;

   const Variables& variables = data_set_pointer->get_variables();

   const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();
   const Vector<size_t> targets_indices = variables.arrange_targets_indices();

   const Vector<double> training_target_data_mean = data_set_pointer->calculate_training_target_data_mean();

   Vector<double> inputs(inputs_number);
   Vector<double> targets(outputs_number);

   // Normalized squared error stuff

   Vector<double> output_gradient(outputs_number);

   Vector< Vector<double> > layers_delta; 

   Vector<double> point_gradient(parameters_number, 0.0);

   double normalization_coefficient = 0.0;

   // Main loop

   Vector<double> gradient(parameters_number, 0.0);

   int i = 0;

   #pragma omp parallel for private(i, training_index, inputs, targets, first_order_forward_propagation, layers_inputs, layers_combination_parameters_Jacobian,\
    output_gradient, layers_delta, particular_solution, homogeneous_solution, point_gradient) \
    reduction(+ : normalization_coefficient)

   for(i = 0; i < (int)training_instances_number; i++)
   {
       training_index = training_indices[i];

      // Data set

      inputs = data_set_pointer->get_instance(training_index, inputs_indices);

      targets = data_set_pointer->get_instance(training_index, targets_indices);

	  // Multilayer perceptron

      first_order_forward_propagation = multilayer_perceptron_pointer->calculate_first_order_forward_propagation(inputs);

      const Vector< Vector<double> >& layers_activation = first_order_forward_propagation[0];
      const Vector< Vector<double> >& layers_activation_derivative = first_order_forward_propagation[1];

      layers_inputs = multilayer_perceptron_pointer->arrange_layers_input(inputs, layers_activation);   

	  layers_combination_parameters_Jacobian = multilayer_perceptron_pointer->calculate_layers_combination_parameters_Jacobian(layers_inputs);

	  // Performance functional

      if(!has_conditions_layer)
      {
         output_gradient = (layers_activation[layers_number-1]-targets)*2.0;

         layers_delta = calculate_layers_delta(layers_activation_derivative, output_gradient);
      }
      else
      {
         particular_solution = conditions_layer_pointer->calculate_particular_solution(inputs);
         homogeneous_solution = conditions_layer_pointer->calculate_homogeneous_solution(inputs);

         output_gradient = (particular_solution+homogeneous_solution*layers_activation[layers_number-1] - targets)*2.0;

         layers_delta = calculate_layers_delta(layers_activation_derivative, homogeneous_solution, output_gradient);
      }

      point_gradient = calculate_point_gradient(layers_combination_parameters_Jacobian, layers_delta);

      #pragma omp critical

      gradient += point_gradient;

      normalization_coefficient += targets.calculate_sum_squared_error(training_target_data_mean);
   }

   if(normalization_coefficient < 1.0e-99)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: NormalizedSquaredError class.\n"
             << "Vector<double> calculate_gradient(void) const method.\n"
             << "Normalization coefficient is zero.\n"
             << "Unuse constant target variables or choose another error functional. ";

      throw std::logic_error(buffer.str());
   }

   return(gradient/normalization_coefficient);
}
	

// Matrix<double> calculate_Hessian(void) const method

/// Returns the normalized squared error function Hessian of a multilayer perceptron on a data set. 
/// It uses the error back-propagation method.
/// @todo

Matrix<double> NormalizedSquaredError::calculate_Hessian(void) const
{
   Matrix<double> Hessian;

   return(Hessian);
}


// Vector<double> calculate_terms(void) const method

/// Returns performance vector of the performance terms function for the normalized squared error.
/// It uses the error back-propagation method.

Vector<double> NormalizedSquaredError::calculate_terms(void) const
{
   // Control sentence (if debug)

   #ifdef __OPENNN_DEBUG__ 

   check();

   #endif

   // Neural network stuff

   const MultilayerPerceptron* multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

   const size_t inputs_number = multilayer_perceptron_pointer->get_inputs_number();
   const size_t outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   // Data set stuff

   const Instances& instances = data_set_pointer->get_instances();

   const size_t training_instances_number = instances.count_training_instances_number();

   const Vector<size_t> training_indices = instances.arrange_training_indices();

   size_t training_index;

   const Variables& variables = data_set_pointer->get_variables();

   const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();
   const Vector<size_t> targets_indices = variables.arrange_targets_indices();

   const Vector<double> training_target_data_mean = data_set_pointer->calculate_training_target_data_mean();

   // Calculate

   Vector<double> performance_terms(training_instances_number);

   Vector<double> inputs(inputs_number);
   Vector<double> outputs(outputs_number);
   Vector<double> targets(outputs_number);

   double normalization_coefficient = 0.0;

   int i = 0;

   #pragma omp parallel for private(i, training_index, inputs, outputs, targets) reduction(+ : normalization_coefficient)

   for(i = 0; i < (int)training_instances_number; i++)
   {
       training_index = training_indices[i];

       // Input vector

      inputs = data_set_pointer->get_instance(training_index, inputs_indices);

      // Output vector

      outputs = multilayer_perceptron_pointer->calculate_outputs(inputs);

      // Target vector

      targets = data_set_pointer->get_instance(training_index, targets_indices);

      // Sum squared error

	  performance_terms[i] = outputs.calculate_distance(targets);

	  // Normalization coefficient

	  normalization_coefficient += targets.calculate_sum_squared_error(training_target_data_mean);
   }

   if(normalization_coefficient < 1.0e-99)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: NormalizedSquaredError class.\n"
             << "Vector<double> calculate_terms(void) const method.\n"
             << "Normalization coefficient is zero.\n"
             << "Unuse constant target variables or choose another error functional. ";

      throw std::logic_error(buffer.str());
   }

   return(performance_terms/sqrt(normalization_coefficient));
}


// Vector<double> calculate_terms(const Vector<double>&) const method

/// Returns which would be the performance terms performance vector of a multilayer perceptron for an hypothetical vector of multilayer perceptron parameters.
/// It does not set that vector of parameters to the multilayer perceptron. 
/// @param network_parameters Vector of a potential multilayer_perceptron_pointer parameters for the multilayer perceptron associated to the performance functional.

Vector<double> NormalizedSquaredError::calculate_terms(const Vector<double>& network_parameters) const
{
   // Control sentence (if debug)

   #ifdef __OPENNN_DEBUG__ 

   check();

   #endif


   #ifdef __OPENNN_DEBUG__ 

   const size_t size = network_parameters.size();

   const MultilayerPerceptron* multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

   const size_t neural_parameters_number = multilayer_perceptron_pointer->count_parameters_number();

   if(size != neural_parameters_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: NormalizedSquaredError class.\n"
             << "double calculate_terms(const Vector<double>&) const method.\n"
             << "Size (" << size << ") must be equal to number of multilayer perceptron parameters (" << neural_parameters_number << ").\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   NeuralNetwork neural_network_copy(*neural_network_pointer);

   neural_network_copy.set_parameters(network_parameters);

   NormalizedSquaredError normalized_squared_error_copy(*this);

   normalized_squared_error_copy.set_neural_network_pointer(&neural_network_copy);

   return(normalized_squared_error_copy.calculate_terms());
}


// Matrix<double> calculate_terms_Jacobian(void) const method

/// Returns the terms_Jacobian matrix of the sum squared error function, whose elements are given by the 
/// derivatives of the squared errors data set with respect to the multilayer perceptron parameters.
/// The terms_Jacobian matrix here is computed using a back-propagation algorithm.

Matrix<double> NormalizedSquaredError::calculate_terms_Jacobian(void) const
{
   // Control sentence

   #ifdef __OPENNN_DEBUG__ 

   check();

   #endif

   // Neural network stuff

   const MultilayerPerceptron* multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

   const size_t inputs_number = multilayer_perceptron_pointer->get_inputs_number();
   const size_t outputs_number = multilayer_perceptron_pointer->get_outputs_number();
   const size_t layers_number = multilayer_perceptron_pointer->get_layers_number();

   const size_t parameters_number = multilayer_perceptron_pointer->count_parameters_number();

   Vector< Vector< Vector<double> > > first_order_forward_propagation(2);

   Vector< Matrix<double> > layers_combination_parameters_Jacobian; 

   Vector< Vector<double> > layers_inputs(layers_number); 

   Vector<double> particular_solution;
   Vector<double> homogeneous_solution;

   const bool has_conditions_layer = neural_network_pointer->has_conditions_layer();

   const ConditionsLayer* conditions_layer_pointer = has_conditions_layer ? neural_network_pointer->get_conditions_layer_pointer() : NULL;

   // Data set stuff

   const Instances& instances = data_set_pointer->get_instances();

   const size_t training_instances_number = instances.count_training_instances_number();

   const Vector<size_t> training_indices = instances.arrange_training_indices();

   size_t training_index;

   const Variables& variables = data_set_pointer->get_variables();

   const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();
   const Vector<size_t> targets_indices = variables.arrange_targets_indices();

   const Vector<double> training_target_data_mean = data_set_pointer->calculate_training_target_data_mean();

   Vector<double> inputs(inputs_number);
   Vector<double> targets(outputs_number);

   // Normalized squared error

   Vector<double> term(outputs_number);
   double term_norm;

   Vector<double> output_gradient(outputs_number);

   Vector< Vector<double> > layers_delta(layers_number);
   Vector<double> point_gradient(parameters_number);

   Matrix<double> terms_Jacobian(training_instances_number, parameters_number);

   double normalization_coefficient = 0.0;

   // Main loop

   int i = 0;

   #pragma omp parallel for private(i, training_index, inputs, targets, first_order_forward_propagation, layers_inputs, \
    layers_combination_parameters_Jacobian, term, term_norm, output_gradient, layers_delta, particular_solution, homogeneous_solution, point_gradient)

   for(i = 0; i < (int)training_instances_number; i++)
   {
       training_index = training_indices[i];

       // Data set

      inputs = data_set_pointer->get_instance(training_index, inputs_indices);

      targets = data_set_pointer->get_instance(training_index, targets_indices);

	  // Neural network

      first_order_forward_propagation = multilayer_perceptron_pointer->calculate_first_order_forward_propagation(inputs);

      const Vector< Vector<double> >& layers_activation = first_order_forward_propagation[0];
      const Vector< Vector<double> >& layers_activation_derivative = first_order_forward_propagation[1];

      layers_inputs = multilayer_perceptron_pointer->arrange_layers_input(inputs, layers_activation);

	  layers_combination_parameters_Jacobian = multilayer_perceptron_pointer->calculate_layers_combination_parameters_Jacobian(layers_inputs);
	  
	  // Performance functional

      if(!has_conditions_layer) // No conditions
      {
         const Vector<double>& outputs = layers_activation[layers_number-1]; 

         term = outputs-targets;
         term_norm = term.calculate_norm();

         if(term_norm == 0.0)
   	     {
            output_gradient.initialize(0.0);
	     }
         else
	     {
            output_gradient = term/term_norm;
	     }

         layers_delta = calculate_layers_delta(layers_activation_derivative, output_gradient);
      }
      else // Conditions
      {        
         particular_solution = conditions_layer_pointer->calculate_particular_solution(inputs);
         homogeneous_solution = conditions_layer_pointer->calculate_homogeneous_solution(inputs);

         const Vector<double>& output_layer_activation = layers_activation[layers_number-1]; 

         term = (particular_solution+homogeneous_solution*output_layer_activation - targets);              
         term_norm = term.calculate_norm();

         if(term_norm == 0.0)
   	     {
            output_gradient.initialize(0.0);
	     }
	     else
	     {
            output_gradient = term/term_norm;
	     }

         layers_delta = calculate_layers_delta(layers_activation_derivative, homogeneous_solution, output_gradient);
	  }

	  normalization_coefficient += targets.calculate_sum_squared_error(training_target_data_mean);

      point_gradient = calculate_point_gradient(layers_combination_parameters_Jacobian, layers_delta);

      terms_Jacobian.set_row(i, point_gradient);

  }

   if(normalization_coefficient < 1.0e-99)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: NormalizedSquaredError class.\n"
             << "Matrix<double> calculate_terms_Jacobian(void) const method.\n"
             << "Normalization coefficient is zero.\n"
             << "Unuse constant target variables or choose another error functional. ";

      throw std::logic_error(buffer.str());
   }

   return(terms_Jacobian/sqrt(normalization_coefficient));
}


// FirstOrderTerms calculate_first_order_terms(void) const method

/// Returns a first order performance terms performance structure, which contains the values and the Jacobian of the performance terms function.
/// @todo

NormalizedSquaredError::FirstOrderTerms NormalizedSquaredError::calculate_first_order_terms(void) const
{
   FirstOrderTerms first_order_terms;

   first_order_terms.terms = calculate_terms();

   first_order_terms.Jacobian = calculate_terms_Jacobian();

   return(first_order_terms);
}


// Vector<double> calculate_squared_errors(void) const method

/// Returns the squared errors of the training instances. 

Vector<double> NormalizedSquaredError::calculate_squared_errors(void) const
{
   // Control sentence (if debug)

   #ifdef __OPENNN_DEBUG__ 

   check();

   #endif

   // Neural network stuff

   const MultilayerPerceptron* multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

   const size_t inputs_number = multilayer_perceptron_pointer->get_inputs_number();
   const size_t outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   // Data set stuff

   const Instances& instances = data_set_pointer->get_instances();

   const size_t training_instances_number = instances.count_training_instances_number();

   const Vector<size_t> training_indices = instances.arrange_training_indices();

   size_t training_index;

   const Variables& variables = data_set_pointer->get_variables();

   const Vector<size_t> inputs_indices = variables.arrange_inputs_indices();
   const Vector<size_t> targets_indices = variables.arrange_targets_indices();

   // Calculate

   Vector<double> squared_errors(training_instances_number);

   Vector<double> inputs(inputs_number);
   Vector<double> outputs(outputs_number);
   Vector<double> targets(outputs_number);

   // Main loop

   int i = 0;

   #pragma omp parallel for private(i, training_index, inputs, outputs, targets)

   for(i = 0; i < (int)training_instances_number; i++)
   {
       training_index = training_indices[i];

       // Input vector

      inputs = data_set_pointer->get_instance(training_index, inputs_indices);

      // Output vector

      outputs = multilayer_perceptron_pointer->calculate_outputs(inputs);

      // Target vector

      targets = data_set_pointer->get_instance(training_index, targets_indices);

      // Error

      squared_errors[i] = outputs.calculate_sum_squared_error(targets);
   }

   return(squared_errors);
}


// Vector<size_t> calculate_maximal_errors(void) const method

/// Returns a vector with the indices of the instances which have the maximum error.
/// @param maximal_errors_number Number of instances required.

Vector<size_t> NormalizedSquaredError::calculate_maximal_errors(const size_t& maximal_errors_number) const
{
    // Control sentence (if debug)

    #ifdef __OPENNN_DEBUG__

    check();

    const Instances& instances = data_set_pointer->get_instances();

    const size_t training_instances_number = instances.count_training_instances_number();

    if(maximal_errors_number > training_instances_number)
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: NormalizedquaredError class.\n"
               << "Vector<size_t> calculate_maximal_errors(void) const method.\n"
               << "Number of maximal errors (" << maximal_errors_number << ") must be equal or less than number of training instances (" << training_instances_number << ").\n";

       throw std::logic_error(buffer.str());
    }

    #endif

    return(calculate_squared_errors().calculate_maximal_indices(maximal_errors_number));
}


// std::string write_performance_term_type(void) const method

/// Returns a string with the name of the normalized squared error performance type, "NORMALIZED_SQUARED_ERROR".

std::string NormalizedSquaredError::write_performance_term_type(void) const
{
   return("NORMALIZED_SQUARED_ERROR");
}


// tinyxml2::XMLDocument* to_XML(void) const method 

/// Serializes the normalized squared error object into a XML document of the TinyXML library. 
/// See the OpenNN manual for more information about the format of this element. 

tinyxml2::XMLDocument* NormalizedSquaredError::to_XML(void) const
{
   std::ostringstream buffer;

   tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument;

   // Normalized squared error

   tinyxml2::XMLElement* normalized_squared_error_element = document->NewElement("NormalizedSquaredError");

   document->InsertFirstChild(normalized_squared_error_element);

   // Display
   {
      tinyxml2::XMLElement* display_element = document->NewElement("Display");
      normalized_squared_error_element->LinkEndChild(display_element);

      buffer.str("");
      buffer << display;

      tinyxml2::XMLText* display_text = document->NewText(buffer.str().c_str());
      display_element->LinkEndChild(display_text);
   }

   return(document);
}


// void from_XML(const tinyxml2::XMLDocument&) method

/// Loads a root mean squared error object from a XML document. 
/// @param document Pointer to a TinyXML document with the object data.

void NormalizedSquaredError::from_XML(const tinyxml2::XMLDocument& document)
{
   const tinyxml2::XMLElement* root_element = document.FirstChildElement("NormalizedSquaredError");

   if(!root_element)
   {
      return;
   }

   const tinyxml2::XMLElement* display_element = root_element->FirstChildElement("Display");

   if(display_element)
   {
      const std::string new_display_string = display_element->GetText();     

      try
      {
         set_display(new_display_string != "0");
      }
      catch(const std::logic_error& e)
      {
         std::cout << e.what() << std::endl;		 
      }
   }
}


// std::string write_information(void) const method

std::string NormalizedSquaredError::write_information(void) const
{
    std::ostringstream buffer;

    buffer << "Normalized squared error: " << calculate_performance() << "\n";

    return(buffer.str());

}

}

// OpenNN: Open Neural Networks Library.
// Copyright (c) 2005-2016 Roberto Lopez.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
