/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:14:54 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/16 01:53:34 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest( void )
{
    reqLineEnd = 0;
    bodyEnd = 0;
    bodySize = 0;
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

std::string HTTPRequest::rtrim(const std::string &str)
{
    size_t end = str.find_last_not_of(" \n\t\f\v");
    return (end == std::string::npos ? str : str.substr(0, end + 1));
}

std::string HTTPRequest::ltrim(const std::string &str)
{
    size_t start = str.find_first_not_of(" \n\t\f\v");
    return (start == std::string::npos ? str : str.substr(start));
}

std::string HTTPRequest::trim(const std::string &str)
{
    return (ltrim(rtrim(str)));
}

void HTTPRequest::parsing(sock_t fd)
{
    if ((reqLineEnd = httpRequest.find_first_of("\r\n")) != std::string::npos)
    {
        request = httpRequest.substr(0, reqLineEnd+2);
        method = request.substr(0, request.find(" "));
        request.erase(0, method.size()+1);
        path = request.substr(0, request.find(" "));
        request.erase(0, path.size()+1);
        version = request.substr(0, request.find("\r\n"));
        httpRequest.erase(0, method.size()+path.size()+version.size()+4);
    }
    if ((reqLineEnd = httpRequest.find("\r\n\r\n")) != std::string::npos)
    {
        headers = httpRequest.substr(0, reqLineEnd);
        std::cout << "**********" << std::endl;
        std::cout << headers << std::endl;
        std::cout << "**********" << std::endl;

    }
}