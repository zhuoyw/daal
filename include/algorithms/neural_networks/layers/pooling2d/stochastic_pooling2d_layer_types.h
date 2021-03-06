/* file: stochastic_pooling2d_layer_types.h */
/*******************************************************************************
* Copyright 2014-2017 Intel Corporation
* All Rights Reserved.
*
* If this  software was obtained  under the  Intel Simplified  Software License,
* the following terms apply:
*
* The source code,  information  and material  ("Material") contained  herein is
* owned by Intel Corporation or its  suppliers or licensors,  and  title to such
* Material remains with Intel  Corporation or its  suppliers or  licensors.  The
* Material  contains  proprietary  information  of  Intel or  its suppliers  and
* licensors.  The Material is protected by  worldwide copyright  laws and treaty
* provisions.  No part  of  the  Material   may  be  used,  copied,  reproduced,
* modified, published,  uploaded, posted, transmitted,  distributed or disclosed
* in any way without Intel's prior express written permission.  No license under
* any patent,  copyright or other  intellectual property rights  in the Material
* is granted to  or  conferred  upon  you,  either   expressly,  by implication,
* inducement,  estoppel  or  otherwise.  Any  license   under such  intellectual
* property rights must be express and approved by Intel in writing.
*
* Unless otherwise agreed by Intel in writing,  you may not remove or alter this
* notice or  any  other  notice   embedded  in  Materials  by  Intel  or Intel's
* suppliers or licensors in any way.
*
*
* If this  software  was obtained  under the  Apache License,  Version  2.0 (the
* "License"), the following terms apply:
*
* You may  not use this  file except  in compliance  with  the License.  You may
* obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
*
*
* Unless  required  by   applicable  law  or  agreed  to  in  writing,  software
* distributed under the License  is distributed  on an  "AS IS"  BASIS,  WITHOUT
* WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
* See the   License  for the   specific  language   governing   permissions  and
* limitations under the License.
*******************************************************************************/

/*
//++
//  Implementation of stochastic 2D pooling layer.
//--
*/

#ifndef __STOCHASTIC_POOLING2D_LAYER_TYPES_H__
#define __STOCHASTIC_POOLING2D_LAYER_TYPES_H__

#include "algorithms/algorithm.h"
#include "data_management/data/tensor.h"
#include "data_management/data/homogen_tensor.h"
#include "services/daal_defines.h"
#include "algorithms/neural_networks/layers/pooling2d/pooling2d_layer_types.h"

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
/**
 * @defgroup stochastic_pooling2d Two-dimensional Stochastic Pooling Layer
 * \copydoc daal::algorithms::neural_networks::layers::stochastic_pooling2d
 * @ingroup pooling2d
 * @{
 */
namespace stochastic_pooling2d
{
/**
 * <a name="DAAL-ENUM-ALGORITHMS__NEURAL_NETWORKS__LAYERS__STOCHASTIC_POOLING2D__METHOD"></a>
 * \brief Computation methods for the stochastic 2D pooling layer
 */
enum Method
{
    defaultDense = 0    /*!< Default: performance-oriented method */
};

/**
 * \brief Identifiers of input tensors for the backward stochastic 2D pooling layer
 *        and results for the forward stochastic 2D pooling layer
 */
enum LayerDataId
{
    auxSelectedIndices,         /*!< p-dimensional tensor that stores the positions of stochastic elements */
    lastLayerDataId = auxSelectedIndices
};

/**
 * \brief Identifiers of input numeric tables for the backward stochastic 2D pooling layer
 *        and results for the forward stochastic 2D pooling layer
 */
enum LayerDataNumericTableId
{
    auxInputDimensions  = lastLayerDataId + 1,         /*!< Numeric table of size 1 x p that contains the sizes
                                          of the dimensions of the input data tensor */
    lastLayerDataNumericTableId = auxInputDimensions
};

/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * <a name="DAAL-STRUCT-ALGORITHMS__NEURAL_NETWORKS__LAYERS__STOCHASTIC_POOLING2D__PARAMETER"></a>
 * \brief Parameters for the stochastic 2D pooling layer
 *
 * \snippet neural_networks/layers/pooling2d/stochastic_pooling2d_layer_types.h Parameter source code
 */
/* [Parameter source code] */
struct DAAL_EXPORT Parameter: public pooling2d::Parameter
{
    /**
     * Constructs the parameters of 2D pooling layer
     * \param[in] firstIndex        Index of the first of two dimensions on which the pooling is performed
     * \param[in] secondIndex       Index of the second of two dimensions on which the pooling is performed
     * \param[in] firstKernelSize   Size of the first dimension of 2D subtensor for which the stochastic element is selected
     * \param[in] secondKernelSize  Size of the second dimension of 2D subtensor for which the stochastic element is selected
     * \param[in] firstStride       Interval over the first dimension on which the pooling is performed
     * \param[in] secondStride      Interval over the second dimension on which the pooling is performed
     * \param[in] firstPadding      Number of data elements to implicitly add to the the first dimension
     *                              of the 2D subtensor on which the pooling is performed
     * \param[in] secondPadding     Number of data elements to implicitly add to the the second dimension
     *                              of the 2D subtensor on which the pooling is performed
     */
    Parameter(size_t firstIndex, size_t secondIndex, size_t firstKernelSize = 2, size_t secondKernelSize = 2,
              size_t firstStride = 2, size_t secondStride = 2, size_t firstPadding = 0, size_t secondPadding = 0);

    size_t seed;                /*!< Seed for multinomial distribution random number generator. \DAAL_DEPRECATED_USE{ engine } */
    engines::EnginePtr engine;  /*!< Engine for multinomial distribution random number generator. */
};
/* [Parameter source code] */

} // interface1
using interface1::Parameter;

} // namespace stochastic_pooling2d
/** @} */
} // namespace layers
} // namespace neural_networks
} // namespace algorithm
} // namespace daal

#endif
