/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.opennn.net                                                                                             */
/*                                                                                                              */
/*   M O D E L   S E L E C T I O N   C L A S S   H E A D E R                                                    */
/*                                                                                                              */
/*   Fernando Gomez                                                                                             */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   fernandogomez@artelnics.com                                                                                */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __MODELSELECTION_H__
#define __MODELSELECTION_H__

// System includes

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <ctime>

// OpenNN includes

#include "training_strategy.h"

#include "incremental_order.h"
#include "golden_section_order.h"
#include "simulated_annealing_order.h"

#include "growing_inputs.h"
#include "pruning_inputs.h"
#include "genetic_algorithm.h"

// TinyXml includes

#include "../tinyxml2/tinyxml2.h"

namespace OpenNN
{

/// This class represents the concept of model selection algorithm.
/// It is used for finding a network architecture with maximum selection capabilities. 

class ModelSelection
{

public:  

    // DEFAULT CONSTRUCTOR

    explicit ModelSelection(void);

    // TRAINING STRATEGY CONSTRUCTOR

    explicit ModelSelection(TrainingStrategy*);

    // FILE CONSTRUCTOR

    explicit ModelSelection(const std::string&);

    // XML CONSTRUCTOR

    explicit ModelSelection(const tinyxml2::XMLDocument&);


    // DESTRUCTOR

    virtual ~ModelSelection(void);

    /// Enumeration of all the available types of inputs selection algorithms.

    enum InputsSelectionType
    {
        NO_INPUTS_SELECTION,
        GROWING_INPUTS,
        PRUNING_INPUTS,
        GENETIC_ALGORITHM
    };

    /// Enumeration of all the available types of order selection algorithms.

    enum OrderSelectionType
    {
        NO_ORDER_SELECTION,
        INCREMENTAL_ORDER,
        GOLDEN_SECTION,
        SIMULATED_ANNEALING
    };


    // STRUCTURES

    ///
    /// This structure contains the results from the model selection process.
    ///

    struct ModelSelectionResults
    {

        void save(const std::string&) const;

        // Order selection results

        /// Pointer to a structure with the results from the incremental order selection algorithm.

        IncrementalOrder::IncrementalOrderResults* incremental_order_results_pointer;

        /// Pointer to a structure with the results from the golden section order selection algorithm.

        GoldenSectionOrder::GoldenSectionOrderResults* golden_section_order_results_pointer;

        /// Pointer to a structure with the results from the simulated annealing order selection algorithm.

        SimulatedAnnealingOrder::SimulatedAnnealingOrderResults* simulated_annealing_order_results_pointer;

        /// Pointer to a structure with the results from the growing inputs selection algorithm.

        GrowingInputs::GrowingInputsResults* growing_inputs_results_pointer;

        /// Pointer to a structure with the results from the pruning inputs selection algorithm.

        PruningInputs::PruningInputsResults* pruning_inputs_results_pointer;

        /// Pointer to a structure with the results from the genetic inputs selection algorithm.

        GeneticAlgorithm::GeneticAlgorithmResults* genetic_algorithm_results_pointer;

    };

    // METHODS

    // Get methods

    TrainingStrategy* get_training_strategy_pointer(void) const;
    bool has_training_strategy(void) const;

    const OrderSelectionType& get_order_selection_type(void) const;
    const InputsSelectionType& get_inputs_selection_type(void) const;

    IncrementalOrder* get_incremental_order_pointer(void) const;
    GoldenSectionOrder* get_golden_section_order_pointer(void) const;
    SimulatedAnnealingOrder* get_simulated_annealing_order_pointer(void) const;

    GrowingInputs* get_growing_inputs_pointer(void) const;
    PruningInputs* get_pruning_inputs_pointer(void) const;
    GeneticAlgorithm* get_genetic_algorithm_pointer(void) const;

    // Set methods

    void set_default(void);

    void set_training_strategy_pointer(TrainingStrategy*);

    void set_order_selection_type(const OrderSelectionType&);
    void set_order_selection_type(const std::string&);

    void set_inputs_selection_type(const InputsSelectionType&);
    void set_inputs_selection_type(const std::string&);

    void set_regression(const bool&);

    // Pointer methods

    void destruct_order_selection(void);

    void destruct_inputs_selection(void);

    // Model selection methods

    void check(void) const;

    ModelSelectionResults perform_order_selection(void) const;

    ModelSelectionResults perform_inputs_selection(void) const;

    ModelSelectionResults perform_model_selection(void) const;

    // Serialization methods

    tinyxml2::XMLDocument* to_XML(void) const;
    void from_XML(const tinyxml2::XMLDocument&);

    void print(void) const;
    void save(const std::string&) const;
    void load(const std::string&);

private: 

    // MEMBERS

    /// Pointer to a training strategy object.

    TrainingStrategy* training_strategy_pointer;

    /// Pointer to a incremental order object to be used in the order selection.

    IncrementalOrder* incremental_order_pointer;

    /// Pointer to a golden section order object to be used in the order selection.

    GoldenSectionOrder* golden_section_order_pointer;

    /// Pointer to a simulated annealing order object to be used in the order selection.

    SimulatedAnnealingOrder* simulated_annelaing_order_pointer;

    /// Pointer to a growing inputs object to be used in the inputs selection.

    GrowingInputs* growing_inputs_pointer;

    /// Pointer to a pruning inputs object to be used in the inputs selection.

    PruningInputs* pruning_inputs_pointer;

    /// Pointer to a genetic inputs object to be used in the inputs selection.

    GeneticAlgorithm* genetic_algorithm_pointer;

    /// Type of order selection algorithm.

    OrderSelectionType order_selection_type;

    /// Type of inputs selection algorithm.

    InputsSelectionType inputs_selection_type;
};

}

#endif
