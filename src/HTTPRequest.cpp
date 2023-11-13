/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:14:54 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/12 21:40:34 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest( void )
{	
}

HTTPRequest::~HTTPRequest()
{
}


std::string const &HTTPRequest::requestMethod( void ) const
{
    return (method);
}

std::string const &HTTPRequest::requestPath( void ) const
{
    return (path);
}

std::string const &HTTPRequest::requestVersion( void ) const
{
    return (version);
}

int HTTPRequest::parse( void )
{
    std::cout << method << std::endl;
    return (0);
}