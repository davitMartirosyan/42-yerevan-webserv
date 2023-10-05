/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 22:30:29 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/05 22:48:30 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest( void )
{
    request_buffer = new char[150000];
    content_length = 0;
}

HTTPRequest::~HTTPRequest()
{
    delete request_buffer;
}

std::string const &HTTPRequest::getMethod( void )
{
    return (method);
}

std::string const &HTTPRequest::getPath( void )
{
    return (path);
}

std::string const &HTTPRequest::getVersion( void )
{
    return (version);
}