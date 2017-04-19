/* file: pooling2d_layer_backward.cpp */
/*******************************************************************************
* Copyright 2014-2016 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/*
//++
//  Implementation of pooling2d calculation algorithm and types methods.
//--
*/

#include "pooling2d_layer_backward_types.h"
#include "pooling2d_layer_types.h"

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
namespace pooling2d
{
namespace backward
{
namespace interface1
{
/** Default constructor */
Input::Input() {}

/**
 * Return the collection with gradient size
 * \return The collection with gradient size
 */
services::Collection<size_t> Input::getGradientSize() const
{
    services::Collection<size_t> dims;
    const data_management::NumericTablePtr inputDims = getAuxInputDimensions();
    if(!data_management::checkNumericTable(inputDims.get(), this->_errors.get(), auxInputDimensionsStr())) { return dims; }

    data_management::BlockDescriptor<int> block;
    inputDims->getBlockOfRows(0, 1, data_management::readOnly, block);
    int *inputDimsArray = block.getBlockPtr();
    for(size_t i = 0; i < inputDims->getNumberOfColumns(); i++)
    {
        dims.push_back((size_t) inputDimsArray[i]);
    }
    inputDims->releaseBlockOfRows(block);
    return dims;
}

services::Collection<size_t> Input::getInputGradientSize(const pooling2d::Parameter *parameter) const
{
    const Parameter *param = static_cast<const Parameter *>(parameter);
    services::Collection<size_t> inputDims = getGradientSize();

    for (size_t d = 0; d < 2; d++)
    {
        inputDims[param->indices.size[d]] = computeInputDimension(
            inputDims[param->indices.size[d]], param->kernelSizes.size[d], param->paddings.size[d], param->strides.size[d]);
    }
    return inputDims;
}

size_t Input::computeInputDimension(size_t maskDim, size_t kernelSize, size_t padding, size_t stride) const
{
    size_t inputDim = (maskDim + 2 * padding - kernelSize + stride) / stride;
    return inputDim;
}

/** Default constructor */
Result::Result() {}

/**
 * Checks the result of the backward 2D pooling layer
 * \param[in] input %Input object for the layer
 * \param[in] parameter %Parameter of the layer
 * \param[in] method Computation method
 */
void Result::check(const daal::algorithms::Input *input, const daal::algorithms::Parameter *parameter, int method) const
{
    const Parameter *param = static_cast<const Parameter *>(parameter);
    if (!param->propagateGradient) { return; }

    layers::backward::Result::check(input, parameter, method);
    if(this->_errors->size() > 0) { return; }

    const Input *algInput = static_cast<const Input *>(input);

    //get expected gradient dimensions
    services::Collection<size_t> gradientDims = algInput->getGradientSize();
    if (!data_management::checkTensor(get(layers::backward::gradient).get(), this->_errors.get(), gradientStr(), &gradientDims)) { return; }

    DAAL_CHECK_EX(param->strides.size[0] != 0 &&
                  param->strides.size[1] != 0, services::ErrorIncorrectParameter, services::ParameterName, stridesStr());

    size_t index0 = param->indices.size[0];
    size_t index1 = param->indices.size[1];
    DAAL_CHECK_EX(index0 <= gradientDims.size() - 1 && index1 <= gradientDims.size() - 1 &&
                  index0 != index1, services::ErrorIncorrectParameter, services::ParameterName, indicesStr());

    size_t kernelSize0 = param->kernelSizes.size[0];
    size_t kernelSize1 = param->kernelSizes.size[1];
    DAAL_CHECK_EX((kernelSize0 != 0 && kernelSize0 <= gradientDims[index0] + 2 * param->paddings.size[0] &&
                   kernelSize1 != 0 && kernelSize1 <= gradientDims[index1] + 2 * param->paddings.size[1]), services::ErrorIncorrectParameter, services::ParameterName,
                  kernelSizesStr());
}

}// namespace interface1
}// namespace backward
}// namespace pooling2d
}// namespace layers
}// namespace neural_networks
}// namespace algorithms
}// namespace daal