/* file: tanh.h */
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
//  Implementation of the interface for the hyperbolic tangent function
//--
*/

#ifndef __TANH_H__
#define __TANH_H__

#include "algorithms/algorithm.h"
#include "data_management/data/numeric_table.h"
#include "services/daal_defines.h"
#include "algorithms/math/tanh_types.h"

namespace daal
{
namespace algorithms
{
namespace math
{
namespace tanh
{
namespace interface1
{
/**
 * @defgroup tanh_batch Batch
 * @ingroup tanh
 * @{
 */
/**
 * <a name="DAAL-CLASS-ALGORITHMS__MATH__TANH__BATCHCONTAINER"></a>
 * \brief Class containing methods for the hyperbolic tangent function computing using algorithmFPType precision arithmetic
 */
template<typename algorithmFPType, Method method, CpuType cpu>
class DAAL_EXPORT BatchContainer : public daal::algorithms::AnalysisContainerIface<batch>
{
public:
    /**
     * Constructs a container for the hyperbolic tangent function with a specified environment
     * in the batch processing mode
     * \param[in] daalEnv   Environment object
     */
    BatchContainer(daal::services::Environment::env *daalEnv);
    /** Default destructor */
    ~BatchContainer();
    /**
     * Computes the result of the hyperbolic tangent function in the batch processing mode
     *
     * \return Status of computation
     */
    virtual services::Status compute() DAAL_C11_OVERRIDE;
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__MATH__TANH__BATCH"></a>
 * \brief Computes the hyperbolic tangent function in the batch processing mode.
 * <!-- \n<a href="DAAL-REF-TANH-ALGORITHM"> the hyperbolic tangent function description and usage models</a> -->
 *
 * \tparam algorithmFPType  Data type to use in intermediate computations for the hyperbolic tangent function,
 *                          double or float
 * \tparam method           The hyperbolic tangent function computation method
 *
 * \par Enumerations
 *      - \ref Method   Computation methods for the hyperbolic tangent function
 *      - \ref InputId  Identifiers of input objects for the hyperbolic tangent function
 *      - \ref ResultId %Result identifiers for the the hyperbolic tangent function
 */
template<typename algorithmFPType = DAAL_ALGORITHM_FP_TYPE, Method method = defaultDense>
class DAAL_EXPORT Batch : public daal::algorithms::Analysis<batch>
{
public:
    /** Default constructor */
    Batch()
    {
        initialize();
    }

    /**
     * Constructs the hyperbolic tangent function by copying input objects of another hyperbolic tangent function
     * \param[in] other function to be used as the source to initialize the input objects of the hyperbolic tangent function
     */
    Batch(const Batch<algorithmFPType, method> &other) : input(other.input)
    {
        initialize();
    }

    /**
     * Returns the method of the hyperbolic tangent function
     * \return Method of the hyperbolic tangent function
     */
    virtual int getMethod() const DAAL_C11_OVERRIDE { return(int) method; }

    /**
     * Returns the structure that contains the result of the hyperbolic tangent function
     * \return Structure that contains the result of the hyperbolic tangent function
     */
    ResultPtr getResult()
    {
        return _result;
    }

    /**
     * Registers user-allocated memory to store the result of the hyperbolic tangent function
     * \param[in] result  Structure to store the result of the hyperbolic tangent function
     *
     * \return Status of computation
     */
    services::Status setResult(const ResultPtr &result)
    {
        DAAL_CHECK(result, services::ErrorNullResult)
        _result = result;
        _res = _result.get();
        return services::Status();
    }

    Input input;                 /*!< %Input data structure */

    /**
     * Returns a pointer to a newly allocated hyperbolic tangent function
     * with a copy of the input objects of this hyperbolic tangent function
     * \return Pointer to the newly allocated hyperbolic tangent function
     */
    services::SharedPtr<Batch<algorithmFPType, method> > clone() const
    {
        return services::SharedPtr<Batch<algorithmFPType, method> >(cloneImpl());
    }

protected:
    virtual Batch<algorithmFPType, method> *cloneImpl() const DAAL_C11_OVERRIDE
    {
        return new Batch<algorithmFPType, method>(*this);
    }

    virtual services::Status allocateResult() DAAL_C11_OVERRIDE
    {
        _result.reset(new Result());
        services::Status s = _result->allocate<algorithmFPType>(&input, NULL, (int) method);
        _res = _result.get();
        return s;
    }

    void initialize()
    {
        Analysis<batch>::_ac = new __DAAL_ALGORITHM_CONTAINER(batch, BatchContainer, algorithmFPType, method)(&_env);
        _in  = &input;
    }
private:
    ResultPtr _result;
};
/** @} */
} // namespace interface1
using interface1::BatchContainer;
using interface1::Batch;

} // namespace tanh
} // namespace math
} // namespace algorithms
} // namespace daal
#endif
