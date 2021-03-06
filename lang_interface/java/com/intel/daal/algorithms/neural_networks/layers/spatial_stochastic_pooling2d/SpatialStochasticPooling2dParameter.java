/* file: SpatialStochasticPooling2dParameter.java */
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

/**
 * @ingroup spatial_stochastic_pooling2d
 * @{
 */
package com.intel.daal.algorithms.neural_networks.layers.spatial_stochastic_pooling2d;

import com.intel.daal.services.DaalContext;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__SPATIAL_STOCHASTIC_POOLING2D__SPATIALSTOCHASTICPOOLING2DPARAMETER"></a>
 * \brief Class that specifies parameters of the two-dimensional spatial stochastic pooling layer
 */
public class SpatialStochasticPooling2dParameter extends com.intel.daal.algorithms.neural_networks.layers.spatial_pooling2d.SpatialPooling2dParameter {
    /** @private */
    public SpatialStochasticPooling2dParameter(DaalContext context, long cObject) {
        super(context, cObject);
    }

    /**
     * @DAAL_DEPRECATED
     *  Returns seed for multinomial distribution random number generator
     */
    public long getSeed() {
        return cGetSeed(cObject);
    }

    /**
     * @DAAL_DEPRECATED
     *  Sets the seed for multinomial distribution random number generator
     *  @param seed Seed for multinomial distribution random number generator
     */
    public void setSeed(long seed) {
        cSetSeed(cObject, seed);
    }

    /**
     * Sets the engine to be used by the algorithm
     * @param engine to be used by the algorithm
     */
    public void setEngine(com.intel.daal.algorithms.engines.BatchBase engine) {
        cSetEngine(cObject, engine.cObject);
    }

    /**
     *  Gets the flag that specifies whether the layer is used for the prediction stage or not
     */
    public boolean getPredictionStage() {
        return cGetPredictionStage(cObject);
    }

    /**
     *  Sets the flag that specifies whether the layer is used for the prediction stage or not
     *  @param predictionStage Flag that specifies whether the layer is used for the prediction stage or not
     */
    public void setPredictionStage(boolean predictionStage) {
        cSetPredictionStage(cObject, predictionStage);
    }

    private native long   cGetSeed(long cParameter);
    private native void   cSetSeed(long cParameter, long seed);
    private native void cSetEngine(long cObject, long cEngineObject);
    private native boolean cGetPredictionStage(long cParameter);
    private native void    cSetPredictionStage(long cParameter, boolean predictionStage);
}
/** @} */
