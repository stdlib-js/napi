/**
* @license Apache-2.0
*
* Copyright (c) 2024 The Stdlib Authors.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "stdlib/napi/create_complex_like.h"
#include "stdlib/napi/argv_complex128.h"
#include "stdlib/napi/argv.h"
#include "stdlib/complex/float64/ctor.h"
#include "stdlib/complex/float64/real.h"
#include "stdlib/complex/float64/imag.h"
#include <node_api.h>
#include <assert.h>

/**
* Identity function.
*
* @param v      input value
* @return       input value
*/
static stdlib_complex128_t identity( const stdlib_complex128_t v ) {
	return v;
}

/**
* Receives JavaScript callback invocation data.
*
* @param env    environment under which the function is invoked
* @param info   callback data
* @return       Node-API value
*/
static napi_value addon( napi_env env, napi_callback_info info ) {
	STDLIB_NAPI_ARGV( env, info, argv, argc, 1 )
	STDLIB_NAPI_ARGV_COMPLEX128( env, value, argv, 0 )

	stdlib_complex128_t out = identity( value );

	STDLIB_NAPI_CREATE_COMPLEX_LIKE( env, stdlib_complex128_real( out ), stdlib_complex128_imag( out ), v )
	return v;
}

/**
* Initializes a Node-API module.
*
* @param env      environment under which the function is invoked
* @param exports  exports object
* @return         main export
*/
static napi_value init( napi_env env, napi_value exports ) {
	napi_value fcn;
	napi_status status = napi_create_function( env, "exports", NAPI_AUTO_LENGTH, addon, NULL, &fcn );
	assert( status == napi_ok );
	return fcn;
}

NAPI_MODULE( NODE_GYP_MODULE_NAME, init )
