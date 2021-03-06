/* file: trans_conv2d_layer_dense_batch.cpp */
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
!  Content:
!    C++ example of forward and backward two-dimensional transposed convolution layer usage
!
!******************************************************************************/

/**
 * <a name="DAAL-EXAMPLE-CPP-TRANSPOSEDCONVOLUTION2D_LAYER_BATCH"></a>
 * \example trans_conv2d_layer_dense_batch.cpp
 */

#include "daal.h"
#include "service.h"

using namespace std;
using namespace daal;
using namespace daal::algorithms;
using namespace daal::algorithms::neural_networks::layers;
using namespace daal::data_management;
using namespace daal::services;

/* Input data set name */
string datasetFileName = "../data/batch/layer.csv";

int main(int argc, char *argv[])
{
    checkArguments(argc, argv, 1, &datasetFileName);

    /* Create collection of dimension sizes of the input data tensor */
    Collection<size_t> inDims;
    inDims.push_back(1);
    inDims.push_back(2);
    inDims.push_back(4);
    inDims.push_back(4);
    TensorPtr tensorData = TensorPtr(new HomogenTensor<>(inDims, Tensor::doAllocate, 1.0f));

    /* Create an algorithm to compute forward two-dimensional transposed convolution layer results using default method */
    transposed_conv2d::forward::Batch<> transposedConv2dLayerForward;
    transposedConv2dLayerForward.input.set(forward::data, tensorData);


    /* Compute forward two-dimensional transposed convolution layer results */
    transposedConv2dLayerForward.compute();

    /* Get the computed forward two-dimensional transposed convolution layer results */
    transposed_conv2d::forward::ResultPtr forwardResult = transposedConv2dLayerForward.getResult();
    printTensor(forwardResult->get(forward::value), "Two-dimensional transposed convolution layer result (first 5 rows):", 5, 15);
    printTensor(forwardResult->get(transposed_conv2d::auxWeights), "Two-dimensional transposed convolution layer weights (first 5 rows):", 5, 15);


    const Collection<size_t> &gDims = forwardResult->get(forward::value)->getDimensions();
    /* Create input gradient tensor for backward two-dimensional transposed convolution layer */
    TensorPtr tensorDataBack = TensorPtr(new HomogenTensor<>(gDims, Tensor::doAllocate, 0.01f));

    /* Create an algorithm to compute backward two-dimensional transposed convolution layer results using default method */
    transposed_conv2d::backward::Batch<> transposedConv2dLayerBackward;
    transposedConv2dLayerBackward.input.set(backward::inputGradient, tensorDataBack);
    transposedConv2dLayerBackward.input.set(backward::inputFromForward, forwardResult->get(forward::resultForBackward));


    /* Compute backward two-dimensional transposed convolution layer results */
    transposedConv2dLayerBackward.compute();

    /* Get the computed backward two-dimensional transposed convolution layer results */
    backward::ResultPtr backwardResult = transposedConv2dLayerBackward.getResult();
    printTensor(backwardResult->get(backward::gradient),
                "Two-dimensional transposed convolution layer backpropagation gradient result (first 5 rows):", 5, 15);
    printTensor(backwardResult->get(backward::weightDerivatives),
                "Two-dimensional transposed convolution layer backpropagation weightDerivative result (first 5 rows):", 5, 15);
    printTensor(backwardResult->get(backward::biasDerivatives),
                "Two-dimensional transposed convolution layer backpropagation biasDerivative result (first 5 rows):", 5, 15);

    return 0;
}
