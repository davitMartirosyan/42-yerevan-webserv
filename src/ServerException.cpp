/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerException.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 00:05:29 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/06 00:52:39 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerException.hpp"

ServerException::ServerException(const char *msg) : message(msg)
{
}
ServerException::~ServerException() throw()
{
}

const char *ServerException::what( void ) const throw()
{
    perror(message.c_str());
    return (NULL);
}