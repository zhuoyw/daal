/* file: TrainingPartialResult.java */
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
 * @ingroup multinomial_naive_bayes_training
 * @{
 */
package com.intel.daal.algorithms.multinomial_naive_bayes.training;

import com.intel.daal.algorithms.ComputeMode;
import com.intel.daal.algorithms.Precision;
import com.intel.daal.algorithms.classifier.training.PartialResultId;
import com.intel.daal.algorithms.multinomial_naive_bayes.PartialModel;
import com.intel.daal.services.DaalContext;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__MULTINOMIAL_NAIVE_BAYES__TRAINING__TRAININGPARTIALRESULT"></a>
 * @brief Provides methods to access results obtained with the compute() method of the
 *        naive Bayes training algorithm in the online or distributed processing mode
 */

public final class TrainingPartialResult extends com.intel.daal.algorithms.classifier.training.TrainingPartialResult {
    /** @private */
    static {
        System.loadLibrary("JavaAPI");
    }

    /**
     * Constructs the partial result of the naive Bayes training algorithm in the online or distributed processing mode
     * @param context   Context to manage the partial result of the naive Bayes training algorithm in the online or distributed processing mode
     */
    public TrainingPartialResult(DaalContext context) {
        super(context);
        cObject = cNewPartialResult();
    }

    public TrainingPartialResult(DaalContext context, long cObject) {
        super(context);
        this.cObject = cObject;
    }

    /**
     * Returns partial result of the naive Bayes training algorithm
     * @param id   Identifier of the result
     * @return     Result that corresponds to the given identifier
     */
    public PartialModel get(PartialResultId id) {
        if (id == PartialResultId.partialModel) {
            return new PartialModel(getContext(), cGetPartialModel(cObject, PartialResultId.partialModel.getValue()));
        } else {
            return null;
        }
    }

    private native long cNewPartialResult();

    private native long cGetPartialModel(long resAddr, int id);
}
/** @} */
