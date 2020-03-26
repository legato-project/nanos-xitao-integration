/**********************************************************************************************/
/*  This program is free software; you can redistribute it and/or modify                      */
/*  it under the terms of the GNU General Public License as published by                      */
/*  the Free Software Foundation; either version 2 of the License, or                         */
/*  (at your option) any later version.                                                       */
/*                                                                                            */
/*  This program is distributed in the hope that it will be useful,                           */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of                            */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                             */
/*  GNU General Public License for more details.                                              */
/*                                                                                            */
/*  You should have received a copy of the GNU General Public License                         */
/*  along with this program; if not, write to the Free Software                               */
/*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA            */
/**********************************************************************************************/

#include "nanos6_helpers.h"


/* Signal the condition variable */
void condition_variable_callback(void *untyped_arg)
{
	condition_variable_t *cond_var = (condition_variable_t *) untyped_arg;

	pthread_mutex_lock(&cond_var->_mutex);
	cond_var->_signaled = 1;
	pthread_cond_signal(&cond_var->_cond);
	pthread_mutex_unlock(&cond_var->_mutex);
}


/* Wait for the condition variable to be signaled */
void wait_condition_variable(condition_variable_t *cond_var)
{
	pthread_mutex_lock(&cond_var->_mutex);
	while (cond_var->_signaled == 0) {
		pthread_cond_wait(&cond_var->_cond, &cond_var->_mutex);
	}
	pthread_mutex_unlock(&cond_var->_mutex);
}

